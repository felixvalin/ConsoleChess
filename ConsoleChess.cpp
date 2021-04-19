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
    //Manager.Init();
    bool restartGame = false;

    do {
        if (restartGame)
        {
            Manager.Reinit();
        }
        else
        {
            Manager.Init();
        }
    } while (restartGame = Manager.StartGame());
    
    return 0;
}