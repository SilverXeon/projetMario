//
// Created by Pierre on 30/05/2016.
//

#ifndef PROJETMARIO_MARIO_HPP
#define PROJETMARIO_MARIO_HPP

#include "Monstre.hpp"
#include <assert.h>


class Mario : public Personnage {
private:
    sf::Texture* texDroit = new sf::Texture;
    sf::Texture* texDroit1 = new sf::Texture;
    sf::Texture* texDroit2 = new sf::Texture;
    sf::Texture* texGauche = new sf::Texture;
    sf::Texture* texGauche1 = new sf::Texture;
    sf::Texture* texGauche2 = new sf::Texture;
    sf::Texture* texSautDroit = new sf::Texture;
    sf::Texture* texSautGauche = new sf::Texture;
    sf::Texture* mort = new sf::Texture;

    sf::SoundBuffer* _soundPotion;
    sf::SoundBuffer* _killMonstre;
    sf::SoundBuffer* _soundBuffSaut;

    sf::Sound* _soundSaut;
    sf::Sound* _soundPot;
    sf::Sound* _soundKill;




public:
    Mario() : Personnage(){
        chargerTexture();

        _position = sf::Vector2f(100, 610);
        _sprite.setPosition(_position);

        _soundPotion = new sf::SoundBuffer;
        _killMonstre = new sf::SoundBuffer;
        _soundBuffSaut = new sf::SoundBuffer;

        _soundPotion->loadFromFile("file/sound/potion.wav");
        _killMonstre->loadFromFile("file/sound/killMonstre.wav");
        _soundBuffSaut->loadFromFile("file/sound/saut.wav");

        _soundSaut = new sf::Sound;
        _soundPot = new sf::Sound;
        _soundKill = new sf::Sound;

        _soundSaut->setBuffer(*_soundBuffSaut);
        _soundPot->setBuffer(*_soundPotion);
        _soundKill->setBuffer(*_killMonstre);

    }



    void init(){
        Personnage::init();
        _position = sf::Vector2f(100, 620);
        _sprite.setPosition(_position);
    }

    void chargerTexture(){
        assert(texDroit->loadFromFile("file/texture/MarioDroit.png"));
        assert(texDroit1->loadFromFile("file/texture/MarioDroit1.png"));
        assert(texDroit2->loadFromFile("file/texture/MarioDroit2.png"));
        assert(texGauche->loadFromFile("file/texture/MarioGauche.png"));
        assert(texGauche1->loadFromFile("file/texture/MarioGauche1.png"));
        assert(texGauche2->loadFromFile("file/texture/MarioGauche2.png"));
        assert(texSautDroit->loadFromFile("file/texture/MarioSautDroit.png"));
        assert(texSautGauche->loadFromFile("file/texture/MarioSautGauche.png"));
        assert(mort->loadFromFile("file/texture/MarioMort.png"));
        _sprite.setTexture(*texDroit);

    }

    void setTexture(){
        if(enVie) {
            if (_saut) {
                if (dir > 0)
                    _sprite.setTexture(*texSautDroit);
                else
                    _sprite.setTexture(*texSautGauche);
            }
            else {
                cycleAnimation = (cycleAnimation + 1) % 225;
                if (dir != 0) {
                    switch (cycleAnimation / 75) {
                        case 0:
                            if (dir == 1)
                                _sprite.setTexture(*texDroit);
                            else
                                _sprite.setTexture(*texGauche);
                            break;
                        case 1:
                            if (dir == 1)
                                _sprite.setTexture(*texDroit1);
                            else
                                _sprite.setTexture(*texGauche1);
                            break;
                        case 2:
                            if (dir == 1)
                                _sprite.setTexture(*texDroit2);
                            else
                                _sprite.setTexture(*texGauche2);
                            break;
                        default:
                            if (dir == 1)
                                _sprite.setTexture(*texDroit);
                            else
                                _sprite.setTexture(*texGauche);
                            break;
                    }
                }
            }
        }
        else{
            _sprite.setTexture(*mort);
        }
    }

    void handleEvent(const sf::Event& evt, Niveau& niveau){

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
            _lanceSaut = true;

            _soundSaut->play();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            dir = -1;
            _state=Event::LEFT;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            dir = 1;
            _state=Event::RIGHT;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            _state = Event::DOWN;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
            switchEchelle();
        }
        else{
            dir = 0;
        }
    }

    void update(Niveau &niveau, sf::Time &tau, vector<Monstre>& vMonstre, int& nbVie){
        Personnage::update(niveau, tau, 26);
        _position.x += _vitesse.x * (_acceleration * (10 * tau.asSeconds()));
        _position.y += _vitesse.y;
        _gravite *= 1.002f;

        _sprite.setPosition(_position);

        if (collisionY(niveau)) {
            _sprite.setPosition(_sprite.getPosition().x, 40 * (getCaseY()));
        }
        collisionChampi(niveau, nbVie);
        checkMort(niveau, vMonstre);
        setTexture();
    }

    void collisionChampi(Niveau& niveau, int& nbVie){
        //Verifie si il y a une potion à la position de mario, si oui la prendre, incrementer les vie et detruire le bloc de la potion
        if(niveau.getTypeBloc(getCaseX(), getCaseY()) == TypeBloc::POTION){
            nbVie++;
            _soundPot->play();
            niveau.detruire(getCaseX(), getCaseY());
        }
        else if(niveau.getTypeBloc(getCaseX()+1, getCaseY()) == TypeBloc::POTION){
            _soundPot->play();
            nbVie++;
            niveau.detruire(getCaseX()+1, getCaseY());
        }
    }

    void checkMort(Niveau& niveau, vector<Monstre>& vMonstre){
        //Si mario est en vie regardez les collisions avec les monstres autour de lui, si au dessus ou en dessous tuer le monstre, si a coté tuer mario
        for(int i = 0;i<vMonstre.size();i++) {
            if(enVie) {
                if(niveau.getTypeBloc(getCaseX(), getCaseY()) == TypeBloc::CUBE || niveau.getTypeBloc(getCaseX()+1, getCaseY()) == TypeBloc::CUBE) {
                    if (vMonstre[i].getEnVie() &&
                        (getCaseY() - 1 == vMonstre[i].getCaseY() &&
                        (getCaseX() == vMonstre[i].getCaseX() || getCaseX() + 1 == vMonstre[i].getCaseX()))) {
                        _soundKill->play();
                        vMonstre[i].mourrir();
                    }
                }
                else if  (vMonstre[i].getEnVie() &&
                          (getCaseY() + 1 == vMonstre[i].getCaseY() &&
                           (getCaseX()-1 == vMonstre[i].getCaseX() ||  getCaseX() == vMonstre[i].getCaseX()|| getCaseX() + 1 == vMonstre[i].getCaseX()))){
                    _soundKill->play();
                    vMonstre[i].mourrir();
                }
                else if ((getCaseX() == vMonstre[i].getCaseX()) &&
                         (getCaseY() == vMonstre[i].getCaseY()) && vMonstre[i].getEnVie()) {
                    mourrir();
                }
            }
        }
    }

    void decharger(){
        Personnage::decharger();
        delete texDroit;
        delete texDroit1;
        delete texDroit2;
        delete texGauche;
        delete texGauche1;
        delete texGauche2;
        delete texSautDroit;
        delete texSautGauche;
        delete mort;

        delete _soundPotion;
        delete _killMonstre;
        delete _soundBuffSaut;

        delete _soundSaut;
        delete _soundPot;
        delete _soundKill;
    }
};


#endif //PROJETMARIO_MARIO_HPP
