#include <Drawer.hpp>
#include <Object.hpp>
#include <Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <string>

Drawer::Drawer(sf::RenderWindow* renderWindow, std::vector<Object>* objects, std::string fontPath) {
    this->m_rRenderWindow = renderWindow;
    this->m_vObjects = objects;
    this->font.loadFromFile(fontPath);
}

void Drawer::draw(void) {
    this->m_rRenderWindow->clear();
    for(size_t i = 0; i < this->m_vObjects->size(); i++) {
        Object object = this->m_vObjects->at(i);
        Vector2 objectVec = object.getPosition();
        // drawing the object
        sf::CircleShape shape(object.getDiameter());
        shape.setFillColor(object.getColor());
        shape.setPosition(objectVec.getX(), objectVec.getY());
        this->m_rRenderWindow->draw(shape);
        // drawing name of the object
        sf::Text name(object.getName(), this->font, 10);
        name.setPosition(objectVec.getX(), objectVec.getY() - 10);
        this->m_rRenderWindow->draw(name);
    }
    this->m_rRenderWindow->display();
}

sf::Font Drawer::getFont(void) {
    return this->font;
}

void Drawer::setFontFromFile(std::string path) {
    this->font.loadFromFile(path);
}