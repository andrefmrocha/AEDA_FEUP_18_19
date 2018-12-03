#include "Aposta.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

bool Aposta::contem(unsigned num) const
{
	tabHInt::const_iterator it = this->numeros.find(num);
	return (it != this->numeros.end());
}


void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
	this->numeros.clear();
	vector<unsigned> storingValues;
	for(auto i: valores)
	{
		if(find(storingValues.begin(), storingValues.end(), i) == storingValues.end())
		{
			storingValues.push_back(i);
		}
		if(storingValues.size() == n)
			break;
	}
	for(auto i: storingValues)
	{
		this->numeros.insert(i);
	}
}


unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
	// TODO
	unsigned certos = 0;
	for(auto i: sorteio)
	{
		if(this->numeros.find(i) != this->numeros.end())
			certos++;
	}
	return certos;
}




