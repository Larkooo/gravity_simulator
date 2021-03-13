#include "Window.hpp"
#include <vector>
#include "Object.hpp"
#include <time.h>
#include "Drawer.hpp"
#include <iostream>
#include "discord_rpc.h"
#include <cstring>
#include "SFML/System/Clock.hpp"

#include "IMGUI/imgui.h"
#include "IMGUI_SFML/imgui-SFML.h"

#define FONT_PATH "./assets/fonts/vcr.ttf"
#define APP_ID "787791190690496542"

Window::Window(sf::RenderWindow* renderWindow, std::vector<Object>* objects) {
    this->m_rRenderWindow = renderWindow;
    // array to vector
    this->m_vObjects = objects;
    // setting initts
    this->m_tInitTs = time(NULL);
    // init drawer
    this->m_dDrawer = Drawer(renderWindow, FONT_PATH);

    // imgui
    ImGui::SFML::Init(*renderWindow);

    // init discord
    DiscordEventHandlers dEventHandlers;
    memset(&dEventHandlers, 0, sizeof(dEventHandlers));
    Discord_Initialize(APP_ID, &dEventHandlers, 1, NULL);

    DiscordRichPresence dRpc;
    memset(&dRpc, 0, sizeof(dRpc));
    {   
        dRpc.startTimestamp = this->getInitTs();
        dRpc.state = "Gravity SIM";
        char buffer[128];
        sprintf(buffer, "FPS : %f | Objects : %o", 0, this->getObjectsSize());
        dRpc.details = buffer;
        dRpc.largeImageKey = "sardge";
        dRpc.instance = 0;
        Discord_UpdatePresence(&dRpc);
    }

    sf::Clock deltaClock;
    size_t frames = 0;
    while (renderWindow->isOpen())
    {
        
        
        // sort objects by z axis  
        std::sort(objects->begin(), objects->end(), [](Object o1, Object o2) {
            return (o1.getPosition().z < o2.getPosition().z);
        });

        // fps counter
        time_t time_now = time(NULL);
        if((difftime(time_now, this->getInitTs())) == 1) {
            this->setInitTs(time_now);
            this->setFramerate(frames);
            this->m_vFrametimes.push_back(frames);
            frames = 0;
            renderWindow->setTitle("Gravity Simulator | FPS : " + std::to_string(this->getFramerate()) + " | Objects : " + std::to_string(this->getObjectsSize()));
            
            {   // update discord rpc
                dRpc.state = "Gravity SIM";
                char buffer[128];
                sprintf(buffer, "FPS : %f | Objects : %o", this->getFramerate(), this->getObjectsSize());
                dRpc.details = buffer;
                dRpc.largeImageKey = "sardge";
                dRpc.instance = 0;
                Discord_UpdatePresence(&dRpc); 
            }
        }
        

        sf::Event event;
        while (renderWindow->pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                renderWindow->close();
            }
        }

        //int willDieCount = 0;
        //for(auto& obj : *objects) {
        //    if(obj.m_bDeath) willDieCount++;
        //}
        //if(willDieCount > 1) std::printf("%i\n", willDieCount);

        this->m_dDrawer.draw(&deltaClock, &m_vFrametimes, m_vObjects);

        frames++;
    }
    ImGui::SFML::Shutdown();
}

Window::~Window(void) {
    this->m_rRenderWindow->close();
}

sf::RenderWindow* Window::getRenderWindow(void) {
    return this->m_rRenderWindow;
}

Object Window::getObject(size_t index) {
    return this->m_vObjects->at(index);
}

int Window::getObjectsSize() {
    return this->m_vObjects->size();
}

void Window::addObject(Object object) {
    this->m_vObjects->push_back(object);
}

void Window::destroyObject(int index) {
    this->m_vObjects->erase(m_vObjects->begin() + index);
}

void Window::clearObjects() {
    this->m_vObjects->clear();
}

short Window::getFramerate(void) {
    return this->m_sFramerate;
}

void Window::setFramerate(short framerate) {
    this->m_sFramerate = framerate;
}

time_t Window::getInitTs(void) {
    return this->m_tInitTs;
}

void Window::setInitTs(time_t ts) {
    this->m_tInitTs = ts;
}