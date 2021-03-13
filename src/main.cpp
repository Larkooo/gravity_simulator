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
    std::vector<Object> objects = std::vector<Object>();
    //for(size_t i = 0; i < 100; i++) {
    //    sf::Vector3f pos(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT, rand() % 1000);
    //    //                                          velocity mass        diameter     color
    //    Object object("", pos, sf::Vector3f(0,0,0), rand() % 100000, rand() % 50, sf::Color::Blue);
    //    objects.push_back(object);
    //}


    sf::RenderWindow renderWindow(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), TITLE);

    sf::RenderWindow* pRenderWindow = &renderWindow;
    //pRenderWindow->setView(sf::View(sf::Vector2f(350.f, 300.f), sf::Vector2f(1000.f, 1000.f)));
    Window window(pRenderWindow, &objects);

    return 0;
}