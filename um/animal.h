#pragma once
#include <iostream>
#include <string>
using namespace std;

// Animal Class
class Animal {
    string name, color, type;

public:
    // Function to take input
    void input()
    {
        name = "Dog";
        color = "White";
    }

    // Function to display the member
    // variables
    void display()
    {
        cout << name << " is of "
            << color << endl;
    }
};
