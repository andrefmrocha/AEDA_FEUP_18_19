#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <vector>

using namespace std;


ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }


bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;  // a fazer
	clientes.push_back(info);
	numClientes++;
	return true;
}
 
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}
  
unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}
                   
unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return lotacao-vagas;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	clientes[pos].frequencia++;
	vagas--;
	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

// a alterar
int ParqueEstacionamento::posicaoCliente(const string & nome) const
{
	InfoCartao ic1;
	ic1.nome = nome;

	return (sequentialSearch(this->clientes, ic1));
}

bool InfoCartao::operator ==(const InfoCartao &ic1) const
{
	return this->nome == ic1.nome;
}

bool InfoCartao::operator <(const InfoCartao & ic1) const
{

	if(this->frequencia == ic1.frequencia)
	{
		return this->nome < ic1.nome;
	}
	else
	{
		return this->frequencia > ic1.frequencia;
	}
}

ClienteNaoExistente::ClienteNaoExistente(const string & nome)
{
	this->nome = nome;
}

string ClienteNaoExistente::getNome()
{
	return nome;
}

int ParqueEstacionamento::getFrequencia(const string & nome) const
{
	int pos = posicaoCliente(nome);
	if(pos == -1)
	{
		throw(ClienteNaoExistente(nome));
	}
	else
	{
		return this->clientes[pos].frequencia;
	}
}

void ParqueEstacionamento::ordenaClientesPorFrequencia()
{
	cout << endl;
	insertionSort(this->clientes);
}


vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
	vector<string> clients;
	ordenaClientesPorFrequencia();
	for(auto i: this->clientes)
	{
		if(i.frequencia >= n1 && i.frequencia <= n2)
			clients.push_back(i.nome);

	}
	return clients;
}

void ParqueEstacionamento::ordenaClientesPorNome()
{
	bool flag = false;
	do
	{
		flag = false;
		for(unsigned int i = 0; i<this->clientes.size()-1; i++)
		{
			if(clientes[i].nome > clientes[i+1].nome)
			{
				swap(clientes[i], clientes[i+1]);
				flag = true;
			}
		}
	}while(flag);
}

PosicaoNaoExistente::PosicaoNaoExistente(int valor)
{
	this->valor = valor;
}

int PosicaoNaoExistente::getValor() const
{
	return this->valor;
}

InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const
{
	if(p > this->clientes.size() - 1)
		throw(PosicaoNaoExistente(p));
	else
	{
		return this->clientes[p];
	}
}

ostream & operator << (ostream &os, const ParqueEstacionamento &pe)
{
	for(auto i: pe.getClientes())
	{
		os << "Nome: " << i.nome << ". Presente: ";
		if(i.presente)
		{
			os << "Sim";
		}
		else
		{
			os <<"Nao";
		}
		os << ". Frequencia: " << i.frequencia << endl;
	}
}

