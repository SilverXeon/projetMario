//
// Created by Pierre on 30/05/2016.
//

#ifndef PROJETMARIO_MONSTRE_HPP
#define PROJETMARIO_MONSTRE_HPP

class Monstre : public Personnage {
private:
    sf::Texture* monstre = new sf::Texture;
    sf::Texture* monstre1 = new sf::Texture;
    sf::Texture* mort = new sf::Texture;


public:

    Monstre() : Personnage(){
        chargerTexture();
        _sprite.setPosition(100, 100);
        _position = _sprite.getPosition();
    }

    Monstre(sf::Texture* texture, int spawn) : Personnage(texture) {
        chargerTexture();
        enVie = true;
        if(spawn%2 == 0)
            _sprite.setPosition(100, 100);
        else
            _sprite.setPosition(500, 100);

        _position = _sprite.getPosition();
        _sprite.setTexture(*_texture);
    }



    void chargerTexture(){
        _texture->loadFromFile("file/texture/monstre.png");
        monstre->loadFromFile("file/texture/monstre.png");
        monstre1->loadFromFile("file/texture/monstre1.png");
        mort->loadFromFile("file/texture/monstreMort.png");
        _sprite.setTexture(*_texture);
    }

    void setTexture(){
        if(enVie){
            cycleAnimation = (cycleAnimation+1)%150;
            switch(cycleAnimation/75){
                case 0:
                    _sprite.setTexture(*monstre);
                    break;
                case 1:
                    _sprite.setTexture(*monstre1);
                    break;
                default: break;
            }
        }
        else{
            _sprite.setTexture(*mort);
        }
    }

    void init(){
        Personnage::init();
        _state = Event::RIGHT;
    }

    void handleEvent(const sf::Vector2f posMario, Niveau& niveau) {
        if (dir == 1){
            _state = Event::RIGHT;
        }

        else
            _state = Event::LEFT;

        int aux = (int)_position.y - (int)posMario.y;

        if (aux <10 && aux >-10){
            if (_position.x > posMario.x) {
                dir = -1;
                _state = Event::LEFT;
            }
            else if (_position.x < posMario.x) {
                dir = 1;
                _state = Event::RIGHT;
            }
        }

        else{

            if (_position.y > posMario.y && onEchelle(niveau) /*&& (int)_position.x+1 == (int)posMario.x*/) {
                // ici on enverra les pos du monstre dans un Vector2f.
                // si les coordonnees sont les mêmes au prochain handleEvent, on en déduira que
                // c'est une echelle qui va vers le haut, et on n'activera pas l'event DOWN
                // ---> utilite de samePos
                // -> vecteur _posAnterieure a creer dans Personnage.hpp
                _state = Event::UP;
                _lanceSaut = true;
            }

            else if (_position.y < posMario.y && onEchelle(niveau)) {
                //cout << "descend" << endl;
                // ici on enverra les pos du monstre dans un Vector2f.
                // si les coordonnees sont les mêmes au prochain handleEvent, on en déduira que
                // c'est une echelle qui va vers le haut, et on n'activera pas l'event DOWN
                // ---> utilite de samePos
                if(!collisionY(niveau))
                    _state = Event::DOWN;
            }


            else if (_state == Event::LEFT){ //mur a gauche
                dir = -1;
                if (Personnage::collisionX(niveau,dir)){
                    dir = 1;
                }
            }

            else if (_state == Event::RIGHT){ //mur à droite
                dir = 1;
                if (Personnage::collisionX(niveau,dir)){
                    dir = -1;
                }
            }

            else if (_state == Event::NONE){
            }

        }






        // ici, on renverra la pos de Mario dans _posAnterieure
    }

    void update(Niveau &niveau, sf::Time &tau, vector<Monstre>& vMonstre){
        Personnage::update(niveau, tau, 6);


        int cptColl = 0;
        for(int i = 0;i<vMonstre.size();i++) {
            if(collisionX(vMonstre[i].getPosition())){
                cptColl++;
            }
        }
        if(cptColl>1){
            //si collision avec un monstre inversion de la vitesse
            _vitesse.x = -_vitesse.x;
        }

        Personnage::update(niveau, tau, 10);

        _position.x += _vitesse.x * (_acceleration * (10 * tau.asSeconds()));
        _position.y += _vitesse.y; // si pas sur bloc
        _gravite *= 1.002f; // on augmente la gravite

        _sprite.setPosition(_position);
        if(collisionY(niveau)){
            _sprite.setPosition(_sprite.getPosition().x, 40*getCaseY());
        }

        setTexture();
    }

    bool collisionX(sf::Vector2f pos) {
        //verifie la collision avec les autres monstres
        return ((getCaseX()-2 == (int)(pos.x/40) ||getCaseX()-1 == (int)(pos.x/40) || getCaseX() == (int)(pos.x/40) || getCaseX() + 1 == (int)(pos.x/40)) && getCaseY() == (int)(pos.y/40));
    }

    void decharger(){
        delete monstre;
        delete monstre1;
        delete mort;
    }

};


#endif //PROJETMARIO_MONSTRE_HPP

