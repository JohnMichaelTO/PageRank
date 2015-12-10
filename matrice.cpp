#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"
#include "conio.h"
#define SYMB 42 // Symbole utilisé pour les listes

/* PageRank */
void pagerank()
{
    printf("\n   %c PageRank %c\n\n\n", SYMB, SYMB);

    //Variables.
    double matrice[TAILLE_MATRICE][TAILLE_MATRICE] = {{0}};
    double PR[TAILLE_MATRICE] = {0};
    t_classement classement[4];

    /*double matrice[TAILLE_MATRICE][TAILLE_MATRICE] = {{0, 1./2., 1./2., 1./2., 1./2., 0, 1./2., 0, 0, 0, 0, 0, 0, 0},
                                                    {1./5., 0, 0, 0, 1./2., 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {1./5., 1./2., 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {1./5., 0, 1./2., 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {1./5., 0, 0, 1./2., 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {1./5., 0, 0, 0, 0, 0, 0, 1, 0, 1./5., 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 1./3., 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 1./3., 1./2., 0, 1./2., 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 1./3., 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 1./2., 0, 1./2., 1./2., 1./2., 1./2.},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1./5., 0, 0, 0, 1./2.},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1./5., 1./2., 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1./5., 0, 1./2., 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1./5., 0, 0, 1./2., 0}};*/
    // afficheMatrice(matrice, PR);
    initMatrice(matrice);
    // afficheMatrice(matrice, PR);
    genererMatrice(matrice);
    // afficheMatrice(matrice, PR);
    genererPR(matrice, PR);
    afficheMatrice(matrice, PR);
    affichePR(PR);
    genererClassement(PR, classement);
    afficheClassement(classement);
}

/* Initialisation de la matrice */
void initMatrice(double matrice[TAILLE_MATRICE][TAILLE_MATRICE])
{
    int i, j, k, K;

    for(i = 0; i < TAILLE_MATRICE; i++)
    {
        k = rand() % (TAILLE_MATRICE / 3) + 1;

        K = k;
        for(j = 0; j < K; j++)
        {
            if(i == j)
            {
                K = K + 1;
                matrice[j][i] = 0.0;
            }
            else
            {
                matrice[j][i] = 1.0 / k;
            }
        }
    }
}

/* Place les coefficients au hasard */
void genererMatrice(double matrice[TAILLE_MATRICE][TAILLE_MATRICE])
{
    int n = TAILLE_MATRICE, temp, i, j;

    for(i = 0; i < TAILLE_MATRICE; i++)
    {
        for(j = 0; j < TAILLE_MATRICE; j++)
        {
            for(n = j - 1; n > 0; n--)
            {
                temp = rand() % n;

                if(n != i && temp != i)
                {
                    swap(&matrice[n][i], &matrice[temp][i]);
                }
            }
        }
    }
}

/* Arrondi */
int arrondir(double x)
{
    int X;
    X = (int)x;

    if(x - X >= 0.5)
    {
        X = X + 1;
    }
    return X;
}

/* Génère le PageRank */
void genererPR(double matrice[TAILLE_MATRICE][TAILLE_MATRICE], double PR[TAILLE_MATRICE])
{
    int i, j, k, t, tmax, cpt = 0, x, y;
    double PR2[TAILLE_MATRICE][TAILLE_MATRICE];
    tmax = 100;

    printf("\n\n");
    x = wherex();
    y = wherey();
    printf("Generation du pagerank..0 %%");

    j = rand() % TAILLE_MATRICE;
    #if DEBUG
    printf("\n\nj = %i\n\n", j + 1);
    #endif
    for(i = 0; i < TAILLE_MATRICE; i++)
    {
        PR[i] = matrice[i][j];
        #if DEBUG
        printf("  %g", PR[i]);
        #endif
    }
    #if DEBUG
    printf("\n\n");
    #endif

    for(t = 0; t < tmax; t++)
    {
        cpt = 0;
        for(i = 0; i < TAILLE_MATRICE; i++)
        {
            if(PR[i] != 0.0)

            {
                j = i;
                for(k = 0; k < TAILLE_MATRICE; k++)
                {
                    PR2[cpt][k] = matrice[k][j] * PR[j];
                    #if DEBUG
                    printf("  %g", PR2[cpt][k]);
                    #endif
                }
                cpt++;
                #if DEBUG
                printf("\ncpt = %i", cpt);
                printf("\n\n");
                #endif
            }
        }
        #if DEBUG
        printf("\n\n-----Test -----------\n\n");
        #endif
        for(i = 1; i < cpt; i++)
        {
            for(j = 0; j < TAILLE_MATRICE; j++)
            {
                PR2[0][j] = PR2[0][j] + PR2[i][j];
            }
        }
        #if DEBUG
        for(i = 0; i < TAILLE_MATRICE; i++)
        {
            printf("  %g", PR2[0][i]);
        }
        printf("\n\n----------------\n\n");
        #endif
        for(i = 0; i < TAILLE_MATRICE; i++)
        {
            PR[i] = PR2[0][i];
        }
        #if DEBUG
        printf("\n\n");
        #endif

        gotoxy(x, y);
        printf("Generation du pagerank..%g %%\t\n", ((double)(t + 1) / (double)tmax) * 100.0);
    }
}

/* Calcul PR */
int calculPR(double PR)
{
    return arrondir((6.0 * PR) / 0.15);
}

/* Génère le classement */
void genererClassement(double PR[TAILLE_MATRICE], t_classement classement[])
{
    int i, j = 0;

    for(i = 0; i < TAILLE_MATRICE; i++)
    {
        if(i == 2 || i == 4 || i == 12 || i == 32)
        {
            classement[j].id = i;
            classement[j].PR = PR[i];
            j++;
        }
    }

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            if(i != j)
            {
                if(classement[j].PR < classement[i].PR)
                {
                    swapClassement(&classement[i], &classement[j]);
                }
            }
        }
    }
}

/* Affichage du classement */
void afficheClassement(t_classement classement[])
{
    int i;

    printf("\n\nClassement des pages 3, 5, 13, 33\n\n");
    printf("N : page - PR\n");
    for(i = 0; i < 4; i++)
    {
        if(classement[i].id + 1 > 9)
        {
            printf("%i :  %i  - %i\n", i + 1, classement[i].id + 1, calculPR(classement[i].PR));
        }
        else
        {
            printf("%i :  %i   - %i\n", i + 1, classement[i].id + 1, calculPR(classement[i].PR));
        }
    }
}

/* Affiche PR */
void affichePR(double PR[])
{
    int i;

    printf("\n\nPageRank\n\nPage : ");

    for(i = 0; i < TAILLE_MATRICE; i++)
    {
        if(i == 2 || i == 4 || i == 12 || i == 32)
        {
            textcolor(LIGHTRED);
        }

        if((i + 1) > 9)
        {
            printf("%i ", i + 1);
        }
        else
        {
            printf("%i  ", i + 1);
        }
        textcolor(WHITE);
    }
    printf("\nPR   : ");
    for(i = 0; i < TAILLE_MATRICE; i++)
    {
        if((i + 1) == 10)
        {
            printf(" ");
        }
        if(i == 2 || i == 4 || i == 12 || i == 32)
        {
            textcolor(LIGHTRED);
            printf("%i  ", calculPR(PR[i]));
            textcolor(WHITE);
        }
        else
        {
            printf("%i  ", calculPR(PR[i]));
        }
    }
}

/* Affichage de la matrice */
void afficheMatrice(double matrice[TAILLE_MATRICE][TAILLE_MATRICE], double PR[TAILLE_MATRICE])
{
    int i, j;

    printf("\n\nMatrice :\n\n  ");

    for(i = 0; i < TAILLE_MATRICE; i++)
    {
        printf(" %2.i  ", i + 1);
    }
    printf("  PR");
    printf("\n");
    for(i = 0; i < TAILLE_MATRICE; i++)
    {
        printf("%2.i ", i + 1);
        for(j = 0; j < TAILLE_MATRICE; j++)
        {
            if(i % 2 == 1)
            {
                textbackground(DARKGRAY);
            }
            else
            {
                textbackground(LIGHTGRAY);
            }

            textcolor(BLACK);

            if(j % 2 == 1)
            {
                textcolor(BLUE);
            }

            if(i == j)
            {
                textcolor(LIGHTRED);
            }

            if(matrice[i][j] != 0.0 && matrice[i][j] != 1.0)
            {
                if(arrondir(1.0 / matrice[i][j]) >= 10.0)
                {
                    printf("1/%g ", 1.0 / matrice[i][j]);
                }
                else
                {
                    printf("1/%g  ", 1.0 / matrice[i][j]);
                }
            }
            else if(matrice[i][j] == 1.0)
            {
                printf(" 1   ");
            }
            else
            {
                printf(" 0   ");
            }
            textbackground(BLACK);
            textcolor(WHITE);
        }
        // printf("  %g | %i", (6.0 * PR[i]) / 0.15, arrondir((6.0 * PR[i]) / 0.15));
        if(i == 2 || i == 4 || i == 12 || i == 32)
        {
            textcolor(LIGHTRED);
            printf("  %i", calculPR(PR[i]));
            // printf("  %g", PR[i]);
            textcolor(WHITE);
        }
        else
        {
            printf("  %i", calculPR(PR[i]));
            // printf("  %g", PR[i]);
        }
        printf("\n");
    }
}

/* Echange */
void swap(double *x, double *y)
{
    double temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/* Echange dans le classement */
void swapClassement(t_classement *x, t_classement *y)
{
    t_classement temp;
    temp.id = x->id;
    temp.PR = x->PR;
    x->id = y->id;
    x->PR = y->PR;
    y->id = temp.id;
    y->PR = temp.PR;
}

/*void verifierWolfram(double matrice[TAILLE_MATRICE][TAILLE_MATRICE])
{
    int i, j;
    int taille = TAILLE_MATRICE;
    printf("Verifier sur wolfram alpha :\n\n");

    printf(" {{");
    for(i = 0; i < taille; i++)
    {
        for(j = 0; j < taille; j++)
        {
            printf("%g", matrice[i][j]);
            printf(", ");
        }
        printf("}, {");
    }
    printf("}}\n\n\n");
}*/
