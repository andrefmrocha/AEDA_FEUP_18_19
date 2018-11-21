#include <iostream>
#include <string>
#include <fstream>
#include "Dicionario.h"
#include "BST.h"

using namespace std;


BST<PalavraSignificado> Dicionario::getPalavras() const
{ return palavras; }



bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const
{
	return this->getPalavra() < ps1.getPalavra();
}


void Dicionario::lerDicionario(ifstream &fich)
{
	string savingString;
	while(getline(fich, savingString))
	{
		string nome= savingString;
		nome = nome.substr(0, nome.find('\r'));
		getline(fich, savingString);
		string significado = savingString;
		significado = significado.substr(0, significado.find('\r'));
		this->palavras.insert(PalavraSignificado(nome, significado));
	}
}


string Dicionario::consulta(string palavra) const
{
	BSTItrIn<PalavraSignificado> it(this->palavras);
	PalavraSignificado prev("",""), current("","");
	while(!it.isAtEnd())
	{
		prev = current;
		current = it.retrieve();
		if(palavra < it.retrieve().getPalavra())
			break;
		if(it.retrieve().getPalavra() == palavra)
		{
			return it.retrieve().getSignificado();
		}
		it.advance();
	}
	throw(PalavraNaoExiste(prev.getPalavra(), prev.getSignificado(), current.getPalavra(), current.getSignificado()));
}


bool Dicionario::corrige(string palavra, string significado)
{
	BSTItrIn<PalavraSignificado> it(this->palavras);
	while(!it.isAtEnd())
	{
		if(palavra < it.retrieve().getPalavra())
			break;
		if(it.retrieve().getPalavra() == palavra)
		{
			this->palavras.remove(it.retrieve());
			this->palavras.insert(PalavraSignificado(palavra, significado));
			return true;
		}
		it.advance();
	}
	this->palavras.insert(PalavraSignificado(palavra, significado));
	return false;
}


void Dicionario::imprime() const
{
	BSTItrIn<PalavraSignificado> it(this->palavras);
	while(!it.isAtEnd())
	{
		cout << it.retrieve().getPalavra() << endl << it.retrieve().getSignificado() << endl;
		it.advance();
	}
}
PalavraNaoExiste::PalavraNaoExiste(string pAntes, string sigAntes, string pApos, string sigApos)
{
	this->pAntes = pAntes;
	this->sigAntes = sigAntes;
	this->pApos = pApos;
	this->sigApos = sigApos;
}

