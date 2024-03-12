#pragma once
enum Estado { JUGANDO, GANADOR, BLOQUEO };
#include "movimiento.h"
#include "pintarTablero.h"

class Juego {
public:
	Juego() : estado_int(BLOQUEO), tablero(0, 0, VACIA), numFichas(0) {}
	Juego(int movimientos);
	void cargar(std::istream&/*ent/sal*/ entrada);
	bool posicion_valida(int f, int c) const;
	void posibles_movimientos(Movimiento&/*ent/sal*/ mov) const;
	Estado estado() const { return estado_int; }
	void jugar(Movimiento const& mov);
	void mostrar() const;
private:
	Tablero tablero;
	int f_meta, c_meta, numFichas;
	Estado estado_int;
	void ejecuta_movimiento(Movimiento const& mov);
	void nuevo_estado();
	bool hay_ganador() const;
	bool hay_movimientos() const;
};
