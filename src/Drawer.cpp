#include <Drawer.hpp>
#include <Object.hpp>
#include <Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <string>

#include <SFML/System/Clock.hpp>

#include "IMGUI/imgui.h"
#include "IMGUI_SFML/imgui-SFML.h"

static char objectNameBuffer[10];
static float objectMass;
static int objectDiameter;
static float objectColor;

Drawer::Drawer(sf::RenderWindow* renderWindow, std::vector<Object>* objects, std::string fontPath) {
    this->m_rRenderWindow = renderWindow;
    this->m_vObjects = objects;
    this->font.loadFromFile(fontPath);
}

void Drawer::draw(sf::Clock* deltaClock) {
    {
        ImGui::SFML::Update(*this->m_rRenderWindow, deltaClock->restart());

        ImGui::Begin("Object creator");
        ImGui::InputText("Name", objectNameBuffer, IM_ARRAYSIZE(objectNameBuffer));
        ImGui::SliderFloat("Mass", &objectMass, 0.f, 1000.f);
        ImGui::SliderInt("Diameter", &objectDiameter, 0, 50);
        ImGui::ColorPicker3("Color", &objectColor);

        if(ImGui::Button("Create object")) {
            
        }
        ImGui::End();
    }

    this->m_rRenderWindow->clear();
    for(size_t i = 0; i < this->m_vObjects->size(); i++) {
        Object object = this->m_vObjects->at(i);
        Vector2 objectVec = object.getPosition();
        // drawing the object
        sf::CircleShape shape(object.getDiameter());
        shape.setFillColor(object.getColor());
        shape.setPosition(objectVec.getX(), objectVec.getY());
        this->m_rRenderWindow->draw(shape);
        // drawing name of the object
        sf::Text name(object.getName(), this->font, 10);
        name.setPosition(objectVec.getX(), objectVec.getY() - 10);
        this->m_rRenderWindow->draw(name);
    }
    ImGui::SFML::Render(*this->m_rRenderWindow);
    this->m_rRenderWindow->display();
}

sf::Font Drawer::getFont(void) {
    return this->font;
}

void Drawer::setFontFromFile(std::string path) {
    this->font.loadFromFile(path);
}