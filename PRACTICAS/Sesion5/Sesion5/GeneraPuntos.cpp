// Programa auxiliar para generar puntos 2D ordenados por si componente x
#include <iostream>
using namespace std;

// Estructura para representar un punto 2D
typedef struct {
    int x, y;
} Punto;



/*
 El programa tiene un entero como entrada por parámetros, que se corresponde con n
 El programa genera un conjunto de n puntos 2D ordenados por su componente x
 Da como salida por pantalla:
     * n (el número de puntos)
     * x1 y1 (primer punto)
     * x2 y2 (segundo punto)
     * ...
     * xn yn (n-ésimo punto)
*/
int main(int argc, char *argv[]) {

    int n;
    Punto *cPuntos;

    if (argc != 2) {
        cerr<<"Se debe proporcionar un entero como argumento\n";
        return 0;
    }

    // Cogemos primer parámetro y lo pasamos a entero
    n= atoi(argv[1]);
    if (n<=0) {
        cerr<<"El entero dado como argumento debe ser positivo\n";
        return 0;
    }
    
    // Generamos n puntos aleatorios en (0, 10000) 
    cerr << "Generación del dataset\n";
    srand(time(0));
    cPuntos= new Punto[n];
    for (int i= 0; i<n; i++) {
        cPuntos[i].x= rand()%n;
        cPuntos[i].y= rand()%n;
    }


    // Mostramos el dataset por consola
    cout<<n<<endl;
    for (int i= 0; i<n; i++) {
        cout<< cPuntos[i].x<<" "<<cPuntos[i].y<<endl;
    }
    cerr<<"Fin\n";

    // Liberación de memoria 
    delete [] cPuntos;

    return 0;
}