
#include <iostream>
#include <cmath> // Para sqrt
#include <chrono> // Para medición de tiempos de ejecución

using namespace std;

// Estructura para representar un punto 2D
typedef struct {
    float x, y;
} Punto;


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
        cin>> cPuntos[i].x >> cPuntos[i].y;
    }
}


float distancia(const Punto pi, const Punto pj) {
    float dx, dy;

    dx= (pi.x - pj.x)*(pi.x - pj.x);
    dy= (pi.y - pj.y)*(pi.y - pj.y);
    return sqrt(dx+dy);
}


float distanciaEnX(const Punto pi, const Punto pj) {
    float dx, dy;

    dx= (pi.x - pj.x)*(pi.x - pj.x);
    return sqrt(dx);
}



//////////////////////////////
// SOLUCIÓN BÁSICO
//////////////////////////////



/*
 Algoritmo básico: Compara todos los puntos entre sí. Devuelve los puntos en resul
 */
float BASICO(const Punto *cPuntos, const int ini, const int fin) {

    float S=-1; // Distancia de los puntos más cercanos. Inicializado a -1 indicando infinito
    float dist; // Distancia de los puntos actuales en comparación

    for (int i= ini; i<fin; i++) {
        for (int j= i+1; j<fin; j++) {

            // Cálculo de distancia entre cPuntos[i] y cPuntos[j]
            dist= distancia(cPuntos[i], cPuntos[j]);
            if (S == -1 || dist < S) {
                S= dist; // Actualización de los puntos más cercanos
            }
        }
    }

    // Devolvemos resultado
    return S;
}



//////////////////////////////
// SOLUCIÓN DYV
//////////////////////////////


float Combinar(const Punto *cPuntos, const int ini, const int centro, const int fin, const float S1, const float S2) {
    
    const float parcial= (S1 < S2)? S1:S2;

    int centroIzq, centroDcha; // Posiciones centrales para la fusión
    float distAux; // Distancia de puntos en comparación
    float S; // Solución a devolver
    
    S= parcial; // Inicialización de solución a devolver

    // COMBINACIÓN: PARTE CENTRAL

    // Búsqueda del punto más a la derecha del problema P1 (parte izquierda)
    centroIzq= centro;
    distAux= 0;
    do {
        centroIzq--;
        if (centroIzq>=ini) {
            distAux= distanciaEnX(cPuntos[centro], cPuntos[centroIzq]);
        }
    } while (centroIzq>ini && distAux < parcial);

    // Búsqueda del punto más a la izquierda del problema P2 (parte derecha)
    centroDcha= centro-1;
    distAux= 0;
    do {
        centroDcha++;
        if (centroDcha<fin) {
            distAux= distanciaEnX(cPuntos[centro], cPuntos[centroDcha]);
        }
    } while (centroDcha<fin && distAux < parcial);

    if (centroDcha < fin) centroDcha++; // Esta línea está para "meter" también el último punto a considerar en el centro

    // Encontramos distancia mínima en parte central
    for (int i = centroIzq; i < centro; i++)  {
        for (int j = centro; j < centroDcha; j++)  {
            distAux= distancia(cPuntos[i], cPuntos[j]);
            if (S > distAux){
                S= distAux;
            }
        }
    }
    return S;
}

/*
 Algoritmo DyV: Divide el conjunto de puntos en 2
 */
float DyV(const Punto *cPuntos, const int ini, const int fin) {

    int centro;
    float S1, S2, S; // Subsoluciones de los subproblemas generados y solución final a devolver

    // Comprobación de caso base: El dataset contiene 2 ó 3 puntos
    if (fin-ini<=3) {
        S= BASICO(cPuntos, ini, fin); // Resolvemos con básico y devolvemos resultado

    } else {

        centro= (ini+fin)/2;
        S1= DyV(cPuntos, ini, centro);
        S2= DyV(cPuntos, centro, fin);

        S= Combinar(cPuntos, ini, centro, fin, S1, S2);
    }

    return S;
}





int main() {

    int n; // Número de puntos
    Punto *cPuntos; // Array para almacenar un conjunto de n puntos
    float distanciaBasico, distanciaDyV; // Distancia calculada por algoritmos básico y DyV
    chrono::time_point<chrono::high_resolution_clock> tBasico0, tBasicof; // Para medir el tiempo de ejecución
    chrono::time_point<chrono::high_resolution_clock> tDyV0, tDyVf; // Para medir el tiempo de ejecución
    double tEjecBasico, tEjecDyV; // Tiempos de ejecución de algoritmos básico y DyV


    // Lectura de los datos
    LeerDatos(n, cPuntos);
    if (cPuntos == 0) return 0; // Salimos si error
    

    // Resolución del problema con el método básico
    tBasico0= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
    distanciaBasico= BASICO(cPuntos, 0, n);
    tBasicof= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que termina la ejecución del algoritmo


    // Resolución del problema con DyV
    tDyV0= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
    distanciaDyV= DyV(cPuntos, 0, n);
    tDyVf= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que termina la ejecución del algoritmo



    // Mostramos soluciones por pantalla
    tEjecBasico= chrono::duration_cast<std::chrono::milliseconds>(tBasicof - tBasico0).count();
    tEjecDyV= chrono::duration_cast<std::chrono::microseconds>(tDyVf - tDyV0).count();
    
    cout <<"El algoritmo básico tarda "<<tEjecBasico<<" ms en dar la solución: "<<distanciaBasico<<endl;
    cout <<"El algoritmo DyV tarda "<<tEjecDyV<<" us en dar la solución:"<<distanciaDyV<<endl;

    // Liberación de memoria dinámica del dataset
    delete [] cPuntos;
    

    return 0;
}