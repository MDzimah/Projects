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

const bool DEBUG = true;

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

//Inicializan el coche con su carril correspondiente
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
	while (objEnCarretera != CENTINELA) { //Se lee hasta el centinela porque nos dice que ya no hay más objetos especiales sobre el carril en cuestión
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
	std::cin >> nombreDelArchivo;

	char saltoDeLinea;
	std::cin.get(saltoDeLinea);

	std::ifstream entrada;
	entrada.open(nombreDelArchivo);


	if (entrada.is_open()) { //Si se abre el archivo, se cargan los datos en "carretera" y se devuelve "true". De lo contrario, se informa del error, se devuelve "false" y se da al usuario otra oportunidad

		//En cada vuelta se inicializa un carril y se cargan los datos leídos del fichero
		for (int i = 0; i < NUM_CARRILES; ++i) {
			iniciaCarril(carriles[i]);
			leeCarril(entrada, carriles[i]);
		}

		entrada.close();

		return true;

	}
	else {
		std::cout << "ERROR: no se pudo abrir.\n";
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
	std::cout << CHAR_LINEA_VERTICAL << '\n';

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
		//std::cout << "(Carril " << carril << ")\n"; Para facilitar la lectura de la simulación
		if (carril < NUM_CARRILES - 1) dibujaLineaDiscontinua();

	}
	dibujaLineaHorizontalInferior();
}


//Verifican si una posición es de un tipo especial ("sorpresa" o "clavo"), la última verifica si una posición está en la carretera
bool esSorpresa(const tTipoPosicion pos[], int p) {
	return pos[p] == SORPRESA;
}
bool esClavo(const tTipoPosicion pos[], int p) {
	return pos[p] == CLAVO;
}
bool enCarretera(int n) {
	return n >= 0 && n < LONG_CARRETERA;
}


//Busca la posicion sorpresa más cercana. Si el modo DEBUG es "true" (modo depuración) entonces pregunta al usuario si quiere avanzar o retroceder a la sorpresa más cercana. Del contrario (modo normal), esto último se hará de manera aleatoria
int	buscaSiguientePosSorpresa(const	tCarril& carril, int incr) {

	int m = carril.coche.pos;
	m += incr; //Como la posicion del coche es una posicion sorpresa, para no saltarse el "while", modifico "m" sumándole "incremento"
	while (enCarretera(m) && carril.posiciones[m] != SORPRESA) m += incr;


	if (enCarretera(m)) return m;
	else return 0; //En el caso de que no haya una posicion sorpresa delante o detrás de la que nos hallamos, se coloca el coche en la posición "0", en el principio
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

		std::cout << "Pasos que avanza o retrocede el coche: ";
		std::cin >> numPasos;
		std::cout << '\n';

		char saltoDeLinea;
		std::cin.get(saltoDeLinea);

		posNuevaCoche = posCoche + numPasos;

		if (posNuevaCoche < 0) return 0;
	}

	return posNuevaCoche;
}


//Analizan la posición del coche, una si el coche del carril en cuestión ha llegado a la meta y la otra si se halla en una posición especial
bool haLlegado(int posCoche) {
	return posCoche >= LONG_CARRETERA;
}
bool calculaPosicion(tCarril& carril) {

	int posOriginCoche = 0;

	if (esClavo(carril.posiciones, carril.coche.pos) && carril.coche.tiempoParado == 0) carril.coche.tiempoParado = TIEMPO_PARADO; //Para que un coche ya pinchado en un turno anterior no vuelva a estar inmovilizado "TIEMPO_PARADO" de turnos, se añade la condición de que el tiempoParado de coche ha de ser 0 necesariamente
	else if (esSorpresa(carril.posiciones, carril.coche.pos)) {
		int incremento = 0;

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


//Avanza cada carril individual y analiza las posiciones especiales gracias a las funciones "calculaPosicion" y "haLlegado"
bool avanzaCarril(tCarretera carretera, int i) {

	int posOriginalCoche = 0;
	posOriginalCoche = carretera[i].coche.pos; //Se almacena la posición del coche antes de mover el coche

	std::cout << std::setw(120) << std::setfill('-') << "-\n\n"; //Para facilitar la lectura de la simulación

	std::cout << "TURNO DEL CARRIL " << i << "\n\n";

	if (!haLlegado(carretera[i].coche.pos) && carretera[i].coche.tiempoParado == 0) {

		carretera[i].coche.pos = avanza(carretera[i].coche.pos); //Se actualiza la posición del coche
	}

	if (haLlegado(carretera[i].coche.pos)) {
		carretera[i].coche.pos = LONG_CARRETERA;
		dibujaCarretera(carretera, carretera[i].coche.pos); //Se dibuja la carretera con el coche ya en la meta. Como "avanza carril" solo se invoca en "simulaCarrera", si la posición del coche es menor que "LONG_CARRETERA", se sigue con lo que hay después en el main
		std::cout << "El coche " << i << " ha llegado a la meta\n\n";
	}
	else {
		dibujaCarretera(carretera, carretera[i].coche.pos);

		/*Con la carretera dibujada, la posición que se observa en la pantalla es analizada como posición "sorpresa" o "clavo".
		Si no es ninguna de las dos, indirectamente se analiza la posción como normal invocando de nuevo a "avanzaCarril" desde "simulaCarrera" */

		if (esClavo(carretera[i].posiciones, carretera[i].coche.pos) || carretera[i].coche.tiempoParado > 0) { //Evalúo primero si la posición en cuestión es "clavo" para evitar llamar a "calculaPosicion" inecesariamente
			calculaPosicion(carretera[i]);

			char respuestaModoNormal;

			std::cout << "Pulse la tecla \"Enter\" para continuar";
			std::cin.get(respuestaModoNormal);
			std::cout << '\n';

			while (respuestaModoNormal != '\n') {
				std::cout << "Pulse la tecla \"Enter\" para continuar";
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

			std::cout << "Pulse la tecla \"Enter\" para continuar";
			std::cin.get(respuestaModoNormal);
			std::cout << '\n';

			while (respuestaModoNormal != '\n') {
				std::cout << "Pulse la tecla \"Enter\" para continuar";
				std::cin.get(respuestaModoNormal);
				std::cout << '\n';
			}

			std::cout << "POSICION SORPRESA :) El coche ahora se halla en la posicion " << carretera[i].coche.pos << '\n';
			dibujaCarretera(carretera, carretera[i].coche.pos);

		}
	}

	return posOriginalCoche != LONG_CARRETERA && haLlegado(carretera[i].coche.pos); //Es necesario saber si anteriormente ya había llegado el coche para evitar que se actualice la clasificación por este caso
}

//Con la función anterior, aquí se avanzan todos los carriles
void avanzaCarriles(tCarretera carretera, tClasificacion& clasificacion) {

	for (int carril = 0; carril < NUM_CARRILES; ++carril) {
		if (avanzaCarril(carretera, carril)) {
			clasificacion.clasificacion[clasificacion.cont] = carril;
			++clasificacion.cont;
		}
	}

}

//Mantiene la simulación en curso solo si todos los coches no han llegado al final
tClasificacion simulaCarrera(tCarretera carretera, tListaClasificacion& lista) {
	dibujaCarretera(carretera, carretera->coche.pos);

	tClasificacion clasificacion;
	clasificacion.cont = 0;

	if (lista.cont < MAX_CARRERAS)
		clasificacion.idCarrera = lista.lista[lista.cont].idCarrera;
	else clasificacion.idCarrera = lista.lista[0].idCarrera;
	/*Cuando la lista de clasificaciones está llena, se guarda el índice de la carrera que va a ser simulada en el carril 0 de las listas de
	clasificaciones ya que el carril 0 será borrado posteriormente de las listas de clasificaciones*/

	while (clasificacion.cont < NUM_CARRILES) avanzaCarriles(carretera, clasificacion);

	return clasificacion;
}


//Subprogramas encargados de gestionar y mostrar la clasificación
std::ostream& operator<<(std::ostream& salida, tClasificacion const& cl) {

	for (int y = 0; y < NUM_CARRILES; ++y)
		salida << "    Puesto " << y + 1 << ": coche del carril " << cl.clasificacion[y] << '\n';

	return salida;
}
void iniciaListaClasificacion(tListaClasificacion& listaC) {
	listaC.cont = 0;
}

void eliminaClasificacion(tListaClasificacion& listaC, int pos) {

	for (int b = pos; b < MAX_CARRERAS - 1; ++b) listaC.lista[b] = listaC.lista[b + 1];
}
void insertaClasificacion(tListaClasificacion& listaC, const tClasificacion& clasificacion) {

	if (listaC.cont < MAX_CARRERAS)
		listaC.lista[listaC.cont] = clasificacion;
	else {
		eliminaClasificacion(listaC, 0);
		listaC.lista[MAX_CARRERAS - 1] = clasificacion;
	}

}

void guardarListaClasificacion(const tListaClasificacion& listaC) {

	std::ofstream archGuardarListaClasf;
	archGuardarListaClasf.open("clasificacion.txt", std::ios::app);

	if (listaC.cont < MAX_CARRERAS)
		archGuardarListaClasf << listaC.lista[listaC.cont - 1].idCarrera << '\n' << (archGuardarListaClasf, listaC.lista[listaC.cont - 1]);
	else archGuardarListaClasf << listaC.lista[MAX_CARRERAS - 1].idCarrera << '\n' << (archGuardarListaClasf, listaC.lista[MAX_CARRERAS - 1]);

	archGuardarListaClasf.close();
}


int main() {

	tCarretera carretera;
	while (!cargaCarretera(carretera));

	tListaClasificacion lista;
	iniciaListaClasificacion(lista);

	std::cout << "\nIntroduzca el identificador para la carrera: ";
	std::cin >> lista.lista[lista.cont].idCarrera;
	std::cout << '\n';

	char saltoDeLinea;
	std::cin.get(saltoDeLinea);

	char respOtraSim;

	do {
		srand(time(NULL));

		/* Como se indica en el guión que hay que introducir el identificador para la carrera en el main, esta función
		"simulaCarrera" necesariamente tiene que recibir la lista porque, de lo contrario, el id de la carrera se perdería*/
		insertaClasificacion(lista, simulaCarrera(carretera, lista));

		/*Si la lista no está todavía llena, las clasificaciones van entrando en la lista de clasificaciones en orden
		ascendente. En caso contrario, se elimina la primera clasificación de la lista y entra la nueva al final de la lista*/
		if (lista.cont < MAX_CARRERAS) {
			std::cout << "Clasificacion de la carrera\n" << lista.lista[lista.cont]; //Se imprime la clasificacion en la pantalla
			++lista.cont;
		}
		else std::cout << "Clasificacion de la carrera\n" << lista.lista[MAX_CARRERAS - 1];



		//Se guarda la lista de clasificaciones al terminar la simulación en el fichero
		guardarListaClasificacion(lista);


		std::cout << '\n' << char(168) << "Desea realizar otra simulacion (S/N)? ";
		std::cin >> respOtraSim;
		std::cout << '\n';

		//Si las respuestas son diferentes de "S" y "N" se pregunta al usuario de nuevo
		while (respOtraSim != 'S' && respOtraSim != 'N') {
			std::cout << char(168) << "Desea realizar otra simulacion (S/N)? ";
			std::cin >> respOtraSim;
			std::cout << '\n';
		}


		//Se comienza una nueva simulación si se desea hacerlo. De lo contrario, se guarda en "clasificacion.txt" la lista de clasificaciones actual
		if (respOtraSim == 'S') {

			std::cout << "Introduzca el identificador para la carrera: ";
			if (lista.cont < MAX_CARRERAS) std::cin >> lista.lista[lista.cont].idCarrera;
			else std::cin >> lista.lista[0].idCarrera;

			std::cout << '\n';

			char saltoDeLinea;
			std::cin.get(saltoDeLinea);

			for (int carril = 0; carril < NUM_CARRILES; ++carril) //En cada carril se coloca el coche en la posicion cero
				iniciaCoche(carretera[carril].coche);
		}
		else {
			std::ofstream archGuardarListaClasf; //Se borra el contenido del fichero
			archGuardarListaClasf.open("clasificacion.txt");

			for (int c = 0; c < lista.cont; ++c)
				archGuardarListaClasf << lista.lista[c].idCarrera << '\n' << (archGuardarListaClasf, lista.lista[c]); //Se guarda la lista de clasificaciones actual en el fichero

			archGuardarListaClasf.close();
		}

	} while (respOtraSim == 'S');

	return 0;
}