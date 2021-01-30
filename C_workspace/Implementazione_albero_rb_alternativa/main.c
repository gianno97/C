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

int inserisci_in_albero_rn(nodo_albero_bin_rn_t *nodo);
nodo_albero_bin_rn_t* grandparent(nodo_albero_bin_rn_t *n);
nodo_albero_bin_rn_t* uncle(nodo_albero_bin_rn_t *n);

int main(int argc, char **argv)
{
    
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

int inserisci_in_albero_rn(nodo_albero_bin_rn_t *n)
{
    if (n->padre_p == NULL)
        n->colore = nero;
    else
        if (n->padre_p->colore == nero)
            return; /* Tree is still valid */
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
                    } else {
                        /* Here, n == n->parent->right && n->parent == grandparent(n)->right */
                        rotate_left(grandparent(n));
                    }
}
