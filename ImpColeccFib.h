//Pablo Martin Huertas


#ifndef ImpColeccFib_h
#define ImpColeccFib_h
#include <vector>
#include <unordered_map>
using namespace std;

template<class T>
class ImpColeccFib {

public:
	
	struct Nodo {
		Nodo() : ant(nullptr), sig(nullptr), padre(nullptr), hijo(nullptr), marcado(false) {}
		Nodo(pair<double, T> pareja, Nodo* ant, Nodo* sig, Nodo* padre, Nodo* hijo, bool marcado) : pareja(pareja), ant(ant), sig(sig), padre(padre), hijo(hijo), marcado(false) {}
		pair<double, T> pareja;
		Nodo* ant;
		Nodo* sig;
		Nodo* padre;
		Nodo* hijo;
		bool marcado;
	};

	bool isEmpty() {
		return estaVacio();
	}

	void insert(pair<double, T> pareja) {
		insertarElem(pareja);
	}

	void deleteKey(double priori) {
		eliminarClave(priori);
	}

	pair<double, T> findMin() {
		return encuentraMinimo();
	}

	bool estaVacio() {
		return this->minimo == nullptr;
	}

	//###IMPLEMENTACION DE OPERACIONES
	pair<double, T> encuentraMinimo() {
		if (this->minimo != nullptr) return this->minimo->pareja;
		else  throw std::domain_error("El monticulo esta vacio");
	}


	Nodo* insertarElem(pair<double, T> pareja) {
		//añade nodo si el arbol es vacio
		if (this->minimo == nullptr) {
			Nodo* aux = new Nodo(pareja, nullptr, nullptr, nullptr, nullptr, false);
			aux->ant = aux;
			aux->sig = aux;
			this->minimo = aux;
			return aux;
		}
		else {
			//añade el nodo nuevo
			Nodo* temporal = this->minimo->ant;
			Nodo* aux = new Nodo(pareja, temporal, this->minimo, nullptr, nullptr, false);
			temporal->sig = aux;
			this->minimo->ant = aux;
			//comprueba si hay que actualizar el puntero al minimo
			if (pareja.first < this->minimo->pareja.first) {
				this->minimo = aux;
			}
			return aux;
		}
	}

	int borrarMinimo() {
		//Comprobamos no es vacia
		if (this->minimo != nullptr) {
			//lo guarda para borrarlo al final
			double prioridad = this->minimo->pareja.first;

			//Vemos si tiene hijos o no
			if (this->minimo->hijo == nullptr) {
				if (this->minimo == this->minimo->sig) {
					delete this->minimo;
					this->minimo = nullptr;
				}
				else {
					this->minimo->ant->sig = this->minimo->sig;
					this->minimo->sig->ant = this->minimo->ant;

					Nodo* aux = this->minimo;
					this->minimo = this->minimo->sig; //minimo temporal que se actualiza despues de consolidar
					delete aux;
				}
			}
			//Ahora si que va a tener hijos asique hay que previamente colocarlos en la lista
			else {
				if (this->minimo == this->minimo->sig) {
					Nodo* aux = this->minimo;
					this->minimo = this->minimo->hijo; //minimo temporal que se actualiza despues de consolidar
					delete aux;
				}

				//ahora ya hay lista anterior
				else {
					this->minimo->ant->sig = this->minimo->sig;
					this->minimo->sig->ant = this->minimo->ant;
					Nodo* siguiente = this->minimo->sig;
					Nodo* anterior = this->minimo->ant;
					Nodo* auxiliar1 = this->minimo->hijo;
					Nodo* auxiliar2 = this->minimo->hijo->ant;
					anterior->sig = auxiliar1;
					auxiliar1->ant = anterior;
					auxiliar2->sig = siguiente;
					siguiente->ant = auxiliar2;

					Nodo* aux = this->minimo;
					this->minimo = this->minimo->hijo; //minimo temporal que se actualiza despues de consolidar
					delete aux;
				}
				this->minimo->padre = nullptr;
			}

			consolidar();
			//solo falta actualizar el minimo
			if (this->minimo != nullptr && this->minimo->sig != this->minimo) {
				Nodo* min = this->minimo;
				Nodo* indice = this->minimo->sig;
				while (indice != this->minimo) {
					if (indice->pareja.first < min->pareja.first) min = indice;
					indice = indice->sig;
				}
				//Ahora ya tenemos localizado el minimo:
				this->minimo = min;
			}

			//Se devuelve la prioridad para que la coleccion pueda borrarla de su mapa
			return prioridad;
		}
		else  throw std::domain_error("El monticulo esta vacio");
		return -1;
	}
	

	void decrementarClave(Nodo* puntero, double priori, double nuevaPriori) {

			puntero->pareja.first = nuevaPriori;
			//1er caso: no tiene padre
			if (puntero->padre == nullptr) {
				if (nuevaPriori < this->minimo->pareja.first) this->minimo = puntero;
			}
			//2do caso: tiene un padre
			else {
				Nodo* padre = puntero->padre;
				//cortamos cuando no es el hijo principal
				if (padre->hijo != puntero) {
					puntero->ant->sig = puntero->sig;
					puntero->sig->ant = puntero->ant;
					puntero->padre = nullptr;
					this->minimo->ant->sig = puntero;
					puntero->ant = this->minimo->ant;
					this->minimo->ant = puntero;
					puntero->sig = this->minimo;
					if (nuevaPriori < this->minimo->pareja.first) this->minimo = puntero;
				}
				//cortamos cuando es el hijo principal
				else {
					//es hijo unico
					if (puntero->sig == puntero) {
						padre->hijo = nullptr;
						puntero->padre = nullptr;
						this->minimo->ant->sig = puntero;
						puntero->ant = this->minimo->ant;
						this->minimo->ant = puntero;
						puntero->sig = this->minimo;
						if (nuevaPriori < this->minimo->pareja.first) this->minimo = puntero;
					}
					//tiene otros hijos
					else {
						puntero->ant->sig = puntero->sig;
						puntero->sig->ant = puntero->ant;
						puntero->padre = nullptr;
						padre->hijo = puntero->sig;
						this->minimo->ant->sig = puntero;
						puntero->ant = this->minimo->ant;
						this->minimo->ant = puntero;
						puntero->sig = this->minimo;
						if (nuevaPriori < this->minimo->pareja.first) this->minimo = puntero;
					}
				}

				//recursion que consigue la amortizacion

				cascada(padre);
			}
	}


	//operacion auxiliar interna que se usa en decrementarClave
	void cascada(Nodo* nodoActual) {
		Nodo* minimoTest = this->minimo;
		if (!nodoActual->marcado) nodoActual->marcado = true;
		else {
			//no tiene padre (acaba recursion)
			if (nodoActual->padre == nullptr) nodoActual->marcado = !nodoActual->marcado;
			//tiene padre luego hay recursion
			else {
				Nodo* padre = nodoActual->padre;

				//no es el hijo principal
				if (padre->hijo != nodoActual) {
					nodoActual->ant->sig = nodoActual->sig;
					nodoActual->sig->ant = nodoActual->ant;
					nodoActual->padre = nullptr;
					this->minimo->ant->sig = nodoActual;
					nodoActual->ant = this->minimo->ant;
					minimoTest->ant = nodoActual;
					nodoActual->sig = this->minimo;
					nodoActual->marcado = false;
					cascada(padre);
				}
				//es el hijo principal
				else {
					//es hijo unico
					if (nodoActual->sig == nodoActual) {
						nodoActual->padre = nullptr;
						this->minimo->ant->sig = nodoActual;
						nodoActual->ant = this->minimo->ant;
						minimoTest->ant = nodoActual;
						nodoActual->sig = this->minimo;
						nodoActual->marcado = false;
						padre->hijo = nullptr;
						cascada(padre);
					}
					//no es hijo unico
					else {
						nodoActual->ant->sig = nodoActual->sig;
						padre->hijo = nodoActual->sig;
						nodoActual->sig->ant = nodoActual->ant;
						nodoActual->padre = nullptr;
						this->minimo->ant->sig = nodoActual;
						nodoActual->ant = this->minimo->ant;
						minimoTest->ant = nodoActual;
						nodoActual->sig = this->minimo;
						nodoActual->marcado = false;
						cascada(padre);
					}
				}
			}
		}
	}

	//Operacion Auxiliar de la operacion unir
	Nodo* devolverMinimo() {
		if (this->minimo != nullptr) return this->minimo;
		else return nullptr;
	}

	//Usada en la actualizacion del minimo de fibUnion
	void setMinimo(Nodo* nuevo) {
		this->minimo = nuevo;
	}

private:
	//###DATOS INTERNOS
	const int TAM_GRADOS_INICIAL = 100000;

	Nodo* minimo;

	void consolidar() {
		if (this->minimo != nullptr) {

			if (this->minimo->sig != this->minimo) {
				unsigned int cantidadResizes = 1;
				vector<Nodo*> gradoDeMonticulo(TAM_GRADOS_INICIAL, nullptr);

				//Comienza el bucle que va calculando grados y llama a link cuando encuentra dos de la misma altura
				Nodo* indice = this->minimo;
				Nodo* final = this->minimo->ant;
				while (indice != final) {
					unsigned int grado = calcularGrado(indice);
					if (gradoDeMonticulo[grado] == nullptr) gradoDeMonticulo[grado] = indice;
					else {
						while (gradoDeMonticulo[grado] != nullptr) {
							indice = link(indice, gradoDeMonticulo[grado]);
							gradoDeMonticulo[grado] = nullptr;
							grado++;
						}
						gradoDeMonticulo[grado] = indice;
					}
					indice = indice->sig;
				}

				//Se repite el codigo pues nos falta un ultimo paso del bucle para finalizar (el de this->minimo)
				unsigned int grado = calcularGrado(indice);
				if (gradoDeMonticulo[grado] == nullptr) gradoDeMonticulo[grado] = indice;
				else {
					while (gradoDeMonticulo[grado] != nullptr) {
						indice = link(indice, gradoDeMonticulo[grado]);
						gradoDeMonticulo[grado] = nullptr;
						grado++;
					}
				}
				this->minimo = indice;
			}
		}
	}

	//operacion auxiliar interna que se usa en consolidar
	Nodo* link(Nodo* nodo1, Nodo* nodo2) {
		if (nodo1->pareja.first < nodo2->pareja.first) {
			//primero arregla el numero que sale
			Nodo* aux1 = nodo2->ant;
			aux1->sig = nodo2->sig;
			nodo2->sig->ant = aux1;
			//ahora lo coloca como un hijo
			if (nodo1->hijo == nullptr) {
				nodo2->ant = nodo2;
				nodo2->sig = nodo2;
				nodo2->padre = nodo1;
				nodo1->hijo = nodo2;
			}
			else {
				Nodo* aux2 = nodo1->hijo->ant;
				nodo1->hijo->ant = nodo2;
				nodo2->sig = nodo1->hijo;
				aux2->sig = nodo2;
				nodo2->ant = aux2;
				nodo2->padre = nodo1;
			}
			return nodo1;
		}
		else {
			//en caso contrario da la vuelta a los nodos para hacerlo como antes
			link(nodo2, nodo1);
		}
	}

	unsigned int calcularGrado(Nodo* node) {
		if (node->hijo == nullptr) return 0;
		else {
			unsigned int grado = 1;
			Nodo* indice = node->hijo->sig;
			while (indice != node->hijo) {
				indice = indice->sig;
				++grado;
			}
			return grado;
		}
	}
};
#endif

