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

void piocherCarteEpavesDebut(S_jeu *plato, S_player *user)
/*ici on a fait le choix de ne pas mélanger les cartes épaves, lorsque le joueur en prends il en prends une au hasard*/
{
    int sommeTest=0;
    int k,i;
    for(k=0; k<12; k++)
    {
        sommeTest=sommeTest+plato->carteEpave[k];       //permet de vérifier qu'il y ai bien au moins une carte dans la pioche
    }
    if(sommeTest != 0)//il ya au moins une carte
    {
        srand(time(NULL));
        do
        {
            i=rand()%15;

        }
        while(plato->carteEpave[i]==0);//permets de reprendre une carte si ce type de acrte n'est plus dans la pioche

        user->nbCartesPossedees++; //user gagne une carte
        user->carteEpavesPossedees[user->nbCartesPossedees-1]=i;//il récupère une carte du type qui l'a pioché
        plato->carteEpave[i]--;//ce type de carte est désincrémenter
    }
    else
    {
        Positionner_Curseur(45,12);
        printf("la pioche est vide ");//cas où sommeTest est resté égale à 0
    }
}



void piocherCarteMeteo(S_jeu *plato)//programme pas nécessairement utile
{
    plato->MeteoActu=plato->carteMeteo[plato->nbTours+1];
}



void vote(S_jeu *plato,S_player tab[])
{
    char voteUser[100];
    int i,k,j=0,l,joueurVivant,nomChoisi,maxVotes=0;

    S_joueurVote tabjoueurVote[plato->joueurRestants];//S_joueurVote est un struct que pour les Votes permet de manipuler un struct plus simple

    for(i=0,joueurVivant=0; i<plato->nbJoueur; i++)
    {
        if(tab[i].mort==0)
        {
            strcpy(tabjoueurVote[joueurVivant].nom,tab[i].nom);
            tabjoueurVote[joueurVivant].nbVotes=0;
            tabjoueurVote[joueurVivant].gourdin=0;

            for(k=0; k<27; k++)
            {
                if(tab[i].carteEpavesPossedees[k]==13)
                {
                    tabjoueurVote[joueurVivant].gourdin=1;
                }
            }
            joueurVivant++;
        }
    }

    for(i=0; i<joueurVivant; i++)
    {
        Positionner_Curseur(30,14);
        printf("\n%s veuillez rentrer le nom EXACT de la personne que vous souhaitez éliminer : ",tabjoueurVote[i].nom);
        scanf("%s",voteUser);
        Positionner_Curseur(30,14);
        printf("                                                                                                                           ");
        for(k=0; k<plato->nbJoueur; k++)
        {
            nomChoisi=strcmp(voteUser,tabjoueurVote[k].nom);//on cherche le nom de la personne pour qui tabjoueurVote[i] a voté contre
            if(nomChoisi==0)
            {
                if(tabjoueurVote[i].gourdin==1)
                {
                    tabjoueurVote[k].nbVotes=tabjoueurVote[k].nbVotes+2;
                }
                else
                {
                    tabjoueurVote[k].nbVotes++;
                }
            }
        }
    }
    for(i=0; i<plato->nbJoueur; i++)
    {
        if(tabjoueurVote[i].nbVotes>maxVotes) //on cherche qui a le plus grand nombre de voix contre
        {
            maxVotes=tabjoueurVote[i].nbVotes;
        }
    }
    for(i=0; i<plato->nbJoueur; i++)
    {
        if(tabjoueurVote[i].nbVotes==maxVotes) //cas où il y a une égalité
        {
            j++;
        }
    }

    srand(time(NULL));
    if(j>1)///on a décidé que comme il n'y avait de preimier joueur ce sont les forces de la natures qui décident qui est éliminé
    {
        S_joueurVote tabElimine[j];
        l=0;
        for(i=0; i<plato->nbJoueur; i++)
        {
            if(tabjoueurVote[i].nbVotes==maxVotes)
            {
                tabElimine[l]=tabjoueurVote[i];
                l++;
            }
        }
        k=rand()%j;
        for(i=0; i<plato->nbJoueur; i++)
        {
            if(strcmp(tabElimine[k].nom,tab[i].nom)==0)
            {
                tab[i].mort=1;
                printf("%s est éliminé(e) par les forces de la nature",tab[i].nom);
            }
        }
    }
    else
    {
        for(i=0; i<plato->nbJoueur; i++)
        {
            if(tabjoueurVote[i].nbVotes==maxVotes)
            {
                for(k=0; k<plato->nbJoueur; k++)
                {
                    if(strcmp(tabjoueurVote[i].nom,tab[k].nom)==0)
                    {
                        tab[k].mort=1;
                        printf("%s est éliminé(e)",tab[i].nom);

                    }
                }
            }

        }
    }
    plato->joueurRestants--;
}

void utilisationCarte(S_jeu *plato,S_player *user,S_player tab[])
{
    int choix[9]; //tableau qui correspond aux cartes utilisables cela permet de stocker la décision de jouer la carte ou non
    int i,k;
    char nomTue[50];//carte
    int nbCarteBase=user->nbCartesPossedees;//on prend le nombre de carte que le joueur a avant d'en jouer
    for(i=0; i<nbCarteBase; i++)
    {
        switch(user->carteEpavesPossedees[i])/*switch case pour toutes les cartes jouables*/ ///on a dans le initialisation.c les valeurs associées à chaque cartes
        {//aussi chaque case décrit une action parmi les cartes jouaubles
        case 0:
            printf("\n\t\tVoulez-vous utilisez une bouteille d'eau ? tapez 1 pour l'utiliser sinon 0. ");
            scanf("%d",&choix[0]);
            if(choix[0]==1)
            {
                user->nbCartesPossedees--;
                user->carteEpavesPossedees[i]=-1;
                plato->compteurEau++;
            }
            break;
        case 1:
            printf("\n\t\tVoulez-vous utilisez un sandwich ? tapez 1 pour l'utiliser sinon 0. ");
            scanf("%d",&choix[1]);
            if(choix[1]==1)
            {
                user->nbCartesPossedees--;
                user->carteEpavesPossedees[i]=-1;
                plato->compteurNourriture++;
            }
            break;
        case 2:
            printf("\n\t\tVoulez-vous utilisez une boîte de sardines ? tapez 1 pour l'utiliser sinon 0. ");
            scanf("%d",&choix[2]);
            if(choix[2]==1)
            {
                user->nbCartesPossedees--;
                user->carteEpavesPossedees[i]=-1;
                plato->compteurNourriture=plato->compteurNourriture+3;
            }
            break;
        case 3:
            printf("\n\t\tVoulez-vous utilisez une noix de coco ? tapez 1 pour l'utiliser sinon 0. ");
            scanf("%d",&choix[3]);
            if(choix[3]==1)
            {
                user->nbCartesPossedees--;
                user->carteEpavesPossedees[i]=-1;
                plato->compteurEau=plato->compteurEau+3;
            }
            break;
        case 4:
            printf("\n\t\tVoulez-vous utilisez une planche de bois ? tapez 1 pour l'utiliser sinon 0. ");
            scanf("%d",&choix[4]);
            if(choix[4]==1)
            {
                user->nbCartesPossedees--;
                user->carteEpavesPossedees[i]=-1;
                plato->placeRadeau++;
            }
            break;
        case 5:
            printf("\n\t\tVoulez-vous boire de l'eau croupie ? tapez 1 pour l'utiliser sinon 0. ");
            scanf("%d",&choix[5]);
            if(choix[5]==1)
            {
                user->nbCartesPossedees--;
                user->carteEpavesPossedees[i]=-1;
                plato->compteurEau++;
                user->malade=1;
            }
            break;
        case 6:
            printf("\n\t\tVoulez-vous manger un poisson pourri ? tapez 1 pour l'utiliser sinon 0. ");
            scanf("%d",&choix[6]);
            if(choix[6]==1)
            {
                user->nbCartesPossedees--;
                user->carteEpavesPossedees[i]=-1;
                plato->compteurNourriture++;
                user->malade=1;
            }
            break;
        case 10:
            printf("\n\t\tVoulez-vous utilisez le revovlver ? tapez 1 pour l'utiliser sinon 0. ");
            scanf("%d",&choix[7]);
            if(choix[7]==1)
            {
                user->nbCartesPossedees--;
                user->carteEpavesPossedees[i]=-1;
                printf("\n\tSur qui souhaitez vous tirer ? ");
                scanf("%s",nomTue);
                for(k=0; k<plato->nbJoueur; k++)
                {
                    if(tab[k].mort!=1)
                    {
                        if(strcmp(nomTue,tab[k].nom)==0)
                        {
                            tab[k].mort=1;
                        }
                    }
                }
            }
            break;
        case 11:
            printf("\n\t\tVoulez-vous utilisez un anti-venin ? tapez 1 pour l'utiliser sinon 0. ");
            scanf("%d",&choix[0]);
            if(choix[0]==1)
            {
                user->nbCartesPossedees--;
                user->carteEpavesPossedees[i]=0;
                user->malade=0;
            }
            break;
        default :
            ;
        }
    }
}

void utiliserAntiVenin(S_player *user) //ce sous-programme concerne seulement le cas lorsque le joueur est malade
{
    int i,choix;


    user->TourMalade=1;//on incrémente le nombre de tour que le joueur a passé en étant malade

    for(i=0; i<27; i++)
    {
        if(user->carteEpavesPossedees[i]==11)
        {
            Positionner_Curseur(60,9);
            printf("\nVous avez une carte anti-venin souhaitez-vous l'utiliser ? Tapez 1 pour l'utiliser sinon 0: ");
            scanf("%d",&choix);
            if(choix==1)
            {
                user->carteEpavesPossedees[i]=-1;
                user->nbCartesPossedees--;
                user->malade=0;
                printf("Vous êtes guéri");
            }
        }
    }
}

