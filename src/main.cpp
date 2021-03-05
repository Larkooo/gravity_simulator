#include "SFML/Graphics.hpp"
#include "Object.hpp"
#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include "Window.hpp"
#include "Drawer.hpp"

#define WINDOW_HEIGHT 1280
#define WINDOW_WIDTH 720

#define TITLE "Gravity Simulator"

int main()
{
    std::vector<Object> objects = {
        Object("lol", sf::Vector3f(500, 500, 1), sf::Vector3f(0,0,0), 200, 1, sf::Color::Blue), 
        Object("yes", sf::Vector3f(300, 200, 50), sf::Vector3f(0,0,0), 50, 1, sf::Color::Red), 
        Object("no", sf::Vector3f(1000, 50, 100), sf::Vector3f(0,0,0), 500, 1, sf::Color::Yellow)
        };


    sf::RenderWindow renderWindow(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), TITLE);

    sf::RenderWindow* pRenderWindow = &renderWindow;
    //pRenderWindow->setView(sf::View(sf::Vector2f(350.f, 300.f), sf::Vector2f(1000.f, 1000.f)));
    Window window(pRenderWindow, &objects);

    return 0;
}