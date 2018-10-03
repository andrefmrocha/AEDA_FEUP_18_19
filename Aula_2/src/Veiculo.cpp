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

bool Veiculo::operator <(const Veiculo &v) const
{
	if(this->ano == v.getAno())
		return (this->mes < v.getMes());
	else
		return (this->ano < v.getAno());
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

float Motorizado::calcImposto() const
{
	if(this->combustivel == "gasolina")
	{
		if(this->cilindrada <= 1000)
		{
			if(this->getAno() <=1995)
				return 8.10;
			else
				return 14.56;
		}
		else if(this->cilindrada <=1300)
		{
			if(this->getAno() <=1995)
				return 14.56;
			else
				return 29.06;
		}
		else if(this->cilindrada <=1750)
		{
			if(this->getAno() <=1995)
				return 22.65;
			else
				return 45.15;
		}
		else if(this->cilindrada <=2600)
		{
			if(this->getAno() <=1995)
				return 54.89;
			else
				return 113.98;
		}
		else if(this->cilindrada <=3500)
		{
			if(this->getAno() <=1995)
				return 87.13;
			else
				return 181.17;
		}
		else
		{
			if(this->getAno() <=1995)
				return 148.37;
			else
				return 320.89;
		}

	}
	else
	{

		if(this->cilindrada <= 1500)
		{
			if(this->getAno() <=1995)
				return 8.10;
			else
				return 14.56;
		}
		else if(this->cilindrada <=2000)
		{
			if(this->getAno() <=1995)
				return 14.56;
			else
				return 29.06;
		}
		else if(this->cilindrada <=3000)
		{
			if(this->getAno() <=1995)
				return 22.65;
			else
				return 45.15;
		}
		else
		{
			if(this->getAno() <=1995)
				return 54.89;
			else
				return 113.98;
		}

	}
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

float Bicicleta::calcImposto() const
{
	return 0;
}
