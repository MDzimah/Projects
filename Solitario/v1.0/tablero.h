#pragma once

enum Celda { NULA, VACIA, FICHA };

const int MAXDIM = 10;

class Tablero {
public:
	Tablero(int fils, int cols, Celda inicial);
	int num_filas() const { return filas; }
	int num_columnas() const { return columnas; }
	bool correcta(int &f, int &c) const;
	Celda leer(int f, int c) const;
	Celda conv_intAenum(int i) { 
		Celda cel = (Celda)i;
		return cel;
	}
	void escribir(int f, int c, Celda valor);
	Celda valorCeldas(int f, int c) { return celdas[f][c]; }
private:
	int filas, columnas;
	Celda celdas[MAXDIM][MAXDIM];
};