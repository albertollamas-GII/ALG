#include <iostream>
 
using namespace std;
 
#include <iomanip>
#include <cstdlib>
 
template<typename T> class Matriz;
template<typename T> ostream& operator<< (ostream &salida, Matriz<T> &z);
 
template <class T>
 
class Matriz {
 
private:
 
    T **a;
    int rows, cols;
 
public:
 
    Matriz(int m, int n);
    void initMatriz(T **x);
 
    friend ostream& operator << <> (ostream &salida, Matriz<T> &z); //sobrecarga del operador <<
 
};
 
//Constructor por parametros
 
template<typename T>
 
Matriz<T>::Matriz(int m , int n){
 
    int i;
 
    rows = m;
 
    cols = n;
 
    a = new T*[rows];
 
    for(i = 0; i< rows; i++){
 
        a[i] = new T[cols];
 
    }
 
}
 
template<typename T>
 
void Matriz<T>::initMatriz(T **x){
 
    int i,j;
 
    for(i=0; i < rows; i++){
 
            for(j=0; j < cols; j++){
 
                a[i][j] = x[i][j]; 
         
        }
    }
     
 
}
 
template<typename T>
 
ostream &operator << (ostream &salida, Matriz<T> &z){//sobrecarga del operador <<
 
    salida.setf(ios::fixed);
    salida.precision(4);    
 
    int i, j;
 
    for (i = 0; i < z.rows; i++) {
 
        for (j = 0; j < z.cols; j++) {
 
            salida << setw(10) << z.a[i][j];
 
        }
 
        salida << "\n";
      
    }
       
    return salida;
 
} 