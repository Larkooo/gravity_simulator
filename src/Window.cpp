#include <Window.hpp>
#include <vector>
#include <Object.hpp>
#include <time.h>
#include <Drawer.hpp>

#define FONT_PATH "./assets/fonts/vcr.ttf"

Window::Window(sf::RenderWindow* renderWindow, std::vector<Object>* objects) {
    this->m_rRenderWindow = renderWindow;
    // array to vector
    this->m_vObjects = objects;
    // setting initts
    this->m_tInitTs = time(NULL);
    // init drawer
    Drawer drawer(renderWindow, objects, FONT_PATH);
    
    size_t frames = 0;
    while (renderWindow->isOpen())
    {
        // fps counter
        time_t time_now = time(NULL);
        if((difftime(time_now, this->getInitTs())) == 1) {
            this->setInitTs(time_now);
            this->setFramerate(frames);
            frames = 0;
            renderWindow->setTitle("Gravity Simulator | FPS : " + std::to_string(this->getFramerate()));
        }
        
        sf::Event event;
        while (renderWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                renderWindow->close();
        }

        drawer.draw();

        frames++;
    }
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