#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

#include "declaration.h"

void Positionner_Curseur(int colonne, int ligne);
void color (int couleurDuTexte, int couleurDuFond);
void plein_ecran();

void menu_action(S_jeu *plato,S_player *user);

void afficherRegle();
void avertissement();

void pionFood(S_jeu *plato,int colonne,int ligne);
void pionEau(S_jeu *plato,int colonne,int ligne);
void compteurRadeau(S_jeu *plato,int colonne,int ligne);
void pionCarteMeteo(S_jeu *plato,int colonne,int ligne);

void afficherCartePlayer(S_player user);

void teteMort();




#endif // AFFICHAGE_H_INCLUDED
