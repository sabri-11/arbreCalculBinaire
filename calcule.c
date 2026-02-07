#include <stdio.h>
#include <stdlib.h> 
#include <assert.h>

// ######################################### Déclarations de fonctions ###################################### //
void verifArgs(int args);
int tailleCalculEntree(char *argv[]);
arbre_t *initArbreBinaire();

// ######################################### Strcutures de données ###################################### //
typedef struct arbre_binaire
{
    char symb;
    int val;
    struct arbre_binaire *enfantGauche;
    struct arbre_binaire *enfantDroit;
}arbre_t;

// ######################################### Main ###################################### //
int main(int args, char *argv[])
{
    verifArgs(args);
    int tailleCalcul = tailleCalculEntree(argv);
    arbre_t *arbre = initArbreBinaire();


    free(arbre);
    return 0;
}

// ######################################### Fonctions ###################################### //

void verifArgs(int args)
{
    while (args < 2)
    {
        printf("Pas assez d'argument, donnez en argument un calcul (ex : ./calcul 3+2*3/4)\n");
    }

    while (args > 2)
    {
        printf("Trop d'arguments, ne donnez qu'un seul calcul en argument (ex : ./calcul 3+2x3:4)\n");
    }
}

int tailleCalculEntree(char *argv[])
{
    int n;
    for (n=0; argv[1][n]; n++);
    return n;
}

arbre_t *initArbreBinaire()
{
    arbre_t *arbre = (arbre_t*) malloc(sizeof(arbre_t));
    if (arbre == NULL)
    {
        printf("Echec de l'allocation de l'arbre.\n");
        assert(0);
    }

    arbre->symb = NULL;
    arbre->val = NULL;
    arbre->enfantDroit = NULL;
    arbre->enfantGauche = NULL;

    return arbre;

}

arbre_t creerNoeudVal(arbre_t a, int val)
{
    
}

arbre_t *insererGauche(arbre_t *a, int val, char symb)
{

    a->enfantGauche = 
}


void free_arbre(arbre_t *a)
{
    free(a);
}

int remplirArbre(arbre_t *a, char **argv, int tailleCalcul)
{
    for (int i=0; i<tailleCalcul; i++)
    {
        if (i%2 == 0)
        {
            a->val = atoi(argv[1][i]);
        }
            
    }
}
