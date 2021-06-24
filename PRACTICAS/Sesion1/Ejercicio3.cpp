// INCLUDES y namespaces necesarios para ejecutar el programa
#include <iostream>
#include <fstream> // Para guardar a fichero
#include <vector>
#include <cmath> // Para el cálculo de log
#include <chrono> // Para medición de tiempos de ejecución

using namespace std;

// Estructura que nos servirá para almacenar tamaños de casos y tiempos de ejecución que han
// tardado los algoritmos en resolver el problema de tamaño de caso dado
struct TEjecucion {
    unsigned int tamCaso; // Tamaño de caso del problema resuelto
    double tiempo; // Tiempo tardado por el algoritmo en resolver el problema de tamaño tamCaso

    TEjecucion(int tam, double t) {
        tamCaso= tam;
        tiempo= t;
    }
};



// Algoritmo que tiene como entrada un vector v ya ordenado, de tamaño n,
// y un valor x a buscar en el vector.
// Devuelve un índice del vector donde se encuentra el elemento x,
// o el valor -1 en caso de que x no esté en el vector
int AlgoritmoA(const int * v, const int n, const int x) {

    for (int i= 0; i<n; i++) {
        if (v[i] == x) return i;
    }
    return -1;
}


// Algoritmo que tiene como entrada un vector v ya ordenado, de tamaño n, 
// y un valor x a buscar en el vector.
// Devuelve un índice del vector donde se encuentra el elemento x,
// o el valor -1 en caso de que x no esté en el vector
int AlgoritmoB(const int * v, const int n, const int x) {

    int ini= 0, fin=n-1, centro;

    while (ini<=fin) {
        centro= (ini+fin)/2;
        if (v[centro] == x) return centro;
        else if (v[centro]>x) fin=centro-1;
        else ini= centro+1;
    }

    return -1;
}




int main() {

    
    const string ficheroSalidaA= "salidaA.csv"; // Fichero de salida de pares (tamCaso, tiempo ejecución) del algoritmo A
    const string ficheroSalidaB= "salidaB.csv"; // Fichero de salida de pares (tamCaso, tiempo ejecución) del algoritmo A
    const vector <int> tamCasos= {50000000, 60000000, 70000000, 80000000, 90000000,
                                 100000000, 110000000, 120000000, 130000000, 140000000 }; // Tamaños de los casos de los problemas a resolver
    ofstream fout; // Fichero de salida de resultados
    const int NEjecuciones= 10; // Número de veces que ejecutamos cada tamaño de caso para estimar mejor K
    
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
    double tiempoEjecucionA, tiempoEjecucionB; // Tiempo que tarda el algoritmo en resolver la instancia
    int tamCaso; // Pasa saber el tamaño de caso actual
    int * v; // Vector donde vamos a buscar un elemento
    int x; // Elemento a buscar en el vector v

    double K_A, K_B; // Constantes ocultas de los algoritmos A y B
    vector<double> K_A_parciales, K_B_parciales; // Constante calculada para cada tamaño de caso y tiempo de ejecución

    vector<TEjecucion> tiemposA; // Array para almacenar los tamaños de casos y tiempos que ha tardado A en resolver cada instancia
    vector<TEjecucion> tiemposB; // Array para almacenar los tamaños de casos y tiempos que ha tardado B en resolver cada instancia



    // Pasamos por cada tamaño de caso
    for (int i= 0; i<tamCasos.size(); i++) {
        
        tamCaso= tamCasos[i]; // Tamaño de caso que se desea resolver
        v= new int[tamCaso]; // Reserva de memoria para v

        // Creamos un vector aleatorio del tamaño de caso, con valores al azar, pero positivos
        for (int pos= 0; pos<tamCaso; pos++) {
            v[pos]= pos;
        }

        x= tamCaso; // Ponemos a buscar un valor que no esté en el vector: Peor caso


        // Realizamos NEjecuciones ejecuciones para aproximar mejor el tiempo de ejecución para resolver el problema
        //  de tamaño tamCaso
        tiempoEjecucionA= tiempoEjecucionB= 0; // Para medir el tiempo de ejecución
        for (int ejecucion= 0; ejecucion<NEjecuciones; ejecucion++) {

            // Medimos el tiempo del algoritmo A en NANOSEGUNDOS, buscando el elemento -200 (que no está en el vector)
            t0= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
            int resultadoA= AlgoritmoA(v, tamCaso, x);
            tf= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecución del algoritmo

            // Sumamos el tiempo de ejecución
            tiempoEjecucionA+= chrono::duration_cast<std::chrono::nanoseconds>(tf - t0).count();


            // Hacemos lo mismo con el algoritmo B
            t0= chrono::high_resolution_clock::now();
            int resultadoB= AlgoritmoB(v, tamCaso, x);
            tf= chrono::high_resolution_clock::now();
            tiempoEjecucionB+= chrono::duration_cast<std::chrono::nanoseconds>(tf - t0).count();
        }

        // Liberamos memoria de v (ya no hace falta)
        delete [] v;

        // Hacemos la media de los tiempos totales que han tardado en hacerse NEjecuciones ejecuciones
        tiempoEjecucionA/= NEjecuciones;
        tiempoEjecucionB/= NEjecuciones;


        // Lo guardamos a nuestra estructura. Lo mostramos por pantalla por gusto.
        tiemposA.push_back( TEjecucion(tamCaso, tiempoEjecucionA) );
        tiemposB.push_back( TEjecucion(tamCaso, tiempoEjecucionB) );
        cout<<"Tam. caso: "<<tamCaso<<" --> Algoritmo A: "<<tiempoEjecucionA<<" ns"<<", Algoritmo B: "<<tiempoEjecucionB<<" ns"<<endl;
    }


    // Guardamos a fichero los tiempos de A y B para luego visualizarlos bien en otro programa
    fout.open(ficheroSalidaA);
    if (!fout) {
        cerr<<"Error abriendo fichero "<<ficheroSalidaA<<endl;
        return 0;
    }
    fout.imbue(std::locale( "" )); // Para que se guarde en el fichero coma decimal en lugar de punto decimal y lo lea LibreOffice Calc
    for (int i= 0; i<tiemposA.size(); i++) {
        fout<<tiemposA[i].tamCaso<<"\t"<<tiemposA[i].tiempo<<endl;
    }
    fout.close();


    fout.open(ficheroSalidaB);
    if (!fout) {
        cerr<<"Error abriendo fichero "<<ficheroSalidaA<<endl;
        return 0;
    }
    fout.imbue(std::locale( "" )); // Para que se guarde en el fichero coma decimal en lugar de punto decimal y lo lea LibreOffice Calc
    for (int i= 0; i<tiemposB.size(); i++) {
        fout<<tiemposB[i].tamCaso<<"\t"<<tiemposB[i].tiempo<<endl;
    }
    fout.close();


    // Cálculo de las constantes ocultas para A y B
    K_A= K_B= 0.0;
    for (int i= 0; i<tiemposB.size(); i++) {

        // El algoritmo A es O(n) --> K= tiempo/n
        K_A_parciales.push_back( tiemposA[i].tiempo/tiemposA[i].tamCaso );
        K_A+= K_A_parciales[K_A_parciales.size()-1];

        // El algoritmo B es O( log2(n) ) --> K= tiempo/log2(n)
        K_B_parciales.push_back( tiemposB[i].tiempo/log2(tiemposB[i].tamCaso) );
        K_B+= K_B_parciales[K_B_parciales.size()-1];
    }
    K_A/= tiemposA.size();
    K_B/= tiemposB.size();

    // Mostramos K parciales y la K final calculada como media de todas las K calculadas
    cout<<"Constantes calculadas:"<<endl;
    for (int i= 0; i<tiemposB.size(); i++) {
        cout<<"Tam. Caso "<<tiemposB[i].tamCaso<<": K_A= "<< K_A_parciales[i]<<", K_B= "<<K_B_parciales[i]<<endl;
    }
    cout<<endl<<"Las K calculadas son: K_A: "<<K_A<<" y K_B= "<<K_B<<endl;


    // Prueba del algoritmo A para un caso de tamaño tamCaso= 40000000
    tamCaso= 40000000;
    cout << "El algoritmo A tardaría en resolver un problema de tamaño "<< tamCaso<<" aproximadamente: "<<K_A*tamCaso<<" ns"<<endl;


    // Comprobación experimental
    v= new int[tamCaso]; // Reserva de memoria para v

    // Realizamos NEjecuciones ejecuciones para aproximar mejor el tiempo de ejecución para resolver el problema
    //  de tamaño tamCaso
    tiempoEjecucionA= 0; // Para medir el tiempo de ejecución
    for (int ejecucion= 0; ejecucion<NEjecuciones; ejecucion++) {

        // Creamos un vector aleatorio del tamaño de caso, con valores al azar, pero positivos
        for (int pos= 0; pos<tamCaso; pos++) {
            int elem= rand(); // Generamos entero aleatorio y lo añadimos a v
            v[pos]= elem;
        }

        // Medimos el tiempo del algoritmo A en NANOSEGUNDOS, buscando el elemento -200 (que no está en el vector)
        t0= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
        int resultadoA= AlgoritmoA(v, tamCaso, x);
        tf= chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecución del algoritmo

        // Sumamos el tiempo de ejecución
        tiempoEjecucionA+= chrono::duration_cast<std::chrono::nanoseconds>(tf - t0).count();
    }

    // Liberamos memoria de v (ya no hace falta)
    delete [] v;

    // Hacemos la media de los tiempos totales que han tardado en hacerse NEjecuciones ejecuciones
    tiempoEjecucionA/= NEjecuciones;

    cout<<"Ha tardado: "<<tiempoEjecucionA<< " ns"<<endl;

    return 0;
}