#define TAILLE_MATRICE 40

typedef struct s_classement
{
    int id;
    double PR;
} t_classement;

/* PageRank */
void pagerank();

/* Initialisation de la matrice */
void initMatrice(double matrice[TAILLE_MATRICE][TAILLE_MATRICE]);

/* Place les coefficients au hasard */
void genererMatrice(double matrice[TAILLE_MATRICE][TAILLE_MATRICE]);

/* Arrondi */
int arrondir(double x);

/* Génère le PageRank */
void genererPR(double matrice[TAILLE_MATRICE][TAILLE_MATRICE], double PR[]);

/* Calcul PR */
int calculPR(double PR);

/* Génère le classement */
void genererClassement(double PR[], t_classement classement[]);

/* Affichage du classement */
void afficheClassement(t_classement classement[]);

/* Affiche PR */
void affichePR(double PR[]);

/* Affichage de la matrice */
void afficheMatrice(double matrice[TAILLE_MATRICE][TAILLE_MATRICE], double PR[]);

/* Echange */
void swap(double *x, double *y);

/* Echange dans le classement */
void swapClassement(t_classement *x, t_classement *y);

/*void verifierWolfram(double matrice[TAILLE_MATRICE][TAILLE_MATRICE]);
}*/
