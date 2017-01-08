//
// Created by pierre on 21/05/16.
// Classe du programme principal
//

#ifndef PROJETMARIO_PROGRAMME_H
#define PROJETMARIO_PROGRAMME_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;


#include "Menu.hpp"
#include "Application.hpp"

class Programme {
private:
    sf::RenderWindow* _window;
public:
    Programme(int resolutionX, int resolutionY){
        _window = new sf::RenderWindow(sf::VideoMode(resolutionX, resolutionY), "Super Mario Bros");
        _window->setFramerateLimit(90);
    };

    void run(){
        Menu m = Menu(*_window);

        string nomFichierNiveau = m.run();


        Application a = Application(*_window);

        a.run(nomFichierNiveau);
    }
};


#endif //PROJETMARIO_PROGRAMME_H
