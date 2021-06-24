#include <iostream>
#include <string>

using namespace std;


void PD(const string S, const string T, string &Sol, int &coste) {

    int **LCS;
    const int n= S.length(), m= T.length();

    // Creación de matriz
    LCS= new int *[S.length()+1];
    LCS[0]= new int [(n+1)*(m+1)];
    for (int i=1; i<=n; i++) {
        LCS[i]= LCS[i-1]+(m+1);
    }

    // Casos base
    for (int i= 0; i<=n; i++) {
        LCS[i][0]= 0;
    }
    for (int j= 0; j<=m; j++) {
        LCS[0][j]= 0;
    }

    // Caso general
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            if (S[i-1] == T[j-1]) {
                LCS[i][j]= 1+ LCS[i-1][j-1];
            } else if (LCS[i-1][j] < LCS[i][j-1]) {
                LCS[i][j]= LCS[i][j-1];
            } else {
                LCS[i][j]= LCS[i-1][j];
            }
        }
    }
    coste= LCS[n][m];


    // Algoritmo de recuperación de solución
    Sol= "";
    int i=n, j=m;

    while (i>0 && j>0) {

        if (S[i-1] == T[j-1]) { 
            Sol= S[i-1]+Sol;
            i--;
            j--;
        } else if (LCS[i][j] == LCS[i][j-1]) {
            j--;
        } else {
            i--;
        }
    }

    // Liberación de matriz
    delete [] LCS[0];
    delete [] LCS;
}


int main() {

    string S, T, Sol;
    int coste;

    // Entradas al problema
    cout<<"Dime la cadena S: ";
    cin>>S;
    cout<<"Dime la cadena T: ";
    cin>>T;

    // Cálculo de la solución
    PD(S, T, Sol, coste);

    cout<<"El coste de la solución es: "<<coste<<endl;
    cout<<"La subcadena común es : "<<Sol<<endl;

    return 0;
}