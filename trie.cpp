#include<iostream>
#include<cstdlib>
#include<algorithm> //Para o uso do transform.
#include<string>
#include<fstream>
#include<vector>
#include "trie.h"
using namespace std;

int VerificaPosicao(int _Posicao)
{
    if(_Posicao<0)
        _Posicao=_Posicao+256;

    return _Posicao;
}

Folha::Folha(string _Palavra)
{
    Palavra=_Palavra;
}
No::No()
{
    for(int i=0; i<256; i++) //Iniciando os vetores de nós internos e externos com nulo.
    {
        Alfabeto[i]=0;
        NoFolha[i]=0;
    }
}
Trie::Trie()
{
    Raiz=new No(); //Construindo a raiz de uma Trie.
}
void Trie::Inserir(string Palavra)
{
    No* NovoNo=Raiz;
    int Posicao=Palavra[0]; //Responsável por verificar em qual posição uma palavra vai ficar na trie.
    Posicao=VerificaPosicao(Posicao);

    if(NovoNo->Alfabeto[Posicao]==0 && NovoNo->NoFolha[Posicao]==0) //Caso não tenha nada inserido em determinada posição
    {
        //correspondente a raiz.
        Folha* NovaPalavra=new Folha(Palavra);
        NovoNo->NoFolha[Posicao]=NovaPalavra;
    }
    else
    {
        int i=0;
        Posicao=Palavra[i];
        Posicao=VerificaPosicao(Posicao);
        Folha* Aux=0;

        while(NovoNo->Alfabeto[Posicao]!=0) //Descendo na árvore Trie.
        {
            NovoNo=NovoNo->Alfabeto[Posicao];
            i++;
            Posicao=Palavra[i];
            Posicao=VerificaPosicao(Posicao);
        }

        if(NovoNo->NoFolha[Posicao]==0) //Caso não tenha palavra naquela posição.
        {
            Folha* NovaPalavra=new Folha(Palavra);
            NovoNo->NoFolha[Posicao]=NovaPalavra;
        }
        else //Expandindo a árvore.
        {
            Aux=NovoNo->NoFolha[Posicao];
            NovoNo->NoFolha[Posicao]=0;

            while(Palavra[i]==Aux->Palavra[i])
            {
                NovoNo->Alfabeto[Posicao]=new No();
                NovoNo=NovoNo->Alfabeto[Posicao];
                i++;
                Posicao=Palavra[i];
                Posicao=VerificaPosicao(Posicao);
            }

            int Posicao2=Palavra[i];
            Posicao2=VerificaPosicao(Posicao2);
            int Posicao3=Aux->Palavra[i];
            Posicao3=VerificaPosicao(Posicao3);

            NovoNo->NoFolha[Posicao2]=new Folha(Palavra);
            NovoNo->NoFolha[Posicao3]=Aux;
        }
    }
}
bool Trie::Busca(string Palavra)
{
    No* NoBusca=Raiz;
    int i=0;
    int Posicao=Palavra[i];
    Posicao=VerificaPosicao(Posicao);

    while(NoBusca->Alfabeto[Posicao]!=0) //Percorrendo a árvore.
    {
        NoBusca=NoBusca->Alfabeto[Posicao];
        i++;
        Posicao=Palavra[i];
        Posicao=VerificaPosicao(Posicao);
    }

    if(NoBusca->NoFolha[Posicao]!=0 && Palavra==NoBusca->NoFolha[Posicao]->Palavra) //Verificando a existência da palavra.
        return true;
    else
        return false;
}
bool Trie::Construir()
{
    string Palavra;
    ifstream Arquivo;
    Arquivo.open("lista.txt");

    if(Arquivo.is_open())
    {
        while(getline(Arquivo,Palavra)) //Inserindo cada palavra do arquivo na Trie.
        {
            transform(Palavra.begin(),Palavra.end(),Palavra.begin(),::tolower);
            Inserir(Palavra);
        }

        Arquivo.close();
        return true;
    }
    else
    {
        cout<<"Nao foi possivel abrir o arquivo!"<<endl;
        return false;
    }
}

void Trie::AuxConsultas(No* NoAVerificar)
{
    for(int j=0; j<256; j++)
    {
        if(NoAVerificar->NoFolha[j]!=0) //Imprimindo em caso de haver um nó externo.
        {
            string Palavra=NoAVerificar->NoFolha[j]->Palavra;
            transform(Palavra.begin(),Palavra.end(),Palavra.begin(),::tolower);
            Opcoes.push_back(Palavra); //Inserindo no vetor de palavras buscadas.
        }
        else if(NoAVerificar->Alfabeto[j]!=0) //Descendo para o próximo nó interno em determinada posição.
            AuxConsultas(NoAVerificar->Alfabeto[j]);
    }
}

void Trie::Consultas(string Prefixo)
{
    No* NoAux=Raiz;
    int i=0;
    int Posicao=Prefixo[i];
    Posicao=VerificaPosicao(Posicao);

    while(NoAux->Alfabeto[Posicao]!=0 && Prefixo[i]!='\0') //Porcorrendo a árvore até completar o prefixo.
    {
        NoAux=NoAux->Alfabeto[Posicao];
        i++;
        Posicao=Prefixo[i];
        Posicao=VerificaPosicao(Posicao);
    }

    AuxConsultas(NoAux);
}

void Trie::ImprimeConsultas()
{
    for(unsigned int i=0; i<Opcoes.size(); i++) //Enquanto i é menor que o tamanho do vetor.
    {
        transform(Opcoes[i].begin(),Opcoes[i].end(),Opcoes[i].begin(),::toupper);
        cout<<"Você disse: "<<Opcoes[i]<<endl;
    }

    Opcoes.clear(); //Limpando o vetor após seu uso.
}

void Trie::Corretor()
{
    cout<<"\nAntes de continuar, copie o texto a ser tratado para o arquivo Entrada.txt na pasta deste programa.\n\n";
    system("pause");
    system("cls");

    ifstream Entrada;
    ofstream Saida;
    Entrada.open("Entrada.txt");
    Saida.open("Saida.txt");

    if(Entrada.is_open() && Saida.is_open())
    {
        string Palavra, Correcao;

        while(Entrada>>Palavra)
        {
            int Opcao;
            transform(Palavra.begin(),Palavra.end(),Palavra.begin(),::tolower);

            if(Busca(Palavra)==false)
            {
                cout<<"A palavra "<<Palavra<<" foi digitada incorretamente ou não existe!\n";
                cout<<"Sugerimos as seguintes palavras, digite um número correspondente, ou 0 caso queira digitar uma nova palavra:\n\n";
                Consultas(Palavra);

                for(unsigned int i=0; i<10; i++) //Enquanto i é menor que o tamanho do vetor.
                {
                    if(i==Opcoes.size())
                        break;

                    transform(Opcoes[i].begin(),Opcoes[i].end(),Opcoes[i].begin(),::toupper);
                    cout<<i+1<<". "<<Opcoes[i]<<endl;
                }

                cout<<"\nEscolha uma opção: ";
                cin>>Opcao;

                if(Opcao==0)
                {
                    cout<<"\nDigite aqui a nova palavra: ";
                    cin>>Correcao;
                    transform(Correcao.begin(),Correcao.end(),Correcao.begin(),::tolower);

                    while(Busca(Correcao)==false)
                    {
                        cout<<"\n\nA palavra foi digitada incorretamente ou não existe! Digite novamente: ";
                        cin>>Correcao;
                        transform(Correcao.begin(),Correcao.end(),Correcao.begin(),::tolower);
                    }

                    Saida<<Correcao; //Copiando para o arquivo de saída.
                    Saida<<" "; //Copiando para o arquivo de saída.
                    system("cls");
                }
                else
                {
                    while(Opcao>10||Opcao<0)
                    {
                        cout<<"Opção inválida! Digite novamente: ";
                        cin>>Opcao;
                    }

                    if(Opcao!=0)
                    {
                        transform(Opcoes[Opcao-1].begin(),Opcoes[Opcao-1].end(),Opcoes[Opcao-1].begin(),::tolower);
                        Saida<<Opcoes[Opcao-1]; //Copiando para o arquivo de saída.
                        Saida<<" "; //Copiando para o arquivo de saída.
                        system("cls");
                    }
                    else
                    {
                        cout<<"\nDigite aqui a nova palavra: ";
                        cin>>Correcao;
                        transform(Correcao.begin(),Correcao.end(),Correcao.begin(),::tolower);

                        while(Busca(Correcao)==false)
                        {
                            cout<<"\n\nA palavra foi digitada incorretamente ou não existe! Digite novamente: ";
                            cin>>Correcao;
                            transform(Correcao.begin(),Correcao.end(),Correcao.begin(),::tolower);
                        }

                        Saida<<Correcao; //Copiando para o arquivo de saída.
                        Saida<<" "; //Copiando para o arquivo de saída.
                        system("cls");
                    }
                }
            }
            else
            {
                Saida<<Palavra; //Copiando para o arquivo de saída.
                Saida<<" "; //Copiando para o arquivo de saída.
            }

            Opcoes.clear(); //Limpando o vetor após seu uso.
        }

        Saida<<".";
        cout<<"Correção finalizada!\n\n";
        Entrada.close();
        Saida.close();
    }
    else
        cout<<"\nNão foi possível abrir o arquivo de entrada ou saída!\n\n";
}

