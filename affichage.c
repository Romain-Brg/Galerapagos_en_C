#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>

#include "actions.h"
#include "affichage.h"
#include "declaration.h"
#include "initialisation.h"
#include "joueurAction.h"

///une partie de ces ssprogs proviennent du TP2
void Positionner_Curseur(int colonne, int ligne)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);//permet de déclarer la variable "hstdout" qui fait référénce à la console
    COORD pos; // COORD est un type structuré défini dans la bibliothèque windows.h
    pos.X=colonne;// numéro de la colonne
    pos.Y=ligne;// numéro de la ligne
    SetConsoleCursorPosition(hStdout, pos); //on positionne le curseur aux coordonnées "pos"
}

void color (int couleurDuTexte, int couleurDuFond)
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDuFond*16+couleurDuTexte);
    // 0.Noir
// 1.Bleu fonc
// 2.Vert fonc
// 3.Turquoise
// 4.Rouge fonc
// 5.Violet
// 6.Vert caca d'oie
// 7.Gris clair
// 8.Gris fonc
// 9.Bleu fluo
// 10.Vert fluo
// 11.Turquoise
// 12.Rouge fluo
// 13.Violet 2
// 14.Jaune
// 15.Blanc
}

void plein_ecran()
{
    keybd_event(VK_MENU,0x38,0,0); //Appuie sur ALT
    keybd_event(VK_RETURN,0x1c,0,0); //Appuie ENTREE
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0); // Relache ENTREE
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0); //Relache ALT
}



void menu_action(S_jeu *plato,S_player *user) ///même programme que dans le TP2 mais adapté pour Galérapagos
{
    color(15,0);
    char menu[4][58]= {"   Recolter de l'eau                                  ","   Recolter de la nourriture                          ","   Fouiller l'epave et recuperer une carte epave      ","   Aller recolter du bois pour le radeau              "};
    int choix=0; // numéro de l'option choisie dans le menu
    int frappe=0; //permet de stocker le code de la touche clavier
    int i;
    while (choix!=4)
    {


        system("cls");
        Positionner_Curseur(40,0);
        printf(" __________________ %s choisissez votre action ! _______________\n",user->nom);
        Positionner_Curseur(40,1);
        printf("                                                               \n");
        Positionner_Curseur(40,2);
        printf("                                                               \n");
        for(i=0; i<4; i++)
        {
            Positionner_Curseur(40,3+i);
            printf("\t%s\n",menu[i]);
        }
        Positionner_Curseur(40,7);
        printf("                                                               \n");
        Positionner_Curseur(40,8);
        printf("                                                               \n");
        Positionner_Curseur(40,9);
        printf("_______________________________________________________________\n");

        while(frappe!=13) // tant qu'on a pas appuyer sur la touche ECHAP
        {
            if (kbhit()) //si on a appuyer sur une touche du clavier
            {


                frappe=getch(); // on récupère le code de la touche sur laquelle on a appuyée


                if(frappe==72) //75 est le code de la flèche directionnelle vers le haut
                {

                    Positionner_Curseur(40,choix+3); // positionne le curseur au choix courant
                    color(15,0); // met la couleur du texte en blanc et celle du fond en noir
                    printf("\t%s",menu[choix]); // On réaffiche le choix courant avec les couleurs préalablement choisies, une manière de le désélectionner
                    choix--; // on décrémebte le numéro de l'option
                    if (choix ==-1) choix =3; // les options sont numérotées de 0 à 11
                    Positionner_Curseur(40,choix+3);// positionne le curseur au choix juste dessus du précédent
                    color(0,15);// met la couleur du texte en noir et celle du fond en blanc
                    printf("\t%s\n",menu[choix]);// On réaffiche le nouveau choix  avec les couleurs préalablement choisies, une manière de le séléctionner
                    color(15,0);
                }
                if(frappe==80) //80 est le code de la flèche directionnelle vers le bas
                {

                    Positionner_Curseur(40,choix+3);
                    color(15,0);
                    printf("\t%s",menu[choix]);
                    choix++;
                    if (choix ==4) choix =0;
                    Positionner_Curseur(40,choix+3);
                    color(0,15);
                    printf("\t%s",menu[choix]);
                    color(15,0);
                }

            }
            Positionner_Curseur(0,19);

        }

        choix++;
        switch(choix)
        {
        case 1 :
            recolterEau(plato,user);
            Sleep(2000);
            return;

        case 2 :
            pecher(plato);
            Sleep(2000);
            return;
        case 3:
            piocherCarteEpaves(plato,user);
            Sleep(2000);
            return;
        case 4:
            recolterBois(plato,user);
            Sleep(2000);
            return;

        default :
            printf("CECI EST UN BUG");
            system("PAUSE");
            break;
        }
        choix=0;
        frappe=0;
    }

}

void afficherRegle()
{
    printf(" _____________________________Bienvenue sur l'île naufragés !_____________________________\n");
    printf("|                                                                                         |\n");
    printf("| Votre objectif est de survivre et de vous échapper de cette île, pour cela vous devrez  |\n");
    printf("| récolter du bois pour construire le radeau, en choisissant l'action de récolter du bois |\n");
    printf("| vous récupérerez 1 bout de bois d'office. 6 bouts de bois correspondent à UNE seule     |\n");
    printf("| place pour un seul joueur. Mais attention si vous allez chercher du bois vous pouvez    |\n");
    printf("| faire mordre par un serpent et être malade. Dans ce cas vous ne pourrez plus faire      |\n");
    printf("| d'action.                                                                               |\n");
    printf("|                                                                                         |\n");
    printf("| Il y a une épave pas loin vous pouvez aussi y aller faire un tour pour y                |\n");
    printf("| trouver des objets utiles mais aussi inutiles. Vous devez aussi surveiller vos stocks   |\n");
    printf("| d'eau et de nourriture. Vous pouvez aller chercher de l'eau. La valeur de la carte      |\n");
    printf("| météo correspond au nombre de ration d'eau que vous pouvez récupérer.                   |\n");
    printf("| Pour la nourriture c'est aléatoire, vous pouvez récolter entre 1 et 3 ration            |\n");
    printf("| de nourriture. Mais il se peut qu'à la fin d'un tour vous n'ayez pas                    |\n");
    printf("| assez de nourriture pour tout le monde. Dans ce cas il faut procéder à un vote pour     |\n");
    printf("| éliminer une ou dans le pire des cas plusieurs personnes.                               |\n");
    printf("|                                                                                         |\n");
    printf("| Fin de partie :                                                                         |\n");
    printf("|                 - Il y a assez de place sur le radeau pour tout le monde.               |\n");
    printf("|                 - La carte Ouragan a été retournée, vous pouvez finir le tour et faire  |\n");
    printf("|                   un vote si il n'y a pas assez de place.                               |\n");
    printf("|                 - Tout le monde est mort                                                |\n");
    printf("|                                                                                         |\n");
    printf("|                          Vous voilà prêts pour votre survie                             |\n");
    printf("|                                                                                         |\n");
    printf("|                                       Bon courage !!                                    |\n");
    printf("|                                                                                         |\n");
    printf("|_________________________________________________________________________________________|\n");
    system("PAUSE");
    system("cls");
}

void avertissement()
{
    color(0,14);
    printf("\n\t\t\t\t\t\t\t\tPour une meilleure expérience nous vos conseillons de jouer sur un grand écran \n\t\t\t\t\t\t\t\tcar l'affichage est fait pour.\n\n\n");
    color(15,0);
    system("PAUSE");
    system("cls");
}

void pionFood(S_jeu *plato,int colonne,int ligne) ///permet d'afficher le compteur nourriture
{

    color(4,4);
    Positionner_Curseur(colonne+3,ligne-3);
    printf(" ");

    Positionner_Curseur(colonne+2,ligne-2);
    printf("   ");
    Positionner_Curseur(colonne+8,ligne-2);
    printf(" ");

    Positionner_Curseur(colonne+1,ligne-1);
    printf(" ");
    color(1,1);
    Positionner_Curseur(colonne+2,ligne-1);
    printf(" ");
    color(4,4);
    Positionner_Curseur(colonne+3,ligne-1);
    printf("   ");
    Positionner_Curseur(colonne+7,ligne-1);
    printf("  ");

    Positionner_Curseur(colonne,ligne);
    printf("         ");
    Positionner_Curseur(colonne+1,ligne+1);
    printf("     ");
    Positionner_Curseur(colonne+7,ligne+1);
    printf("  ");

    Positionner_Curseur(colonne+2,ligne+2);
    printf("   ");
    Positionner_Curseur(colonne+8,ligne+2);
    printf(" ");

    Positionner_Curseur(colonne+3,ligne+3);
    printf(" ");

    Positionner_Curseur(colonne-10,ligne+5);
    color(15,0);
    printf("Nombre de ration de nourriture : %d",plato->compteurNourriture);



}




void pionEau(S_jeu *plato,int colonne,int ligne) ///permet d'afficher le compteur nourriture
{
    color(1,1);
    Positionner_Curseur(colonne,ligne);
    printf(" ");
    Positionner_Curseur(colonne-1,ligne+1);
    printf("   ");
    Positionner_Curseur(colonne-2,ligne+2);
    printf("     ");
    Positionner_Curseur(colonne-3,ligne+3);
    printf("       ");
    Positionner_Curseur(colonne-3,ligne+4);
    printf("       ");
    Positionner_Curseur(colonne-3,ligne+5);
    printf("       ");
    Positionner_Curseur(colonne-1,ligne+6);
    printf("   ");

    Positionner_Curseur(colonne-10,ligne+8);
    color(15,0);
    printf("Nombre de ration d'eau : %d",plato->compteurEau);

}

void compteurRadeau(S_jeu *plato,int colonne,int ligne) ///permet d'afficher les infos relatives au radeau
{
    color(15,0);
    Positionner_Curseur(colonne,ligne);
    printf("Bout(s) de bois récolté(s) : %d ",plato->compteurRadeau);
    Positionner_Curseur(colonne,ligne+3);
    printf("Place(s) disponible(s) sur le radeau : %d ",plato->placeRadeau);
    color(15,0);
}
void pionCarteMeteo(S_jeu *plato,int colonne,int ligne)
{
    Positionner_Curseur(colonne+2,ligne-3);
    printf("Carte météo actuelle :");

    Positionner_Curseur(colonne,ligne);
    printf("Vous pouvez récupérer : %d ration(s) d'eau.",plato->MeteoActu);
}

void afficherCartePlayer(S_player user)
{
    int i,carte,tabCartes[15]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; /*tabCartes[] nous permet de savoir combien de cartes d'un même types possède le joueur
                                                                    ce qui permet d'afficher "vous possédez tant de cartes de types tel"*/

    for(i=0; i<27; i++) //27 Correspond au nombre de carte maximales qu'un joueur peut avoir
    {
        carte=user.carteEpavesPossedees[i];
        switch(carte)
        {
        case 0 :
            tabCartes[0]++;
            break;
        case 1 :
            tabCartes[1]++;
            break;
        case 2:
            tabCartes[2]++;
            break;
        case 3:
            tabCartes[3]++;
            break;
        case 4:
            tabCartes[4]++;
            break;
        case 5:
            tabCartes[5]++;
            break;
        case 6:
            tabCartes[6]++;
            break;
        case 7:
            tabCartes[7]++;
            break;
        case 8:
            tabCartes[8]++;
            break;
        case 9:
            tabCartes[9]++;
            break;
        case 10:
            tabCartes[10]++;
            break;
        case 11:
            tabCartes[11]++;
            break;
        case 12:
            tabCartes[12]++;
            break;
        case 13 :
            tabCartes[13]++;
            break;
        case 14:
            tabCartes[14]++;
            break;
        }
    }

    for(i=0; i<15; i++)
    {
        if(tabCartes[i]!=0)
        {
            switch(i) ///ici pour les valeurs du case on connaît les valeurs de chaque cartes elles sont dans iniTab() autrement on dit on sait que 0=bouteille d'eau,1=sandwich ...ect
            {
            case 0 :

                printf("\nVous avez %d bouteille(s) d'eau ce qui correspond à %d ration(s) d'eau. ", tabCartes[0], tabCartes[0]);
                break;
            case 1 :

                printf("\nVous avez %d sandwich ce qui correspond à %d ration(s) de nourriture. ", tabCartes[1],tabCartes[1]);
                break;
            case 2:

                printf("\nVous avez %d boîte(s) de sardines ce qui correspond à %d ration(s) de nourriture. ",tabCartes[2],3*tabCartes[2]);
                break;
            case 3:

                printf("\nVous avez %d noix de coco ce qui correspond à %d ration(s) d'eau. ",tabCartes[3],3*tabCartes[3]);
                break;
            case 4:

                printf("\nVous avez %d planches de bois ce qui correspond à %d places de radeau ",tabCartes[4],tabCartes[4]);
                break;
            case 5:

                printf("\nVous avez %d bouteille(s) d'eau courpie ce qui correspond à %d ration(s) d'eau mais si vous l'utilisez vous etes malade. ",tabCartes[5],tabCartes[5]);
                break;
            case 6:
                printf("\nVous avez %d poisson(s) pourri ce qui correspond à %d ration(s) de nourriture mais si vous l'utilisez vous etes malade. ",tabCartes[6],tabCartes[6]);;
                break;
            case 7:

                printf("\nVous avez %d slip usagé, cela ne sert à rien mais vous êtes couvert. ",tabCartes[7]);
                break;
            case 8:

                printf("\nVous avez %d clés de voitures cela ne sert à rien mais elles sont jolies. ", tabCartes[8]);
                break;
            case 9:

                printf("\nVous avez %d tickets de loto cela ne sert à rien mais il est peut-être gagnant. ",tabCartes[9]);
                break;
            case 10:

                printf("\nVous avez un revolver, vous pouvez tuer UNE SEULE personne, faites en bon usage. ");
                break;
            case 11:

                printf("\nVous avez %d anti-venin, si vous êtes malade vous pouvez vous soigner. ",tabCartes[11]);
                break;
            case 12:

                printf("\nVous avez une gourde, si vous recoltez de l'eau vous en récupérer 2 fois plus. ");
                break;
            case 13 :

                printf("\nVous avez un gourdin, votre vote vaut 2 voix. ");
                break;
            case 14:

                printf("\nVous avez une hache, si vous recoltez du bois vous aurez d'office 2 bouts de bois. ");
                break;
            }
        }
    }
    printf("\n\n");
}

void teteMort()
{
    printf("          _,.-----.,_\n");
    printf("       ,-~           ~-.\n");
    printf("      ,^___           ___^.\n");
    printf("    /~*   ~*   .   *~   *~\n");
    printf("   Y  ,--._    I    _.--.  Y\n");
    printf("    | Y     ~-. | ,-~     Y |\n");
    printf("    | |        }:{        | |\n");
    printf("    j l       / | \x5C       ! l\n");
    printf(" .-~  (__,.--* .^. *--.,__)  ~-.\n");
    printf("(           / / | \x5C  \x5C     )\n");
    printf(" \x5C .____,   ~  \x5C /*\x5C .____,/\n");
    printf("  ^.____                 ____.^\n");
    printf("     | |T ~\x5C  !   !  /~ T| |\n");
    printf("     | |l   _ _ _ _ _   !| |\n");
    printf("     | l \x5C /V V V V V V\x5C / j |\n");
    printf("     l  \x5C  \x5C |_|_|_|_|_|/ /  !\n");
    printf("      \x5C   \x5C [T T T T T TI/  /\n");
    printf("       \x5C   `^-^-^-^-^-^'  /\n");
    printf("        \x5C                /\n");
    printf("         \x5C            ,/\n");
    printf("           *^-.___,-^*\n");
}


