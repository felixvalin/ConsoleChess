// ConsoleChess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "DEBUG.h"
#include <iostream>
#include <chrono>

#include "GameManager.h"

int main()
{
    if (DEBUG)
        std::cout << "First text entry!" << std::endl;

    GameManager Manager;
    Manager.Init();

    if (Manager.StartGame())
    {
        return 0;
    }

    return -1;
}