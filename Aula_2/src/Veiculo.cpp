#include "Veiculo.h"
#include <iostream>

using namespace std;

Veiculo::Veiculo(string mc, int m, int a): marca(mc), ano(a), mes(m){}

int Veiculo::info() const
{
	return 3;
}

string Veiculo::getMarca() const
{
	return marca;
}

int Veiculo::getAno() const
{
	return ano;
}

int Veiculo::getMes() const
{
	return mes;
}

Motorizado::Motorizado(string mc, int m, int a, string c, int cil): Veiculo(mc,m,a),combustivel(c), cilindrada(cil){}

int Motorizado::info() const
{
	return 5;
}

string Motorizado::getCombustivel() const
{
	return combustivel;
}

Automovel::Automovel(string mc, int m, int a,string c, int cil): Motorizado(mc,m,a,c,cil){}

int Automovel::info() const
{
	return 5;
}

Camiao::Camiao(string mc, int m, int a, string c, int cil, int cm): Motorizado(mc,m,a,c,cil), carga_maxima(cm){}

int Camiao::info() const
{
	return 6;
}

Bicicleta::Bicicleta(string mc, int m, int a,string t): Veiculo(mc,m,a), tipo(t){}

int Bicicleta::info() const
{
	return 4;
}
