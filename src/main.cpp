#include <SFML/Graphics.hpp>
#include <Object.hpp>
#include <vector>
#include <Vector2.hpp>
#include <string>
#include <time.h>
#include <iostream>
#include <Window.hpp>
#include <Drawer.hpp>

int main()
{
    std::vector<Object> objects = {Object("lol", Vector2(500, 500), 500, 100, sf::Color::Blue), Object("yes", Vector2(300, 200), 50, 10, sf::Color::Blue), Object("no", Vector2(1000, 50), 500, 500, sf::Color::Blue)};


    sf::RenderWindow renderWindow(sf::VideoMode(1280, 720), "Gravity Simulator");

    sf::RenderWindow* pRenderWindow = &renderWindow;
    Window window(pRenderWindow, &objects);

    return 0;
}