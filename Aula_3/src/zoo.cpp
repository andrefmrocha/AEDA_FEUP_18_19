#include "zoo.h"


int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}


void Zoo::adicionaAnimal(Animal *a1)
{
	this->animais.push_back(a1);
}
