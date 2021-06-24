#include <iostream>

using namespace std;

int Pivotar(double *V, int ini, int fin){

    double aux, pivote = V[ini];
    int i = ini+1, j = fin;
    while (i <= j){
        while (V[i] < pivote && i <= j) i++;
        while (V[j] >= pivote && i <= j) j++;

        aux = V[i]; V[i] = V[j]; V[j] = aux;
    }

    if (ini < j){
        V[ini] = V[j];
        V[j] = pivote;
    }

    return j;
}

void QuickSort(double *V, int ini, int fin){
    if (ini < fin){
        int pospivote = Pivotar(V, ini, fin);
        QuickSort(V, ini, pospivote);
        QuickSort(V, pospivote+1, fin);
    }
}