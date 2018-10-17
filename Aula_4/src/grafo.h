#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo(){};
    ~Grafo(); 
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const;
    int indiceNo(const N &dados);
};




// excecao  NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }



// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};

template<class N>
class ArestaRepetida{
public:
	N n1;
	N n2;
	ArestaRepetida(N n1, N n2)
	{
		this->n1 = n1;
		this->n2 = n2;
	}
};

template<class N>
class ArestaInexistente{
public:
	N n1;
	N n2;
	ArestaInexistente(N n1, N n2)
	{
		this->n1 = n1;
		this->n2 = n2;
	}
};



template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &ar)
{
	out << "Aresta repetida: " << ar.n1 << " , " << ar.n2;
	return out;
}

template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaInexistente<N> &ar)
{
	out << "Aresta inexistente: " << ar.n1 << " , " << ar.n2;
	return out;
}

template<class N, class A>
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> gr)
{
	gr.imprimir(out);
	return out;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template<class N, class A>
Grafo<N,A>::~Grafo()
{
	for (auto i: this->nos)
		delete i;
}

template<class N, class A>
int Grafo<N,A>::numNos() const
{
	return this->nos.size();
}

template<class N, class A>
int Grafo<N,A>::numArestas() const
{
	int counter = 0;
	for (unsigned int i = 0; i < this->nos.size(); i++)
	{
		counter+=(this->nos[i])->arestas.size();
	}
	return counter;
}

template<class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirNo(const N& dados)
{
	for(auto i: this->nos)
	{
		if(i->info == dados)
		{
			throw(NoRepetido<N>(dados));
		}
	}
	nos.push_back(new No<N,A>(dados));
	return *this;
}

template<class N, class A>
int Grafo<N,A>::indiceNo(const N &dados)
{
	for(unsigned int i = 0; i < nos.size(); i++)
	{
		if (nos[i]-> info == dados)
		{
			return i;
		}
	}
	return -1;
}

template<class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirAresta(const N &inicio, const N &fim, const A &val)
{
	int start = indiceNo(inicio);
	int end = indiceNo(fim);

	if(start == -1)
		throw(NoInexistente<N>(inicio));

	if(end == -1)
		throw(NoInexistente<N>(fim));

	for (auto i: nos[start]->arestas)
	{
		if(i.destino->info == fim)
		{
			throw(ArestaRepetida<N> (inicio, fim));
		}
	}

	nos.at(start)->arestas.push_back(Aresta<N,A>(nos.at(end), val));
	return *this;
}

template<class N, class A>
A & Grafo<N,A>::valorAresta(const N & inicio, const N &fim)
{
	int start = indiceNo(inicio);
	int end = indiceNo(fim);

	// verificar se não existem
	if(start == -1)
		throw (NoInexistente<N>(inicio));
	if(end == -1)
		throw (NoInexistente<N>(fim));


	for(unsigned int i=0 ; i<nos[start]->arestas.size() ; i++){
		if(nos[start]->arestas[i].destino == nos[end]){	// found it!
			return nos[start]->arestas[i].valor;
		}
	}

	throw(ArestaInexistente<N>(inicio,fim));
}




template<class N, class A>
Grafo<N,A> & Grafo<N,A>::eliminarAresta(const N & inicio, const N &fim)
{
	int start = indiceNo(inicio);
	int end = indiceNo(fim);

	// verificar se não existem
	if(start == -1)
		throw (NoInexistente<N>(inicio));
	if(end == -1)
		throw (NoInexistente<N>(fim));

	for(unsigned int i=0; i < nos[start]->arestas.size(); i++)
	{
		if(nos[start]->arestas[i].destino == nos[end])
		{
			nos[start]->arestas.erase(nos[start]->arestas.begin()+i);
			return *this;
		}
	}
	throw(ArestaInexistente<N>(inicio,fim));
}


template<class N, class A>
void Grafo<N,A>::imprimir(ostream & os) const
{
	for(auto i: this->nos)
	{
		os << "( " << i->info;
		for(auto j: i->arestas)
		{
			os << "[ " << j.destino->info << " " << j.valor << "] ";
		}
		os << ") ";
	}
}


