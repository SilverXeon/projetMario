//
// Created by pierre.sacre on 25/05/16.
//

#ifndef PROJETMARIO_HUD_HPP
#define PROJETMARIO_HUD_HPP

#include <cstdlib>
#include <sstream>

class HUD {
private:
    int score;
    int nbVie;
    sf::Font _font;
    sf::Text _texte;

    sf::Texture _texture;
    sf::Sprite _sprite;
public:
    HUD(){
        score = 0;
        nbVie = 3;
        _font.loadFromFile("file/font/arial.ttf");
        _texte.setFont(_font);
        _texte.setColor(sf::Color::White);

        _texture.loadFromFile("file/texture/marioVie.png");
        _sprite.setTexture(_texture);
        _sprite.setPosition(10, 10);
        _texte.setPosition(45, 10);
    }

    ~HUD(){}

    void incrementeScore(){
        score += 100;
    }

    int getScore(){
        return score;
    }

    void decrementeVie(){
        if(nbVie>0)
            nbVie--;
    }

    void update(int nbVie){
        string s = "x ";
        s += + (char)(nbVie+48);
        s += "\nScore :";
        s += " "+itos(score);
        _texte.setString(s);
    }

    string itos(int nb){
        ostringstream oss;
        oss << nb;
        return oss.str();
    }

    void draw(sf::RenderTarget& renderer){
        renderer.draw(_sprite);
        renderer.draw(_texte);
    }
};


#endif //PROJETMARIO_HUD_HPP
