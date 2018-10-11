
#ifndef ZOO_H_
#define ZOO_H_

#include "animal.h"
#include <vector>
#include<fstream>


class Zoo {
	vector<Animal *> animais;
	vector<Veterinario *> veterinarios;
public:
	int numAnimais() const;
	int numVeterinarios() const;
	void adicionaAnimal(Animal *a1);
	string getInformacao() const;
	bool animalJovem(string nomeA) const;
	void alocaVeterinarios(istream &isV);
	bool removeVeterinario(string nomeV);
	bool operator< (Zoo & zoo2) const;
	int countIdades() const;
};


#endif /* ZOO_H_ */
