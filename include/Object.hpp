#pragma once
#include <stdint.h>
#include <string>
#include "SFML/Graphics.hpp"

class Object {
    std::string m_sName;    
    float m_nMass;
    unsigned short m_iDiameter;
    sf::Color m_eColor;

    public:
        static size_t s_lCount;

        sf::Vector3f m_vPos;
        sf::Vector3f m_vVelocity;
        sf::Vector3f m_vAcceleration;

        Object(std::string name, sf::Vector3f position, sf::Vector3f velocity, float mass, short diameter, sf::Color color);

        std::string getName(void);

        sf::Vector3f getPosition(void);
        void setPosition(sf::Vector3f position);

        sf::Vector3f getVelocity(void);
        void setVelocity(sf::Vector3f velocity);

        sf::Vector3f getAcceleration(void);
        void setAcceleration(sf::Vector3f acceleration);

        int getMass(void);
        unsigned short getDiameter(void);
        sf::Color getColor(void);

        float gravitationalForceTo(Object* object);


};
