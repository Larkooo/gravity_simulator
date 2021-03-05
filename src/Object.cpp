#include "Object.hpp"
#include <string>
#include "SFML/Graphics.hpp"
#include <cmath>
#include "Calculations.h"
#include <iostream>

size_t Object::s_lCount = 0;

Object::Object(std::string name, sf::Vector3f pos, sf::Vector3f velocity, float mass, short diameter, sf::Color color) {
    this->m_sName = name;
    this->m_vPos = pos;
    this->m_vVelocity = velocity;
    this->m_nMass = mass;
    this->m_iDiameter = diameter;
    this->m_eColor = color;

    ++Object::s_lCount;
}

std::string Object::getName() {
    return this->m_sName;
}

sf::Vector3f Object::getPosition() {
    return this->m_vPos;
}

void Object::setPosition(sf::Vector3f newPosition) {
    this->m_vPos = newPosition;
}

sf::Vector3f Object::getVelocity() {
    return this->m_vVelocity;
}

void Object::setVelocity(sf::Vector3f velocity) {
    this->m_vVelocity = velocity;
}

sf::Vector3f Object::getAcceleration() {
    return this->m_vAcceleration;
}

void Object::setAcceleration(sf::Vector3f acceleration) {
    this->m_vAcceleration = acceleration;
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

sf::Vector3f Object::gravitationalForceTo(Object* object) {

        sf::Vector3f distVec = object->getPosition() - this->getPosition();

        float gmm = calculations::GRAVITATIONAL_CONSTANT * this->getMass() * object->getMass();
        float r = std::pow(std::pow(distVec.x,2) + std::pow(distVec.y,2) + std::pow(distVec.z,2), 1.5);
        return sf::Vector3f(gmm * distVec.x / r, gmm * distVec.y / r, gmm * distVec.z / r);

}