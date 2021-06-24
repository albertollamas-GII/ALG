#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

int infinito; // Variable para conocer internamente el valor "infinito"


bool RecuperaSolucion(int ** P, const int origen, const int destino, vector<int> & S) {

    vector<int> S1, S2;
    S.clear();

    //Si no hay camino
    if (P[origen][destino] == infinito) {
        return false;
    }
    //Que te den el mismo nodo o que vaya de origen del tiron
    if (origen == destino || P[origen][destino] == origen)
        return true;
    
    //Si recursivamente te devuelve que no se puede volver al origen
    if (!RecuperaSolucion(P, origen, P[origen][destino], S1)) {
        return false;
    }

    cout << P[origen][destino] << " ";

    if (!RecuperaSolucion(P, P[origen][destino], destino, S2)) {
        return false;
    }

    // Construcción de la solución
    S.push_back(origen);
    for (auto it=S1.begin(); it != S1.end(); it++) {
        S.push_back(*it);
        // cout << (*it) << " ";
    }
    S.push_back(P[origen][destino]);
    for (auto it=S2.begin(); it != S2.end(); it++) {
        S.push_back(*it);
    }
    S.push_back(destino);


    return true;
}


bool Diccionarios(const vector<string> &idiomas, const vector<pair<int, int> > diccionarios,
            const int origen, const int destino, vector<int> &S) {

    int **T, **P, **L;
    const int n= idiomas.size(), m= diccionarios.size();
    infinito= m+1; // Representación del valor infinito

    S.clear();

    // Reserva de memoria
    T= new int *[n];
    P= new int *[n];
    L= new int *[n];
    for (int i= 0; i<n; i++) {
        T[i]= new int[n];
        P[i]= new int[n];
        L[i]= new int[n];
    }
    for (int i= 0; i<n; i++) {
        for (int j= 0; j<n; j++) {
            if (i==j) {
                L[i][j]= 0;
            }else {

                bool hayDiccionario= false;
                for (int k= 0; k<m && !hayDiccionario; k++) {
                    if ((diccionarios[k].first == i && diccionarios[k].second == j) ||
                        (diccionarios[k].first == j && diccionarios[k].second == i)) {

                        L[i][j]= L[j][i]= 1;
                        hayDiccionario= true;
                    }
                }
                if (!hayDiccionario)
                    L[i][j]= L[j][i]= infinito;
            }
        }
    }

    for (int i= 0; i<n; i++) {
        for (int j= 0; j<n; j++) {
            T[i][j]= L[i][j];
            if (L[i][j] != infinito) {
                P[i][j]= i;
            } else {
                P[i][j]= infinito;
            }

        }
    }

    // Algoritmo
    for (int k= 0; k<n; k++) {
        for (int i= 0; i<n; i++) {
            for (int j= 0; j<n; j++) {
                if (T[i][j] > T[i][k]+T[k][j]) {
                    T[i][j]= T[i][k]+T[k][j];
                    P[i][j]= k;
                }
            }
        }
    }

    bool sePuede= true;
    if (!RecuperaSolucion(P, origen, destino, S)) {
        S.clear();
        sePuede= false;
    }


    // Liberación de memoria
    for (int i= 0; i<n; i++) {
        delete [] T[i];
        delete [] P[i];
        delete [] L[i];
    }
    delete [] T;
    delete [] P;
    delete [] L;

    return sePuede;
}


void CargarDatos(vector<string> &idiomas, vector<pair<int, int> > &diccionarios, int &origen, int &destino) {

    int n,m, a, b;
    string s;

    idiomas.clear();
    diccionarios.clear();

    // Leemos desde flujo estándar cuántos idiomas hay
    cin>>n;

    // Cargamos los nombres de idiomas:
    for (int i= 0; i<n; i++) {
        cin>>s;
        idiomas.push_back(s);
    }

    // Cargamos el número de diccionarios
    cin>>m;

    // Leemos los índices de diccionarios existentes
    for (int i= 0; i<m; i++) {
        cin>>a>>b;
        diccionarios.push_back(pair<int, int>(a,b));
    }

    // Leemos el origen y el destino
    cin>>origen>>destino;
}


int main() {

    vector<string> idiomas;
    vector<pair<int, int> > diccionarios;
    vector<int> S;
    int origen, destino;

    // Leemos desde consola los datos
    CargarDatos(idiomas, diccionarios, origen, destino);

    // Mostramos los datos
    cout<<"Idiomas: "<<idiomas.size()<<endl;
    for (auto it=idiomas.begin(); it != idiomas.end(); it++) {
        cout <<"\t"<<*it<<endl;
    }

    cout<<"Diccionarios: "<<diccionarios.size()<<endl;
    for (auto it=diccionarios.begin(); it != diccionarios.end(); it++) {
        cout<<"\t"<<idiomas[it->first]<<" <-> "<<idiomas[it->second]<<endl;
    }
    cout<<"Se pide traducir del "<<idiomas[origen]<<" al "<<idiomas[destino]<<endl;

    bool sePuede= Diccionarios(idiomas, diccionarios, origen, destino, S);
    if (!sePuede) {
        cout <<"No se puede traducir\n";
    } else {
        cout<<"El coste de la solución es: "<<S.size()<<" traducciones intermedias: "<<endl;
        for (auto it=S.begin(); it != S.end(); it++) {
            cout<<"\t"<<idiomas[*it]<<endl;
        }
    }


    return 0;
}
