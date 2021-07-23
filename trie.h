#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED
using namespace std;

int VerificaPosicao(int _Posicao); //Fun��o para verifcar se uma letra possui um correspondente decimal negativo, pois
//h� diferen�as entre a tabela ASCII e o compilador.

class Folha  //Classe com a fun��o de n� externo.
{
public:
    string Palavra;
    Folha(string _Palavra);
};
class No  //Classe com a fun��o de n� interno.
{
public:
    No();
    No* Alfabeto[256]; //Vetor de ponteiros para N� interno, representando o alfabeto.
    Folha* NoFolha[256]; //Vetor de ponteiros para N� externo, representando o alfabeto.
};
class Trie  //Classe respons�vel pela constru��o da trie e buscas na mesma.
{
public:
    No* Raiz;
    vector<string> Opcoes; //Vetor para armazenar palavras buscadas.
    Trie(); //Construtor da trie.
    void Inserir(string Palavra); //Fun��o de inser��o na trie.
    bool Busca(string Palavra); //Fun��o de busca na trie.
    bool Construir(); //Fun��o para a constru��o de uma Trie a partir de um arquivo de texto.
    void AuxConsultas(No* NoAVerificar); //Fun��o recursiva para a inser��o das palavras que possuem determinado prefixo no vetor.
    void Consultas(string Prefixo);  //Fun��o para a pesquisa de determinado prefixo.
    void ImprimeConsultas(); //Fun��o para impress�o do vetor com palavras buscadas a partir de determinada prefixo.
    void Corretor(); //Corretor ortogr�fico.

};

#endif // TRIE_H_INCLUDED
