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
	virtual string getInformacao() const;
	virtual bool eJovem() const = 0;
	string getNome() const;
	int getIdade() const;
	static int getMaisJovem();
	void setVet(Veterinario *v1);
	string getVetName() const;
};



class Cao: public Animal {
	string raca;
public:
	Cao(string nome, int idade, string raca);
	bool eJovem()const;
	string getInformacao() const;
};



class Voador {
	int velocidade_max;
	int altura_max;
public:
	Voador(int vmax, int amax);
	virtual ~Voador(){};
	virtual string getInformacao() const;
};



class Morcego: public Animal, public Voador {
public:
	Morcego(string nome, int idade, int vmax, int amax);
	bool eJovem()const;
	string getInformacao() const;
 };


#endif /* SRC_ANIMAL_H_ */
