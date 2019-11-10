#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h> 

/*Rotina que será executada*/
void * routine(void *arg);
/*Função para preenchimento da tela*/
int preencheTela();

int main (int argc, char *argv[])
{
	int i = preencheTela();
	// pthread_t thread_id;
	// void * thread_res;
	// int rstatus;
	


	// /*tenta iniciar o thread, indicando a função 'routine' e passando como argumento a string "Minha primeira Thread!"*/
	// rstatus = pthread_create (&thread_id, NULL, routine, (void*)("Minha primeira Thread!"));
	
	// /*verificar se ocorreu algum erro na chamada de pthread_create*/
	// if(rstatus != 0)
	// {
	// printf ("Erro ao criar o thread.\n");
	// exit(EXIT_FAILURE);
	// }
	
	// printf ("Thread criado com sucesso!\n");
	
	// /*aguarda finalização do thread identificado por thread_id. O retorno é passado pelo ponteiro thread_res*/
	// rstatus = pthread_join (thread_id, &thread_res);
	
	// /*verificar se ocorreu algum erro na chamada de pthread_join*/
	// if(rstatus != 0)
	// {
	// printf ("Erro ao aguardar finalização do thread.\n");
	// exit(EXIT_FAILURE);
	// }
	
	// /*exibe o valor de retorno da função 'routine'*/
	// printf ("Thread finalizado! Retorno = %s\n", (char *)thread_res);
	
	// return 0;
}
 
void * routine(void *arg)
{
 /*exibe o argumento recebido*/
 printf("Argumento: %s\n", (char *)arg);
 
 /*finaliza a função retornando o argumento que foi recebido*/
 pthread_exit(arg);
}

int preencheTela(){
    int xInicial = 0;     // valor inicial
    int xfinal = 29; // valor final
    int step = 1;

    FILE *pont_arq; // cria variável ponteiro para o arquivo
    char palavra[20]; // variável do tipo string
  
    //abrindo o arquivo com tipo de abertura w
    pont_arq = fopen("mapa.txt", "w");
    
    //testando se o arquivo foi realmente criado
    if(pont_arq == NULL)
    {
		printf("Erro na abertura do arquivo!");
		return 1;
    }
    fprintf(pont_arq, "%s", "# x \t f(x) \n");
 
    while ( xInicial <= xfinal ) {
		
        fprintf(pont_arq, "%s",  ("%d \t %d \n", xInicial, pow(xInicial, 2)/20));
        xInicial += step;
    }
    //usando fprintf para armazenar a string no arquivo
    
    //usando fclose para fechar o arquivo
    fclose(pont_arq);



	return 0;
    

 
}