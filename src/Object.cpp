#include "Object.hpp"
#include <string>
#include "SFML/Graphics.hpp"
#include <cmath>
#include "Calculations.h"
#include <iostream>

size_t Object::s_lCount = 0;

Object::Object(std::string name, sf::Vector3f pos, sf::Vector3f velocity, float mass, uint16_t radius, sf::Color color) {
    this->m_sName = name;
    this->m_vPos = pos;
    this->m_vVelocity = velocity;
    this->m_nMass = mass;
    this->m_nRadius = radius;
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

float Object::getMass() {
    return this->m_nMass;
}

sf::Color Object::getColor() {
    return this->m_eColor;
} 

uint16_t Object::getRadius() {
    return this->m_nRadius;
}

uint32_t Object::getDiameter() {
    return this->m_nRadius * 2;
}

sf::Vector3f Object::gravitationalForceTo(Object* object, float* scale) {
    sf::Vector3f distVec = (object->getPosition() - this->getPosition())/* * *scale*/;
    // tweak to prevent objects from propulsing themselves 
    // order object's death when it collides with a bigger object
    {
        float directDistance = std::sqrt((distVec.x * distVec.x) + (distVec.y * distVec.y) + (distVec.z * distVec.z));
        // biggest object
        bool biggerThan = this->getMass() >= object->getMass();
        //std::printf("%f\n", directDistance);
        // ugly fix to prevent objects from deleting themselves, only for now
        if(biggerThan && (directDistance <= ((this->getRadius() + object->getRadius()) / *scale))) {
            //std::printf("%f\n", directDistance);
            std::printf("this - X : %f Y : %f Z : %f    object - X : %f Y : %f Z : %f\n", this->m_vPos.x, this->m_vPos.y, this->m_vPos.z, object->m_vPos.x, object->m_vPos.y, object->m_vPos.z);
            //biggerThan ? object->m_bDeath = true : this->m_bDeath = true;
            sf::Vector3f newVelocity = ((this->m_vVelocity * this->m_nMass) + (object->m_vVelocity * object->m_nMass)) / (this->m_nMass + object->m_nMass);
            //if(biggerThan) {
                this->m_nMass += object->m_nMass;
                this->m_vVelocity = newVelocity;
                object->m_bDeath = true;
            /*} else {
                this->m_bDeath = true;
                object->m_nMass += object->m_nMass;
                object->m_vVelocity = newVelocity;
            }*/
            //this->m_vAcceleration = sf::Vector3f(0,0,0);
            return sf::Vector3f(0,0,0);
        }
    }
    float gmm = calculations::GRAVITATIONAL_CONSTANT * this->getMass() * object->getMass();
    float r = std::pow(std::pow(distVec.x,2) + std::pow(distVec.y,2) + std::pow(distVec.z,2), 1.5);
    return sf::Vector3f(gmm * distVec.x / r, gmm * distVec.y / r, gmm * distVec.z / r);
}

void Object::destroyObject() {
    this->~Object();
}