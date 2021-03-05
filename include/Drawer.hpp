#pragma once
#include <Object.hpp>
#include <vector>
#include <string>
#include "SFML/System/Clock.hpp"

class Drawer {
    sf::RenderWindow* m_rRenderWindow;
    sf::Font font;
    public:
        Drawer(sf::RenderWindow*, std::string);
        Drawer() = default;
        void draw(sf::Clock*, std::vector<float>*, std::vector<Object>*);

        sf::Font getFont(void);
        void setFontFromFile(std::string);
};