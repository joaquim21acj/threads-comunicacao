#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#define LINHA 3
#define COLUNA 3
struct no
{
//utilizando os tipos redefinidos dentro da struct
    int thread;
    int fogo;
};
//redefinindo a struct para encurtar o comando na declaração
typedef struct no no ;

//Estrutura que define o mapa de onde a thread vai atuar
struct atuacao{
int linha[3];
int coluna[3];
int posicaoX, posicaoY;
no **mapa;
};
//definição da área de atuação
typedef struct atuacao atuacao;

/*Rotina que será executada*/
void * routine(void *arg);
/*Função para preenchimento da tela*/
int** alocarMatriz(int Linhas,int Colunas);
int preencheTela(no **matriz);
int isThread(int valor);
int *temFoco(int linha[LINHA], int coluna[COLUNA], no **matriz);

int main (int argc, char *argv[])
{
    no **matriz;
    int i = preencheTela(&matriz);
    int a;
//    /*tenta iniciar o thread, indicando a função 'routine' e passando como argumento a string "Thread A"*/
//    rstatus = pthread_create(&thread_idA, NULL, routine, (void*)("Thread A"));
//
//    /*verificar se ocorreu algum erro na chamada de pthread_create*/
//    if(rstatus != 0)
//    {
//        printf ("Erro ao criar o thread A.\n");
//        exit(EXIT_FAILURE);
//    }
//
//    printf ("Thread A criado com sucesso!\n");
//
//    /*tenta iniciar o thread, indicando novamente a função 'routine' e passando como argumento a string "Thread B"*/
//    rstatus = pthread_create (&thread_idB, NULL, routine, (void*)("Thread B"));
//
//    /*verificar se ocorreu algum erro na chamada de pthread_create*/
//    if(rstatus != 0)
//    {
//        printf ("Erro ao criar o thread B.\n");
//        exit(EXIT_FAILURE);
//    }
//
//    printf ("Thread B criado com sucesso!\n");
//
//
//    /*aguarda finalização do thread A identificado por thread_idA. O retorno é passado pelo ponteiro thread_res*/
//    rstatus = pthread_join (thread_idA, &thread_res);
//
//    if(rstatus != 0)
//    {
//        printf ("Erro ao aguardar finalização do thread A.\n");
//        exit(EXIT_FAILURE);
//    }
//
//    printf ("Thread A finalizado! Retorno = %s\n", (char *)thread_res);
//
//
//    /*aguarda finalização do thread B identificado por thread_idB. O retorno é passado pelo ponteiro thread_res*/
//    rstatus = pthread_join (thread_idB, &thread_res);
//
//    if(rstatus != 0)
//    {
//        printf ("Erro ao aguardar finalização do thread B.\n");
//        exit(EXIT_FAILURE);
//    }
//
//    printf ("Thread B finalizado! Retorno = %s\n", (char *)thread_res);
    return 0;
}

void * routine(void *arg)
{
    atuacao *thr;
    thr = (atuacao *)arg;
    printf("Posicao da thread X: %d Y: %d\n", thr->posicaoX, thr->posicaoY);
    temFoco(thr->linha, thr->coluna, thr->mapa);
    /*finaliza a função retornando o argumento que foi recebido*/
    pthread_exit(arg);
}
int preencheTela(no **matriz)
{
    int xinicial = 0;     // valor inicial
    int xfinal = 29; // valor final
    matriz = alocarMatriz(30, 30);
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if((isThread(i)==1) && (isThread(j)==1))
            {
                matriz[i][j].thread=1;
                atuacao area;
                area.posicaoX = i;
                area.posicaoY = j;
                // vai da linha anterior à thread até a linha posterior
                int posicao = 0;
                for(int x=(i-1); x<=(i+1); x++){
                  area.linha[posicao] = x;
                  posicao++;
                }
                // vai da coluna anterior à thread até a coluna posterior
                posicao = 0;
                for(int y=(j-1); y<=(j+1); y++){
                    area.coluna[posicao] = y;
                    posicao++;
                }
                // criação da thread
                pthread_t thread_id;
                void * thread_res;
                int rstatus;

                area.mapa = &matriz;
                atuacao *ptArea = &area;
                rstatus = pthread_create (&thread_id, NULL, routine, (void*)(ptArea));

            }
        }
    }
    return 0;
}
//Pode ter que alterar para passar por refência, já que enquanto executa uma funçao pode haver um novo foco de incêndio
int *temFoco(int linha[LINHA], int coluna[COLUNA], no **matriz){
    static int posicao[2];
    for(int i = 0; i<LINHA; i++){
        for(int j = 0; j<COLUNA; j++){
            int x = linha[i];
            int y = coluna[j];
            no mt = matriz[x][y];
            if(mt.fogo==1){
                posicao[0] = x;
                posicao[1] = y;
                return posicao;
            }else{
                printf("\nNão houve");
                char a;
                scanf(&a);
            }
        }
    }
}

int** alocarMatriz(int Linhas,int Colunas){ //Recebe a quantidade de Linhas e Colunas como Parâmetro

  int i,j; //Variáveis Auxiliares

  no **m = (no**)malloc(Linhas * sizeof(no*)); //Aloca um Vetor de Ponteiros

  for (i = 0; i < Linhas; i++){ //Percorre as linhas do Vetor de Ponteiros
       m[i] = (no*) malloc(Colunas * sizeof(no)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
       for (j = 0; j < Colunas; j++){ //Percorre o Vetor de Inteiros atual.
            m[i][j].fogo = 0;
            m[i][j].thread = 0;
             //Inicializa com 0.
       }
  }
return m; //Retorna o Ponteiro para a Matriz Alocada
}

int isThread(int valor)
{
    if(valor==1 || valor==4 || valor==7 || valor==10 || valor==13 || valor==16 || valor==19 || valor==22 || valor==25 || valor==28)
        return 1;
    else
        return 0;
}
