#include "Object.hpp"
#include <string>
#include "Vector2.hpp"
#include "SFML/Graphics.hpp"

size_t Object::s_lCount = 0;

Object::Object(std::string name, Vector2 pos, int mass, short diameter, sf::Color color) {
    this->m_sName = name;
    this->m_vPos = pos;
    this->m_nMass = mass;
    this->m_iDiameter = diameter;
    this->m_eColor = color;

    ++Object::s_lCount;
}

std::string Object::getName() {
    return this->m_sName;
}

Vector2 Object::getPosition() {
    return this->m_vPos;
}

int Object::getMass() {
    return this->m_nMass;
}

sf::Color Object::getColor() {
    return this->m_eColor;
} 

unsigned short Object::getDiameter() {
    return this->m_iDiameter;
}