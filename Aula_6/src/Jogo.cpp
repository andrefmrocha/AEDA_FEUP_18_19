/*
 * Jogo.cpp
 *
 */

#include "Jogo.h"
using namespace std;
#include<iostream>

unsigned Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;
  int n=1;
  int pos = frase.find(' ');
  while ( pos != string::npos ) {
	frase = frase.substr(pos+1);
	pos = frase.find(' ');
	n++;
  }
  return n;
}


Jogo::Jogo()
{}

Jogo::Jogo(list<Crianca>& lc2)
{
	this->criancas = lc2;
}

void Jogo::insereCrianca(const Crianca &c1)
{
	this->criancas.push_back(c1);
}

list<Crianca> Jogo::getCriancasJogo() const
{
	return this->criancas;
}


string Jogo::escreve() const
{
	string res;
	for(auto i: this->criancas)
	{
		res+=i.escreve()+'\n';
	}
	return res;
}


Crianca& Jogo::perdeJogo(string frase)
{
	unsigned int size = this->numPalavras(frase);
	size = (size)%criancas.size();
	cout << size << endl;
	list<Crianca>::iterator it = this->criancas.begin();
	Crianca c1, c2;
	for(it; it != this->criancas.end(); it++)
	{
		if(size == 0)
		{
			c1 = * it;
			c2 = c1;
			it = this->criancas.erase(it);
			break;
		}
		size--;
	}

	return c2;
}


list<Crianca>& Jogo::inverte()
{
	this->criancas.reverse();
	return criancas;
}


list<Crianca> Jogo::divide(unsigned id)
{
	list<Crianca> removed;
	list<Crianca>::iterator itAux;

	for(list<Crianca>::iterator it = this->criancas.begin(); it != criancas.end();)
	{
		if(it->getIdade() > id)
		{
			removed.push_back(*it);
			itAux = it;
			itAux++;
			criancas.erase(it);
			it = itAux;
		}
		else
			it++;
	}
	return removed;
}


void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
	this->criancas.insert(criancas.begin(), l1.begin(), l1.end());
}


bool Jogo::operator==(Jogo& j2)
{
	list<Crianca> c2 = j2.getCriancasJogo();
	if(c2.size() != this->criancas.size())
		return false;
	list<Crianca>::iterator it1 = this->criancas.begin();
	list<Crianca>::iterator it2 = c2.begin();
	for(int i = 0; i < c2.size(); i++)
	{
		if(!(*it1 == *it2))
			return false;
		it1++;
		it2++;
	}
	return true;
}


list<Crianca> Jogo::baralha() const
{
	// a alterar
	list<Crianca> res;
	return res;
}
