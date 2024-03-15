#include "tablero.h"
#include <iostream>
#include <assert.h>

bool Tablero::correcta(int f, int c, bool op) const {
	--f; --c;
	//Utilizo una variable bool para el caso de generar un tablero aleatorio
	if (!op) {
		return f >= 0 && f < filas && c >= 0 && c < columnas && celdas[f][c] != NULA;
	}
	else return f >= 0 && f < filas && c >= 0 && c < columnas;
}

Celda Tablero::leer(int f, int c, bool op) const {
	if (!op) {
		assert(correcta(f, c, false));
	}
	else assert(correcta(f, c, true));
	--f; --c;
	return celdas[f][c];
}

void Tablero::escribir(int f, int c, Celda valor, bool op) {
	if (!op) {
		assert(correcta(f, c, false));
	}
	else assert(correcta(f, c, true));
	--f; --c;
	celdas[f][c] = valor;
}

