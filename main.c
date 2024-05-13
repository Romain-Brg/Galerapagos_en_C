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


int main()
{
    SetConsoleOutputCP(1252); //accent
    plein_ecran();


    avertissement();// pour prevenir qu'il faut mieux jouer sur un grand écran

    afficherRegle();

    S_jeu Plateau; //création du plateau
    MiseEnPlace(&Plateau); /*initialisation des compteurs de nourritures et d'eau en focntion du nombre de joueurs et mise à zéro de tout
                            les sous-champs de S_jeu Plateau + mélange des Cartes Météo plus de détails dans initialisation.c*/



    S_player joueurs[Plateau.nbJoueur]; //création du tableau de joueur en fonction du nombre de joueurs rentré dans MiseEnPlace(&Plateau)
    nomEtCartes(&Plateau,joueurs);//ssprog permettant de rentrer les noms de chaque joueur et leur attribuer 3 cartes oui c'est 4 mais on a réduit le nombre de cartes codées
    system("cls");//table rase
    int k,i,choix; //k et i pour les boucles for et choix permet de savoir si le joueur souhaite jouer une de ces cartes

    do
    {
        for(i=0; i<Plateau.nbJoueur; i++)
        {
            if(joueurs[i].mort!=1)//on vérifie que le joueur est vivant
            {
                Positionner_Curseur(40,5);
                printf("%s",joueurs[i].nom);
                afficherCartePlayer(joueurs[i]); //on affiche au joueur ses cartes

                if(joueurs[i].malade==1)
                {
                    if(joueurs[i].TourMalade==0)//tour malade voir declarations.h
                    {
                        srand(time(NULL));
                        Positionner_Curseur(60,8);
                        color(15,6);
                        printf(" %s vous êtes malades, vous ne pouvez pas jouer !",joueurs[i].nom);
                        Sleep(4000);
                        color(15,0);
                        Positionner_Curseur(60,8);
                        printf("                                                                                                  "); //printf sans rien sert à effacer
                        utiliserAntiVenin(&joueurs[i]);//ssprog qui regarde si un joueur possède un anti-venin
                        Positionner_Curseur(60,9);
                        printf("                                                                                                                                              ");
                    }
                    else
                    {
                        Positionner_Curseur(60,8);
                        printf("%s vous n'êtes plus malade vous pouvez jouer ",joueurs[i].nom);
                        joueurs[i].malade=0;
                        joueurs[i].TourMalade=0;
                        Sleep(2000);
                        pionFood(&Plateau,20,40),pionEau(&Plateau,70,37),compteurRadeau(&Plateau,100,42),pionCarteMeteo(&Plateau,150,45),Sleep(4000);//le joueur est plus malade il peut jouer
                        menu_action(&Plateau,&joueurs[i]);
                        for(k=0; k<15; k++)
                        {
                            Positionner_Curseur(40,k);
                            color(15,0);
                            printf("                                                                                                                                          ");
                        }

                        printf("\n%s :",joueurs[i].nom);
                        afficherCartePlayer(joueurs[i]);//ssprog voir affichage.c
                        printf("\nSouhaitez vous jouez vos cartes ? tapez 1 si oui sinon tapez 0 :");
                        scanf("%d",&choix);
                        if(choix==1)
                        {
                            utilisationCarte(&Plateau,&joueurs[i],joueurs);//ssprog voir action.c
                        }
                        system("cls");

                    }


                }
                else //cas où le joueur n'est pas malade
                {
                    pionFood(&Plateau,20,40),pionEau(&Plateau,70,37),compteurRadeau(&Plateau,100,42),pionCarteMeteo(&Plateau,150,45),Sleep(4000);
                    menu_action(&Plateau,&joueurs[i]);
                    for(k=0; k<15; k++)
                    {
                        Positionner_Curseur(40,k);
                        color(15,0);
                        printf("                                                                                                                                          ");
                    }
                    color(15,0);

                    printf("\n%s :",joueurs[i].nom);
                    afficherCartePlayer(joueurs[i]);
                    printf("\nSouhaitez vous jouez vos cartes ? tapez 1 si oui sinon tapez 0 :");
                    scanf("%d",&choix);
                    if(choix==1)
                    {
                        utilisationCarte(&Plateau,&joueurs[i],joueurs);
                    }
                    system("cls");
                }
            }
        }

        if(Plateau.compteurEau-Plateau.joueurRestants<0 || Plateau.compteurNourriture-Plateau.joueurRestants<0)//cas où il n'y a pas assez de ressources
        {
            color(15,4);
            Positionner_Curseur(60,2);
            printf("Il n'y a pas assez de ressources pour tout le monde !!");
            color(15,0);
            pionFood(&Plateau,40,40),pionEau(&Plateau,90,37);


            for(i=0; i<Plateau.nbJoueur; i++)  //on demande d'abord aux joueurs si ils veulent jouer leurs cartes pour éviter le vote
            {
                pionFood(&Plateau,40,40),pionEau(&Plateau,90,37);
                Positionner_Curseur(2,1);
                if(joueurs[i].mort!=1)
                {
                    printf("\n%s :",joueurs[i].nom);
                    afficherCartePlayer(joueurs[i]);
                    printf("\nSouhaitez vous jouez vos cartes ? tapez 1 si oui sinon tapez 0 :");
                    scanf("%d",&choix);
                    if(choix==1)
                    {
                        utilisationCarte(&Plateau,&joueurs[i],joueurs);
                    }
                    system("PAUSE");
                }
                system("cls");
            }
            if(Plateau.compteurEau-Plateau.joueurRestants<0 || Plateau.compteurNourriture-Plateau.joueurRestants<0) //cas où même après la possibilité donnée aux joueurs de jouer leur cartes il n'y a toujours pas assez de ressources
            {
                Positionner_Curseur(40,5);
                printf("Il n'y a toujours pas assez de nourriture ou d'eau, nous allons procéder au vote");
                vote(&Plateau,joueurs);//ssprog voir action.c
                system("PAUSE");
            }
            system("cls");
        }
        //mise à jour des compteurs dans le cas où on a considéré qu'un seul vote peut être fait par tour le compteur sont mis à 0 si il y a toujours pas assez de ressources pour tout le monde
        if(Plateau.compteurEau-Plateau.joueurRestants<0)
        {
            Plateau.compteurEau=0;
        }
        else
        {
            Plateau.compteurEau=Plateau.compteurEau-Plateau.joueurRestants;
        }
        if(Plateau.compteurNourriture-Plateau.joueurRestants<0)
        {
            Plateau.compteurNourriture=0;
        }
        else
        {
            Plateau.compteurNourriture=Plateau.compteurNourriture-Plateau.joueurRestants;
        }
        Plateau.nbTours++;
        Plateau.MeteoActu=Plateau.carteMeteo[Plateau.nbTours];
        system("cls");
        Positionner_Curseur(100,24);
        printf("NOUVEAU TOUR");
        Sleep(2000);
        Positionner_Curseur(100,24);
        printf("            ");
    }
    while(Plateau.MeteoActu != 4 &&  Plateau.placeRadeau != Plateau.joueurRestants && Plateau.joueurRestants != 0);//conditions d'arrêt des tours "normaux"


    if(Plateau.MeteoActu==4)//cas si l'ouragan arrive
    {
        Positionner_Curseur(40,5);
        printf("L'ouragan arrive !! Il ne vous reste qu'un seul tour pour vous échapper et pour cela vous devez avoir %d places sur votre radeau !",Plateau.joueurRestants),Sleep(3500);
        Positionner_Curseur(40,5);
        printf("                                                                                                                                    ");
        for(i=0; i<Plateau.nbJoueur; i++) //ultime tour de jeu on a simplifier en permettant aux joueurs de pouvoir s'échapper même si ils ont pas assez de ressources
        {
            if(joueurs[i].mort!=1)
            {
                Positionner_Curseur(40,5);
                printf("%s",joueurs[i].nom);
                afficherCartePlayer(joueurs[i]);
                system("PAUSE");

                if(joueurs[i].malade==1)
                {
                    if(joueurs[i].TourMalade==1)
                    {
                        Positionner_Curseur(60,9);
                        printf("Vous n'êtes plus malade.");
                        Sleep(1000);
                        joueurs[i].TourMalade=0;
                        joueurs[i].malade=0;
                        menu_action(&Plateau,&joueurs[i]);
                        for(k=0; k<15; k++)
                        {
                            Positionner_Curseur(40,k);
                            color(15,0);
                            printf("                                                                                      ");
                        }
                        color(15,0);

                    }
                    if(joueurs[i].TourMalade==0)
                    {
                        Positionner_Curseur(60,8);
                        printf(" %s vous êtes malades, vous ne pouvez pas jouer !",joueurs[i].nom);
                        Sleep(2000);
                        Positionner_Curseur(60,8);
                        printf("                                                                                     ");
                        utiliserAntiVenin(&joueurs[i]);
                        Positionner_Curseur(60,9);
                        printf("                                                                                     ");
                    }


                }
                else
                {
                    menu_action(&Plateau,&joueurs[i]);
                    for(k=0; k<15; k++)
                    {
                        Positionner_Curseur(40,k);
                        color(15,0);
                        printf("                                                                                      ");
                    }
                    color(15,0);
                }
            }
        }

        if(Plateau.placeRadeau!=Plateau.joueurRestants) ///cas où il y a pas assez de places pour tout les joueurs restants pour partir lors de l'ouragan
        {
            printf("\n\n\nIl n'y a pas assez de places dans le radeau ");
            while(Plateau.placeRadeau!=Plateau.joueurRestants)
            {
                vote(&Plateau,joueurs);
            }
            printf("\n\n\n\n\n\nAu prix de sacrifices vous vous en êtes sortis BRAVO !!");
        }
        else
        {
            printf("\n\n\n\n\n\nVous vous en êtes sortis BRAVO !!!");
        }
    }



    if(Plateau.placeRadeau==Plateau.joueurRestants)//cas où il y a assez de places pour tout le monde
    {
        printf("\n\n\n\n\n\nVous vous en êtes sortis BRAVO !!!");
    }
    if(Plateau.joueurRestants==0)//cas où tout le monde est mort
    {
        printf("\n\n\n\n\n\nTout le monde est mort\n\n\n\n\n\n ");
        teteMort();
    }

    return 0;
}
