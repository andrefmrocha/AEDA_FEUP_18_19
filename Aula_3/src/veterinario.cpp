
#include "veterinario.h"


Veterinario::Veterinario(string nome, int cod): nome(nome), codOrdem(cod){}

string Veterinario::getNome() const {
	return nome;
}



