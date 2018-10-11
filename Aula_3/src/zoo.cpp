#include "zoo.h"
#include<iostream>

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

string Zoo::getInformacao() const
{
	string info = "Animais:\n";
	for(auto i: animais)
	{
		info+=i->getInformacao() + "\n";
	}
	info += "Veterinarios: \n";
	for(auto i: veterinarios)
	{
		info+=i->getInformacao() + "\n";
	}
	return info;
}

bool Zoo::animalJovem(string nomeA) const
{
	for(auto i: animais)
	{
		if(i->getNome() == nomeA)
		{
			if(i->eJovem())
			{
				return true;
			}
		}
	}
	return false;
}


void Zoo::alocaVeterinarios(istream &isV)
{
	string savingString;
	while(getline(isV, savingString))
	{
		string nome = savingString;
		nome.erase(nome.size()-1,1);
		getline(isV, savingString);
		int cod = stoi(savingString);
		Veterinario *v1 = new Veterinario(nome, cod);
		veterinarios.push_back(v1);
	}


	for(unsigned int i=0 ; i<animais.size() ; i++)
	{
		animais[i]->setVet(veterinarios[i%veterinarios.size()]);
	}

}

bool Zoo::removeVeterinario(string nomeV)
{
	for (unsigned int i = 0; i < this->veterinarios.size(); i++)
	{
		if(veterinarios[i]->getNome() == nomeV)
		{
			for(auto j: this->animais)
			{
				if (j->getVetName() == nomeV)
				{
					j->setVet(veterinarios[i+1]);
				}
			}

			this->veterinarios.erase(veterinarios.begin()+i);
			return true;
		}
	}
	return false;
}

int Zoo::countIdades()const
{
	int counter = 0;
	for (auto i: this->animais)
	{
		counter+= i->getIdade();
	}
	return counter;
}

bool Zoo::operator<(Zoo &zoo2) const
{
	return (this->countIdades() < zoo2.countIdades());
}
