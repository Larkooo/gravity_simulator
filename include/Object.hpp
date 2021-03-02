#pragma once
#include <stdint.h>
#include "Vector2.hpp"
#include <string>
#include "SFML/Graphics.hpp"

class Object {
    std::string m_sName;
    Vector2 m_vPos;
    float m_fVelocity;
    int m_nMass;
    unsigned short m_iDiameter;
    sf::Color m_eColor;

    public:
        static size_t s_lCount;
        Object(std::string name, Vector2 pos, int mass, short diameter, sf::Color color);

        std::string getName();
        Vector2 getPosition();
        int getMass();
        unsigned short getDiameter();
        sf::Color getColor();


};
