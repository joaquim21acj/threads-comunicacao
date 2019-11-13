#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
struct no
{
//utilizando os tipos redefinidos dentro da struct
    int thread;
    int fogo;
};
//redefinindo a struct para encurtar o comando na declaração
typedef struct no no ;


/*Rotina que será executada*/
void * routine(void *arg);
/*Função para preenchimento da tela*/
int preencheTela(no matriz[30][30]);
int isThread(int valor);
int main (int argc, char *argv[])
{
    no matriz[30][30];
    int i = preencheTela(matriz);

    pthread_t thread_idA;
    pthread_t thread_idB;
    void * thread_res;
    int rstatus;

    /*tenta iniciar o thread, indicando a função 'routine' e passando como argumento a string "Thread A"*/
    rstatus = pthread_create(&thread_idA, NULL, routine, (void*)("Thread A"));

    /*verificar se ocorreu algum erro na chamada de pthread_create*/
    if(rstatus != 0)
    {
        printf ("Erro ao criar o thread A.\n");
        exit(EXIT_FAILURE);
    }

    printf ("Thread A criado com sucesso!\n");

    /*tenta iniciar o thread, indicando novamente a função 'routine' e passando como argumento a string "Thread B"*/
    rstatus = pthread_create (&thread_idB, NULL, routine, (void*)("Thread B"));

    /*verificar se ocorreu algum erro na chamada de pthread_create*/
    if(rstatus != 0)
    {
        printf ("Erro ao criar o thread B.\n");
        exit(EXIT_FAILURE);
    }

    printf ("Thread B criado com sucesso!\n");


    /*aguarda finalização do thread A identificado por thread_idA. O retorno é passado pelo ponteiro thread_res*/
    rstatus = pthread_join (thread_idA, &thread_res);

    if(rstatus != 0)
    {
        printf ("Erro ao aguardar finalização do thread A.\n");
        exit(EXIT_FAILURE);
    }

    printf ("Thread A finalizado! Retorno = %s\n", (char *)thread_res);


    /*aguarda finalização do thread B identificado por thread_idB. O retorno é passado pelo ponteiro thread_res*/
    rstatus = pthread_join (thread_idB, &thread_res);

    if(rstatus != 0)
    {
        printf ("Erro ao aguardar finalização do thread B.\n");
        exit(EXIT_FAILURE);
    }

    printf ("Thread B finalizado! Retorno = %s\n", (char *)thread_res);
    return 0;
}

void * routine(void *arg)
{
    int contador = 10;

    /*procedimento para decrementar um contador e exibir o seu valor*/
    while(contador--)
    {
        printf("%s: %i\n", (char *)arg, contador);
    }

    /*finaliza a função retornando o argumento que foi recebido*/
    pthread_exit(arg);
}
int preencheTela(no matriz[30][30])
{
    int xinicial = 0;     // valor inicial
    int xfinal = 29; // valor final
    for(int i=0; i<xfinal; i++)
    {
        for(int j=0; j<xfinal; j++)
        {
            if((isThread(i)==1) && (isThread(j)==1))
            {
                matriz[i][j].thread=1;
            }
        }
    }
    return 0;
}

int isThread(int valor)
{
    if(valor==1 || valor==4 || valor==7 || valor==10 || valor==13 || valor==16 || valor==19 || valor==22 || valor==25 || valor==28)
        return 1;
    else
        return 0;
}
