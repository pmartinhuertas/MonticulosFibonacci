//Pablo Martin Huertas

#include "ColeccionFib.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	
	//Test 1 (insercciones y borrados de minimo consolidando)
	ColeccionFib<string> prueba;
	string id1 = "MonticuloTest1";
	prueba.crearMonticulo(id1);

	prueba.insert(id1,pair<double, string>(1, "A"));    //1
	prueba.deleteMin(id1);                               //2
	prueba.insert(id1, pair<double, string>(2, "B"));    //3
	prueba.insert(id1, pair<double, string>(3, "C"));    //4
	prueba.insert(id1, pair<double, string>(0, "Z"));    //5
	prueba.deleteMin(id1);                               //6
	prueba.insert(id1, pair<double, string>(1, "A"));    //7
	prueba.insert(id1, pair<double, string>(4, "D"));    //8
	prueba.deleteMin(id1);                               //9
	prueba.insert(id1, pair<double, string>(1, "A"));    //10
	prueba.insert(id1, pair<double, string>(5, "E"));    //11
	prueba.insert(id1, pair<double, string>(6, "F"));    //12
	prueba.deleteMin(id1);                               //13
	

	/*
	//Test 2 (decremento de claves y corte en cascada)
	ColeccionFib<string> prueba;
	string id2 = "MonticuloTest2";
	prueba.crearMonticulo(id2);

	prueba.insert(id2, pair<double, string>(1, "A"));    //1
	prueba.insert(id2, pair<double, string>(2, "B"));    //2
	prueba.insert(id2, pair<double, string>(3, "C"));    //3
	prueba.insert(id2, pair<double, string>(4, "D"));    //4
	prueba.insert(id2, pair<double, string>(5, "E"));    //5
	prueba.insert(id2, pair<double, string>(6, "F"));    //6
	prueba.insert(id2, pair<double, string>(7, "G"));    //7
	prueba.insert(id2, pair<double, string>(8, "H"));    //8
	prueba.insert(id2, pair<double, string>(9, "I"));    //9
	prueba.deleteMin(id2);                               //10
	prueba.decreaseKey(id2, 7, 1);                       //11
	prueba.decreaseKey(id2, 8, 0);                       //12
	*/


	/*
	//Test 3 (Eliminacion de una clave concreta)
	ColeccionFib<string> prueba;
	string id3 = "MonticuloTest3";
	prueba.crearMonticulo(id3);

	prueba.insert(id3, pair<double, string>(1, "A"));    //1
	prueba.insert(id3, pair<double, string>(2, "B"));    //2
	prueba.insert(id3, pair<double, string>(3, "C"));    //3
	prueba.insert(id3, pair<double, string>(4, "D"));    //4
	prueba.insert(id3, pair<double, string>(5, "E"));    //5
	prueba.insert(id3, pair<double, string>(6, "F"));    //6
	prueba.insert(id3, pair<double, string>(7, "G"));    //7
	prueba.insert(id3, pair<double, string>(8, "H"));    //8
	prueba.insert(id3, pair<double, string>(9, "I"));    //9
	prueba.deleteMin(id3);                               //10
	prueba.deleteKey(id3, 8);                            //11
	*/

	/*
	//Test 4 (Union y operaciones posteriores)
	ColeccionFib<string> prueba;
	string id4A = "MonticuloTest4A";
	prueba.crearMonticulo(id4A);
	string id4B = "MonticuloTest4B";
	prueba.crearMonticulo(id4B);

	prueba.insert(id4A, pair<double, string>(1, "A"));    //1
	prueba.insert(id4A, pair<double, string>(2, "B"));    //2
	prueba.insert(id4A, pair<double, string>(3, "C"));	  //3
	prueba.insert(id4A, pair<double, string>(4, "D"));    //4
	prueba.deleteMin(id4A);								  //5
	prueba.insert(id4B, pair<double, string>(0, "E"));    //6
	prueba.insert(id4B, pair<double, string>(5, "F"));    //7
	prueba.fibUnion(id4A, id4B);						  //8
	prueba.decreaseKey(id4A, 3, -1);				      //9
	prueba.deleteKey(id4A, 0);							  //10
	*/


	return 0;
}