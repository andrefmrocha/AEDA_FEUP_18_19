
#include "Clinica.h"

//Animal

Animal::Animal(string umNome, string umaEspecie, int numeroConsultas):
nome(umNome), especie(umaEspecie), numConsultas(numeroConsultas)
{}

string Animal::getNome() const
{ return nome; }

string Animal::getEspecie() const
{ return especie; }

int Animal::getNumConsultas() const
{ return numConsultas; }

void Animal::incNumConsultas()
{ numConsultas++; }


// Veterinario

Veterinario::Veterinario(string umNome):nome(umNome)
{}

string Veterinario::getNome() const
{ return nome; }

list<string> Veterinario::getAnimais() const
{ return meusAnimais; }

void Veterinario::addAnimal(string umNomeAnimal)
{ meusAnimais.push_back(umNomeAnimal); }


// Consulta

Consulta::Consulta(int umaHora, int umDia, int umMes, string umNomeAnimal):
	hora(umaHora), dia(umDia), mes(umMes), nomeAnimal(umNomeAnimal)
{}

string Consulta::getNomeAnimal() const
{ return nomeAnimal; }

int Consulta::getHora() const { return hora; }
int Consulta::getDia() const { return dia; }
int Consulta::getMes() const { return mes; }


void ConsultasVet::addConsulta(const Consulta &c1)
{ minhasConsultas.insert(c1); }


//Clinica

Clinica::Clinica()
{}

list<ConsultasVet> Clinica::getConsultasDisponiveis() const
{ return consultasDisponiveis; }

hashAnimal Clinica::getAnimais() const
{ return animais; }

priority_queue<Veterinario> Clinica::getVeterinarios() const
{ return veterinarios; }

void Clinica::addConsultasDisponiveisVet(const ConsultasVet &v1)
{ consultasDisponiveis.push_front(v1); }

void Clinica::addAnimal(const Animal &a1)
{ animais.insert(a1); }

void Clinica::addVeterinario(const Veterinario &v1)
{ veterinarios.push(v1); }


/////////////////////////////////////////////////////////////////////////


//TODO: Implementar corretamente o construtor e inicializacao da BST!
ConsultasVet::ConsultasVet(string umNomeVet): nomeVeterinario(umNomeVet),
		minhasConsultas(Consulta(0,0,0))
{

}


bool Consulta::operator < (const Consulta &c2) const {
	if(this->getMes() == c2.getMes())
	{
		if(this->getDia() == c2.getDia())
			return this->getHora() < c2.getHora();
		return this->getDia() < c2.getDia();
	}
	return this->getMes() < c2.getMes();
}

bool Veterinario::operator<(const Veterinario& v1) const
{
	if(this->getAnimais().size() == v1.getAnimais().size())
		return this->getNome() > v1.getNome();

	return this->getAnimais().size() > v1.getAnimais().size();
}

void Clinica::addConsultas(const vector<Consulta> consultas1, string nomeVet)
{
	for(auto i: this->consultasDisponiveis)
	{
		if(i.nomeVeterinario == nomeVet)
		{
			for(auto j: consultas1)
			{
				i.addConsulta(j);
				return;
			}
		}
	}
	ConsultasVet newVet(nomeVet);
	for(auto i: consultas1)
	{
		newVet.addConsulta(i);
	}
	this->consultasDisponiveis.push_front(newVet);
}

list<Consulta> Clinica::veConsultasDisponiveis(int dia1, int dia2, int mesC, string nomeVet)const
{
	list<Consulta> consultas;
	for(auto i: this->consultasDisponiveis)
	{
		if(i.nomeVeterinario == nomeVet)
		{
			BSTItrIn<Consulta> it(i.minhasConsultas);
			while(!it.isAtEnd())
			{
				if(it.retrieve().getMes() == mesC && it.retrieve().getDia() >= dia1 && it.retrieve().getDia() <= dia2)
				{
					consultas.push_back(it.retrieve());
				}
				it.advance();
			}
		}
	}
	return consultas;
}
/*
bool Clinica::marcaConsulta(int &horaC, int &diaC, int &mesC, string nomeAnimal, string nomeVet)
{
	Consulta prev(0, 0, 0, 0);
	for(auto i: this->consultasDisponiveis)
	{
		if(i.nomeVeterinario == nomeVet)
		{
			BSTItrIn<Consulta> it(i.minhasConsultas);
				while(!it.isAtEnd())
				{
					if(it.retrieve().getMes() == mesC)
					{

					}
					it.advance();
				}
		}
	}
}*/

Animal Clinica::fimConsulta(string umNomeAnimal, string umNomeEspecie)
{
	Animal pet(umNomeAnimal, umNomeEspecie);
	for(auto i: this->animais)
	{
		if(i == pet)
		{
			pet = i;
			this->animais.erase(i);
		}
	}
	pet.incNumConsultas();
	this->animais.insert(pet);
	return pet;
}

int Clinica::numAnimaisEspecie(string umNomeEspecie) const
{
	int counter = 0;
	for(auto i: this->animais)
	{
		if(i.getEspecie() == umNomeEspecie)
			counter++;
	}
	return counter;
}

Veterinario Clinica::alocaVeterinario(string umNomeAnimal)
{
	Veterinario vet = this->veterinarios.top();
	this->veterinarios.pop();
	vet.addAnimal(umNomeAnimal);
	this->veterinarios.push(vet);
	return vet;
}

list<string> Clinica::veterinariosMaisN(int n) const
{
	list<string>vets;
	priority_queue<Veterinario> copy = this->veterinarios;
	while(!copy.empty())
	{
		if(copy.top().getAnimais().size() > n)
			vets.push_front(copy.top().getNome());
		copy.pop();
	}
	return vets;
}

