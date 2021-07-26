#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("hello world\n");
    return 0;
}

vertice_grafo_t *avvia_ord_top_grafo(vertice_grafo_t *grafo_p)
{
    vertice_grafo_t *testa_p,
                    *vertice_p;

    for (vertice_p = grafo_p;
         (vertice_p != NULL);
         vertice_p = vertice_p->vertice_succ_p)
        vertice_p->colore = bianco;
    for (vertice_p = grafo_p, testa_p = NULL;
         (vertice_p != NULL);
         vertice_p = vertice_p->vertice_succ_p)
        if (vertice_p->colore == bianco)
            ordina_top_grafo(vertice_p,
                             &testa_p);
    return(testa_p);
}



void ordina_top_grafo(vertice_grafo_t *vertice_p,
                      vertice_grafo_t **testa_p)
{
    arco_grafo_t    *arco_p;
    vertice_grafo_t *nuovo_elem_p;

    vertice_p->colore = grigio;
    for (arco_p = vertice_p->lista_archi_p;
         (arco_p != NULL);
         arco_p = arco_p->arco_succ_p)
        if (arco_p->vertice_adiac_p->colore == bianco)
            ordina_top_grafo(arco_p->vertice_adiac_p,
                             testa_p);
    vertice_p->colore = nero;
    nuovo_elem_p = (vertice_grafo_t *)malloc(sizeof(vertice_grafo_t));
    nuovo_elem_p->valore = vertice_p->valore;
    nuovo_elem_p->lista_archi_p = vertice_p->lista_archi_p;
    nuovo_elem_p->vertice_succ_p = *testa_p;
    *testa_p = nuovo_elem_p;
}
