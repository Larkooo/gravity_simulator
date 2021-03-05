#include <Drawer.hpp>
#include <Object.hpp>
#include <SFML/Graphics.hpp>
#include <string>

#include <SFML/System/Clock.hpp>

#include "IMGUI/imgui.h"
#include "IMGUI_SFML/imgui-SFML.h"

#include <iostream>
#include <vector>

#include "Calculations.h"

#define MAX_COLOR 255
#define TIME_MULTIPLIER 0.0001

static char objectNameBuffer[10];
static float objectMass;
static int objectDiameter;
static float objectColor[3] = {0.f, 0.f, 1.f};

Drawer::Drawer(sf::RenderWindow* renderWindow, std::string fontPath) {
    this->m_rRenderWindow = renderWindow;
    this->font.loadFromFile(fontPath);
}

void Drawer::draw(sf::Clock* pDeltaClock, std::vector<float>* pFrametimes, std::vector<Object>* pObjects) {
    {
        ImGui::SFML::Update(*this->m_rRenderWindow, pDeltaClock->restart());
        /* Object Creator GUI */
        {
            ImGui::Begin("Object Creator");
            ImGui::InputText("Name", objectNameBuffer, IM_ARRAYSIZE(objectNameBuffer));
            ImGui::SliderFloat("Mass", &objectMass, 1.f, 1000.f);
            ImGui::SliderInt("Diameter", &objectDiameter, 1, 50);
            ImGui::ColorPicker3("Color", objectColor);

            if(ImGui::Button("Create object")) {
                Object obj(objectNameBuffer, sf::Vector3f(rand() % this->m_rRenderWindow->getSize().x, rand() % this->m_rRenderWindow->getSize().y, rand() % 100), sf::Vector3f(0,0,0), objectMass, objectDiameter, sf::Color(objectColor[0] * MAX_COLOR, objectColor[1] * MAX_COLOR, objectColor[2] * MAX_COLOR, MAX_COLOR));
                pObjects->push_back(obj);
            }
            ImGui::End();
        }

        /* Objects Manager GUI */
        {
            ImGui::Begin("Objects Manager");
            // vector to array
            ImGui::PlotLines("Frame Times", pFrametimes->data(), pFrametimes->size());
            ImGui::Text("Objects - %d", pObjects->size());
            ImGui::BeginChild("Scrolling");
            for(size_t i = 0; i < (pObjects->size()); i++) {
                Object object = pObjects->at(i);
                if(ImGui::Button(object.getName().c_str())) {
                    pObjects->erase(pObjects->begin() + i);
                };
            }
            ImGui::EndChild();
            ImGui::End();
        }
    }
    
    {
        this->m_rRenderWindow->clear();
        int i = 0;
        for(auto& object : *pObjects) {
            //printf("%i - X : %f Y : %f Z : %f\n", 1, object.m_vPos.x, object.m_vPos.y, object.m_vPos.z);
            /* Object */
            {
                /* Calculations */
                {
                    // get sum of forces applied to object
                    float forces = 0;
                    for(size_t n = 0; n < pObjects->size(); n++) {
                        // ignore if object is itself
                        if(n == i) continue;
                        forces += object.gravitationalForceTo(&pObjects->at(n));
                    }
                    
                    // acceleration
                    sf::Vector3f acceleration = calculations::acceleration(forces, object.getMass());
                    printf("%f", acceleration.x);

                    // velocity
                    object.m_vVelocity += (acceleration * (float)(pDeltaClock->getElapsedTime().asSeconds() * TIME_MULTIPLIER));
                    //object.setVelocity(velocity);
                    object.m_vPos += (object.m_vVelocity * (float)(pDeltaClock->getElapsedTime().asSeconds() * TIME_MULTIPLIER));
                    //object.setPosition(newPos);                    
                }
                sf::CircleShape shape(object.getDiameter());
                shape.setFillColor(object.getColor());
                sf::Color outlineColor = object.getColor();
                outlineColor.a /= 2;
                shape.setOutlineColor(outlineColor);
                shape.setOutlineThickness(object.getMass() / 10);
                // z is used by drawing the objects in a specific order
                shape.setPosition(object.m_vPos.x, object.m_vPos.y);
                this->m_rRenderWindow->draw(shape);
            }

            /* Object alias */
            {
                sf::Text name(object.getName(), this->font, 10);
                name.setPosition(object.m_vPos.x, object.m_vPos.y - 10);
                this->m_rRenderWindow->draw(name);
            }
            i++;
        }
        ImGui::SFML::Render(*this->m_rRenderWindow);
        this->m_rRenderWindow->display();
    }
    
}

sf::Font Drawer::getFont(void) {
    return this->font;
}

void Drawer::setFontFromFile(std::string path) {
    this->font.loadFromFile(path);
}