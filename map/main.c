#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include"mapa.h"    //inclusão das funções contidas no TAD Mapa.h para o funcionamento do Dicionario de Mapa

int main(){
    int z ;
    char k[30];
    tipo_elem el;   // defifinição de uma variavel "el" como tipo_elem
    abb *M; 
    M = define();   //função que define M como uma mapa, para que os procedimentos seguntes sejam realizados
    const tipo_elem empty = {"",""};
    setlocale(LC_ALL, "Portuguese");

    do{
        printf("\nDicionario de Mapa:\n");        //Através dessa interface simples o usuraio pode acessar todas as opções disponiveis no Dicionario de Mapa
        printf("1 - Search:\n");                  //Pesquisa no mapa o elemento que o usuario deseja
        printf("2 - Insert:\n");                  //Insere um elemento e sua respectiva informação no mapa, quando o usuario a chama
        printf("3 - Replace:\n");                 //Subistitui um elemento no Mapa, atravez da sua chave,sendo que para tal, o elemteno com a respectiva chave necessariamente tem que existir
        printf("4 - Remove:\n");                  //Remove o elemento desejado pelo usuario
        printf("5 - Percurso inter-fixado\n");    //Expoem o percusor de elementos inseridos no mapa, através do percurso interfixiado
        printf("6 - Sair\n");                     //Artibui a possibilidade do usurario sair do programa
        scanf ("%d", &z);

    switch(z){

       case 1 :

            printf("\nDigite o elemento desejado:\n ");     //Expoem a ação desejada pelo usuario
            scanf(" %[^\n]",k);                             //obtem o elemento que o usario deseja que seja feita a ação em cima do mesmo
            el=search(k, M);                                //consegue o elemento adivindo da função search chamada
            if (el.chave[0] != empty.chave[0])      //faz uma averiguaçao atravez da tranformação dos carracteres da string em inteiros e compara com os valores para ver se não são nulo ou espaço
            printf("\nElemento encontrado: %s - %s", el.chave, el.info); //exprime o progresso esperado pelo usuario
            else printf("\nBusca sem suceso!\n");           // em caso de falha, exprime que não foi possivel a realização do objetivo proposto pela função

            break;                                                  //saida da opção 1

        case 2 :
            printf("\nDigite a chave do elemento a ser inserido, e sua respectiva informação:\n "); //Expoem a ação desejada pelo usuario
            scanf(" %[^\n]", el.chave);                     //obtem o elemento que o usario deseja que seja feita a ação sobre o mesmo
            scanf(" %[^\n]", el.info);                      //obtem o elemento que o usario deseja que seja feita a ação sobre o mesmo
            if (insert(el, M))                               //através da verificação da função , para ver se o elemento foi inserido com sucesso ou não
                printf("O elemento foi inserido com sucesso.\n");//exprime o progresso esperado pelo usuario
            else
                printf("O elemento já existe!\n");         // em caso de falha, exprime que não foi possivel a realização do objetivo proposto pela função

            break;                                                 //saida da opção 2

        case 3 :
            printf("\nDigite a chave do elemento a ter sua informação substituída:\n"); //Expoem a ação desejada pelo usuario
            scanf(" %[^\n]", el.chave);                            //obtem o elemento que o usario deseja que seja feita a ação sobre o mesmo
            printf("\nDigite a nova informação para o elemento:\n");            //Expoem a ação desejada pelo usuario
            scanf(" %[^\n]",el.info);                         //obtem o elemento que o usario deseja que seja feita a ação sobre o mesmo
            if (replace(el, M))                              //através da verificação da função , para ver se o elemento foi substituido com sucesso ou não
                printf("\nSubstituído com sucesso.\n");          //exprime o progresso esperado pelo usuario
            else printf("\n Elemento não encontrado!\n");   //em caso de falha, exprime que não foi possivel a realização do objetivo proposto pela função
            break;                                                   //saida da opção 3

        case 4 :
            printf("\nDigite o elemento que deseja remover:\n");  //Expoem a ação desejada pelo usuario
            scanf(" %[^\n]", k);                                  //obtem o elemento que o usario deseja que seja feita a ação sobre o mesmo
            el=remover(k, M);                                     //consegue o elemento removido o qual foi chamado pela função remove
            if (el.chave[0] != empty.chave[0])         //faz uma averiguaçao atravez da tranformação dos carracteres da string em inteiros e compara com os valores para ver se não são nulo ou espaço
                printf("\nO elemento de chave %s foi removido com sucesso!\n", el.chave);//exprime o progresso esperado pelo usuario,através da apresentação da palavra removida e sua chave
            else 
                printf("\n O elemento não existe!\n");           // em caso de falha, exprime que não foi possivel a realização do objetivo proposto pela função
            break;                                                            //saida da opção 4

        case 5 :
            print(M);       //Expoem o percurso inter-fixado dos elemento contidos no mapa
            printf("%d", M->nelem);
            break;                      //saida da opção 5

        case 6 :   
        	freeNodesMap(M, M->root);
    		free(M); 
            exit(1);       //Executa a odrem de saida do programa desejada pelo usuario
            break;                      //saida da opção 6

        default:    printf("\nOpção inválida.\n"); //Avisa o usario de um possivel erro na hora da escolha de opções pelo usuario

    }

    } while (z != 6); //Caso o operação escolhida pelo usario não seja umas das seis, ele reapresenta o menu para o usuaria para uma nova escolha de opçoes

    
    return 0;
}