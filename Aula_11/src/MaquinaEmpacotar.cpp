/*
 * Empacotador.cpp
 */

#include "MaquinaEmpacotar.h"
#include <algorithm>
#include <sstream>

MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas): capacidadeCaixas(capCaixas)
{}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}


/* a implementar pelos estudantes */

unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {
	unsigned counter = 0;
	for(unsigned int i = 0; i < objs.size(); i++)
	{
		if(objs[i].getPeso() <= this->capacidadeCaixas)
		{
			this->objetos.push(objs[i]);
			objs.erase(objs.begin() + i);
			i--;
			counter++;
		}
	}
	return counter;
}


Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
	Caixa cx(this->capacidadeCaixas);
	vector<Caixa> boxes;
	while(!this->caixas.empty())
	{
		Caixa box = this->caixas.top();
		this->caixas.pop();
		if(box.getCargaLivre() >= obj.getPeso())
		{
			for(auto i: boxes)
			{
				this->caixas.push(i);
			}
			return box;
		}
		else
			boxes.push_back(box);
	}
	for(auto i: boxes)
	{
		this->caixas.push(i);
	}
	return cx;
}


unsigned MaquinaEmpacotar::empacotaObjetos() {
	vector<unsigned> ids;
	while(!this->objetos.empty())
	{
		Objeto obj = this->objetos.top();
		this->objetos.pop();
		Caixa caixa = this->procuraCaixa(obj);
		if(find(ids.begin(), ids.end(), caixa.getID()) == ids.end())
			ids.push_back(caixa.getID());
		caixa.addObjeto(obj);
		this->caixas.push(caixa);
	}
	return ids.size();
}

string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
	if(this->objetos.empty())
		return "Nao ha objetos!\n";
	ostringstream oss;
	HEAP_OBJS objects = this->objetos;
	while(! objects.empty())
	{
		Objeto obj = objects.top();
		objects.pop();
		oss << obj << "\n";
	}
	return oss.str();
}



Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
	if(this->caixas.empty())
		throw(MaquinaSemCaixas());
	HEAP_CAIXAS boxes = this->caixas;
	Caixa cx;
	while(!boxes.empty())
	{
		if(boxes.top().getSize() > cx.getSize())
		{
			cx = boxes.top();
		}
		boxes.pop();
	}
	return cx;
}



