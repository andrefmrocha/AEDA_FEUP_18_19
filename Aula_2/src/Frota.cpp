#include "Frota.h"
#include <string>
#include<iostream>
#include<climits>

using namespace std;

void Frota::adicionaVeiculo(Veiculo *v1)
{
	veiculos.push_back(v1);
}

int Frota::numVeiculos() const
{
	return veiculos.size();
}

int Frota::menorAno() const
{
	int ano = INT_MAX;
	if(numVeiculos() == 0)
	{
		return 0;
	}
	for(auto i: veiculos)
	{
		if(i->getAno() < ano)
		{
			ano = i->getAno();
		}

	}
	return ano;
}

ostream & operator<<(ostream &o, const Frota &f)
{
	for (auto i: f.veiculos)
	{
		o << i->getMarca() << " do Ano " << i->getAno() << " do Mês " << i->getMes() << "." << endl;
	}
	return (o);
}

vector<Veiculo *> Frota::operator ()(int anoM) const
{
	vector<Veiculo *> vecs;
	for (auto i: this->veiculos)
	{
		if(i->getAno() == anoM)
			vecs.push_back(i);
	}
	return vecs;
}
