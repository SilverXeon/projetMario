//
// Created by pierre on 21/05/16.
// Classe representant tous le Mario
//

#ifndef PROJETMARIO_APPLICATION_HPP
#define PROJETMARIO_APPLICATION_HPP

#include <unistd.h>
#include <SFML/Audio.hpp>
#include "Niveau.hpp"
#include "Personnage.hpp"
#include "Mario.hpp"
#include "Monstre.hpp"
#include "HUD.hpp"
#include "EcranMort.hpp"

class Application {
private:
    sf::RenderWindow& _window;
    Niveau _niveau;
    Mario _mario;
    vector<Monstre> vMonstre;
    HUD _hud;

    sf::Music* _music;
    sf::SoundBuffer* _soundMort;
    sf::Sound* _sound;

    int nbVie = 3;

public:
    Application(sf::RenderWindow& window) : _window(window){
        _music = new sf::Music;
        _music->openFromFile("file/sound/music.ogg");
        _music->setLoop(true);
        _soundMort = new sf::SoundBuffer;
        _soundMort->loadFromFile("file/sound/mort.wav");
        _sound = new sf::Sound;
        _sound->setBuffer(*_soundMort);
    }

    void run(string nomNiveau){
        //Chargement des textures et du niveau
        _niveau.chargerNiveau(nomNiveau);

        for(int i = 0 ;i<_niveau.getNbMonstre();i++)
            vMonstre.push_back(Monstre());



        //loop
        sf::Event evt;
        evt.type = sf::Event::Resized;
        sf::Clock clock;
        bool affiche = true;
        while(nbVie>=0) {
            _music->play();
            _mario.init();

            vMonstre = vector<Monstre>();
            for(int i = 0 ;i<_niveau.getNbMonstre();i++)
                vMonstre.push_back(Monstre());

            for(int i = 0;i<_niveau.getNbMonstre();i++) {
                vMonstre[i] = Monstre(vMonstre[0].getTexture(), i);
            }

            while (_mario.getEnJeu() && _window.isOpen()) {
                sf::Time tau = clock.restart();
                _window.pollEvent(evt);

                update(evt, tau);


                affiche = !affiche;
                if(affiche)
                    draw();

                if(!_mario.getEnVie()){
                    _music->stop();
                    _sound->play();
                }

            }
            nbVie--;
            _hud.decrementeVie();

            if(nbVie<0) {
                EcranMort em = EcranMort(_hud.getScore(), _window, true);
                em.run();
                usleep(2000);
            }
            else {
                EcranMort em = EcranMort(nbVie, _window, false);
                em.run();
            }
            sf::Time tau = clock.restart();
            update(evt, tau);
        }
        decharger();
    }


    void update(sf::Event& evt, sf::Time& tau){

        if(evt.type == sf::Event::Closed)
            _window.close();
        _mario.handleEvent(evt, _niveau);
        for(int i = 0;i<vMonstre.size();i++)
            vMonstre[i].handleEvent(_mario.getPosition(), _niveau);

        _mario.update(_niveau, tau, vMonstre, nbVie);

        for(int i = 0;i<vMonstre.size();i++) {
            vMonstre[i].update(_niveau, tau, vMonstre);
            if(!vMonstre[i].getEnJeu()) {
                vMonstre[i] = Monstre(vMonstre[0].getTexture(), i);
                _hud.incrementeScore();
            }
        }

        _hud.update(nbVie);
    }

    void draw(){
        _window.clear();
        _niveau.draw(_window);
        _mario.draw(_window);
        for(int i = 0;i<vMonstre.size();i++) {
            vMonstre[i].draw(_window);
        }
        _hud.draw(_window);
        _window.display();
    }

    void decharger(){
        delete _music;
        delete _soundMort;
        delete _sound;

        _mario.decharger();
        for(int i = 0;i<vMonstre.size();i++)
            vMonstre[i].decharger();

    }
};


#endif //PROJETMARIO_APPLICATION_HPP
