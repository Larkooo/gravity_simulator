#pragma once
#include <stdint.h>
#include <string>
#include "SFML/Graphics.hpp"

class Object {
    std::string m_sName;    
    float m_nMass;
    uint16_t m_nRadius;
    sf::Color m_eColor;

    public:
        static size_t s_lCount;

        sf::Vector3f m_vPos;
        sf::Vector3f m_vVelocity;
        sf::Vector3f m_vAcceleration;
        bool m_bDeath = false;

        Object(std::string name, sf::Vector3f position, sf::Vector3f velocity, float mass, uint16_t radius, sf::Color color);

        std::string getName(void);

        sf::Vector3f getPosition(void);
        void setPosition(sf::Vector3f position);

        sf::Vector3f getVelocity(void);
        void setVelocity(sf::Vector3f velocity);

        sf::Vector3f getAcceleration(void);
        void setAcceleration(sf::Vector3f acceleration);

        float getMass(void);
        uint32_t getDiameter(void);
        uint16_t getRadius(void);
        sf::Color getColor(void);

        sf::Vector3f gravitationalForceTo(Object* object, float* scale);
        void destroyObject();


};