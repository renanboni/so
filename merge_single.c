//
//  main.c
//  ArquiteturaEP2
//
//  Created by Bruno Rogacheski on 02/12/16.
//  Copyright © 2016 Bruno Rogacheski. All rights reserved.
//
//  Arquitetura EP2 - EACH USP  - Clodoaldo A. M. Lima
//  Bruno Rogacheski - nUSP 7651479
//  9 de Outubro de 2016
//

#include <stdio.h>
#include <omp.h>
void merging(int low, int mid, int high,int *vetorR, int *lastResult) {
    int l1, l2, i;
    
    for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
        if(vetorR[l1] <= vetorR[l2])
            lastResult[i] = vetorR[l1++];
        else
            lastResult[i] = vetorR[l2++];
    }
    
    while(l1 <= mid)
        lastResult[i++] = vetorR[l1++];
    
    while(l2 <= high)
        lastResult[i++] = vetorR[l2++];
    
    for(i = low; i <= high; i++)
        vetorR[i] = lastResult[i];
    
    return;
}


void sort(int low, int high,int *vetorR, int *lastResult) {
    int mid;
    if(low < high) {
        mid = (low + high) / 2;

        sort(low, mid, vetorR, lastResult);
        sort(mid+1, high, vetorR, lastResult);
        merging(low, mid, high, vetorR, lastResult);
    } else {
        return;
    }
}


int * concatena(int tam1, int *vetor1, int tam2, int *vetor2) {
    
    int  result[tam1+tam2];
    int  lastResult[tam1+tam2];
    int i=0, j=0, k=0;
    
    while(i < tam1) {
        result[k] = vetor1[i];
        i = i + 1;
        k = k + 1;
    }
    
    while(j < tam2) {
        result[k] = vetor2[j];
        j = j + 1;
        k = k + 1;
    }
    
    k = 0;
    
    sort(k,(tam1+tam2 - 1), result, lastResult);
    
    return lastResult;
}

/* main function to call above defined function */
int main (int argc, char **argv) {
    
    //Array1.txt
    //Array2.txt
    //Resultado.txt
    
    FILE *file = fopen(argv[1], "r");
    int array1[5000];
    
    FILE *fileR = fopen(argv[3], "w");
    int *r;
    int h;
    
    int i=0;
    int num;
    while(fscanf(file, "%d", &num) > 0) {
        array1[i] = num;
        i++;
    }
    fclose(file);
    
    file = fopen(argv[2], "r");
    int array2[5000];
    
    int j=0;
    int num2;
    while(fscanf(file, "%d", &num2) > 0) {
        array2[j] = num2;
        j++;
    }
    fclose(file);
    
    r = concatena(i,array1,j,array2);
    
    int anterior = 0;
    
    for ( h = 0; h < (i+j); h++ ) {
        if(r[h] == anterior) {
            
        } else {
            fprintf(fileR, "%d\n", r[h]);
        }
        anterior = r[h];
    }
    fclose(file);
    
    return 0;
}


