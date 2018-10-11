
#include "veterinario.h"


Veterinario::Veterinario(string nome, int cod): nome(nome), codOrdem(cod){}

string Veterinario::getNome() const {
	return nome;
}


string Veterinario::getInformacao() const
{
	string info = nome + ", " + to_string(codOrdem);
	return info;
}

long Veterinario::getCod() const
{
	return this->codOrdem;
}
