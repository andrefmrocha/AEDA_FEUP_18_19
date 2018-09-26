#include "Parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned nMaxCli):lotacao(lot), numMaximoClientes(nMaxCli), vagas(lot){
	cout << lotacao << " " << numMaximoClientes <<  " " << vagas << endl;
}

unsigned int ParqueEstacionamento::getNumLugares() const{
	return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const{
	return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const{
	for (size_t i = 0; i < clientes.size(); i++)
		{
			if (clientes[i].nome == nome){
				return i;
			}
		}
	return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome){
	if(numMaximoClientes == clientes.size())
		return false;
	InfoCartao client;
	client.nome = nome;
	client.presente = false;
	clientes.push_back(client);
	return true;
}

bool ParqueEstacionamento::entrar(const string & nome){
	int index = posicaoCliente(nome);
	if(index == -1)
		return false;
	if(clientes[index].presente == true)
		return false;
	if(vagas==0)
		return false;
	clientes[index].presente = true;
	vagas--;
	return true;
}

bool ParqueEstacionamento::retiraCliente(const string & nome){
	int index = posicaoCliente(nome);
	if(index == -1 || clientes[index].presente==true)
	{
		return false;
	}
	{
		clientes.erase(clientes.begin()+index);
		return true;
	}
}

bool ParqueEstacionamento::sair(const string & nome){
	int index = posicaoCliente(nome);
	if(index == -1 || clientes[index].presente==false)
	{
		return false;
	}
	{
		clientes[index].presente = false;
		return true;
	}
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const{
	return (lotacao - vagas);
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const{
	return clientes.size();
}

