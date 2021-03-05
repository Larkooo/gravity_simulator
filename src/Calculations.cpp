#include <cmath>
#include "Object.hpp"
#include "Calculations.h"
#include <iostream>
#include "SFML/System/Vector3.hpp"

// function took from quake 3, fast inverse square root // modified to work on modern c++
float calculations::Q_rsqrt( float number )
{
    static_assert(std::numeric_limits<float>::is_iec559, 
                  "fast inverse square root requires IEEE-comliant 'float'");
    static_assert(sizeof(float)==sizeof(std::uint32_t), 
                  "fast inverse square root requires 'float' to be 32-bit");
    float x2 = number * 0.5F, y = number;
    std::uint32_t i;
    memcpy(&i, &y, sizeof(float));
    i  = 0x5f3759df - ( i >> 1 );
    memcpy(&y, &i, sizeof(float));
    return y * ( 1.5F - ( x2 * y * y ) );
}

sf::Vector3f calculations::acceleration(sf::Vector3f force, float mass) {
	return force / mass;
}

// Compares two objects by their z value 
bool compareObject(Object o1, Object o2) 
{ 
    return (o1.getPosition().z < o2.getPosition().z); 
} 