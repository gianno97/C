#include <stdio.h>

typedef struct albero_rn
{
    nodo_albero_bin_rn_t *radice;
    nodo_albero_bin_rn_t *sent_p;
} albero_rn_t;

nodo_albero_bin_rn_t *ROOT;
nodo_albero_bin_rn_t *NILL;

albero_rn_t* nuovo_albero_rn();
nodo_albero_bin_rn_t* nuovo_nodo_albero(int valore);

int main(int argc, char **argv)
{
    //albero_rn_t *t = nuovo_albero_rn();
    
    /*
    nodo_albero_bin_rn_t *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
    a = nuovo_nodo_albero(10);
    b = nuovo_nodo_albero(20);
    c = nuovo_nodo_albero(30);
    d = nuovo_nodo_albero(100);
    e = nuovo_nodo_albero(90);
    f = nuovo_nodo_albero(40);
    g = nuovo_nodo_albero(50);
    h = nuovo_nodo_albero(60);
    i = nuovo_nodo_albero(70);
    j = nuovo_nodo_albero(80);
    k = nuovo_nodo_albero(150);
    l = nuovo_nodo_albero(110);
    m = nuovo_nodo_albero(120);
    */
    
    return 0;
}

nodo_albero_bin_rn_t* nuovo_nodo_albero(int valore)
{
    nodo_albero_bin_rn_t* n = malloc(sizeof(nodo_albero_bin_rn_t));
    n->sx_p = NULL;
    n->dx_p = NULL;
    n->padre_p = NULL;
    n->valore = valore;
    n->colore = rosso;

    return n;
}

albero_rn_t* nuovo_albero_rn()
{
    albero_rn_t *t = malloc(sizeof(albero_rn_t));
    nodo_albero_bin_rn_t *sent_p_node = malloc(sizeof(nodo_albero_bin_rn_t));
    sent_p_node->sx_p = NULL;
    sent_p_node->dx_p = NULL;
    sent_p_node->padre_p = NULL;
    sent_p_node->colore = nero;
    sent_p_node->valore = 0;
    t->sent_p = sent_p_node;
    t->radice = t->sent_p;

    return t;
}
