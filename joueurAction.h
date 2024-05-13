#ifndef JOUEURACTION_H_INCLUDED
#define JOUEURACTION_H_INCLUDED

#include "declaration.h"

void pecher(S_jeu *plato);

void recolterEau(S_jeu *plato,S_player *user);

void recolterBois(S_jeu *plato, S_player *user);

void piocherCarteEpaves(S_jeu *plato,S_player *user);
#endif // JOUEURACTION_H_INCLUDED
