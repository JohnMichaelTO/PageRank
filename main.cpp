#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrice.h"
#include "conio.h"

#define SYMB 42 // Symbole utilisé pour les listes
#define NOMBRE_OPTIONS 1

using namespace std;

int main()
{
    system ("MODE CON COLS=210 LINES=60");
    int selection = 0, run = 1;

    do
    {
        system("cls");
        printf("\n   %c PageRank %c\n\n\n %c 0 - Quitter\n\n %c 1 - PageRank\n\n\n", SYMB, SYMB, SYMB, SYMB);
        do
        {
            printf("\n  Selection d'une option : ");
            scanf("%d", &selection);

            if (selection < 0 || selection > NOMBRE_OPTIONS) // Erreur dans la saisie.
            {
                printf(" /!\\ Erreur : Ceci n'est pas une option selectionnable. /!\\ \n");
            }
            else if (selection != 0) // Sous-programme valide sélectionné : lancement.
            {
                printf(" Execution de la fonction desiree.\n\n");
            }
            else // Arrêt
            {
                run = 0;
                exit(1);
            }
        } while (selection < 0 || selection > NOMBRE_OPTIONS);

        system("cls");
        switch (selection) // Vérification et lancement du sous-programme approprié.
        {
            case 1:
                srand((unsigned)time(NULL));
                pagerank();
                system("pause");
                break;
        }
    } while(run != 0);

    return 0;
}
