#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

#include "declaration.h"

void piocherCarteEpavesDebut(S_jeu *plato, S_player *user);


void piocherCarteMeteo(S_jeu *plato);



void vote(S_jeu *plato,S_player tab[]);

void utilisationCarte(S_jeu *plato,S_player *user,S_player tab[]);

void utiliserAntiVenin(S_player *user);

#endif // ACTIONS_H_INCLUDED
