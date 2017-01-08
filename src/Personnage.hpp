//
// Created by pierre on 21/05/16.
//

#ifndef PROJETMARIO_PERSONNAGE_HPP
#define PROJETMARIO_PERSONNAGE_HPP


enum class Event
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Personnage {
protected:
	sf::Texture *_texture;
	sf::Sprite _sprite;

	Event _state;
	sf::Vector2f _position, _vitesse;
	float _acceleration, _gravite;
	bool _saut, _lanceSaut;

	int dir; //0 rien, -1 gauche et 1 droite
	bool enVie, surEchelle, enJeu;
	int cycleAnimation = 0;
public:
	//Louis et Jeremy
	Personnage() {
		enVie = true;
		enJeu = true;
		_texture = new sf::Texture();
		_acceleration = 1.0f;
		//_accelerationY = -1.3f;
		_saut = true;
		_gravite = 0.0f;
	}

	Personnage(sf::Texture *texture) {
		enVie = true;
		enJeu = true;
		_texture = texture;
		_acceleration = 1.0f;
		//_accelerationY = -1.3f;
		_saut = false;
		_gravite = 0.0f;
	}

	virtual void init() {
		enVie = true;
		enJeu = true;
		_state = Event::NONE; //etat passif au depart
		_vitesse = sf::Vector2f(0, 0); //vitesse nulle au depart
	}

	virtual void update(Niveau &niveau, sf::Time &tau, float cst) {
		if(enVie) {
			switch (_state) {
				case Event::DOWN:
					if (onEchelle(niveau)) {
						_vitesse = sf::Vector2f(_vitesse.x, 1);
					}
					break;

				case Event::LEFT:
					_vitesse = sf::Vector2f(-cst, _vitesse.y);
					_acceleration = 1.002f;
					break;

				case Event::RIGHT:
					_vitesse = sf::Vector2f(cst, _vitesse.y);
					_acceleration = 1.002f;
					break;

				default: break;
			}
			_state = Event::NONE;

			onEchelle(niveau);
			if (surEchelle && _lanceSaut) {
				_vitesse = sf::Vector2f(0, -1);
			}
			else if (_lanceSaut && !_saut) {
				_saut = true;
				_vitesse.y = -8;
				_lanceSaut = false;

			}


			if (collisionX(niveau, dir)) {
				_vitesse.x = 0;
				if (dir < 0)
					_sprite.setPosition(40 * getCaseX(), _sprite.getPosition().y);
				else
					_sprite.setPosition(40 * (getCaseX() - 1), _sprite.getPosition().y);
			}

			decceleration(niveau);


		}
		else{
			if(_sprite.getPosition().y<800) {
				_vitesse.x = 0;
				_vitesse.y += 0.1;
			}
			else{
				enJeu = false;
			}
		}
	}

	void decceleration(Niveau& niveau) {
		if (_vitesse.x > 0) {
			_vitesse.x -= 2;
		}
		else if (_vitesse.x < 0) {
			_vitesse.x += 2;
		}

		if (!collisionY(niveau) && !onEchelle(niveau)) {
				_vitesse.y += 0.2;
		}
		else if(collisionY(niveau)){
			_vitesse.y = 0;
			_saut = false;
		}



		_lanceSaut = false;
		
	}


	sf::Texture* getTexture(){
		return _texture;
	}


	void mourrir(){
		enVie = false;
		_vitesse.y = -4;
	}

	bool onEchelle(Niveau& niveau){
		//Verifie si le personnage se trouve sur une echelle
		surEchelle = (niveau.getTypeBloc(getCaseX(), getCaseY()) == TypeBloc::ECHELLE || niveau.getTypeBloc(getCaseX()+1, getCaseY()) == TypeBloc::ECHELLE);
		return surEchelle;
	}

	void switchEchelle(){
		surEchelle = !surEchelle;
	}

	int getCaseX(){ //retourne la case correspondant au niveau
		if(_sprite.getPosition().x<0)
			return 0;
		return (int)(_sprite.getPosition().x/40)+1;
	}

	int getCaseY() {
		return (int) (_sprite.getPosition().y/40);

	}

	bool getEnVie() const {
		return enVie;
	}

	bool getEnJeu() const {
		return enJeu;
	}

	void draw(sf::RenderTarget& renderer){
		renderer.draw(_sprite);
	}

	bool collisionX(Niveau& niveau,int dir){
		//Regarde s'il y a des collision avec le niveau sur l'axe X
		if(dir>0) {
			if (niveau.getTypeBloc(getCaseX() + 1, getCaseY()) == TypeBloc::CUBE || niveau.getTypeBloc(getCaseX() + 1, getCaseY()) == TypeBloc::TUYAU)
				if(niveau.getTypeBloc(getCaseX() + 1, getCaseY()+1) == TypeBloc::CUBE || niveau.getTypeBloc(getCaseX() + 1, getCaseY()+1) == TypeBloc::TUYAU)
					return true;
		}
		if(dir<0){
			if(niveau.getTypeBloc(getCaseX(), getCaseY()) == TypeBloc ::CUBE || niveau.getTypeBloc(getCaseX(), getCaseY()) == TypeBloc ::TUYAU)
				if(niveau.getTypeBloc(getCaseX(), getCaseY()+1) == TypeBloc ::CUBE || niveau.getTypeBloc(getCaseX(), getCaseY()) == TypeBloc ::TUYAU)
					return true;
		}

		return false;
	}

	sf::Vector2f getPosition(){
		return _sprite.getPosition();
	}

	bool collisionY(Niveau& niveau){
		//Regarde s'il y a des collisions avec le niveau sur l'axe Y
		if(_vitesse.y>=0) {
				if (niveau.getTypeBloc(getCaseX(), getCaseY() +1) == TypeBloc::CUBE || niveau.getTypeBloc(getCaseX()+1, getCaseY() +1) == TypeBloc::CUBE) {
				_saut = false;
				return true;
			}

			return false;
		}
		else{
			if(niveau.getTypeBloc(getCaseX(), getCaseY()) == TypeBloc::CUBE || niveau.getTypeBloc(getCaseX()+1, getCaseY()) == TypeBloc::CUBE){
				_vitesse.y = 2;
				return true;
			}
			return false;
		}
	}

	virtual void decharger(){
		delete _texture;
	}
};


#endif //PROJETMARIO_PERSONNAGE_HPP
