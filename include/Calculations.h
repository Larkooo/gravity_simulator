#include "Object.hpp"
#include <cmath>

namespace calculations {
    const double GRAVITATIONAL_CONSTANT = 6.67 * std::pow(10, 11);

    float Q_rsqrt( float );

    float gravitationalForce(Object* object1, Object* object2); 

    sf::Vector3f acceleration(float force, float mass);

    bool compareObject(Object, Object);
}
