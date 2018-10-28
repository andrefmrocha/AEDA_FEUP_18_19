/*
 * Condominio.cpp
 */

#include "Condominio.h"

int Urbanizacao::nextID = 1;

Imovel::Imovel(int areaH, string prop, int id): areaHabitacao(areaH), proprietario(prop), ID(id)
{

}

int Imovel::getID() const
{ return ID; }

void Imovel::setID(int id)
{ ID=id; }

int Imovel::getAreaHabitacao() const
{ return areaHabitacao; }

string Imovel::getProprietario() const
{ return proprietario; }


Apartamento::Apartamento(int areaH, int anda, string prop, int id): Imovel(areaH,prop,id), andar(anda)
{}

Vivenda::Vivenda(int areaH, int areaExt, bool pisc, string prop, int id):Imovel(areaH,prop,id), areaExterior(areaExt), piscina(pisc)
{}


Urbanizacao::Urbanizacao(string nm, int id): nome(nm), ID(id)
{}


void Urbanizacao::adicionaImovel(Imovel *im1)
{
	if(this->ImovelID == NULL || this->ImovelID >= 1000)
	{
		this->ImovelID = 1;
	}
	im1->setID(this->ImovelID++);
	imoveis.push_back(im1);
}



vector<Imovel *> Urbanizacao::getImoveis() const
{ return imoveis; }

string Urbanizacao::getNome() const
{ return nome; }

int Urbanizacao::getID() const
{ return ID; }


void ECondominio::adicionaUrbanizacao(Urbanizacao urb1)
{ urbanizacoes.push_back(urb1); }

vector<Urbanizacao> ECondominio::getUrbanizacoes() const
{ return urbanizacoes; }


float Imovel::mensalidade() const
{
	return (this->areaHabitacao*0.2+50);
}

float Apartamento::mensalidade() const
{
	return (Imovel::mensalidade() + this->andar);
}

float Vivenda::mensalidade() const
{
	return (Imovel::mensalidade() + this->areaExterior*0.1 + 10 * this->piscina);
}

float ECondominio::mensalidadeDe(string nome) const
{
	float total = 0;
	for(auto i: this->urbanizacoes)
	{
		for(auto j: i.getImoveis())
		{
			if(j->getProprietario() == nome)
			{
				total += j->mensalidade();
			}
		}
	}
	return total;
}

vector<Urbanizacao> ECondominio::removeUrbanizacaoDe(string nome)
{
	vector <Urbanizacao> urbans;
	for(unsigned int i = 0; this->urbanizacoes.size(); i++)
	{
		for(auto j: this->urbanizacoes[i].getImoveis())
		{
			if(j->getProprietario() == nome)
			{
				urbans.push_back(this->urbanizacoes[i]);
				this->urbanizacoes.erase(this->urbanizacoes.begin() + i);
				i--;
				break;
			}
		}
	}
	return urbans;
}


int Apartamento::getArea() const
{
	return Imovel::getAreaHabitacao();
}

int Vivenda::getArea() const
{
	return Imovel::getAreaHabitacao()+this->areaExterior;
}

vector<Imovel *> Urbanizacao::areaSuperiorA(int area1) const
{
	vector<Imovel *> casas;
	for(auto i: this->imoveis)
	{
		if(i->getArea() > area1)
		{
			casas.push_back(i);
		}
	}
	return casas;
}

unsigned int Urbanizacao::getNumeroProps() const
{
	vector<string> nomes;
	for(auto& i: this->imoveis)
	{
		bool flag = true;
		for(auto j: nomes)
		{
			if(i->getProprietario() == j)
			{
				flag = false;
				break;
			}
		}
		if(flag)
		{
			nomes.push_back(i->getProprietario());
		}
	}
	return nomes.size();
}

bool Urbanizacao::operator >(Urbanizacao urb) const
{
	float reason1, reason2;
	if(this->imoveis.size()== 0)
		return false;
	if(urb.getImoveis().size() == 0)
		return true;
	reason1 = (float)this->imoveis.size()/this->getNumeroProps();
	reason2 = (float)urb.getImoveis().size()/urb.getNumeroProps();
	return reason1 < reason2;
}

vector<Imovel *> ECondominio::operator ()(string nome) const
{
	vector<Imovel *> casas;
	for(auto i: this->urbanizacoes)
	{
		if(i.getNome() == nome)
		{
			casas = i.getImoveis();
		}
	}
	return casas;
}

Urbanizacao::Urbanizacao(string nm)
{
	this->nome = nm;
	this->ID = this->nextID++;
}

void Urbanizacao::resetID()
{
	nextID = 1;
}



