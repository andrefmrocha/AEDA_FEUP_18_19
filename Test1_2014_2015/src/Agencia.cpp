/*
 * Agencia.cpp
 */

#include "Agencia.h"


//Conta
 int nextID = 0;
Conta::Conta(int nConta, float sd, int nTrans): numConta(nConta), saldo(sd), numTransacoes(nTrans), titular2(NULL)
{ }

int Conta::getNumConta() const
{ return numConta; }

float Conta::getSaldo() const
{ return saldo; }

int Conta::getNumTransacoes() const
{ return numTransacoes; }


void Conta::setTitular2(Cliente *cli2)
{ titular2=cli2; }

Cliente *Conta::getTitular2() const
{ return titular2; }



Normal::Normal(int nConta, float sd, int nTrans): Conta(nConta, sd, nTrans)
{}

DeOperacao::DeOperacao(int nConta, float tx, float sd, int nTrans): Conta(nConta, sd, nTrans), taxa(tx)
{}


//Cliente
Cliente::Cliente (string nm): nome(nm)
{}

string Cliente::getNome() const
{ return nome; }

vector<Conta *> Cliente::getContas() const
{ return contas; }

void Cliente::adicionaConta(Conta *c1)
{ contas.push_back(c1); }


//Agencia
Agencia::Agencia(string desig): designacao(desig)
{}

string Agencia::getDesignacao() const
{ return designacao; }

vector<Cliente *> Agencia::getClientes() const
{ return clientes; }

vector<Gerente> Agencia::getGerentes() const
{ return gerentes; }

void Agencia::adicionaCliente(Cliente *cli1)
{ clientes.push_back(cli1); }


//Gerente
int Gerente::getID() const
{ return ID; }

string Gerente::getNome() const
{ return nome; }


bool Conta::levantamento(float valor)
{
	if(valor > this->saldo)
		return false;
	this->saldo -= valor;
	this->numTransacoes++;
	return true;
}

void Conta::deposito(float valor)
{
	this->saldo += valor;
	this->numTransacoes++;
}


bool Normal::levantamento(float valor)
{
	return Conta::levantamento(valor);
}

bool DeOperacao::levantamento(float valor)
{
	if(valor > this->saldo)
		return false;
	this->saldo -= valor + this->taxa;
	this->numTransacoes++;
	return true;
}

Conta* Agencia::levantamento(string nome, float valor)
{
	for(auto& i: this->clientes)
	{
		if(i->getNome() == nome)
		{
			for(auto& j: i->getContas())
			{
				if(j->levantamento(valor))
				{
					return j;
				}
			}
		}
	}
	Conta *fail = new Normal(-1);
	return fail;
}

float Normal::tax()
{
	this->saldo -= 1.5;
	return this->saldo;
}

float DeOperacao::tax()
{
	return saldo;
}

float Agencia::fimMes()const
{
	float total = 0;
	for(auto& i: this->clientes)
	{
		for(auto&j: i->getContas())
		{
			total += j->tax();
		}
	}
	return total;
}

vector<Conta*> Agencia::removeCliente(string nome)
{
	vector<Conta *> contas;
	vector<Conta *> contasClientes;
	for(unsigned int i = 0;i < this->clientes.size(); i++)
	{
		if(this->clientes[i]->getNome() == nome)
		{
			for(auto j: this->clientes[i]->getContas())
			{
				if(j->getTitular2() == NULL)
				{
					contas.push_back(j);
				}
				else
				{
					contasClientes.push_back(j);
				}
			}
			this->clientes.erase(this->clientes.begin() + i);
			i--;
			break;
		}
	}

	for(auto& i: this->clientes)
	{
		for(auto& j: contasClientes)
		{
			if(i->getNome() == j->getTitular2()->getNome())
			{
				j->setTitular2(NULL);
				i->adicionaConta(j);
			}
		}
	}
	for(auto& i: this->clientes)
	{
		for(auto &j: i->getContas())
		{
			if(j->getTitular2() == NULL)
			{
				continue;
			}
			if(j->getTitular2()->getNome() == nome)
			{
				j->setTitular2(NULL);
			}
		}
	}
	return contas;
}


bool Agencia::operator <(Agencia ag)
{
	float totalIn, totalOut;
	for(auto& i: this->clientes)
	{
		for(auto&j: i->getContas())
		{
			totalIn += j->getSaldo();
		}
	}
	for(auto& i: ag.getClientes())
	{
		for(auto&j: i->getContas())
		{
			totalOut += j->getSaldo();
		}
	}
	totalIn /= this->clientes.size();
	totalOut /= ag.clientes.size();
	return totalIn < totalOut;
}

float Agencia::operator ()(string nome)
{
	float total = -1;
	for(auto i: this->clientes)
	{
		if(i->getNome() == nome)
		{
			total = 0;
			for(auto j: i->getContas())
			{
				total += j->getSaldo();
			}
		}
	}
	return total;
}


void Agencia::setGerenteID(int id)
{
	nextID = id;
}

void Agencia::adicionaGerente(string nomeGer)
{
	Gerente g(nomeGer);
	this->gerentes.push_back(g);
}

Gerente::Gerente(string nm)
{
	this->nome = nm;
	this->ID = nextID;
	nextID++;
}
