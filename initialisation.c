#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>

#include "declaration.h"
#include "actions.h"
#include "affichage.h"
#include "initialisation.h"
#include "joueurAction.h"

void saisieNbJoueurs(S_jeu *plato)
{
    Positionner_Curseur(80,8);
    printf("Veuillez rentrer le nombre de joueurs entre 3 et 7 : ");
    scanf("%d", &plato->nbJoueur);
}

void IniCompteur(S_jeu *plato)//initialisation des compteurs eau et nourriture en fonction du nombre de joueurs
{
    switch(plato->nbJoueur)
    {
    case 3 :
        plato->compteurEau=6,plato->compteurNourriture=5;
        break;
    case 4 :
        plato->compteurEau=8,plato->compteurNourriture=7;
        break;
    case 5 :
        plato->compteurEau=10,plato->compteurNourriture=8;
        break;
    case 6 :
        plato->compteurEau=12,plato->compteurNourriture=10;
        break;
    case 7 :
        plato->compteurEau=14,plato->compteurNourriture=12;
        break;
    default :
        printf("Erreur compteur");
    }
}

void iniTab(S_jeu *plato)
{
    plato->carteEpave[0]=5; //Bouteille d’eau (1ration d’eau)
    plato->carteEpave[1]=5; // Sandwich (1 ration de food)
    plato->carteEpave[2]=3; // Sardine (3 rations nourriture)
    plato->carteEpave[3]=3; //Noix de coco (3 ration d’eau)
    plato->carteEpave[4]=2; //Planche de bois(un place de plus sur le radeau à la fin si il y a plus de place)
    plato->carteEpave[5]=2; //Eau croupie (1 ration d’eau mais rend malade)
    plato->carteEpave[6]=2; //Poisson pourri (ration de food mais rend malade
    plato->carteEpave[7]=2; //Slip usagé (sert à rien)
    plato->carteEpave[8]=2; //Clé de voiture (sert à rien)
    plato->carteEpave[9]=2; //Ticket loto (sert à rien)
    plato->carteEpave[10]=1; //Revolver (tue 1 personne usage unique)
    plato->carteEpave[11]=3;//Anti-venin (annule la morsure)
    plato->carteEpave[12]=1;//Gourde permet de récupérer x2 eau
    plato->carteEpave[13]=1;//Gourdin permet de donner 2 voix lors du vote
    plato->carteEpave[14]=1;//Hache permet de récolter 2 bois d'office sans risques si joueur choisi l'action recolerBois

    plato->carteMeteo[0]=0; //le nombre correspond aux nombres de gouttes et donc le nombre d'eau que l'on peut récupérer
    plato->carteMeteo[1]=0;
    plato->carteMeteo[2]=0;
    plato->carteMeteo[3]=1;
    plato->carteMeteo[4]=1;
    plato->carteMeteo[5]=1;
    plato->carteMeteo[6]=2;
    plato->carteMeteo[7]=2;
    plato->carteMeteo[8]=2;
    plato->carteMeteo[9]=3;
    plato->carteMeteo[10]=3;
    plato->carteMeteo[11]=4;
}

void melangeCarteMeteo(S_jeu *plato)//mélange spécifique puisqu'il ne faut pas que la carte ourgan qui vaut 4 ne soit avant la 6ème place
{
    int i, j, temp;
    srand(time(NULL));

    for (i = 11; i >= 1; i--)
    {
        j = rand()%(i+1);
        temp = plato->carteMeteo[j];
        plato->carteMeteo[j] = plato->carteMeteo[i];
        plato->carteMeteo[i] = temp;
    }


    for (i = 0; i < 6; i++)//vérification que l'ouragan n'est pas avant la 6ème place
    {
        if (plato->carteMeteo[i] == 4)
        {
            for (j = 6; j < 12; j++)
            {
                if (plato->carteMeteo[j] != 4)
                {
                    temp = plato->carteMeteo[i];
                    plato->carteMeteo[i] = plato->carteMeteo[j];
                    plato->carteMeteo[j] = temp;
                }
            }
        }
    }
}


void MiseEnPlace(S_jeu *plato)//mise à zéro des compteurs nécéssaires
{
    saisieNbJoueurs(plato);
    IniCompteur(plato);
    iniTab(plato);
    melangeCarteMeteo(plato);


    plato->MeteoActu=plato->carteMeteo[0];
    plato->compteurRadeau=0;
    plato->placeRadeau=0;
    plato->nbTours=0;
    plato->joueurRestants=plato->nbJoueur;

}

void nomEtCartes(S_jeu *plato,S_player tab[]) //rentre le nom des joueurs et leur donnent leurs cartes pour débuter
{
    int i,k;

     for(i=0; i<plato->nbJoueur; i++)
     {
         tab[i].mort=0;
         tab[i].malade=0;
         tab[i].nbCartesPossedees=0;
         tab[i].TourMalade=0;
     }
    for(i=0; i<plato->nbJoueur; i++)
    {
        for(k=0;k<MAX;k++)
        {
            tab[i].carteEpavesPossedees[k]=-1;
        }
    }

    for(i=0; i<plato->nbJoueur; i++)
    {
        Positionner_Curseur(80,10+i);
        printf("Rentrez le nom du joueur %d de moins de 20 caractères : ",i+1);
        scanf("%s",tab[i].nom);
    }
    for(i=0; i<plato->nbJoueur; i++)
    {
        piocherCarteEpavesDebut(plato,&tab[i]);
        piocherCarteEpavesDebut(plato,&tab[i]);
        piocherCarteEpavesDebut(plato,&tab[i]);
    }
    for(i=0;i<9;i++)
    {
        color(0,0);
        Positionner_Curseur(0,i);
        printf("                                                                                            ");
    }
    color(15,0);

}

