#include <stdio.h>
#include <stdlib.h> 
#include <assert.h>
#include <stdbool.h>

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


// ######################################### Déclarations de fonctions ###################################### //
void verifArgs(int args);
int tailleCalculEntree(char *argv[]);
expression_t *creerExpression(char **argv, int tailleCalcul);
noeud_t *construireArbre(expression_t *e, int taille);
int calculerArbre(noeud_t *racine);
void afficherResultat(char *expressionInit, int res);
void free_arbre(noeud_t *r);
void free_expr(expression_t *expr);


// ######################################### Main ###################################### //
int main(int args, char *argv[])
{
    verifArgs(args);
    int tailleCalcul = tailleCalculEntree(argv);

    expression_t *expr = creerExpression(argv, tailleCalcul);
    assert(expr != NULL);

    noeud_t *racine = construireArbre(expr, tailleCalcul);
    assert(racine != NULL);

    int resultat = calculerArbre(racine);
    afficherResultat(argv[1], resultat);

    free_arbre(racine);
    free_expr(expr);

    return 0;
}

// ######################################### Fonctions ###################################### //

void verifArgs(int args)
{
    if (args < 2)
    {
        printf("Pas assez d'argument, donnez en argument un calcul (ex : ./calcul 3+2*4)\n");
        exit(1);
    }

    if (args > 2)
    {
        printf("Trop d'arguments, ne donnez qu'un seul calcul en argument (ex : ./calcul 3+2*4)\n");
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
    noeud_t *n = (noeud_t*) malloc(sizeof(noeud_t));
    n->type = VALEUR;
    n->elt.val = val;

    n->noeudDroit = NULL;
    n->noeudGauche = NULL;
    return n;

}

noeud_t *creerNoeudOp(char op)
{
    noeud_t *n = (noeud_t*) malloc(sizeof(noeud_t));
    n->type = OPERATEUR;
    n->elt.op = op;

    n->noeudDroit = NULL;
    n->noeudGauche = NULL;
    return n;

}

expression_t *creerExpression(char **argv, int tailleCalcul)
{
    bool estDansPar = 0;
    noeud_t * noeud;
    
    expression_t *e = (expression_t*) malloc(sizeof(expression_t));
    e->termes = (noeud_t **) malloc(tailleCalcul*sizeof(noeud_t*));
    e->priorite = (int*) malloc(tailleCalcul*sizeof(int));

    assert(e != NULL && e->termes != NULL && e->priorite != NULL);

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


int trouverRacineIndice(expression_t *e, int tailleCalcul)
{
    racine_t *rt = (racine_t*)malloc(sizeof(racine_t));
    assert(rt!=NULL);

    int min = 1000, indiceRacine = -1;   // On ne mets pas priorite[0] au cas ou le calcul commence par une parenthèse
    for (int i=0; i<tailleCalcul; i++)
    {
        if (e->termes[i]->type == OPERATEUR)
        {
            if (e->priorite[i] <= min)
            {
                min = e->priorite[i];
                rt->racine = e->termes[i];
                indiceRacine = i;
            }
        }
    }
    return indiceRacine;
}


expression_t *sousExpression(expression_t *e, int debut, int fin)
{
    int taille = fin-debut;
    expression_t *nvE = (expression_t *) malloc(sizeof(expression_t));

    for (int i=0; i<taille; i++)
    {
        nvE->termes = malloc(taille * sizeof(noeud_t *));
        nvE->priorite = malloc(taille * sizeof(int));

        for (int i = 0; i < taille; i++)
        {
            nvE->termes[i] = e->termes[debut + i];
            nvE->priorite[i] = e->priorite[debut + i];
        }
    }
    return nvE;
}

noeud_t *construireArbre(expression_t *e, int taille)
{

    if (taille == 1)
        return e->termes[0];

    int indice = trouverRacineIndice(e, taille);
    assert(indice != -1);

    noeud_t *racine = e->termes[indice];

    expression_t *gauche = sousExpression(e, 0, indice);

    expression_t *droite = sousExpression(e, indice+1, taille);

    racine->noeudGauche = construireArbre(gauche, indice);
    racine->noeudDroit = construireArbre(droite, taille-indice-1);

    return racine;
}

int calculerArbre(noeud_t *racine)
{

    if (racine->type == VALEUR)
    {
        return racine->elt.val;
    }
    else
    {   
        int gauche = calculerArbre(racine->noeudGauche);
        int droite = calculerArbre(racine->noeudDroit);

        switch(racine->elt.op)
        {

            case '+':
                return gauche + droite;
                break;
            case '-':
                return gauche - droite;
                break;
            case '*':
            case 'x':
                return gauche * droite;
                break;
            case '/':
            case ':':
                assert(droite != 0);
                return gauche / droite;
                break;
            default:
                printf("Erreur sur l'opérateur : %c\n", racine->elt.op);
                exit(1);
        
        }
    }
}


void afficherResultat(char *eInit, int res)
{
    printf("%s = %d\n", eInit, res);
}


void free_arbre(noeud_t *r)
{
    if (r == NULL) return;
    free_arbre(r->noeudGauche);
    free_arbre(r->noeudDroit);
    free(r);
}

void free_expr(expression_t *expr)
{
    free(expr->termes);
    free(expr->priorite);
    free(expr);
}
