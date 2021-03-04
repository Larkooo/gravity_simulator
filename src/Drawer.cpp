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
#define TIME_MULTIPLIER 1

static char objectNameBuffer[10];
static float objectMass;
static int objectDiameter;
static float objectColor[3] = {0.f, 0.f, 1.f};

Drawer::Drawer(sf::RenderWindow* renderWindow, std::vector<Object>* objects, std::string fontPath) {
    this->m_rRenderWindow = renderWindow;
    this->m_vObjects = objects;
    this->font.loadFromFile(fontPath);
}

void Drawer::draw(sf::Clock* deltaClock, std::vector<float>* frametimes) {
    {
        ImGui::SFML::Update(*this->m_rRenderWindow, deltaClock->restart());
        /* Object Creator GUI */
        {
            ImGui::Begin("Object Creator");
            ImGui::InputText("Name", objectNameBuffer, IM_ARRAYSIZE(objectNameBuffer));
            ImGui::SliderFloat("Mass", &objectMass, 1.f, 1000.f);
            ImGui::SliderInt("Diameter", &objectDiameter, 1, 50);
            ImGui::ColorPicker3("Color", objectColor);

            if(ImGui::Button("Create object")) {
                Object obj(objectNameBuffer, sf::Vector3f(rand() % this->m_rRenderWindow->getSize().x, rand() % this->m_rRenderWindow->getSize().y, rand() % 100), objectMass, objectDiameter, sf::Color(objectColor[0] * MAX_COLOR, objectColor[1] * MAX_COLOR, objectColor[2] * MAX_COLOR, MAX_COLOR));
                this->m_vObjects->push_back(obj);
            }
            ImGui::End();
        }

        /* Objects Manager GUI */
        {
            ImGui::Begin("Objects Manager");
            // vector to array
            ImGui::PlotLines("Frame Times", frametimes->data(), frametimes->size());
            ImGui::Text("Objects - %d", this->m_vObjects->size());
            ImGui::BeginChild("Scrolling");
            for(size_t i = 0; i < (this->m_vObjects->size()); i++) {
                Object object = this->m_vObjects->at(i);
                if(ImGui::Button(object.getName().c_str())) {
                    this->m_vObjects->erase(this->m_vObjects->begin() + i);
                };
            }
            ImGui::EndChild();
            ImGui::End();
        }
    }
    
    {
        this->m_rRenderWindow->clear();
        for(size_t i = 0; i < this->m_vObjects->size(); i++) {
            Object object = this->m_vObjects->at(i);
            sf::Vector3f objectPos = object.getPosition();
            /* Object */
            {
                /* Calculations */
                {
                    // get sum of forces applied to object
                    float forces = 0;
                    for(size_t n = 0; n < this->m_vObjects->size(); n++) {
                        if(n == i) continue;
                        forces += object.gravitationalForceTo(&this->m_vObjects->at(n));
                    }
                    
                    // acceleration
                    sf::Vector3f acceleration = calculations::acceleration(forces, object.getMass());
                    std::cout << acceleration.x << std::endl;

                    // velocity
                    sf::Vector3f velocity = object.getVelocity() + (acceleration * (float)(deltaClock->getElapsedTime().asSeconds() * TIME_MULTIPLIER));
                    object.setVelocity(velocity);
                    sf::Vector3f newPos = objectPos + (velocity * (float)(deltaClock->getElapsedTime().asSeconds() * TIME_MULTIPLIER));
                    object.setPosition(newPos);
                    objectPos = newPos;
                }

                sf::CircleShape shape(object.getDiameter());
                shape.setFillColor(object.getColor());
                sf::Color outlineColor = object.getColor();
                outlineColor.a /= 2;
                shape.setOutlineColor(outlineColor);
                shape.setOutlineThickness(object.getMass() / 10);
                // z is used by drawing the objects in a specific order
                shape.setPosition(objectPos.x, objectPos.y);
                this->m_rRenderWindow->draw(shape);
            }

            /* Object alias */
            {
                sf::Text name(object.getName(), this->font, 10);
                name.setPosition(objectPos.x, objectPos.y - 10);
                this->m_rRenderWindow->draw(name);
            }
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