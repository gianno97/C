#include <stdio.h>

#define MAXINPUT 100

int main(int argc, char **argv)
{
    int insieme_finito_num_naturali[10] = {0};
    int prima_relazione_binaria[10] = {0};
    int seconda_relazione_binaria[10] = {0};
    int numero_acquisito, i;
    int contatore_numeri_insieme = 0;
    int contatore_coppie_relazioni_binarie = 0;
    int j, k;
    int array_composizione[100] = {0};
    int array_diff_simm[100] = {0};
    int contatore_esterno = 0;
    int contatore_interno = 0;
    int contatore_prima_rel_bin = 1;
    int contatore_seconda_rel_bin = 0;
    int contatore_elem_coppia_comp = 0;
    int a, b;
    int contatore_esterno_diff = 0;
    int contatore_interno_diff = 0;
    int contatore_prima_rel_bin_diff_simm = 0;
    int contatore_seconda_rel_bin_diff_simm = 0;
    int contatore_array_diff_simm = 0;
    int cat[n];
    int n;
    
    /*Dichiarazione variabili per la validazione dell'input*/
    char input[MAXINPUT] = "";
    int contatore_str_input = 0;
    int numero = 0;
    
    printf("Digita uno alla volta i numeri di un insieme finito di numeri naturali{0, 1, 2, 3, 4...}:\n");
    /*while(contatore_numeri_insieme < 10){
        scanf("%d", &numero_acquisito);
        insieme_finito_num_naturali[contatore_numeri_insieme] = numero_acquisito;
        contatore_numeri_insieme++;
    }*/
    
    
    printf("Insieme acquisito da tastiera:\n");
    for(i = 0; i < 10; i++)
        printf("%d ", insieme_finito_num_naturali[i]);
        
    printf("\n");
    
    printf("Digita due relazioni binarie sull'insieme acquisito da tastiera.\n");
    printf("Digita la prima relazione binaria:\n");
    printf("Digita i due numeri della coppia:\n");
    
    while(contatore_coppie_relazioni_binarie < 10){
        scanf("%d %d", &prima_relazione_binaria[contatore_coppie_relazioni_binarie], &prima_relazione_binaria[contatore_coppie_relazioni_binarie+1]);
        contatore_coppie_relazioni_binarie += 2;
    }
    contatore_coppie_relazioni_binarie = 0;
    printf("Prima relazione binaria acquisita!\n");
    
    printf("Digita la seconda relazione binaria:\n");
    printf("Digita i due numeri della coppia:\n");
    while(contatore_coppie_relazioni_binarie < 10){
        scanf("%d %d", &seconda_relazione_binaria[contatore_coppie_relazioni_binarie], &seconda_relazione_binaria[contatore_coppie_relazioni_binarie+1]);
        contatore_coppie_relazioni_binarie += 2;
    }
    printf("Seconda relazione binaria acquisita!\n");
    
    printf("Prima relazione binaria:\n");
    for(j = 0; j < 10; j += 2)
        printf("%d,%d ", prima_relazione_binaria[j], prima_relazione_binaria[j+1]);
    printf("\n");
    
    printf("Seconda relazione binaria:\n");
    for(k = 0; k < 10; k += 2)
        printf("%d,%d ", seconda_relazione_binaria[k], seconda_relazione_binaria[k+1]);
    printf("\n");
    
    /*Composizione*/
    while(contatore_esterno < 5){
        while(contatore_interno < 5){
            if(prima_relazione_binaria[contatore_prima_rel_bin] == seconda_relazione_binaria[contatore_seconda_rel_bin]){
                array_composizione[contatore_elem_coppia_comp] = prima_relazione_binaria[contatore_prima_rel_bin-1];
                contatore_elem_coppia_comp++;
                array_composizione[contatore_elem_coppia_comp] = seconda_relazione_binaria[contatore_seconda_rel_bin+1];
                contatore_elem_coppia_comp++;
            }
            contatore_seconda_rel_bin += 2;
            contatore_interno++;
        }
        contatore_esterno++;
        contatore_interno = 0;
        contatore_seconda_rel_bin = 0;
        contatore_prima_rel_bin += 2;
    }
    
    printf("Composizione:\n");
    for(a = 0; a < 50; a += 2)
        printf("%d,%d ", array_composizione[a], array_composizione[a+1]);
    printf("\n");
    
    /*Differenza simmetrica*/
    while(contatore_esterno_diff < 10){
        if(contatore_esterno_diff < 5){
            while(contatore_interno_diff < 5){
                if((prima_relazione_binaria[contatore_prima_rel_bin_diff_simm] == seconda_relazione_binaria[contatore_seconda_rel_bin_diff_simm]) && 
                   (prima_relazione_binaria[contatore_prima_rel_bin_diff_simm+1] == seconda_relazione_binaria[contatore_seconda_rel_bin_diff_simm+1])){
                    contatore_interno_diff = 5;
                }
                else{
                    contatore_interno_diff++;
                    contatore_seconda_rel_bin_diff_simm += 2;
                    if(contatore_interno_diff == 5){
                        array_diff_simm[contatore_array_diff_simm] = prima_relazione_binaria[contatore_prima_rel_bin_diff_simm];
                        contatore_array_diff_simm++;
                        array_diff_simm[contatore_array_diff_simm] = prima_relazione_binaria[contatore_prima_rel_bin_diff_simm+1];
                        contatore_array_diff_simm++;
                    }
                }
            }
            contatore_prima_rel_bin_diff_simm += 2;
            contatore_seconda_rel_bin_diff_simm = 0;
            contatore_interno_diff = 0;
            contatore_esterno_diff++;
        }
        else{
            contatore_prima_rel_bin_diff_simm = 0;
            while(contatore_interno_diff < 5){
                if((seconda_relazione_binaria[contatore_seconda_rel_bin_diff_simm] == prima_relazione_binaria[contatore_prima_rel_bin_diff_simm]) && 
                   (seconda_relazione_binaria[contatore_seconda_rel_bin_diff_simm+1] == prima_relazione_binaria[contatore_prima_rel_bin_diff_simm+1])){
                    contatore_interno_diff = 5;
                }
                else{
                    contatore_interno_diff++;
                    contatore_prima_rel_bin_diff_simm += 2;
                    if(contatore_interno_diff == 5){
                        array_diff_simm[contatore_array_diff_simm] = seconda_relazione_binaria[contatore_seconda_rel_bin_diff_simm];
                        contatore_array_diff_simm++;
                        array_diff_simm[contatore_array_diff_simm] = seconda_relazione_binaria[contatore_seconda_rel_bin_diff_simm+1];
                        contatore_array_diff_simm++;
                    }
                }
            }
            contatore_prima_rel_bin_diff_simm = 0;
            contatore_seconda_rel_bin_diff_simm += 2;
            contatore_interno_diff = 0;
            contatore_esterno_diff++;
        }
    }
    
    printf("Differenza simmetrica:\n");
    for(b = 0; b < 50; b += 2)
        printf("%d,%d ", array_diff_simm[b], array_diff_simm[b+1]);
    printf("\n");
    
    return 0;
}
