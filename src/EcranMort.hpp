//
// Created by Pierre on 12/06/2016.
//

#ifndef PROJETMARIO_ECRANMORT_HPP
#define PROJETMARIO_ECRANMORT_HPP



class EcranMort {
private:
    sf::RenderWindow& _window;
    sf::Sprite _sprite;
    sf::Texture _texture;

    sf::Font _font;
    sf::Text _texte;


public:
    EcranMort(int var, sf::RenderWindow& window, bool fin) : _window(window){
        if(!fin) {
            _texture.loadFromFile("file/texture/marioVie.png");
            _sprite.setTexture(_texture);
        }

        _font.loadFromFile("file/font/arial.ttf");
        _texte.setFont(_font);
        _texte.setColor(sf::Color::White);

        _texte.setPosition(300, 400);
        _sprite.setPosition(240 ,400);

        if(!fin) {
            _texte.setString("x " + itos(var));
        }
        else {
            _texte.setString("GAME OVER\n Score : " + itos(var));
            _texte.setPosition(200, 400);
        }
    }

    void run(){
        sf::Event evt;
        evt.type = sf::Event::Resized;
        sf::Clock clock;
        while(clock.getElapsedTime().asSeconds()<=5 && _window.isOpen()){
            usleep(10); //Permet de limiter la charge CPU
            _window.pollEvent(evt);
            if(evt.type == sf::Event::Closed){
                _window.close();
            }
            draw();
        }

    }

    void draw(){
        _window.clear();
        sf::RectangleShape rec = sf::RectangleShape(sf::Vector2f(_window.getSize()));
        rec.setPosition(0,0);
        rec.setFillColor(sf::Color::Black);
        _window.draw(rec);
        _window.draw(_sprite);
        _window.draw(_texte);
        _window.display();
    }

    string itos(int nb){
        ostringstream oss;
        oss << nb;
        return oss.str();
    }
};


#endif //PROJETMARIO_ECRANMORT_HPP
