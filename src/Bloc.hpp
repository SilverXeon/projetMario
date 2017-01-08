//
// Created by pierre on 21/05/16.
//

#ifndef PROJETMARIO_BLOC_HPP
#define PROJETMARIO_BLOC_HPP

enum TypeBloc{
    VIDE,
    CUBE,
    POTION,
    ECHELLE,
    TUYAU
};


class Bloc {
private:
    TypeBloc _type;

    sf::Texture _texture;
    sf::Sprite _sprite;
public:
    Bloc(){
    }

    void dessine(string image, int etat)
    {
        _texture.loadFromFile(image);
        _sprite.setTexture(_texture);
        setTypeBloc(etat);
    }

    void setTypeBloc(int etat){
        switch(etat)
        {
            case 0:
                _type = TypeBloc::VIDE;
                break;
            case 1:
                _type = TypeBloc::CUBE;
                break;
            case 2:
                _type = TypeBloc::ECHELLE;
                break;
            case 3:
                _type = TypeBloc::POTION;
            default:
                break;
        }
    }

    void setPos(int i, int j)
    {
        sf::Vector2f _position = sf::Vector2f(i,j);
        _sprite.setPosition(_position);
    }

    TypeBloc getType(){
        return _type;
    }

    void draw(sf::RenderTarget& _window)
    {
        _window.draw(_sprite);
    }
};


#endif //PROJETMARIO_BLOC_HPP
