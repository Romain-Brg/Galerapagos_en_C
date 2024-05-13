#ifndef DECLARATION_H_INCLUDED
#define DECLARATION_H_INCLUDED

#define MAX 30


typedef struct player S_player;
struct player
{
	char nom[20];
	int carteEpavesPossedees[MAX];//contient les types de cartes que chaque joueur possède
	int nbCartesPossedees;
	int malade;//oui ou non
	int TourMalade; //permet de savoir pendant combien de tour le joueur a été malade
	int mort;
};


struct jeu
{
	int nbJoueur;
	int carteEpave[15]; // 15 cartes différentes ce tableau contient leur nombre dans la pioche
	int boules[6]; //3 boules 1 poisson | 2 boule 2 poissons | 1 boule 3 poissons et noire
	int compteurNourriture;
	int compteurEau;
	int compteurRadeau;
	int placeRadeau;
	int carteMeteo[12]; //numero= nombre goutte dessus 4=ouragon
	int joueurRestants;
	int nbTours;
	int MeteoActu;//carte météo actuellement retournée
};
typedef struct jeu S_jeu;

struct joueurVote //struct propre au vote permet de manipuler un type struct plus petit dans le sous-programme vote
{
    char nom[100];
    int nbVotes;
    int gourdin;
};
typedef struct joueurVote S_joueurVote;

#endif // DECLARATION_H_INCLUDED
