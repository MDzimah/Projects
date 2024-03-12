#include "juego.h"
#include <string>
#include <fstream>

int main() {

	std::string respuesta;
	while (respuesta != "C" && respuesta != "A") {
		std::cout << char(168) << "Prefiere cargar un tablero [C] o empezar con uno aleatorio [A]? ";
		std::getline(std::cin, respuesta);
	}
	
	if (respuesta == "C") {
		std::ifstream archivo;
		bool error = true;
		while (error) {
			std::cout << "Indique el nombre del archivo (no olvides el \".txt\" al final del nombre del mismo): ";
			std::cin >> respuesta;
			archivo.open(respuesta);
			if (archivo.is_open()) {
				Juego solitario;
				do {
					solitario.cargar(archivo);
					solitario.mostrar();
				} while (solitario.estado() == JUGANDO);
				error = false;
			}
			else std::cout << "ERROR: no se pudo abrir el archivo indicado.\n\n"; 
			
		}
	}
	else {
		Juego solitario;
		std::cout << "Indique el numero de pasos para crear el tablero aleatorio:";

	}

}