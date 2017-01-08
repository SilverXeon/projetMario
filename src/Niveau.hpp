//
// Created by pierre on 21/05/16.
//

#ifndef PROJETMARIO_NIVEAU_HPP
#define PROJETMARIO_NIVEAU_HPP

#include "Bloc.hpp"
#include <fstream>


class Niveau {
private:
    int map[18][20] = {};

    Bloc _tabBloc[18][20];
    sf::Sprite _spriteFond;
    sf::Texture _textureFond;


    int nbMonstre;
public:
    Niveau(){
        nbMonstre = 2;


    }

    void chargerFichier(string nomFichier){
        ifstream fichier(nomFichier.c_str(), ios::in);

        string stringTmp;
        char charTmp;
        int intTmp;
        int i = 0;
        int j = 0;
        if(fichier){
            while(fichier.get(charTmp)){
                if(charTmp >= 48 && charTmp <= 58){
                    stringTmp += charTmp;
                }
                else{
                    if(stringTmp != "") {
                        map[i][j] = atoi(stringTmp.c_str());
                        stringTmp = "";
                        i++;
                        if (i == 18) {
                            j++;
                            i = 0;
                        }
                    }

                }
            }
        }
    }

    void detruire(int i, int j){
        _tabBloc[i][j] = Bloc();
        _tabBloc[i][j].setTypeBloc(0);
    }

    void chargerNiveau(string nomNiveau){
        chargerFichier(nomNiveau);
        _textureFond.loadFromFile("file/texture/fond.png");
        _spriteFond.setTexture(_textureFond);
        _spriteFond.setPosition(0,0);

        for(int j = 0; j<20; j++)
            for(int i = 0; i<18; i++)
            {
                _tabBloc[i][j].setPos((i-1)*40, j*40);
                switch(map[i][j])
                {
                    case 0:
                        _tabBloc[i][j].setTypeBloc(0);
                        break;
                    case 1:
                        _tabBloc[i][j].dessine("file/texture/floor.png", 1);
                        break;
                    case 2:
                        _tabBloc[i][j].dessine("file/texture/platform.png", 1);
                        break;
                    case 3:
                        _tabBloc[i][j].dessine("file/texture/downLeftTube.png", 1);
                        break;
                    case 4:
                        _tabBloc[i][j].dessine("file/texture/upLeftTube.png", 1);
                        break;
                    case 5:
                        _tabBloc[i][j].dessine("file/texture/downHorizontalTube.png", 1);
                        break;
                    case 6:
                        _tabBloc[i][j].dessine("file/texture/upHorizontalTube.png", 1);
                        break;
                    case 7:
                        _tabBloc[i][j].dessine("file/texture/downRightTube.png", 1);
                        break;
                    case 8:
                        _tabBloc[i][j].dessine("file/texture/upRightTube.png", 1);
                        break;
                    case 9:
                        _tabBloc[i][j].dessine("file/texture/Ladder.png", 2);
                        break;
                    case 10:
                        _tabBloc[i][j].dessine("file/texture/champi.png", 3);
                    default:
                        break;
                }
            }
    }

    TypeBloc getTypeBloc(int i, int j){
        return _tabBloc[i][j].getType();
    }

    int getNbMonstre(){
        return nbMonstre;
    }

    void draw(sf::RenderTarget& window){
        window.draw(_spriteFond);
        for(int i = 0;i<18;i++)
            for(int j = 0;j<20;j++)
                _tabBloc[i][j].draw(window);

    }
};


#endif //PROJETMARIO_NIVEAU_HPP
