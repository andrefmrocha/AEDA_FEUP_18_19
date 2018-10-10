
#include "animal.h"

int Animal::maisJovem = 5000;

Animal::Animal(string nome, int idade):nome(nome), idade(idade){
	if(idade < this->maisJovem)
		this->maisJovem = idade;
}


string Animal::getNome() const {
	return nome;
}

int Animal::getMaisJovem()
{
	return maisJovem;
}

Cao::Cao(string nome, int idade, string raca): Animal(nome,idade), raca(raca){}

bool Cao::eJovem() const
{
	return (this->idade < 5);
}

Voador::Voador(int vmax, int amax): velocidade_max(vmax), altura_max(amax){}

Morcego::Morcego(string nome, int idade, int vmax, int amax): Animal(nome,idade), Voador(vmax, amax){}

bool Morcego::eJovem() const
{
	return (this->idade < 4);
}




