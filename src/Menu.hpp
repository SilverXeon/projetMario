//
// Created by pierre on 21/05/16.
// Classe affichant le menu retournant le fichier du niveau
//

#ifndef PROJETMARIO_MENU_HPP
#define PROJETMARIO_MENU_HPP

#include <unistd.h>

#define MAX_ITEMS 4

class Menu {
private:
    sf::RenderWindow& _window;
    int selectedItemIndex = 0;
    sf::Font font;
    sf::Text menu[MAX_ITEMS];

    sf::Sprite _spriteFond;
    sf::Texture _textureFond;
public:
    Menu(sf::RenderWindow& window): _window(window){
        if(!font.loadFromFile("file/font/arial.ttf"))
        {
            //handle error
        }

        menu[0].setFont(font);
        menu[0].setColor(sf::Color::Red);
        menu[0].setCharacterSize(40);
        menu[0].setString("Level 1");
        menu[0].setPosition(sf::Vector2f(window.getSize().x/3.5, window.getSize().y/(MAX_ITEMS + 1)*1));

        menu[1].setFont(font);
        menu[1].setColor(sf::Color::White);
        menu[1].setCharacterSize(40);
        menu[1].setString("Level 2");
        menu[1].setPosition(sf::Vector2f(window.getSize().x/3.5, window.getSize().y/(MAX_ITEMS + 1)*2));

        menu[2].setFont(font);
        menu[2].setColor(sf::Color::White);
        menu[2].setCharacterSize(40);
        menu[2].setString("Credit");
        menu[2].setPosition(sf::Vector2f(window.getSize().x/3.5, window.getSize().y/(MAX_ITEMS + 1)*3));

        menu[3].setFont(font);
        menu[3].setColor(sf::Color::White);
        menu[3].setCharacterSize(40);
        menu[3].setString("Exit");
        menu[3].setPosition(sf::Vector2f(window.getSize().x/3.5, window.getSize().y/(MAX_ITEMS + 1)*4));

        // Sert à initialiser le texte, lui donner une couleur, une taille, un texte qui apparaitra et une position

        _textureFond.loadFromFile("file/texture/Menu.png");
        _spriteFond.setTexture(_textureFond);
        _spriteFond.setPosition(-490,-120);
        // Initialise et inclue un fond qui est télécharger a partir du fichier file/texture, et lui donne une position
    }

    void moveDown()
    {
        if(selectedItemIndex+1  < MAX_ITEMS)
        {

            menu[selectedItemIndex].setColor(sf::Color::White);
            menu[selectedItemIndex].setCharacterSize(40);
            selectedItemIndex ++;
            menu[selectedItemIndex].setColor(sf::Color::Red);
            menu[selectedItemIndex].setCharacterSize(45);

            // Permet de changer l'item en modifiant sa taille et sa couleur quand on descend
        }
    }

    void moveUp()
    {
        if(selectedItemIndex -1 >= 0)
        {
            menu[selectedItemIndex].setColor(sf::Color::White);
            menu[selectedItemIndex].setCharacterSize(40);
            selectedItemIndex --;
            menu[selectedItemIndex].setColor(sf::Color::Red);
            menu[selectedItemIndex].setCharacterSize(45);

            // Permet de changer l'item en modifiant sa taille et sa couleur quand on monte
        }
    }


    string run() {
        bool inactif = true;
        while (_window.isOpen()) {
            sf::Event event;
            _window.waitEvent(event);

            if(inactif && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))){
                inactif = false;
                moveUp();

                // Fait le changement d'item vers le haut avec la fléche du haut ou la touche Z en appelant moveUp()
            }


            else if(inactif && (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)|| sf::Keyboard::isKeyPressed(sf::Keyboard::S))) {
                inactif = false;
                moveDown();

                // Fait le changement d'item vers le bas avec la fléche du bas ou la touche s en appelant moveDown()
            }

            else if(inactif && (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::E))) {
                inactif = false;

                // si touche entré ou touche E enfoncé
                switch (getPressedItem()) {
                    case 0 :
                        return "file/level/niveau1.txt";
                    //niveau 1 se charge


                    case 1 :
                        return "file/level/niveau2.txt";
                    // niveau 2 se charge


                    case 2 :
                        cout << "\nCreated by Lefebvre Jérémy, Marie Louis, Merlin Anthony, Sacre Pierre \n"
                                "Copyright © years 2015/2016" << endl;
                        break;

                    case 3 :
                        _window.close();
                        break;

                    default: break;
                }
            }else{
                inactif = true;
            }

            if(event.type == sf::Event::Closed)
                _window.close();

            draw();
        }
        return "";
    }

    int getPressedItem()
    {
        return selectedItemIndex;
    }

    void draw(){
        _window.clear();
        _window.draw(_spriteFond); // dessine le fond
        for(int i = 0; i < MAX_ITEMS; i++)
        {
            _window.draw(menu[i]); // dessine les textes
        }
        _window.display();
    }
};


#endif //PROJETMARIO_MENU_HPP
