
#include <iostream>
#include <chrono> // Para medición de tiempos de ejecución
#include <limits>
using namespace std;

#define K 2

// Estructura para representar un punto 2D
struct Punto {
    int v[K];
};


/*
Determina si el punto p2 es dominado por el punto p1 (devuelve true), o no (devuelve false)
*/
bool EsDominado(const Punto p1, const Punto p2) {

    int domP1= 0, domP2= 0; // Para saber cuántas componentes de p1 y p2 se dominan entre sí

    for (int i= 0; i<K; i++) {
        
        if (p1.v[i] > p2.v[i]) domP1++;
        else if (p1.v[i] < p2.v[i]) domP2++;
    }

    if (domP1 > 0 && domP2 == 0) return true; // P1 domina a P2
    return false;
}


/* 
    Función para leer el dataset desde entrada por línea de comandos
    Se pide introducir por teclado:
     * n (el número de puntos)
     * x1 y1 (primer punto)
     * x2 y2 (segundo punto)
     * ...
     * xn yn (n-ésimo punto)
    Como salida, devuelve por referencia "n" y el array "cPuntos" creado con memoria dinámica
    Será responsabilidad del programador liberar cPuntos
*/
void LeerDatos(int &n, Punto * &cPuntos) {

    // Lectura del número de puntos
    cin>>n; 
    if (n<=0) {
        cPuntos= 0;
        return;
    }

    // Reserva de memoria
    cPuntos= new Punto[n];

    // Lectura de todos los puntos
    for (int i= 0; i<n; i++) {
        for (int j= 0; j<K; j++) {
            cin>> cPuntos[i].v[j];
        }
        
    }
}






//////////////////////////////
// SOLUCIÓN BÁSICO
//////////////////////////////

/*
    Calcula el conjunto de puntos no dominados del array de puntos "puntos", para los índices puntos[ini...fin-1]
    Devuelve la lista de no dominados en "solucion", de tam. "tamSol"
*/
void BASICO(const Punto * puntos, const int ini, const int fin, int *solucion, int &tamSol) {

    bool dominado;

    tamSol= 0;

    for (int i= ini; i<fin; i++) { // Comprobamos si i es dominado por alguno del resto de puntos

        dominado= false; // Suponemos que no es dominado por ninguno de los demás puntos

        for (int j= ini; j<fin && !dominado; j++) {
            if (i != j) {
                if (EsDominado(puntos[j], puntos[i])) {
                    dominado= true;
                }
            }
        }

        if (!dominado) { // Si no es dominado por ninguno, lo añadimos a solución
            solucion[tamSol]= i;
            tamSol++;
        }
    }
}




//////////////////////////////
// SOLUCIÓN DyV
//////////////////////////////

void fusionar(const Punto * puntos, const int * S1, const int tamS1, const int * S2, const int tamS2, 
             int *solucion, int &tamSol) {

    bool dominado;
    int topeS1;
    tamSol= 0;

    // Comprobamos si los puntos de S1 son dominados por alguno de S2
    for (int i= 0; i<tamS1; i++) {
        dominado= false;
        for (int j= 0; j<tamS2 && !dominado; j++) {
            if (EsDominado(puntos[S2[j]], puntos[S1[i]])) {
                dominado= true;
            }
        }

        if (!dominado) { // El punto i no es dominado, lo pasamos a la solución
            solucion[tamSol]= S1[i];
            tamSol++;
        }
    }


    // Comprobamos si los puntos de S2 son dominados por alguno de S1 no dominado
    topeS1= tamSol;
    for (int i= 0; i<tamS2; i++) {
        dominado= false;
        for (int j= 0; j<topeS1 && !dominado; j++) {
            if (EsDominado(puntos[solucion[j]], puntos[S2[i]])) {
                dominado= true;
            }
        }

        if (!dominado) { // El punto i no es dominado, lo pasamos a la solución
            solucion[tamSol]= S2[i];
            tamSol++;
        }
    }

}


void DyV(const Punto * puntos, const int ini, const int fin, int *solucion, int &tamSol) {

    int centro;
    int *S1, *S2, tamS1, tamS2; // Para crear las subsoluciones

    // Si estamos en el caso base, resolvemos con el algoritmo básico
    if (fin-ini<=2) {
        BASICO(puntos, ini, fin, solucion, tamSol);

    } else { // Caso general

        // División del problema en subproblemas: P1 (Una mitad de los puntos)) y P2 (otra mitad)
        centro= (ini+fin)/2; // Dividimos el problema por la mitad


        // Reservamos memoria para subsoluciones
        // OJO: ESTO ES INEFICIENTE PORQUE SE HACE RESERVA Y LIBERACIÓN DE MEMORIA EN CADA LLAMADA.
        // LA MEJOR ALTERNATIVA ES PASAR ESTOS ARRAYS AUXILIARES COMO ARGUMENTOS DE LA FUNCIÓN, O
        // PONERLOS COMO VARIABLES GLOBALES Y HACER LA RESERVA AL PRINCIPIO DEL PROGRAMA.
        // No obstante, se deja así en este código por claridad a la hora de entender la implementación
        S1= new int[fin-ini];
        S2= new int[fin-ini];

        
        // Resolvemos cada subproblema por separado
        DyV(puntos, ini, centro, S1, tamS1);
        DyV(puntos, centro, fin, S2, tamS2); 

        // Combinamos las soluciones: Calculamos los no dominados entre todos los puntos de las soluciones
        fusionar(puntos, S1, tamS1, S2, tamS2, solucion, tamSol);

        // Liberar recursos de memoria
        delete [] S1;
        delete [] S2;
    }
}




int main() {

    int n; // Número de puntos
    Punto *cPuntos; // Array para almacenar un conjunto de n puntos
    int *solucionBasico; // Array para almacenar la solución del método básico
    int *solucionDyV; // Array para almacenar la solución del método DyV
    int tamSolBasico= 0, tamSolDyV= 0; // Tam. de los arrays de solución de básico y DyV
    chrono::time_point<chrono::high_resolution_clock> tBasico0, tBasicof; // Para medir el tiempo de ejecución
    chrono::time_point<chrono::high_resolution_clock> tDyV0, tDyVf; // Para medir el tiempo de ejecución
    double tEjecBasico, tEjecDyV; // Tiempos de ejecución de algoritmos básico y DyV


    // Lectura de los datos
    LeerDatos(n, cPuntos);
    if (cPuntos == 0) return 0; // Salimos si error

    // Reserva de memoria para soluciones
    solucionBasico= new int[n];
    solucionDyV= new int[n];


    // Resolución del problema con el método básico
    tBasico0= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
    BASICO(cPuntos, 0, n, solucionBasico, tamSolBasico);
    tBasicof= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que termina la ejecución del algoritmo

    


    // Resolución del problema con DyV
    tDyV0= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
    DyV(cPuntos, 0, n, solucionDyV, tamSolDyV);
    tDyVf= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que termina la ejecución del algoritmo


    // Mostramos soluciones por pantalla
    tEjecBasico= chrono::duration_cast<std::chrono::milliseconds>(tBasicof - tBasico0).count();
    tEjecDyV= chrono::duration_cast<std::chrono::microseconds>(tDyVf - tDyV0).count();
    
    cerr <<"El algoritmo básico tarda "<<tEjecBasico<<" ms en dar la solución con "<<tamSolBasico<<" puntos:"<< endl;
    for (int i= 0; i<tamSolBasico; i++) {
        for (int j= 0; j<K; j++) {
            cerr <<cPuntos[solucionBasico[i]].v[j]<<" ";
        }
        cerr<<endl;
    }

    cerr <<"El algoritmo DyV tarda "<<tEjecDyV<<" us en dar la solución con "<<tamSolDyV<<" puntos:"<< endl;
    for (int i= 0; i<tamSolDyV; i++) {
        for (int j= 0; j<K; j++) {
            cerr <<cPuntos[solucionDyV[i]].v[j]<<" ";
        }
        cerr<<endl;
    }    





    // Liberación de memoria
    delete [] cPuntos; 
    delete [] solucionBasico; 
    delete [] solucionDyV; 


    return 0;
}