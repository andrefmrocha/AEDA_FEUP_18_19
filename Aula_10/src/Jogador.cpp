#include "Jogador.h"


void Jogador::adicionaAposta(const Aposta & ap)
{
	this->apostas.insert(ap);
}

unsigned Jogador::apostasNoNumero(unsigned num) const
{
	unsigned count = 0;
	for(auto i: this->apostas)
	{
		if(i.getNumeros().find(num) != i.getNumeros().end())
			count++;
	}
	return count;
}


tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const
{
	tabHAposta money;
	for(auto i: this->apostas)
	{
		if(i.calculaCertos(sorteio) > 3)
		{
			money.insert(i);
		}
	}
	return money;
}
