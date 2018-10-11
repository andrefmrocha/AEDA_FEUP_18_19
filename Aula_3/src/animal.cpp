
#include "animal.h"
#include<iostream>

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

string Animal::getInformacao() const
{
	string info = nome + ", " + to_string(idade);
	if(vet != NULL)
	{
		info += ", " + this->vet->getNome() + ", " + to_string(this->vet->getCod());
	}
	return info;
}

void Animal::setVet(Veterinario *v1)
{
	this->vet = v1;
}

string Animal::getVetName() const
{
	return vet->getNome();
}

int Animal::getIdade() const
{
	return this->idade;
}

Cao::Cao(string nome, int idade, string raca): Animal(nome,idade), raca(raca){}

bool Cao::eJovem() const
{
	return (this->idade < 5);
}

string Cao::getInformacao() const
{
	return Animal::getInformacao() + ", " + this->raca;
}

Voador::Voador(int vmax, int amax): velocidade_max(vmax), altura_max(amax){}

string Voador::getInformacao() const
{
	return to_string(this->velocidade_max) + ", " + to_string(this->altura_max);
}


Morcego::Morcego(string nome, int idade, int vmax, int amax): Animal(nome,idade), Voador(vmax, amax){}

bool Morcego::eJovem() const
{
	return (this->idade < 4);
}

string Morcego::getInformacao() const
{
	return Animal::getInformacao() + ", " + Voador::getInformacao();
}



