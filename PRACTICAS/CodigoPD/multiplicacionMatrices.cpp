#include <iostream>
#include <vector>

using namespace std;


int MultiplicacionEncadenada(vector<pair<int,int> > p,int n){

    int **N;
    //Asignación de memoria
    N = new int *[n];
    for (int i = 0; i < n; i++)
        N[i] = new int[n];

    //Caso base
    for (int i = 0; i < n; i++){
        N[i][i] = 0;
    }

    



    //Liberacion de memoria
    for (int i = 0; i < n; i++)
        delete[] N[i];

    delete[] N;
}
int main(){


}