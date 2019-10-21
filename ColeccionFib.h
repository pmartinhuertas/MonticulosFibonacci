//Pablo Martin Huertas


#ifndef ColeccionFib_h
#define ColeccionFib_h
#include <vector>
#include <unordered_map>
#include "ImpColeccFib.h"
#include <string>
using namespace std;


template<class T>
class ColeccionFib {
	using Nodo = typename ImpColeccFib<T>::Nodo;
public:

	ColeccionFib (): mapaNodos(), mapaMonticulos(){
		unordered_map<string, ImpColeccFib<T>>  a;
		unordered_map<double, Nodo*>  b;

		mapaNodos = b;
		mapaMonticulos = a;
	}

	void crearMonticulo(const string&identificador) {
		auto it = mapaMonticulos.find(identificador);
		if (it != mapaMonticulos.end()) cout << "Ya existe el montículo con el identificador " << identificador << '\n';
		else {
			ImpColeccFib<T> mont;
			mapaMonticulos.insert({ identificador, mont });
		}
	}

	bool isEmpty(const string&identificador) {
		auto it = mapaMonticulos.find(identificador);
		if (it == mapaMonticulos.end()) cout << "No existe el montículo con el identificador " << identificador << '\n';
		else return it->second.isEmpty();
		return false;
	}


	void insert(const string&identificador, pair<double, T> pareja) {
		auto it = mapaMonticulos.find(identificador);
		if (it == mapaMonticulos.end()) cout << "No existe el montículo con el identificador " << identificador << '\n';
		else { 
			Nodo* aux = it->second.insertarElem(pareja); 
			mapaNodos.insert(pair<double, Nodo*>(pareja.first, aux));
		}
	}

	void deleteMin(const string&identificador) {
		auto it = mapaMonticulos.find(identificador);
		if (it == mapaMonticulos.end()) cout << "No existe el montículo con el identificador " << identificador << '\n';
		else {
			if (!it->second.isEmpty()) {
				int prio = it->second.borrarMinimo();
				auto it2 = mapaNodos.find(prio);
				mapaNodos.erase(it2);
			}
		}
	}

	void decreaseKey(const string&identificador, double priori, double nuevaPriori) {
		auto it = mapaMonticulos.find(identificador);
		if (it == mapaMonticulos.end()) cout << "No existe el montículo con el identificador " << identificador << '\n';
		else {
			auto it2 = mapaNodos.find(priori);
			if (it2 == mapaNodos.end()) throw std::domain_error("No existe nodo con dicha prioridad");
			else {
				Nodo* puntero = it2->second;
				mapaNodos.erase(it2);
				mapaNodos.insert(pair<double, Nodo*>(nuevaPriori, puntero));
				it->second.decrementarClave(puntero, priori, nuevaPriori);

			}
			
		}
		
	}

	void deleteKey(const string&identificador, double priori) {
		auto it = mapaMonticulos.find(identificador);
		if (it == mapaMonticulos.end()) cout << "No existe el montículo con el identificador " << identificador << '\n';
		else {
			auto it2 = mapaNodos.find(priori);
			if (it2 == mapaNodos.end()) cout << "No existe un nodo con la prioridad indicada " << identificador << '\n';
			else {
				Nodo* puntero = it2->second;
				mapaNodos.erase(it2);
				pair<double, T> aux = it->second.findMin();
				it->second.decrementarClave(puntero, priori, aux.first - 1);
				it->second.borrarMinimo();
			}
		}
	}

	pair<double, T> findMin(const string&identificador) {
		auto it = mapaMonticulos.find(identificador);
		if (it == mapaMonticulos.end()) cout << "No existe el montículo con el identificador " << identificador << '\n';
		else {
			it->second.encuetraMinimo();
		}
	}

	void fibUnion(const string&idA, const string&idB) {
		auto itA = mapaMonticulos.find(idA);
		auto itB = mapaMonticulos.find(idB);

		if (itA != mapaMonticulos.end() && itB != mapaMonticulos.end()) {

			Nodo* unoMinimo = itA->second.devolverMinimo();
			Nodo* otroMinimo = itB->second.devolverMinimo();
			if (unoMinimo != nullptr && otroMinimo != nullptr) {
				//Une las dos listas doblemente enlazadas
				Nodo* antPrincipal = unoMinimo->ant;
				Nodo* antSecundaria = otroMinimo->ant;
				unoMinimo->ant = antSecundaria;
				antSecundaria->sig = unoMinimo;
				otroMinimo->ant = antPrincipal;
				antPrincipal->sig = otroMinimo;

				//comprobacion claves
				if (unoMinimo->pareja.first > otroMinimo->pareja.first) itA->second.setMinimo(otroMinimo);
				else  itB->second.setMinimo(unoMinimo);

			}
		}
	}

	~ColeccionFib() {
		mapaMonticulos.clear();
		mapaNodos.clear();
	}

private:

	unordered_map<string, ImpColeccFib<T>> mapaMonticulos;
	unordered_map<double, Nodo*> mapaNodos;

};
#endif

