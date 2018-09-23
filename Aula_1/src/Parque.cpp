#include "Parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned nMaxCli):lotacao(lot), numMaximoClientes(nMaxCli){
	this->vagas = nMaxCli;
}

unsigned int ParqueEstacionamento::getNumLugares() const{
	return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const{
	return numMaximoClientes;
}


