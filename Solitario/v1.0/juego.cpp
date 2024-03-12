#include "juego.h"

void Juego::cargar(std::istream& entrada) {
	int filas, cols;
	entrada >> filas >> cols;
	tablero = Tablero(filas, cols, NULA);
	for (int f = 1; f <= tablero.num_filas(); ++f)
		for (int c = 1; c <= tablero.num_columnas(); ++c) {
			
			short int val;
			entrada >> val;
			
			if (val == 2) ++numFichas;
			tablero.escribir(f, c, tablero.conv_intAenum(val));
		}
	entrada >> f_meta >> c_meta;


	estado_int = JUGANDO;
}

bool Juego::posicion_valida(int f, int c) const {
	if (tablero.correcta(f, c)) return tablero.leer(f, c) == FICHA;
	else return false;
}

void Juego::posibles_movimientos(Movimiento& mov) const {
	
	for (int i = 0; i < 4; ++i) {
		if (tablero.leer(mov.fila() + dirs[i].first, mov.columna() + dirs[i].second) == FICHA
			&& tablero.leer(mov.fila() + 2 * dirs[i].first, mov.columna() + 2 * dirs[i].second) == VACIA)
			mov.insertar_dir(mov.direccion(i));
	}
}

void Juego::jugar(Movimiento const& mov) {
	nuevo_estado();
	if (estado_int == JUGANDO) 
		ejecuta_movimiento(mov);
}

void Juego::ejecuta_movimiento(Movimiento const& mov) {

	int i = mov.dir_activa();

	tablero.escribir(mov.fila() + dirs[i].first, mov.columna() + dirs[i].second, VACIA);
	tablero.escribir(mov.fila() + 2 * dirs[i].first, mov.columna() + dirs[i].second, FICHA);
}

void Juego::nuevo_estado() {
	if (hay_ganador()) estado_int = GANADOR;
	if (hay_movimientos()) estado_int = JUGANDO;
	else estado_int = BLOQUEO;
}

bool Juego::hay_ganador() const {
	return numFichas == 1 && tablero.leer(f_meta,c_meta) == FICHA;
}

bool Juego::hay_movimientos() const {
	for (int f = 0; f < tablero.num_filas(); ++f)
		for (int c = 0; c < tablero.num_columnas(); ++c)
			if (tablero.leer(f, c) == FICHA) {
				Movimiento m(f, c);
				posibles_movimientos(m);
				return m.num_dirs() > 0;
			}
}

void Juego::mostrar() const {
	Colores pintarTablero(tablero, f_meta, c_meta);
	pintarTablero.pintar();
}



