#include <iostream>

using namespace std;

int BB(const int *V, int ini, int fin, int x){
    int centro;
    if (ini > fin) return -1;
    centro = (ini+fin)/2;

    if (V[centro] == x) return centro;
    else if (V[centro] > x) return BB(V,ini, centro-1, x);
    else return BB(V,centro+1, fin, x);
}

int main(){

    int V[100]={1,2,3,4,5,6,7};

    cout << BB(V,0,7,5) << endl;
}