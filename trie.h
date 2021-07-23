#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED
using namespace std;

int VerificaPosicao(int _Posicao); //Função para verifcar se uma letra possui um correspondente decimal negativo, pois
//há diferenças entre a tabela ASCII e o compilador.

class Folha  //Classe com a função de nó externo.
{
public:
    string Palavra;
    Folha(string _Palavra);
};
class No  //Classe com a função de nó interno.
{
public:
    No();
    No* Alfabeto[256]; //Vetor de ponteiros para Nó interno, representando o alfabeto.
    Folha* NoFolha[256]; //Vetor de ponteiros para Nó externo, representando o alfabeto.
};
class Trie  //Classe responsável pela construção da trie e buscas na mesma.
{
public:
    No* Raiz;
    vector<string> Opcoes; //Vetor para armazenar palavras buscadas.
    Trie(); //Construtor da trie.
    void Inserir(string Palavra); //Função de inserção na trie.
    bool Busca(string Palavra); //Função de busca na trie.
    bool Construir(); //Função para a construção de uma Trie a partir de um arquivo de texto.
    void AuxConsultas(No* NoAVerificar); //Função recursiva para a inserção das palavras que possuem determinado prefixo no vetor.
    void Consultas(string Prefixo);  //Função para a pesquisa de determinado prefixo.
    void ImprimeConsultas(); //Função para impressão do vetor com palavras buscadas a partir de determinada prefixo.
    void Corretor(); //Corretor ortográfico.

};

#endif // TRIE_H_INCLUDED
