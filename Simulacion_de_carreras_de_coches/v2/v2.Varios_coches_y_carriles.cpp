//Nombre y apellidos: Manuel Kwabenanro Dzimah Castro

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>

//VARIABLES
const int LONG_CARRETERA = 10,
MAX_PASOS = 2,
TIEMPO_PARADO = 2,
NUM_CARRILES = 3,
MAX_CARRERAS = 3;

const bool DEBUG = false;

const char CHAR_LINEA_HORIZONTAL = char(205),
CHAR_ESQUINA_SUPERIOR_IZQUIERDA = char(201),
CHAR_ESQUINA_SUPERIOR_DERECHA = char(187),
CHAR_ESQUINA_INFERIOR_IZQUIERDA = char(200),
CHAR_ESQUINA_INFERIOR_DERECHA = char(188),
CHAR_LINEA_VERTICAL = char(186),
CHAR_COCHE = char(254),
CHAR_CLAVO = char(193),
CHAR_SORPRESA = char(63),
CHAR_NORMAL = char(32);
std::string CENTINELA = "XX";

enum tTipoPosicion { NORMAL, CLAVO, SORPRESA };

struct tCoche {
	int pos;
	int tiempoParado;
};

struct tCarril {
	tCoche coche;
	tTipoPosicion posiciones[LONG_CARRETERA];
};

using tCarretera = tCarril[NUM_CARRILES];

struct tClasificacion {
	std::string	idCarrera;
	int	clasificacion[NUM_CARRILES];
	int	cont;
};
struct tListaClasificacion {
	tClasificacion lista[MAX_CARRERAS];
	int	cont;
};


//FUNCIONES

//Inicializan el coche y la carretera
void iniciaCoche(tCoche& coche) {
	coche.pos = coche.tiempoParado = 0;
}
void iniciaCarril(tCarril& carril) {
	for (int k = 0; k < LONG_CARRETERA; ++k) carril.posiciones[k] = NORMAL;
	iniciaCoche(carril.coche);
}


//Leen el archivo dado por el usuario y cargan la carretera
tTipoPosicion stringToEnum(std::string s) { //Transforma el string "s" en su correspondiente elemento del tipo enumerado "tTipoPosicion".

	if (s == "CLAVO") return CLAVO;
	else if (s == "SORPRESA") return SORPRESA;
	else return NORMAL;

}

void leeCarril(std::ifstream& archivo, tCarril& carril) {

	std::string objEnCarretera;
	int numObj, posObj;

	archivo >> objEnCarretera;
	while (objEnCarretera != CENTINELA) {
		archivo >> numObj;
		for (int i = 0; i < numObj; ++i) {
			archivo >> posObj;
			carril.posiciones[posObj] = stringToEnum(objEnCarretera); //Se recurre a la funcion "stringToEnum" para realizar la transformacion necesaria
		}
		archivo >> objEnCarretera;
	}
}

bool cargaCarretera(tCarretera& carriles) {

	std::cout << "Introduzca el nombre del archivo de la carretera: ";
	std::string nombreDelArchivo;
	std::cin >> nombreDelArchivo; // Pide el nombre del archivo al usuario 

	char saltoDeLinea;
	std::cin.get(saltoDeLinea); //Evita que el salto de línea al introducir el nombre del archivo se capte en la función "avanza"

	std::ifstream entrada;
	entrada.open(nombreDelArchivo);


	if (entrada.is_open()) { //Si se abre el archivo, se cargan los datos en "carretera" y se devuelve "true". De lo contrario, se informa del error, se devuelve "false" y se da al usuario otra oportunidad

		for (int i = 0; i < NUM_CARRILES; ++i) {
			iniciaCarril(carriles[i]);
			leeCarril(entrada, carriles[i]);
		}

		entrada.close();

		return true;

	}
	else {
		std::cout << "ERROR: No se pudo abrir.\n";
		return false;
	}

}


//Dibujo de los tramos individuales de la carretera

void dibujaLineaHorizontalSuperior() {
	std::cout << CHAR_ESQUINA_SUPERIOR_IZQUIERDA << std::setw(LONG_CARRETERA) << std::setfill(CHAR_LINEA_HORIZONTAL) << CHAR_LINEA_HORIZONTAL << CHAR_ESQUINA_SUPERIOR_DERECHA << '\n';
}
void dibujaCarril(const	tCarril& carril) {

	std::cout << CHAR_LINEA_VERTICAL;

	for (int j = 0; j < LONG_CARRETERA; ++j) { //Según lo cargado en las posiciones de cada carril se muestran los caracteres "clavo", "sorpresa" y "normal" por encima del carril en el que va a circular el coche 
		if (carril.posiciones[j] == CLAVO) std::cout << CHAR_CLAVO;
		else if (carril.posiciones[j] == SORPRESA) std::cout << CHAR_SORPRESA;
		else std::cout << CHAR_NORMAL;
	}

	std::cout << CHAR_LINEA_VERTICAL << '\n' << CHAR_LINEA_VERTICAL;

	//Se muestra el carril por donde circula el coche teniendo en cuenta la posición del coche
	for (int k = 0; k < carril.coche.pos; ++k) std::cout << ' ';
	std::cout << CHAR_COCHE;
	for (int l = 0; l < LONG_CARRETERA - (carril.coche.pos + 1); ++l) std::cout << ' ';
	std::cout << CHAR_LINEA_VERTICAL;

}
void dibujaLineaDiscontinua() {

	std::cout << CHAR_LINEA_VERTICAL;
	for (int v = 0; v < LONG_CARRETERA / 2; ++v) std::cout << CHAR_LINEA_HORIZONTAL << ' ';
	std::cout << CHAR_LINEA_VERTICAL << '\n';
}
void dibujaLineaHorizontalInferior() {
	std::cout << CHAR_ESQUINA_INFERIOR_IZQUIERDA << std::setw(LONG_CARRETERA) << std::setfill(CHAR_LINEA_HORIZONTAL) << CHAR_LINEA_HORIZONTAL << CHAR_ESQUINA_INFERIOR_DERECHA << "\n\n";
}

//Dibujo global de la carretera
void dibujaCarretera(const tCarretera carretera, int posCocche) {
	dibujaLineaHorizontalSuperior();
	for (int carril = 0; carril < NUM_CARRILES; ++carril) {
		dibujaCarril(carretera[carril]);
		std::cout << " \t (Carril " << carril << ")\n"; //Para facilitar la lectura de la simulación
		if (carril < NUM_CARRILES - 1) dibujaLineaDiscontinua();

	}
	dibujaLineaHorizontalInferior();
}



//Verifican si una posición es de un tipo especial (sorpresa o clavo), la última verifica si una posición está en la carretera
bool esSorpresa(const tTipoPosicion pos[], int p) {
	return pos[p] == SORPRESA;
}
bool esClavo(const tTipoPosicion pos[], int p) {
	return pos[p] == CLAVO;
}
bool enCarretera(int n) {
	return n >= 0 && n < LONG_CARRETERA;
}


//Busca la posicion sorpresa más cercana. Si el modo DEBUG es "true" (modo depuración) entonces pregunta al usuario si quiere avanzar o retroceder a la sorpresa más cercana. Del contrario (modo normal), esto último es de manera aleatoria
int	buscaSiguientePosSorpresa(const	tCarril& carril, int incr) {

	int m = carril.coche.pos;
	m += incr; //Puesto que "posIni" es inicialmente una posicion sorpresa, para no saltarse el "while", hay que modificar "m" sumándole "incremento"
	while (enCarretera(m) && carril.posiciones[m] != SORPRESA) m += incr;


	if (enCarretera(m)) return m;
	else return 0; //En el caso de que no haya una posicion sorpresa delante o detrás de la que nos hallamos, se coloca el coche en la posición "0", el principio
}


//Calcula la nueva posición del coche. En el modo depuración, el número de pasos es introducido por el usuario. En el modo normal, el número de pasos es generado aleatoriamente
int avanza(int posCoche) {

	int numPasos, posNuevaCoche;

	if (!DEBUG) {

		numPasos = 1 + rand() % MAX_PASOS; //Genera un número aleatorio entre 1 y MAX_PASOS, que es sumado luego a la posición del coche
		posNuevaCoche = posCoche + numPasos;

		if (numPasos > 1) std::cout << "El coche avanza " << numPasos << " pasos\n\n";
		else std::cout << "El coche avanza " << numPasos << " paso\n\n";


		char respuestaModoNormal;

		std::cout << "Pulse la tecla \"Enter\" para continuar";
		std::cin.get(respuestaModoNormal); //Se capta el primer salto de línea ("Enter") después de imprimir la frase, no un salto de línea anterior
		std::cout << '\n';

		while (respuestaModoNormal != '\n') {
			std::cout << "Pulse la tecla \"Enter\" para continuar";
			std::cin.get(respuestaModoNormal);
			std::cout << '\n';
		}

	}
	else {

		std::cout << std::setw(120) << std::setfill('-') << "-\n\n"; //Para facilitar la lectura de la simulación

		std::cout << "Pasos que avanza o retrocede el coche: ";
		std::cin >> numPasos;

		char saltoDeLinea;
		std::cin.get(saltoDeLinea);

		posNuevaCoche = posCoche + numPasos;

		if (posNuevaCoche < 0) return 0;
	}

	return posNuevaCoche;
}

//Analiza el caso en el que la posición del coche es mayor o igual que la meta
bool haLlegado(int posCoche) {
	return posCoche >= LONG_CARRETERA;
}


//Analiza la posición del coche
bool calculaPosicion(tCarril& carril) {

	int posOriginCoche = 0;

	if (esClavo(carril.posiciones, carril.coche.pos) && carril.coche.tiempoParado == 0) carril.coche.tiempoParado = TIEMPO_PARADO; //Para que un coche ya pinchado en un turno anterior no vuelva a estar inmovilizado "TIEMPO_PARADO" de turnos, se añade la condición de que el tiempoParado de coche ha de ser 0 necesariamente
	else if (esSorpresa(carril.posiciones, carril.coche.pos)) {
		int incremento;

		if (!DEBUG) {
			incremento = rand() % 2;

			if (incremento == 0) --incremento;

		}
		else {

			int incremento;
			std::cout << char(168) << "Desea avanzar o retroceder hacia la posicion de la sorpresa mas cercana (1/-1)? ";
			std::cin >> incremento;

			char saltoDeLinea;
			std::cin.get(saltoDeLinea); //Evita que el salto de línea al introducir la respuesta se capte en la función "avanza"
			std::cout << '\n';


			//Si las respuestas son diferentes de "1" y "-1" se pregunta al usuario de nuevo
			while (incremento != 1 && incremento != -1) {
				std::cout << char(168) << "Desea avanzar o retroceder hacia la posicion de la sorpresa mas cercana (1/-1)? ";
				std::cin >> incremento;
				std::cin.get(saltoDeLinea);
				std::cout << '\n';
			}
			if (incremento == 0) --incremento;

		}

		/*Como se indica que esta funcion tiene que devolver "true" solo si la posicion del coche es sorpresa, hace falta almacenar la posicion original del coche antes
		de modificarla. De este modo, al volver a la funcion "avanzaCarril", "calculaPosicion" es "true" y se dibuja la carretera correspondiente en lugar de saltarlo*/
		posOriginCoche = carril.coche.pos;


		carril.coche.pos = buscaSiguientePosSorpresa(carril, incremento);
	}

	return esSorpresa(carril.posiciones, posOriginCoche);
}



//Actualiza la posición del coche con las datos conseguidos del análisis de la posición del coche en "calculaPosición"
bool avanzaCarril(tCarretera carretera, int i) {

	std::cout << std::setw(120) << std::setfill('-') << "-\n\n"; //Para facilitar la lectura de la simulación

	std::cout << "Avanzando en el carril " << i << "...\n\n";

	if (!haLlegado(carretera[i].coche.pos) && carretera[i].coche.tiempoParado == 0) carretera[i].coche.pos = avanza(carretera[i].coche.pos); //Se actualiza la posición del coche

	if (haLlegado(carretera[i].coche.pos)) {
		carretera[i].coche.pos = LONG_CARRETERA;
		dibujaCarretera(carretera, carretera[i].coche.pos); //Se dibuja la carretera con el coche ya en la meta. Como "avanza carril" solo se invoca en "simulaCarrera", si la posición del coche es menor que "LONG_CARRETERA", se sigue con lo que hay después en el main
	}
	else {
		dibujaCarretera(carretera, carretera[i].coche.pos);

		/*Con la carretera dibujada, la posición que se observa en la pantalla es analizada como posición "sorpresa" o "clavo".
		Si no es ninguna de las dos, indirectamente se analiza la posción como normal invocando de nuevo a "avanzaCarril" desde "simulaCarrera" */

		if (esClavo(carretera[i].posiciones, carretera[i].coche.pos) || carretera[i].coche.tiempoParado > 0) { //Evalúo primero si la posición en cuestión es "clavo" para evitar llamar a "calculaPosicion" inecesariamente
			calculaPosicion(carretera[i]);

			char respuestaModoNormal;

			std::cout << "Pulse la tecla " << "\"Enter\"" << " para continuar";
			std::cin.get(respuestaModoNormal);
			std::cout << '\n';

			while (respuestaModoNormal != '\n') {
				std::cout << "Pulse la tecla " << "\"Enter\"" << " para continuar";
				std::cin.get(respuestaModoNormal);
				std::cout << '\n';
			}

			if (carretera[i].coche.tiempoParado == TIEMPO_PARADO) std::cout << "El coche se ha pinchado. Va estar " << TIEMPO_PARADO << " turnos sin moverse\n\n";
			else {
				if (carretera[i].coche.tiempoParado > 1) std::cout << "Coche en carril " << i << " pinchado. Va a estar " << carretera[i].coche.tiempoParado << " turnos sin moverse\n\n";
				else std::cout << "Coche en carril " << i << " pinchado. Va a estar " << carretera[i].coche.tiempoParado << " turno sin moverse\n\n";
			}

			--carretera[i].coche.tiempoParado;
		}
		else if (calculaPosicion(carretera[i])) {

			char respuestaModoNormal;

			std::cout << "Pulse la tecla " << "\"Enter\"" << " para continuar";
			std::cin.get(respuestaModoNormal);
			std::cout << '\n';

			while (respuestaModoNormal != '\n') {
				std::cout << "Pulse la tecla " << "\"Enter\"" << " para continuar";
				std::cin.get(respuestaModoNormal);
				std::cout << '\n';
			}

			std::cout << "POSICION SORPRESA :) El coche ahora se halla en la posicion " << carretera[i].coche.pos << '\n';
			dibujaCarretera(carretera, carretera[i].coche.pos);

		}
	}

	return haLlegado(carretera[i].coche.pos);
}

void avanzaCarriles(tCarretera carretera, tClasificacion clasificacion) {

	for (int carril = 0; carril < NUM_CARRILES; ++carril) {
		if (avanzaCarril(carretera, carril)) {
			clasificacion.clasificacion[clasificacion.cont] = carril;
			++clasificacion.cont;
		}
	}

}




//Mantiene la simulación en curso mientras se de la condición dada
tClasificacion simulaCarrera(tCarretera carretera, tListaClasificacion lista) { //PREGUNTAR A PITA SI FALTA PONER tListaClasificacion lista en la cabecera de la funcion (en el guión de la práctica no está)
	dibujaCarretera(carretera, carretera->coche.pos);
	while (carretera->coche.pos < LONG_CARRETERA) avanzaCarriles(carretera, lista.lista[lista.lista->cont]);

	return lista.lista[lista.lista->cont];
}

//Subprogramas encargados de gestionar y mostrar la clasificación

std::ostream& operator<<(std::ostream& salida, tClasificacion const& cl) {

	salida << cl.idCarrera << '\n';
	for (int y = 0; y < cl.cont; ++y)
		salida << "\tPuesto " << y << ": coche del carril " << cl.clasificacion[y] << '\n';

	return salida;
}

void iniciaListaClasificacion(tListaClasificacion& listaC) {
	listaC.cont = listaC.lista->cont = 0;
}

void eliminaClasificacion(tListaClasificacion& listaC, int pos) {

	for (int b = pos; b < MAX_CARRERAS - 1; ++b) listaC.lista[b] = listaC.lista[b + 1];
}
void insertaClasificacion(tListaClasificacion& listaC, const tClasificacion& clasificacion) {

	if (listaC.cont == MAX_CARRERAS) eliminaClasificacion(listaC, 0);

	listaC.lista[listaC.cont - 1] = clasificacion;

}

void guardarListaClasificacion(const tListaClasificacion& listaC) {

	std::ofstream archGuardarListaClasf;
	archGuardarListaClasf.open("clasificacion.txt");
	archGuardarListaClasf << (archGuardarListaClasf, listaC.lista);

}

int main() {

	std::string respOtraSim;

	do {
		srand(time(NULL));

		tCarretera carretera;
		tListaClasificacion lista;

		while (!cargaCarretera(carretera)); //Carga los datos a "carretera", un array de tipo "tCarretera" (enumerado)

		iniciaListaClasificacion(lista);

		std::cout << "Introduzca el identificador para la carrera: ";
		std::cin >> lista.lista->idCarrera;
		std::cout << '\n';

		char saltoDeLinea;
		std::cin.get(saltoDeLinea);

		simulaCarrera(carretera, lista); //Se simula la carrera

		guardarListaClasificacion(lista); //Se guarda la lista de clasificaciones al terminar la simulación


		std::cout << char(168) << "Desea realizar otra simulacion (S/N)? ";
		std::cin >> respOtraSim;
		std::cout << '\n';

		//Si las respuestas son diferentes de "S" y "N" se pregunta al usuario de nuevo
		while (respOtraSim != "S" && respOtraSim != "N") {
			std::cout << char(168) << "Desea realizar otra simulacion (S/N)? ";
			std::cin >> respOtraSim;
			std::cout << '\n';
		}

	} while (respOtraSim == "S");


	return 0;

}