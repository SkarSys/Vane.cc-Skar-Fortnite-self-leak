#pragma once

// C++ program to create header file
// named as Dog.h

// Include the header file "Animal.h"
#include "Animal.h"

// Dog Class
class Dog {
    Animal d;

public:
    // Take input to member variable
    // using function call in another
    // header file
    void dog_input() { d.input(); }

    // Function to display the member
    // variable using function call
    // in another header file
    void dog_display() { d.display(); }
};