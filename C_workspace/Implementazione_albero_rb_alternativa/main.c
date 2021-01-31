#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <float.h>
#include <time.h>

typedef enum {rosso, nero} colore_t;

typedef struct nodo_albero_bin_rn
{
    int valore;
    colore_t colore;
    struct nodo_albero_bin_rn *sx_p, *dx_p, *padre_p;
} nodo_albero_bin_rn_t;

//int inserisci_in_albero_rn(nodo_albero_bin_rn_t *nodo);
nodo_albero_bin_rn_t* grandparent(nodo_albero_bin_rn_t *n);
nodo_albero_bin_rn_t* uncle(nodo_albero_bin_rn_t *n);
int insert_case1(nodo_albero_bin_rn_t *n);
void insert_case2(nodo_albero_bin_rn_t *n);
void insert_case3(nodo_albero_bin_rn_t *n);
void insert_case4(nodo_albero_bin_rn_t *n);
void insert_case5(nodo_albero_bin_rn_t *n);
void rotate_right(nodo_albero_bin_rn_t *sent_p, nodo_albero_bin_rn_t *y_p);
void rotate_left(nodo_albero_bin_rn_t *sent_p, nodo_albero_bin_rn_t *x_p);

int main(int argc, char **argv)
{
    nodo_albero_bin_rn_t *sent_p = (nodo_albero_bin_rn_t *)malloc(sizeof(nodo_albero_bin_rn_t));
    sent_p->sx_p = NULL;
    sent_p->dx_p = NULL;
    sent_p->padre_p = NULL;
    sent_p->colore = nero;
    sent_p->valore = 0;
    
    return 0;
}

nodo_albero_bin_rn_t* grandparent(nodo_albero_bin_rn_t *n)
{
    return n->padre_p->padre_p;
}

nodo_albero_bin_rn_t* uncle(nodo_albero_bin_rn_t *n)
{
    if (n->padre_p == grandparent(n)->sx_p)
        return grandparent(n)->dx_p;
    else
        return grandparent(n)->sx_p;
}

int insert_case1(nodo_albero_bin_rn_t *n)
{
    int inserito;
    
    if (n->padre_p == NULL)
    {
        n->colore = nero;
        inserito = 1; 
    }
    else
        insert_case2(n);
    
    return inserito;
}

void insert_case2(nodo_albero_bin_rn_t *n)
{
    if (n->padre_p->colore == nero)
        /* Tree is still valid */
        printf("L'albero è ancora valido");
    else
        insert_case3(n);
}

void insert_case3(nodo_albero_bin_rn_t *n)
{
    if (uncle(n) != NULL && uncle(n)->colore == rosso) {
        n->padre_p->colore = nero;
        uncle(n)->colore = nero;
        grandparent(n)->colore = rosso;
        insert_case1(grandparent(n));
    }
    else
        insert_case4(n);
}

void insert_case4(nodo_albero_bin_rn_t *n)
{
    if (n == n->padre_p->dx_p && n->padre_p == grandparent(n)->sx_p) {
        rotate_left(sent_p, n->padre_p);
        n = n->sx_p;
    } else if (n == n->padre_p->sx_p && n->padre_p == grandparent(n)->dx_p) {
        rotate_right(sent_p, n->padre_p);
        n = n->dx_p;
    }
        insert_case5(n);
}

void insert_case5(nodo_albero_bin_rn_t *n)
{
    n->padre_p->colore = nero;
    grandparent(n)->colore = rosso;
    if (n == n->padre_p->sx_p && n->padre_p == grandparent(n)->sx_p) {
        rotate_right(sent_p, grandparent(n));
    } else {
        /* Here, n == n->parent->right && n->parent == grandparent(n)->right */
        rotate_left(sent_p, grandparent(n));
    }
}

void rotate_right(nodo_albero_bin_rn_t *sent_p, nodo_albero_bin_rn_t *y_p)
{
    nodo_albero_bin_rn_t *x_p;
    
    x_p = y_p->sx_p;
    y_p->sx_p = x_p->dx_p;
    x_p->dx_p->padre_p = y_p;
    x_p->padre_p = y_p->padre_p;
    
    if(y_p == sent_p->dx_p)
        sent_p->dx_p = sent_p->sx_p = x_p;
    else
        if(y_p == y_p->padre_p->dx_p)
            y_p->padre_p->dx_p = x_p;
        else
            y_p->padre_p->sx_p = x_p;
            
    x_p->dx_p = y_p;
    y_p->padre_p = x_p;
}

void rotate_left(nodo_albero_bin_rn_t *sent_p, nodo_albero_bin_rn_t *x_p)
{
    nodo_albero_bin_rn_t *y_p;
    
    y_p = x_p->dx_p;
    x_p->dx_p = y_p->sx_p;
    y_p->sx_p->padre_p = x_p;
    y_p->padre_p = x_p->padre_p;
    
    if(x_p == sent_p->sx_p)
        sent_p->sx_p = sent_p->dx_p = y_p;
    else
        if(x_p == x_p->padre_p->sx_p)
            x_p->padre_p->sx_p = y_p;
        else
            x_p->padre_p->dx_p = y_p;

    y_p->sx_p = x_p;
    x_p->padre_p = y_p;
}

/*
int inserisci_in_albero_rn(nodo_albero_bin_rn_t *n)
{
    if (n->padre_p == NULL)
        n->colore = nero;
    else
        if (n->padre_p->colore == nero)
            return;*/ /* Tree is still valid */ /*
        else
            if (uncle(n) != NULL && uncle(n)->colore == rosso) {
                n->padre_p->colore = nero;
                uncle(n)->colore = nero;
                grandparent(n)->colore = rosso;
                insert_case1(grandparent(n));
            }
            else
                if (n == n->parent->right && n->parent == grandparent(n)->left) {
                    rotate_left(n->parent);
                    n = n->left;
                } else if (n == n->parent->left && n->parent == grandparent(n)->right) {
                    rotate_right(n->parent);
                    n = n->right;
                }
                    n->parent->color = BLACK;
                    grandparent(n)->color = RED;
                    if (n == n->parent->left && n->parent == grandparent(n)->left) {
                        rotate_right(grandparent(n));
                    } else {*/
                        /* Here, n == n->parent->right && n->parent == grandparent(n)->right */
                        /*
                        rotate_left(grandparent(n));
                    }
}*/