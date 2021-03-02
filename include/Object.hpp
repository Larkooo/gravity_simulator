#pragma once
#include <stdint.h>
#include <string>
#include "SFML/Graphics.hpp"

class Object {
    std::string m_sName;
    sf::Vector3f m_vPos; 
    sf::Vector3f m_vVelocity;
    float m_nMass;
    unsigned short m_iDiameter;
    sf::Color m_eColor;

    public:
        static size_t s_lCount;
        Object(std::string name, sf::Vector3f position, float mass, short diameter, sf::Color color);

        std::string getName(void);

        sf::Vector3f getPosition(void);
        void setPosition(sf::Vector3f position);

        sf::Vector3f getVelocity(void);
        void setVelocity(sf::Vector3f velocity);

        int getMass(void);
        unsigned short getDiameter(void);
        sf::Color getColor(void);

        sf::Vector3f gravitationalForceTo(Object* object);


};
