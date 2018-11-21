#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "BST.h"


class PalavraSignificado {
      string palavra;
      string significado;
public:
       PalavraSignificado(string p, string s): palavra(p), significado(s) {}
       string getPalavra() const { return palavra; }
       string getSignificado() const { return significado; }
       void setSignificado(string sig) { significado = sig; }
       bool operator < (const PalavraSignificado &ps1) const;
};

class Dicionario
{
      BST<PalavraSignificado> palavras;
public:
      Dicionario(): palavras(PalavraSignificado("","")){};
      BST<PalavraSignificado> getPalavras() const;
      void lerDicionario(ifstream &fich);
      string consulta(string palavra) const;
      bool corrige(string palavra, string significado);
      void imprime() const;
};


// a alterar
class PalavraNaoExiste
{
	string pAntes;
	string sigAntes;
	string pApos;
	string sigApos;
public:
	PalavraNaoExiste(string pAntes, string sigAntes, string pApos, string sigApos);
	string getPalavraAntes() const { return pAntes; }
	string getSignificadoAntes() const { return sigAntes; }
	string getPalavraApos() const { return pApos; }
	string getSignificadoApos() const { return sigApos; }
};



#endif
