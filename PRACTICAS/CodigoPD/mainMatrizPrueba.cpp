#include "matrizTemplate.h"


struct casilla{
    int a;
    int b;
};

int main(){
 
    system ("clear");
 
    Matriz<double> a(3,3);
 
    int i, rows, cols;
 
    double **m;
 
    rows = 3;
 
    cols = 3;
 
    m = new double *[rows];
 
    for(i = 0; i< rows; i++){
 
        m[i] = new double [cols];
 
    }
 
    m[0][0] = 1, m[0][1] = 2, m[0][2] = 3,
    m[1][0] = 4, m[1][1] = 5, m[1][2] = 6,
    m[2][0] = 7, m[2][1] = 8, m[2][2] = 9;
 
    a.initMatriz(m);

 
    cout << "Imprime el objeto a:\n\n" << a;
    
    

    return 0;
 
}