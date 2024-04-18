//Manuel Dzimah Castro
#pragma
#include <iostream>

//N�mero de direcciones a considerar
const int NUMDIR = 4;

enum Direccion { ARRIBA, ABAJO, IZQUIERDA, DERECHA, INDETERMINADA };
std::string to_string(Direccion d);
class Movimiento {
public:
	Movimiento(int f, int c) : fil(f), col(c), cont(0), activa(INDETERMINADA) {
		for (int i = 0; i < NUMDIR; ++i)
			direcciones[i] = INDETERMINADA;
	}
	int fila() const { return fil; }
	int columna() const { return col; }
	Direccion dir_activa() const { return activa; }
	void fijar_dir_activa(Direccion d) { activa = d; }
	void insertar_dir(Direccion d) { direcciones[cont] = d; ++cont; }
	int num_dirs() const { return cont; }
	Direccion direccion(int i) const { return direcciones[i]; }
private:
	int fil;
	int col;
	Direccion activa; //De todas las direcciones posibles, contiene la direcci�n activa (la que se ejecuta)
	int cont; //N�mero de direcciones a las que se puede mover
	Direccion direcciones[NUMDIR]; //Direcciones a las que se puede mover desde una posici�n con ficha
};

//Vectores de direcci�n: {dif. fila, dif. columna }
const std::pair<int, int> dirs[NUMDIR] = { {-1,0}, {1,0}, {0,-1}, {0,1} };