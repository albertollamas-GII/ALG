
#include <iostream>
#include <chrono> // Para medición de tiempos de ejecución
#include <limits>
using namespace std;

// Estructura para representar un punto 2D
struct Punto {
    long x, y;
};


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






//////////////////////////////
// SOLUCIÓN GREEDY
//////////////////////////////

/*
 FUNCIÓN AUXILIAR
 Determina la posición (izquierda, derecha, centro) de un punto pq con respecto al vector director (pi, pj)
 Devuelve -1 si pq está a la "izquierda" del vector director, +1 si está a la derecha, y 0 si es un punto de la recta
*/
int PosicionVectorDirector(const Punto &pi, const Punto &pj, const Punto &pq) {

    float det; // Determinante de ([pi.x, pi.y, 1], [pj.x, pj.y, 1], [pq.x, pq.y, 1])

    // Cálculo del determinante
    det= pi.x*pj.y + pj.x*pq.y + pq.x*pi.y - pj.y*pq.x - pq.y*pi.x - pi.y*pj.x;
    
    // determinación de la posición de pq con respecto al vector director
    if (det < 0) return 1;
    if (det > 0) return -1;
    return 0;
}


/*
 FUNCIÓN AUXILIAR
 Esta función busca un punto pj tal que el vector director
    (pi, pj) deja todos los demas puntos en el array "puntos[ini...fin]" a la izquierda 
    del mencionado vector. Además, si existen varios puntos pj
    que cumplen esta propiedad, se escoge el vector (pi, pj) de máxima norma

 Se devuelve el índice del vector de puntos que se corresponde con el punto pj seleccionado
*/
int BuscarPunto(const Punto *puntos, const int ini, const int fin, const Punto pi) {

    float maxDist, currentDist; // Distancia entre puntos
    bool tieneDcha; // para saber si el vector director tiene puntos a la dcha
    Punto pj;
    int p= -1; // Punto a devolver

    // Buscamos aquel pj tal que el vector (pi, pj) deje todos los demás puntos a la izq
    // y que también tenga máxima norma (maxDist)
    maxDist= 0;
    for (int j= ini; j<fin; j++) {

        pj.x= puntos[j].x; pj.y= puntos[j].y; // Seleccionamos nuevo posible candidato pj

        // Miramos el vector director (pi, pj) para ver si deja algún punto a la dcha o no
        tieneDcha= false;
        for (int q= ini; q<fin && !tieneDcha; q++) { // Recorremos todos los puntos para ver si están a dcha de (pi, pj)

            if (PosicionVectorDirector(pi, pj, puntos[q]) > 0) {
                tieneDcha= true; // Tiene puntos a la dcha. Se descarta
            }
        }


        // Miramos si la recta desde el último punto de la solución hasta i no deja puntos a la dcha
        // Si es así, entonces pj es candidato a formar parte de la solución si (pi, pj) tiene norma máxima
        if (!tieneDcha) { 

            // Si no tiene puntos a la dcha, miramos si la norma de (pi, pj) es la mayor
            currentDist= (pj.x-pi.x)*(pj.x-pi.x) + (pj.y-pi.y)*(pj.y-pi.y);
            
            if (currentDist > maxDist) { // Nos quedamos con el punto actual (de momento)
                p= j;
                maxDist= currentDist;
            }
        }
    }

    return p;
}



// Algorimo greedy
// Devuelve la envolvente convexa de puntos en solucion, en el sentido contrario a las agujas del reloj
// solucion debe tener espacio para almacenar al menos n componentes
void Greedy(const Punto * puntos, const int ini, const int fin, int * &solucion, int &tamSol) {

    int p= ini; // Punto a insertar en la solución
    bool seguir= true;
    

    // Búsqueda del punto más a la izq de menor valor en coordenada y
    for (int i= ini; i<fin; i++) {
        if ( puntos[i].y < puntos[p].y || 
             (puntos[i].y == puntos[p].y && puntos[i].x < puntos[p].x) ) {
        
            p= i;
        }
    }

    // Insertamos el punto de menor coordenada y en la solución
    tamSol= 0;
    solucion[tamSol]= p;
    tamSol++;

    // Repetimos mientras no se incluya el primer punto de nuevo en el conjunto
    while (seguir) {

        // Búsqueda del siguiente punto que deja a la izq todos los demás puntos
        // y que tiene mayor distancia al actual
        p= BuscarPunto(puntos, ini, fin, puntos[solucion[tamSol-1]]);

        // Finalizado el barrido de todos los puntos, en p tenemos el siguiente punto a añadir a la solución
        // Comprobamos que no sea el primero que metimos
        if (p == solucion[0]) {
            seguir= false;
        } else {
            solucion[tamSol]= p;
            tamSol++;
        }
    }
}






int main() {

    int n; // Número de puntos
    Punto *cPuntos; // Array para almacenar un conjunto de n puntos
    int *solucion; // Array para almacenar la solución
    int tamSol= 0; // Tam. de solución 
    chrono::time_point<chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
    double tEjec; // Tiempos de ejecución de algoritmos básico y DyV


    // Lectura de los datos
    LeerDatos(n, cPuntos);
    if (cPuntos == 0) return 0; // Salimos si error

    // Reserva de memoria para soluciones
    solucion= new int[n];


    // Resolución del problema con greedy
    t0= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
    Greedy(cPuntos, 0, n, solucion, tamSol);
    tf= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que termina la ejecución del algoritmo


    // Mostramos soluciones por pantalla
    tEjec= chrono::duration_cast<std::chrono::milliseconds>(tf - t0).count();
    
    cerr <<"El algoritmo greedy tarda "<<tEjec<<" ms en dar la solución con "<<tamSol<<" puntos:"<< endl;
    for (int i= 0; i<tamSol; i++) {
        cerr << "\t("<<cPuntos[solucion[i]].x<<" , "<<cPuntos[solucion[i]].y<<")"<<endl;
    }



    // Mostramos solución por consola
    for (int i= 0; i<tamSol; i++) {
        cout<< cPuntos[solucion[i]].x << " " << cPuntos[solucion[i]].y << endl;
    }



    // Liberación de memoria
    delete [] cPuntos; 
    delete [] solucion; 


    return 0;
}