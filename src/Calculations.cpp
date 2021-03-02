#include <cmath>
#include "Object.hpp"
#include "Calculations.h"
#include <iostream>
#include "SFML/System/Vector3.hpp"

float calculations::Q_rsqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck? 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

sf::Vector3f calculations::acceleration(sf::Vector3f force, float mass) {
    return sf::Vector3f() * (force / mass);
}

// Compares two objects by their z value 
bool compareObject(Object o1, Object o2) 
{ 
    return (o1.getPosition().z < o2.getPosition().z); 
} 