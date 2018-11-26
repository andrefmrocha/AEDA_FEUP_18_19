#include "Jogo.h"

BinaryTree<Circulo> & Jogo::getJogo() {
	return jogo;
}


ostream &operator << (ostream &os, Circulo &c1)
{
	// a alterar
	return os;
}



Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados)
{
	this->jogo = Jogo::startGame(niv, pontos, estados, 0);
}

BinaryTree<Circulo> Jogo::startGame(int niv, vector<int> &pontos, vector<bool> &estados, int pos)
{
	Circulo c(pontos[pos], estados[pos]);

	if(niv == 0)
		return BinaryTree<Circulo>(c);

	BinaryTree<Circulo> esquerda = startGame(niv-1, pontos, estados, 2*pos+1);
	BinaryTree<Circulo> direita = startGame(niv-1, pontos, estados, 2*pos+2);

	return BinaryTree<Circulo>(c, esquerda, direita);
}


string Jogo::escreveJogo()
{
	BTItrLevel<Circulo> it(this->jogo);
	string game;
	while(!it.isAtEnd())
	{
		game+= to_string(it.retrieve().getPontuacao())+ "-";
		if(it.retrieve().getEstado())
			game+="true";
		else
			game+="false";
		game+= "-" + to_string(it.retrieve().getNVisitas())+"\n";
		it.advance();
	}
	return game;
}


int Jogo::jogada()
{
	int score = 1;
	int node = 1;
	BTItrLevel<Circulo> it(this->jogo);

	while(!it.isAtEnd())
	{
		Circulo & c = it.retrieve();
		if(c.getPontuacao() != node)
		{
			it.advance();
			continue;
		}

		if(c.getEstado())
			node = node * 2 +1;
		else
			node = node * 2;
		score = c.getPontuacao();
		c.changeState();
		++c;
	}
	return score;
}



int Jogo::maisVisitado()
{
	BTItrLevel<Circulo> it(this->jogo);
	it.advance();
	int counter = 0;
	while(!it.isAtEnd())
	{
		if(counter < it.retrieve().getNVisitas())
		{
			counter = it.retrieve().getNVisitas();
		}
		it.advance();
	}
	return counter;
}




