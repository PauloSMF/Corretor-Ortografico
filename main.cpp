#include<iostream>
#include<cstdlib>
#include<algorithm> //Para o uso do transform.
#include<string>
#include<fstream>
#include<vector>
#include "trie.h"

using namespace std;

int main()
{
    setlocale(LC_ALL,"Portuguese");
    int Opcao;
    Trie Arvore;

    if(Arvore.Construir())
    {
        do
        {
            cout<<"MENU\n\n";
            cout<<"1-Corretor Ortogr�fico\n";
            cout<<"2-Consultas\n";
            cout<<"3-Sair\n\n";
            cout<<"Escolha uma op��o: ";
            cin>>Opcao;

            switch(Opcao)
            {
            case 1:
                Arvore.Corretor();
                system("pause");
                system("cls");
                break;

            case 2:
            {
                string Prefixo;
                cout<<"\nDigite um prefixo: ";
                cin>>Prefixo;
                cout<<endl;
                transform(Prefixo.begin(),Prefixo.end(),Prefixo.begin(),::tolower);
                Arvore.Consultas(Prefixo);
                Arvore.ImprimeConsultas();
                cout<<endl;
                system("pause");
                system("cls");
                break;
            }

            case 3:
                cout<<"\nVoc� saiu do programa.\n";
                break;

            default:
                cout<<"\nOp��o inv�lida!\n\n";
                system("pause");
                system("cls");
            }
        }
        while(Opcao!=3);
    }
    else
        cout<<"N�o foi poss�vel abrir o arquivo.";

    return 0;
}
