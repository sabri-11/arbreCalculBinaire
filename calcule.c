#include <stdio.h>
#include <stdlib.h> 
#include <assert.h>
#include <stdbool.h>

// ######################################### Déclarations de fonctions ###################################### //
void verifArgs(int args);
int tailleCalculEntree(char *argv[]);
noeud *initArbreBinaire();

// ######################################### Strcutures de données ###################################### /
typedef enum
{
    VALEUR,
    OPERATEUR
}TypeNoeud;

typedef struct noeud_t
{
    TypeNoeud type;
    union 
    {
        int val;
        char op;
    }elt;
    struct noeud_t *noeudGauche;
    struct noeud_t *noeudDroit;
}noeud;

/* typedef struct arbre_t
{
    noeud *racine;
}arbre; */

// ######################################### Main ###################################### //
int main(int args, char *argv[])
{
    verifArgs(args);
    int tailleCalcul = tailleCalculEntree(argv);
    noeud *racine = initArbreBinaire();

    free(racine);
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


noeud *creerNoeudVal(int val)
{
    noeud *n = (noeud*) malloc(sizeof(noeud));
    n->type = VALEUR;
    n->elt.val = val;

    n->noeudDroit = NULL;
    n->noeudGauche = NULL;
    return n;

}

bool estFeuille(noeud *n)
{
    return (n->noeudDroit == NULL && n->noeudGauche == NULL);
}

noeud *creerNoeudOp(char op)
{
    noeud *n = (noeud*) malloc(sizeof(noeud));
    n->type = OPERATEUR;
    n->elt.op = op;

    n->noeudDroit = NULL;
    n->noeudGauche = NULL;
    return n;

}



noeud *insererGauche(noeud *r, int val)
{
    

}

noeud *insererDroit(noeud *r, int val, char symb)
{

}


void free_arbre(noeud *r)
{
    if (r == NULL) return 
    free_arbre(r->noeudDroit);
    free_arbre(r->noeudGauche);
}

int remplirArbre(noeud *r, char **argv, int tailleCalcul)
{
    int i = 0, nb1 = 0, nb2 = 0;
    char op = '\0';
    
    char 
}
