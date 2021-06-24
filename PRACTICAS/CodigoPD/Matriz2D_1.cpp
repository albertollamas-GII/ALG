#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "Matriz2D_1.h"

using namespace std;

/*************************************************************************/
/*************************************************************************/
// Constructor sin argumentos, crea una matriz vacía

Matriz2D_1 :: Matriz2D_1 (void)
{

	fils = 0;
	cols = 0;
	datos = 0;

}

/*************************************************************************/
/*************************************************************************/
// Constructor con un argumento, matriz n*n

Matriz2D_1 :: Matriz2D_1 (int lado)
{

	fils = lado;
	cols = lado;

	ReservarMemoria(fils,cols);

}

/*************************************************************************/
/*************************************************************************/
// Constructor con dos argumentos (f,c) crea matriz f*c

Matriz2D_1 :: Matriz2D_1 (int filas, int columnas)
{

	fils = filas;
	cols = columnas;

	ReservarMemoria(fils, cols);

}

/*************************************************************************/
/*************************************************************************/
// Constructor con tres argumentos (f,c,n) crea matriz f*c con el valor n en
// todas las casillas

Matriz2D_1 :: Matriz2D_1 (int filas, int columnas, TipoBase valor)
{

	fils = filas;
	cols = columnas;
	
	ReservarMemoria(fils, cols);

	Inicializar(valor);

}

/*************************************************************************/
/*************************************************************************/
// Constructor que recibe el nombre de un fichero de texto y rellena las 
// casillas de la matriz con los datos contenidos en el fichero

Matriz2D_1 :: Matriz2D_1 (const char * nombre)
{

	ifstream fi;

	fi.open(nombre);

	if (fi) {

		int filas;
		int columnas;

		fi >> filas;
		fi >> columnas;

		fils = filas;
		cols = columnas;

		ReservarMemoria(fils, cols);

		TipoBase valor;

		for (int i = 0; i < fils; i++) {
			for (int j = 0; j < cols; j++){
				fi >> valor;
				datos[i][j] = valor;
			}
		}

	}

}

/*************************************************************************/
/*************************************************************************/
// Constructor de copia

Matriz2D_1 :: Matriz2D_1 (const Matriz2D_1 & otro)
{

	// Reservamos memoria para la matriz
	ReservarMemoria (otro.fils, otro.cols);

	// Copiamos los datos de una matriz a otra
	CopiarDatos(otro);

}

/*************************************************************************/
/*************************************************************************/
// Destructor

Matriz2D_1 :: ~Matriz2D_1 (void)
{

	// Liberamos la memoria de la matriz
	LiberarMemoria();

}

/*************************************************************************/
/*************************************************************************/
// Guarda en el fichero de texto pasado como argumento el contenido de la 
// matriz

void Matriz2D_1 :: EscribirMatriz2D_1 (const char * nombre) const
{

	ofstream fo; // Flujo de salida

	fo.open(nombre);

	if (fo) {

		for (int i = 0; i < fils; i++) {
			for (int j = 0; j < cols; j++)
				fo << datos[i][j] << "	";
			fo << endl;
		}

	}

}

/*************************************************************************/
/*************************************************************************/
// Sustituye el contenido de la matriz por los valores que están en el fichero 
// de texto

void Matriz2D_1 :: LeerMatriz2D_1 (const char * nombre)
{

	ifstream fi;

	fi.open(nombre);

	if (fi) {

		LiberarMemoria();

		int filas, columnas;

		fi >> filas;
		fi >> columnas;

		fils = filas;
		cols = columnas;

		ReservarMemoria(fils, cols);

		TipoBase valor;

		for (int i = 0; i < fils; i++) {
			for (int j = 0; j < cols; j++){
				fi >> valor;
				datos[i][j] = valor;
			}
		}
	
	}

}

/*************************************************************************/
/*************************************************************************/
// Metodo que devuelve el numero de filas de la matriz

int Matriz2D_1 :: GetFilas (void)
{
	
	return (fils);
	
}

/*************************************************************************/
/*************************************************************************/
// Metodo que devuelve el numero de columnas de la matriz

int Matriz2D_1 :: GetColumnas (void)
{
	
	return (cols);
	
}

/*************************************************************************/
/*************************************************************************/
// Metodo que inicializa una matriz a un numero indicado

void Matriz2D_1 :: Inicializar(int valor = 0)
{

	for (int f = 0; f < fils; f++) {
		for (int c = 0; c < cols; c++)
			datos[f][c] = valor;
	}

}

/*************************************************************************/
/*************************************************************************/
// Metodo que devuelve el valor de una posicion de la matriz

TipoBase Matriz2D_1 :: LeerValor (int fila, int columna)
{

	return (datos[fila][columna]);	

}

/*************************************************************************/
/*************************************************************************/
// Metodo que permite modificar el valor de una posicion

void Matriz2D_1 :: ModificarValor (int fila, int columna, TipoBase valor)
{

	datos[fila][columna] = valor;

}

/*************************************************************************/
/*************************************************************************/
// Metodo que devuelve si una matriz esta vacia o no (true/false)

bool Matriz2D_1 :: EsMatrizVacia (void)
{

	return (datos == 0);

}

/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/

// SOBRECARGAS

/*************************************************************************/
/*************************************************************************/
// Sobrecarga del operador de asignacion

Matriz2D_1 & Matriz2D_1 :: operator = (const Matriz2D_1 & otro)
{

	// Liberamos la memoria ocupada
	LiberarMemoria();

	// Reservamos memoria con los nuevos datos
	ReservarMemoria(otro.fils, otro.cols);

	// Copiamos los datos
	CopiarDatos(otro);

	// Devolver el objeto implicito
	return (*this);

}

/*************************************************************************/
/*************************************************************************/
// Sobrecarga alternativa del operador de asignacion
// Recibe un dato de tipo TipoBase e inicializa toda la matriz a ese valor

Matriz2D_1 & Matriz2D_1 :: operator = (const TipoBase & valor)
{

	// Inicializamos todas las posiciones de la matriz al valor
	Inicializar(valor);

	// Devolvemos el objeto implicito
	return (*this);

}

/*************************************************************************/
/*************************************************************************/
// Sobrecarga del operador () como rvalue

TipoBase & Matriz2D_1 :: operator () (const int fila, const int columna) const
{

	return (datos[fila][columna]);

}

/*************************************************************************/
/*************************************************************************/
// Sobrecarga del operador () como lvalue

TipoBase & Matriz2D_1 :: operator () (const int fila, const int columna)
{

	return (datos[fila][columna]);

}

/*************************************************************************/
/*************************************************************************/
// Sobrecarga de operadores unarios + y -

Matriz2D_1 Matriz2D_1 :: operator + (void)
{
	
	return (*this);

}

Matriz2D_1 Matriz2D_1 :: operator - (void)
{

	Matriz2D_1 tmp;

	tmp = *this;

	for (int i = 0; i < fils; i++) {
		for (int j = 0; j < cols; j++)
			tmp.datos[i][j] = -datos[i][j];
	}

	return (tmp);

}

/*************************************************************************/
/*************************************************************************/
// Sobrecarga de operadores binarios + y -

Matriz2D_1 operator + (const Matriz2D_1 & m1, const Matriz2D_1 & m2)
{

	Matriz2D_1 suma;

	if ((m1.fils == m2.fils) && (m1.cols == m2.cols)) {
	
		// Reservo memoria para la nueva matriz
		suma.ReservarMemoria(m1.fils, m1.cols);

		suma = m1;

		for (int i = 0; i < m1.fils; i++) {
			for (int j = 0; j < m1.cols; j++)
				suma(i,j) += m2(i,j);
		}

	}

	return (suma);

}

//////////////////////////////////////////////////////////////////////////

Matriz2D_1 operator - (const Matriz2D_1 & m1, const Matriz2D_1 & m2)
{

	Matriz2D_1 resta;

	if ((m1.fils == m2.fils) && (m1.cols == m2.cols)) {

		// Reservo memoria para la nueva matriz
		resta.ReservarMemoria(m1.fils, m1.cols);

		resta = m1;

		for (int i = 0; i < m1.fils; i++) {
			for (int j = 0; j < m1.cols; j++)
				resta(i,j) -= m2(i,j);
		}

	}

	return (resta);

}

//////////////////////////////////////////////////////////////////////////

Matriz2D_1 operator + (const Matriz2D_1 & m1, const TipoBase & valor)
{

	Matriz2D_1 suma(m1.fils, m1.cols);

	suma = valor;

	return (m1 + suma);

}

//////////////////////////////////////////////////////////////////////////

Matriz2D_1 operator - (const Matriz2D_1 & m1, const TipoBase & valor)
{
	
	Matriz2D_1 resta(m1.fils, m1.cols);

	resta = valor;

	return (m1 - resta);

}

//////////////////////////////////////////////////////////////////////////

Matriz2D_1 operator + (const TipoBase & valor, const Matriz2D_1 & m1)
{

	Matriz2D_1 suma(m1.fils, m1.cols);

	suma = valor;

	return (m1 + suma);

}

//////////////////////////////////////////////////////////////////////////

Matriz2D_1 operator - (const TipoBase & valor, const Matriz2D_1 & m1)
{

	Matriz2D_1 resta(m1.fils, m1.cols);

	resta = m1;

	return ((-resta) + valor);

}

/*************************************************************************/
/*************************************************************************/
// Sobrecarga de los operadores combinados += y -=

Matriz2D_1 & Matriz2D_1 :: operator += (const TipoBase & valor)
{

	*this = *this + valor;

	return (*this);

}

//////////////////////////////////////////////////////////////////////////

Matriz2D_1 & Matriz2D_1 :: operator -= (const TipoBase & valor)
{

	*this = *this - valor;

	return (*this);

}

/*************************************************************************/
/*************************************************************************/
// Sobrecarga de los operadores combinados == y !=

bool operator == (const Matriz2D_1 & m1, const Matriz2D_1 & m2)
{

	bool son_iguales = true;

	if ((m1.fils != m2.fils) || (m1.cols != m2.cols)) son_iguales = false;

	if (son_iguales) {

		for (int i = 0; i < m1.fils; i++) {
			for (int j = 0; j < m1.cols; j++)
				if (m1(i,j) != m2(i,j)) son_iguales = false;
		}

	}

	return (son_iguales);

}

//////////////////////////////////////////////////////////////////////////

bool operator != (const Matriz2D_1 & m1, const Matriz2D_1 & m2)
{

	bool son_diferentes = true;

	if (m1 == m2) son_diferentes = false;

	return (son_diferentes);

}

/*************************************************************************/
/*************************************************************************/

// METODOS PRIVADOS

/*************************************************************************/
/*************************************************************************/
// Metodo que reserva memoria para una matriz

void Matriz2D_1 :: ReservarMemoria (int filas, int columnas)
{

	// Reservar memoria para el vector de punteros
	datos = new TipoBase * [filas];

	// Reservar memoria para el vector de cada fila
	for (int i = 0; i < filas; i++)
		datos[i] = new TipoBase [cols];

}

/*************************************************************************/
/*************************************************************************/
// Metodo que copia datos de una matriz a otra
	
void Matriz2D_1 :: CopiarDatos (const Matriz2D_1 & otro)
{

	fils = otro.fils;
	cols = otro.cols;

    for (int f=0; f<fils; f++)
    	memcpy (datos[f], otro.datos[f], cols*sizeof(TipoBase));

}

/*************************************************************************/
/*************************************************************************/
// Metodo que libera la memoria de una matriz

void Matriz2D_1 :: LiberarMemoria (void)
{

	if (datos) { // Soi existen datos

		// Liberar memoria de los vectores de las filas
		for (int i = 0; i < fils; i++)
			delete [] datos[i];
	
		// Liberar memoria del vector de punteros
		delete [] datos;

		datos = 0;

	}
}

/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/

// FUNCIONES EXTERNAS A LA CLASE

/*************************************************************************/
/*************************************************************************/
// Funcion que pinta una matriz

void PintaMatriz (Matriz2D_1 matriz) 
{

	int filas = matriz.GetFilas();
	int columnas = matriz.GetColumnas();

	cout << "La matriz es: " << endl;

	for (int f = 0; f < filas; f++) {
		for (int c = 0; c < columnas; c++)
			cout << matriz.LeerValor(f,c) << " ";
		cout << endl;
	}

}
