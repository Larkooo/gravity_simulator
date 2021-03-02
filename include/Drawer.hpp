#pragma once
#include <Object.hpp>
#include <vector>
#include <string>
#include "SFML/System/Clock.hpp"

class Drawer {
    std::vector<Object>* m_vObjects;
    sf::RenderWindow* m_rRenderWindow;
    sf::Font font;
    public:
        Drawer(sf::RenderWindow*, std::vector<Object>*, std::string);
        Drawer() = default;
        void draw(sf::Clock*);

        sf::Font getFont(void);
        void setFontFromFile(std::string);
};