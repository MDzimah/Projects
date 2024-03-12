#include "tablero.h"
#include <iostream>
#include <assert.h>

Tablero::Tablero(int fils, int cols, Celda inicial) : filas(fils), columnas(cols) {
	for (int f = 0; f < fils; ++f)
		for (int c = 0; c < cols; ++c)
			celdas[f][c] = inicial;
}

bool Tablero::correcta(int &f, int &c) const {
	--f; --c;
	return f >= 0 && f < filas && c >= 0 && c < columnas && celdas[f][c] != NULA; //da mal el assert, lo de nula
}

Celda Tablero::leer(int f, int c) const {
	assert(correcta(f, c));
	return celdas[f][c];
}

void Tablero::escribir(int f, int c, Celda valor) {
	assert(correcta(f, c));
	celdas[f][c] = valor;
}

