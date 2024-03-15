#include "juego.h"
#include <string>
#include <fstream>

bool string_es_num(std::string& const s) {
	for (int i = 0; i < s.size(); ++i)
		if (!std::isdigit(s[i])) return false;

	return true;
}

bool mostrar_posibilidades_y_fijar_dir_activa(Movimiento& mov) {

	if (mov.num_dirs() > 1) {
		std::cout << "Seleccione una direccion\n";
		for (int i = 0; i < mov.num_dirs(); ++i)
			std::cout << '\t' << i + 1 << " - " << to_string(mov.direccion(i)) << '\n';

		std::cout << "Respuesta: ";
		std::string dirRespuesta;
		std::getline(std::cin, dirRespuesta);

		while (!string_es_num(dirRespuesta) || std::stoi(dirRespuesta) > mov.num_dirs() || std::stoi(dirRespuesta) <= 0) {
			std::cout << "Respuesta: ";
			std::getline(std::cin, dirRespuesta);
		}
		
		mov.fijar_dir_activa(mov.direccion(std::stoi(dirRespuesta)-1));
		return false;
	}
	else if (mov.num_dirs() == 1) {
		mov.fijar_dir_activa(mov.direccion(0));
		return false;
	}
	else {
		std::cout << "La posicion no es valida o no es posible realizar un movimiento sobre la ficha seleccionada.\n";
		return true;
	}
}

void simulacion_juego(Juego &sol) {

	do {
		sol.mostrar();
		bool errorSelecc = true;
		while (errorSelecc) {

			std::cout << "\nSeleccione la ficha que quiere mover (fila y columna): ";
			std::string f, c;
			std::cin >> f;
			char aux;
			std::cin.get(aux);
			std::getline(std::cin, c);

			while (!string_es_num(f) || !string_es_num(c)) {
				std::cout << "\nSeleccione la ficha que quiere mover (fila y columna): ";
				std::cin >> f;
				char aux;
				std::cin.get(aux);
				std::getline(std::cin, c);
			}

			Movimiento mov(std::stoi(f), std::stoi(c));
			/*Dada una posición elegida por el usuario, se averigua las
			distintas posibilidades que se tiene para moverse*/ 
			sol.posibles_movimientos(mov);

			//Se muestran por pantalla los posibles movimientos a elegir, si los hay
			errorSelecc = mostrar_posibilidades_y_fijar_dir_activa(mov);

			/*Ante un error en la selección de la ficha o posición,
			no se ejecutará el movimiento. Se solicitará otro movimiento diferente*/
			if (!errorSelecc) { 
				sol.jugar(mov); 
				break;
			}
		}
	} while (sol.estado() == JUGANDO);

	sol.mostrar();

	if (sol.estado() == GANADOR) std::cout  << "\n\t" << LGREEN << char(173) << "Enhorabuena! Has ganado :)\n\n";
	else std::cout << "\n\t" << RED << char(173) << "GAME OVER! Te has quedado bloqueado\n\n";

	std::cout << WHITE;

	//Para que el salto de línea no sea captado por el "getline" del final del programa
	char aux;
	std::cin.get(aux);
}

int main() {

	std::string respuestaFinal = "";

	while(respuestaFinal != "N"){
		
		respuestaFinal = "";

		std::string respuesta = "";

		//El usuario elige entre cargar un tablero o generar uno aleatorio
		while (respuesta != "C" && respuesta != "A") {
			std::cout << char(168) << "Prefiere cargar un tablero [C] o empezar con uno aleatorio [A]? ";
			std::getline(std::cin, respuesta);
		}

		if (respuesta == "C") { //Si se quiere jugar sobre un tablero leído de un fichero
			
			std::ifstream archivo;
			bool error = true;
			while (error) {

				std::cout << "Indique el nombre del archivo (ejemplo: archivo.txt): ";
				std::cin >> respuesta;
				archivo.open(respuesta);

				if (archivo.is_open()) {

					Juego s;

					//Se lee y simula el juego completo
					if (s.cargar(archivo)) {
						error = false;
						simulacion_juego(s);
					}
					else error = true;
				}
				else std::cout << "ERROR: no se pudo abrir el archivo indicado.\n\n";
				
			}
		}
		else { //Si se quiere jugar sobre un tablero aleatorio
			
			std::string pasos;
			std::cout << "Indique el numero de pasos para crear el tablero aleatorio: ";
			std::getline(std::cin, pasos);
			std::cout << '\n';

			while (!string_es_num(pasos) || std::stoi(pasos) <= 0) {
				std::cout << "Indique el numero de pasos para crear el tablero aleatorio: ";
				std::getline(std::cin, pasos);
				std::cout << '\n';
			}

			Juego s(std::stoi(pasos));

			simulacion_juego(s); //Se simula el juego completo
		}

		//El usuario elige si quiere o no jugar otra partida
		while (respuestaFinal != "S" && respuestaFinal != "N") {
			std::cout << char(168) << "Quiere jugar de nuevo [S/N]? ";
			std::getline(std::cin, respuestaFinal);
			std::cout << '\n';
		}
	}

	return 0;
}