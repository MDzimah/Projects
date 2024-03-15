#pragma once
#include <vector>
enum Celda { NULA, VACIA, FICHA };

/*Añado una variable bool a la lista de parámetros de las funciones "correcta", "leer" y "escribir"
porque, si se crea un tablero, aleatorio es necesario obviar la condición "celdas[f][c] != NULA" de
de "correcta". Las otras dos lo llevan porque hacen un assert(correcta) como se indica en el guión*/

class Tablero {
public:
	Tablero(int fils, int cols, Celda inicial) : filas(fils), columnas(cols), celdas(fils, std::vector<Celda>(cols, inicial)) {}
	int num_filas() const { return filas; }
	int num_columnas() const { return columnas; }
	bool correcta(int f, int c, bool op) const;
	Celda leer(int f, int c, bool op) const;
	Celda conv_intAenum(int i) { 
		Celda cel = (Celda)i;
		return cel;
	}
	void escribir(int f, int c, Celda valor, bool op);
	Celda valorCeldas(int f, int c) { return celdas[f][c]; }
private:
	int filas, columnas;
	std::vector<std::vector<Celda>> celdas;
};