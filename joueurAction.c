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


void pecher(S_jeu *plato)//la pêche est purement aléatoire
{
    int i;
    srand(time(NULL));
    i=rand()%6;
    if(i<=3)//correspond aux 3 boules n'ayant qu'un poisson
    {
        Positionner_Curseur(45,12);
        printf("Vous avez récolté 1 poisson");
        plato->compteurNourriture=plato->compteurNourriture+1;
    }
    if(i==3 || i==4)//correspond aux 2 boules ayant 2 poissons
    {
        Positionner_Curseur(45,12);
        printf("Vous avez récolté 2 poissons");
        plato->compteurNourriture=plato->compteurNourriture+2;
    }
    if(i==5) //correspond à la boule ayant un poisson dessus
    {
        Positionner_Curseur(45,12);
        printf("Vous avez récolté 3 poissons");
        plato->compteurNourriture=plato->compteurNourriture+3;
    }
}

void recolterEau(S_jeu *plato,S_player *user)//recolte l'eau en fonction du nombre indiqué sur la carte météo retournée
{
    int i,presenceGourde=0; //presenceGourde permet de savoir si le joueur a une gourde

    for(i=0; i<27; i++)     //on vérifie si un joueur possède une gourde
    {
        if(user->carteEpavesPossedees[i]==12)
        {
            plato->compteurEau=plato->MeteoActu+plato->compteurEau; //on incrémente une fois le compteur d'eau si user a une gourde
            presenceGourde=1;
        }
    }
    Positionner_Curseur(45,12);
    plato->compteurEau=plato->MeteoActu+plato->compteurEau; //on ajoute une fois la valeur de la carte météo de façon normale

    if(presenceGourde==1)
    {
        printf("Vous avez recolte %d ration d'eau",2*plato->MeteoActu);
    }
    else
    {
        printf("Vous avez recolte %d ration d'eau",plato->MeteoActu);
    }

}

void recolterBois(S_jeu *plato, S_player *user)
{
    /*Ici le joueur, en fonction du nombre de bois qu'il a annoncé, tire d'un coup ce nombre de boules si la boule noire se trouve parmi les boules qu'il a tirer alors il est malade
      le ssprog recolterBois utilise le sous-champs boules[6] du S_jeu en effet après avoir initialisé le tableau avec que des 0 sauf dans une case où il y a un seul 1
      on mélange le tableau boules puis le joueur choisi le nombre N de bois qu'il souhaite récupérer. On va ensuite parcourir le tableau mélangé et vérifier que la valeur
      1 ne se trouve pas dans les N-ièmes premières cases comme ceci on garde les mêmes probabilités que de tout tirer d'un coup*/

    int i,nbBois,j,temp;
    Positionner_Curseur(45,10);
    printf("Si vous souhaitez récupérer du bois en plus, rentrez un nombre entre 1 et 5 sinon tapez 0 : ");
    scanf("%d",&nbBois);
    for(i=0; i<27; i++)
    {
        if(user->carteEpavesPossedees[i]==14)
        {
            plato->compteurRadeau++;//si il a une hache alors il récupère deux fois plus
        }
    }
    plato->compteurRadeau++;//si l'on choisi cette action on récupère d'office 1 bout de bois

    for(i=0; i<5; i++)
    {
        plato->boules[i]=0;
    }
    plato->boules[5]=1;

    for (i=0; i<6; i++) //on mélange le tableau boules
    {
        srand(time(NULL));
        j=rand()%(6-i)+i;
        temp=plato->boules[i];
        plato->boules[i]=plato->boules[j];
        plato->boules[j]=temp;
    }

    if(nbBois==1)
    {
        if(plato->boules[0]==1)//le cas avec plusieurs bouts de bois est plus parlant pour expliquer
        {
            Positionner_Curseur(45,12);
            printf("Vous vous êtes fait mordre par un serpent, vous êtes donc malade");
            user->malade=1;
        }
        else
        {
            Positionner_Curseur(45,12);
            printf("Vous avez récupéré 1 bout de bois sans vous faire mordre ");
            plato->compteurRadeau=plato->compteurRadeau+1;
        }
    }
    if(nbBois==2)
    {
        if(plato->boules[0]==1 || plato->boules[1]==1)//on vérifie que la valeur 1 n'est ni dans la première case ni dans la deuxième case, autrement dit que le joueur n'ai pas tiré la boule noire
        {
            Positionner_Curseur(45,12);
            printf("Vous vous êtes fait mordre par un serpent, vous êtes donc malade");
            user->malade=1;
        }
        else
        {
            Positionner_Curseur(45,12);
            printf("Vous avez récupéré 2 bouts de bois sans vous faire mordre ");
            plato->compteurRadeau=plato->compteurRadeau+2;
        }
    }
    if(nbBois==3)
    {
        if(plato->boules[0]==1 || plato->boules[1]==1 || plato->boules[2]==1)//même chose ensuite
        {
            Positionner_Curseur(45,12);
            printf("Vous vous êtes fait mordre par un serpent, vous êtes donc malade");
            user->malade=1;
        }
        else
        {
            Positionner_Curseur(45,12);
            printf("Vous avez récupéré 3 bouts de bois sans vous faire mordre ");
            plato->compteurRadeau=plato->compteurRadeau+3;
        }
    }
    if(nbBois==4)
    {
        if(plato->boules[0]==1 || plato->boules[1]==1 || plato->boules[2]==1 || plato->boules[3]==1)
        {
            Positionner_Curseur(45,12);
            printf("Vous vous êtes fait mordre par un serpent, vous êtes donc malade");
            user->malade=1;
        }
        else
        {
            Positionner_Curseur(45,12);
            printf("Vous avez récupéré 4 bouts de bois sans vous faire mordre ");
            plato->compteurRadeau=plato->compteurRadeau+4;
        }
    }
    if(nbBois==5)
    {
        if(plato->boules[0]==1 || plato->boules[1]==1 || plato->boules[2]==1 || plato->boules[3]==1 || plato->boules[4]==1)
        {
            Positionner_Curseur(45,12);
            printf("Vous vous êtes fait mordre par un serpent, vous êtes donc malade");
            user->malade=1;
        }
        else
        {
            Positionner_Curseur(45,12);
            printf("Vous avez récupéré 5 bouts de bois sans vous faire mordre ");
            plato->compteurRadeau=plato->compteurRadeau+5;
        }
    }


    int reste; //on regarde si le nombre de bouts de bois rammassés + ceux déjà possédés dépasse 6 si oui alors une place sur le radeau est créée
    if(plato->compteurRadeau>=6)
    {
        reste=plato->compteurRadeau-6;
        plato->placeRadeau++;
        plato->compteurRadeau=reste;
    }
}

void piocherCarteEpaves(S_jeu *plato,S_player *user)///même Programme que piocherCarteEpavesDebut mais cette fois-ci il affiche le type de carte piochée
{
    int sommeTest=0;
    int k,i;
    for(k=0; k<15; k++) //15 est le nombre de cartes
    {
        sommeTest=sommeTest+plato->carteEpave[k];
    }
    if(sommeTest != 0)
    {
        srand(time(NULL));
        do
        {
            i=rand()%15;

        }
        while(plato->carteEpave[i]==0);

        user->nbCartesPossedees++;
        user->carteEpavesPossedees[user->nbCartesPossedees-1]=i;
        plato->carteEpave[i]--;
    }
    else
    {
        Positionner_Curseur(45,12);
        printf("la pioche est vide ");
        printf("                   ");
    }

    switch(i)/// ce switch case est utilisé plusieurs fois dans ce programme
    {
    case 0 :
        Positionner_Curseur(45,12);
        printf("Vous avez pioché 1 bouteille d'eau ce qui correspond à 1 ration d'eau. ");

        color(15,0);
        break;
    case 1 :
        Positionner_Curseur(45,12);
        printf("Vous avez pioché 1 sandwich ce qui correspond à 1 rations de nourriture. ");

        color(15,0);
        break;
    case 2:
        Positionner_Curseur(45,12);
        printf("Vous avez pioché 1 boîte de sardines ce qui correspond à 3 ration de nourriture. ");

        color(15,0);
        break;
    case 3:
        Positionner_Curseur(45,12);
        printf("Vous avez pioché 1 noix de coco ce qui correspond à 3 rations d'eau. ");

        color(15,0);
        break;
    case 4:
        Positionner_Curseur(45,12);
        printf("Vous avez pioché 1 planche de bois ce qui correspond à 1 place de radeau ");

        color(15,0);
        break;
    case 5:
        Positionner_Curseur(45,12);
        printf("Vous avez pioché 1 bouteille d'eau courpie ce qui correspond à 1 ration d'eau mais si vous l'utilisez vous êtes malade. ");

        color(15,0);
        break;
    case 6:
        Positionner_Curseur(45,12);
        printf("Vous avez pioché 1 poisson pourri ce qui correspond à 1 ration de nourriture mais si vous l'utilisez vous êtes malade. ");

        color(15,0);
        break;
    case 7:
        Positionner_Curseur(45,12);
        printf("Vous avez pioché 1 slip usagé, cela ne sert à rien mais vous êtes couvert. ");

        color(15,0);
        break;
    case 8:
        Positionner_Curseur(45,12);
        printf("Vous avez pioché 1 clé de voitures cela ne sert à rien mais elles sont jolies. ");

        color(15,0);
        break;
    case 9:
        Positionner_Curseur(45,12);
        printf("Vous avez pioché 1 ticket de loto cela ne sert à rien mais il est peut-être gagnant. ");

        color(15,0);
        break;
    case 10:
        Positionner_Curseur(45,12);
        printf("Vous avez pioché un revolver, vous pouvez tuer UNE SEULE personne, faites en bon usage. ");

        color(15,0);
        break;
    case 11:
        Positionner_Curseur(45,12);
        printf("Vous avez pioché 1 anti-venin, si vous êtes malade vous pouvez vous soigner. ");

        color(15,0);
        break;
    case 12:
        Positionner_Curseur(45,12);
        printf("Vous avez pioché une gourde, désormais vous récupérerez 2 fois plus d'eau. ");

        color(15,0);
        break;
    case 13:
        Positionner_Curseur(45,12);
        printf("Vous avez pioché un gourdin, désormais lors des votes votre vote compte pour deux voix. ");

        color(15,0);
        break;
    case 14:
        Positionner_Curseur(45,12);
        printf("Vous avez pioché une hache, désormais lorsque vous récolterez du bois vous aurez 2 bouts de bois d'office au lieu de 1. ");

        color(15,0);
        break;


    }
}
