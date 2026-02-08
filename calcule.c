#include <stdio.h>
#include <stdlib.h> 
#include <assert.h>
#include <stdbool.h>

// Faire des fonctions pour insérer des noeuds directement. Creer des noeuds en fct de val ou op. 

// ######################################### Déclarations de fonctions ###################################### //
void verifArgs(int args);
int tailleCalculEntree(char *argv[]);
noeud_t *initArbreBinaire();

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
}noeud_t;

typedef struct 
{
    int *priorite;
    noeud_t **termes;

}expression_t;

typedef struct
{
    noeud_t *racine;
    expression_t *exprDroite;
    expression_t *exprGauche;
}racine_t;

/* typedef struct arbre_t
{
    noeud_t *racine;
}arbre; */

// ######################################### Main ###################################### //
int main(int args, char *argv[])
{
    verifArgs(args);
    int tailleCalcul = tailleCalculEntree(argv);
    noeud_t *racine = initArbreBinaire();

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


noeud_t *creerNoeudVal(int val)
{
    noeud_t *n = (noeud*) malloc(sizeof(noeud));
    n->type = VALEUR;
    n->elt.val = val;

    n->noeudDroit = NULL;
    n->noeudGauche = NULL;
    return n;

}

noeud_t *creerNoeudOp(char op)
{
    noeud_t *n = (noeud*) malloc(sizeof(noeud));
    n->type = OPERATEUR;
    n->elt.op = op;

    n->noeudDroit = NULL;
    n->noeudGauche = NULL;
    return n;

}

bool estFeuille(noeud_t *n)
{
    return (n->noeudDroit == NULL && n->noeudGauche == NULL);
}



noeud_t *insererGaucheVal(noeud_t *r, int val)  // besoin pour le dernier noeud opérateur.
{   
    
}

noeud_t *insererGaucheOp(noeud_t *r, char op)   // On insère tous les opérateurs à gauche jusqu'à la fin de l'arbre ou le dernier opérateur aura 2 enfants valeures
{
    if (r == NULL) r = creerNoeudOp(op);
    insererGaucheOp(r, op);

    return r;
}

noeud_t *insererDroit(noeud_t *r, int val)  // on ne va insérer que des valeures à droite 
{

}


void free_arbre(noeud_t *r)
{
    if (r == NULL) return;
    free_arbre(r->noeudGauche);
    free_arbre(r->noeudDroit);
    free(r);
}

expression_t *creerExpression(char **argv, int tailleCalcul)
{
    bool estDansPar = 0;
    noeud_t * noeud;
    
    expression_t *e = (expression_t*) malloc(sizeof(expression));
    e->termes = (noeud_t **) malloc(tailleCalcul*sizeof(noeud*));
    e->priorite = (int*) malloc(tailleCalcul*sizeof(int));


    for (int i=0; i<tailleCalcul; i++)
    {
        char lu = argv[1][i];
        switch(lu)
        {
            case '+':
            case '-':
                noeud = creerNoeudOp(lu);
                if (estDansPar) e->priorite[i] = 2;
                else e->priorite[i] = 0;
                break;
            case '*':
            case 'x':
            case '/':
            case ':':
                noeud = creerNoeudOp(lu);
                if (estDansPar) e->priorite[i] = 2;
                else e->priorite[i] = 1;
                break;
            case '(':
                estDansPar = 1;
                break;
            case ')':
                estDansPar = 0;
                break;
            default:
                noeud = creerNoeudVal((lu-'0'));
                break;
        }
        e->termes[i] = noeud;
    }
    return e;
}


racine_t *trouverRacine(expression_t *e, tailleCalcul)
{
    racine_t *rt = (racine*)malloc(sizeof(racine_t));

    int min = 100, indiceRacine = -1;   // On ne mets pas priorite[0] au cas ou le calcul commence par une parenthèse
    for (int i=0; i<tailleCalcul; i++)
    {
        if (e->termes[i]->type == OPERATEUR)
        {
            if (e->priorite[i] < min)
            {
                min = e->priorite[i];
                rt->racine = e->termes[i];
                indiceRacine = i;
            }
        }
    }
    rt->exprGauche = malloc(indiceRacine*sizeof(expression_t));
    rt->exprDroite = malloc((tailleCalcul-indiceRacine)*sizeof(expression_t));

    for (int i=0; i<indiceRacine; i++)
        rt->exprGauche[i] = e->termes[i];
    
    for (int i = indiceRacine+1; i<tailleCalcul; i++)
    {
        int k = i - (indiceRacine+1);    // 0, 1, 2...
        rt->exprDroite[k] = e->termes[i];
    }
    return rt;
}


void construireArbre(racine_t *rt, expression_t *expression)
{
    racine = trouverRacine(expression)
    noeud *racineGauche = trouverRacine(rt->exprGauche);
    noeud *racineDroite = trouverRacine(rt->exprDroite);
    racine->noeudGauche = racineGauche;
    racine->noeudDroit = racineDroite;


}
