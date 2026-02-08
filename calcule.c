#include <stdio.h>
#include <stdlib.h> 
#include <assert.h>
#include <stdbool.h>

// Faire des fonctions pour insérer des noeuds directement. Creer des noeuds en fct de val ou op. 

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
    if (args < 2)
    {
        printf("Pas assez d'argument, donnez en argument un calcul (ex : ./calcul 3+2*3/4)\n");
        exit(1);
    }

    if (args > 2)
    {
        printf("Trop d'arguments, ne donnez qu'un seul calcul en argument (ex : ./calcul 3+2x3:4)\n");
        exit(1);
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

noeud *creerNoeudOp(char op)
{
    noeud *n = (noeud*) malloc(sizeof(noeud));
    n->type = OPERATEUR;
    n->elt.op = op;

    n->noeudDroit = NULL;
    n->noeudGauche = NULL;
    return n;

}

bool estFeuille(noeud *n)
{
    return (n->noeudDroit == NULL && n->noeudGauche == NULL);
}



noeud *insererGaucheVal(noeud *r, int val)  // besoin pour le dernier noeud opérateur.
{   
    
}

noeud *insererGaucheOp(noeud *r, char op)   // On insère tous les opérateurs à gauche jusqu'à la fin de l'arbre ou le dernier opérateur aura 2 enfants valeures
{
    if (r == NULL) r = creerNoeudOp(op);
    insererGaucheOp(r, op);

    return r;
}

noeud *insererDroit(noeud *r, int val)  // on ne va insérer que des valeures à droite 
{

}


void free_arbre(noeud *r)
{
    if (r == NULL) return;
    free_arbre(r->noeudGauche);
    free_arbre(r->noeudDroit);
    free(r);
}

int remplirArbre(noeud *r, char **argv, int tailleCalcul)
{
    int i = 0, nb1 = 0, nb2 = 0;
    char op = '\0';

    for (int i=0; i<tailleCalcul; i++)
    {
        char lu = argv[1][i];
        switch (lu)
        {
            case '+':
                r = insererGaucheOp(r, lu);     // insère l'opérateur à gauche
                break;
            case '-':
                r = insererGaucheOp(r, lu);    // insère l'opérateur à gauche
                break;
            default: 
                break;
        }
    }
}
