#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <Object.hpp>
#include <time.h>

class Window {
    short m_sFramerate;
    std::vector<Object>* m_vObjects;
    sf::RenderWindow* m_rRenderWindow;
    time_t m_tInitTs;

    public: 
        Window(sf::RenderWindow* renderWindow, std::vector<Object>* objects);
        ~Window(void);

        sf::RenderWindow* getRenderWindow(void);

        Object getObject(size_t index);

        int getObjectsSize(void);
        void addObject(Object object);
        void destroyObject(int index);
        void clearObjects(void);

        short getFramerate(void);
        void setFramerate(short framerate); 

        time_t getInitTs(void);
        void setInitTs(time_t ts);
};