#pragma once
#include <Object.hpp>
#include <vector>
#include <string>

class Drawer {
    std::vector<Object>* m_vObjects;
    sf::RenderWindow* m_rRenderWindow;
    sf::Font font;
    public:
        Drawer(sf::RenderWindow*, std::vector<Object>*, std::string);
        void draw(void);

        sf::Font getFont(void);
        void setFontFromFile(std::string);
};