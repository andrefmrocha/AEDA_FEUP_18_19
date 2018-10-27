#include "Escritorio.h"
#include <iostream>


//Documento
Documento::Documento(int nPag, float pP, float pA):
			numPaginas(nPag), pPreto(pP), pAmarelo(pA)
{ }
Documento::~Documento() {}

int Documento::getNumPaginas() const { return numPaginas; }

float Documento::getPercentagemPreto() const { return pPreto; }

float Documento::getPercentagemAmarelo() const { return pAmarelo; }



//Impressora
Impressora::Impressora(string cod, int a): codigo(cod), ano(a)
{}
Impressora::~Impressora() {}

string Impressora::getCodigo() const
{ return codigo; }

int Impressora::getAno() const
{ return ano; }

vector<Documento> Impressora::getDocumentosImpressos() const
{ return docsImpressos; }



//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner): Impressora(cod, a), numPagImprimir(toner)
{}

int ImpressoraPB::getNumPaginasImprimir() const
{ return numPagImprimir; }



//ImpressoraCores
ImpressoraCores::ImpressoraCores(string cod, int a, int toner): Impressora(cod, a),
		numPagImprimirPreto(toner), numPagImprimirAmarelo(toner)
{}

int ImpressoraCores::getNumPaginasImprimir() const {
	if (numPagImprimirPreto < numPagImprimirAmarelo) return (int)numPagImprimirPreto;
	return (int)numPagImprimirAmarelo;
}



//Funcionario
Funcionario::Funcionario(string cod): codigo(cod)
{}
Funcionario::~Funcionario() {}

void Funcionario::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

vector<Impressora *> Funcionario::getImpressoras() const
{ return impressoras; }

string Funcionario::getCodigo() const
{ return codigo; }



//Escritorio
Escritorio::Escritorio() {}
Escritorio::~Escritorio() {}

void Escritorio::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

void Escritorio::adicionaFuncionario(Funcionario f1)
{ funcionarios.push_back(f1); }

vector<Impressora *> Escritorio::getImpressoras() const
{ return impressoras; }


int Escritorio::numImpressorasSemResponsavel() const
{
	vector <Impressora *> printers;
	for (auto i: this->funcionarios)
	{
		for(auto j: i.getImpressoras())
		{
			bool flag=true;
			for(auto z: printers)
			{
				if(j->getCodigo() == z->getCodigo())
				{
					flag = false;
				}
			}
			if(flag)
			{
				printers.push_back(j);
			}
		}
	}
	return this->impressoras.size() - printers.size();

}

vector<Impressora *> Escritorio::retiraImpressoras(int ano)
{
	vector<Impressora *> removed;
	for(unsigned int i = 0; i < this->impressoras.size(); i++)
	{
		if(this->impressoras[i]->getAno() < ano)
		{
			removed.push_back(this->impressoras[i]);
			this->impressoras.erase(this->impressoras.begin() + i);
			i--;
		}
	}
	return removed;
}

bool ImpressoraPB::imprime(Documento doc)
{
	if(doc.getNumPaginas() > this->numPagImprimir)
		return false;
	this->numPagImprimir-=doc.getNumPaginas();
	this->docsImpressos.push_back(doc);
	return true;
}

bool ImpressoraCores::imprime(Documento doc)
{
	if(doc.getNumPaginas()*doc.getPercentagemPreto() > this->numPagImprimirPreto || doc.getNumPaginas()*doc.getPercentagemAmarelo() > this->numPagImprimirAmarelo)
		return false;
	this->numPagImprimirPreto -= doc.getNumPaginas()*doc.getPercentagemPreto();
	this->numPagImprimirAmarelo -= doc.getNumPaginas()*doc.getPercentagemAmarelo();
	this->docsImpressos.push_back(doc);
	return true;
}




