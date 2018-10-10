#ifndef SRC_ANIMAL_H_
#define SRC_ANIMAL_H_

#include "veterinario.h"
#include <string>
using namespace std;

class Animal {
protected:
	string nome;
	int idade;
	Veterinario *vet;
	static int maisJovem;
public:
	Animal(string nome, int idade);
	virtual ~Animal(){};
	virtual bool eJovem() const = 0;
	string getNome() const;
	static int getMaisJovem();
};



class Cao: public Animal {
	string raca;
public:
	Cao(string nome, int idade, string raca);
	bool eJovem()const;

};



class Voador {
	int velocidade_max;
	int altura_max;
public:
	Voador(int vmax, int amax);
	virtual ~Voador(){};
	//completar
};



class Morcego: public Animal, public Voador {
public:
	Morcego(string nome, int idade, int vmax, int amax);
	 bool eJovem()const;
	 };


#endif /* SRC_ANIMAL_H_ */
