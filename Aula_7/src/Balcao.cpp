#include <queue>
#include <cstdlib>
#include "Balcao.h"

using namespace std;


Cliente::Cliente() {
	this->numPresentes = rand() % 5 + 1;
}


int Cliente::getNumPresentes() const {
	return this->numPresentes;
}


Balcao::Balcao(int te): tempo_embrulho(te) {
	this->tempo_atual = 0;
	this->prox_chegada = rand() % 20 + 1;
	this->clientes_atendidos = 0;
	this->prox_saida = 0;
}      


void Balcao:: proximoEvento()
{
	if(this->tempo_atual ==0)
	{
		this->chegada();
		this->tempo_atual = ((this->prox_saida < this->prox_chegada) ? this->prox_saida : this->prox_chegada);
	}
	else if(this->prox_chegada < this->prox_saida)
	{
		this->chegada();
		this->tempo_atual = this->prox_chegada;
	}
	else
	{
		this->tempo_atual = this->prox_saida;
		this->saida();
	}
}


void Balcao::chegada()
{
	Cliente c1;
	this->clientes.push(c1);
	if(this->clientes.size() == 1)
	{
		this->prox_saida = this->tempo_atual + c1.getNumPresentes() * this->tempo_embrulho;
	}
	this->prox_chegada = this->tempo_atual + (rand() % 20 + 1);
	cout << "tempo: " << to_string(this->tempo_atual) << endl << "chegou novo cliente com " << to_string(c1.getNumPresentes())
			<< " presentes" << endl;
}   


void Balcao::saida()
{
	Cliente c;
	try{
		c = getProxCliente();
	}
	catch(FilaVazia &e){
		cout << e.getMsg();
		prox_saida = 0;
		return;
	}

	this->getProxCliente();
	this->clientes_atendidos++;
	this->clientes.pop();
	this->prox_saida = this->tempo_atual + this->clientes.front().getNumPresentes() * this->tempo_embrulho;
}


int Balcao::getTempoAtual() const { return tempo_atual; }

int Balcao::getFilaSize() const
{
	return this->clientes.size();
}

int Balcao::getProxChegada() const { return prox_chegada; }


ostream & operator << (ostream & out, const Balcao & b1)
{
	out << "Numero de clientes atendidos: " << b1.getClientesAtendidos() << endl;
	out << "Numero de clientes em espera: " << b1.getFilaSize() << endl;
    return out;
}


int Balcao::getTempoEmbrulho() const {
	return this->tempo_embrulho;
}


int Balcao::getProxSaida() const {
	return this->prox_saida;
}


int Balcao::getClientesAtendidos() const {
	return this->clientes_atendidos;
}


Cliente & Balcao::getProxCliente() {
	if(this->clientes.size() == 0)
	{
		throw(FilaVazia());
	}
	return this->clientes.front();
}



      
