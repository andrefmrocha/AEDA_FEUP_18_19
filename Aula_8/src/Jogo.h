#ifndef JOGO_H_
#define JOGO_H_

#include "BinaryTree.h"
#include <iostream>
#include <stdlib.h>
using namespace std;


class Circulo {
 int pontuacao;
 bool estado;
 int nVisitas;
public:
 Circulo(int p=0, bool e=false): pontuacao(p), estado(e), nVisitas(0) {}
 int getPontuacao() const { return pontuacao; }
 bool getEstado() const { return estado; }
 int getNVisitas() const { return nVisitas; }
 friend ostream &operator << (ostream &os, Circulo &c1);
 void changeState(){this->estado = !this->estado;};
 Circulo operator++(){this->nVisitas++;};
};



class Jogo {
	BinaryTree<Circulo> jogo;
public:
	Jogo(int niv, vector<int> &pontos, vector<bool> &estados);
	BinaryTree<Circulo> startGame(int niv, vector<int> &pontos, vector<bool> &estados, int pos);
	BinaryTree<Circulo> &getJogo();
	string escreveJogo();
	int jogada();
	int maisVisitado();
};


#endif
