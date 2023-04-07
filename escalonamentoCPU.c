#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RR_QUANTUM 2

int leArquivo();

void FCFS();
void calculaTempoEsperaFCFS();
void calculaTempoRetornoFCFS();
void calculaTempoRespostaFCFS();

void SJF();
void calculaTempoEsperaSJF();
void calculaTempoRetornoSJF();
void calculaTempoRespostaSJF();

typedef struct processos
{
    int tempoChegada;
    int tempoDuracao;
    int tempoInicio;
    int tempoFim;
    int tempoResposta;
    int tempoRetorno;
    int tempoEspera;
} Processo;

Processo processos[100] = {0};
float    NUM_PROCESSOS  = 0.0;

int leArquivo()
{
    FILE *arq    = NULL;
    char *result = NULL;
    char aux[10] = {'\0'};
    int  i       = 0;

    arq = fopen("processos.txt", "r");
    
    if (arq == NULL)
    {
        printf("Problemas na abertura do arquivo");
        return 0;
    }

    // tempo de chegada e tempo de duração de cada processo
    // ex: 0 3
    while (!feof(arq))
    {
        result = fgets(aux, 10, arq);
        
        if(result)
        {
            processos[i].tempoChegada = atoi(aux);
            processos[i].tempoDuracao = atoi(aux+2);
        }

        i++;
    }

    NUM_PROCESSOS = i;
    fclose(arq);

    return 1;
}

// FCFS - First Come First Served
// ex saida: FCFS {retornoM} {respostaM} {esperaM}
void FCFS()
{
    int tempoTotal      = 0;
    int tempoRetorno    = 0;
    int tempoResposta   = 0;
    int tempoEspera     = 0;

    processos[0].tempoInicio = 0;
    processos[0].tempoFim    = processos[0].tempoDuracao;

    for(int i = 1; i < NUM_PROCESSOS; i++) processos[i].tempoInicio = processos[i-1].tempoInicio + processos[i-1].tempoDuracao;
    for(int i = 1; i < NUM_PROCESSOS; i++) processos[i].tempoFim    = processos[i].tempoInicio + processos[i].tempoDuracao;
    
    calculaTempoEsperaFCFS();
    calculaTempoRetornoFCFS();
    calculaTempoRespostaFCFS();


    for(int i = 0; i < NUM_PROCESSOS; i++)
    {
        tempoRetorno  += processos[i].tempoRetorno;
        tempoResposta += processos[i].tempoResposta;
        tempoEspera   += processos[i].tempoEspera;
    }

    printf("FCFS %.2f %.2f %.2f\n", tempoRetorno/NUM_PROCESSOS, tempoResposta/NUM_PROCESSOS, tempoEspera/NUM_PROCESSOS);
}

void calculaTempoEsperaFCFS()
{
    for(int i = 0; i != NUM_PROCESSOS; i++) processos[i].tempoEspera = processos[i].tempoInicio - processos[i].tempoChegada;
}

void calculaTempoRetornoFCFS()
{
    for(int i = 0; i != NUM_PROCESSOS; i++) processos[i].tempoRetorno = processos[i].tempoFim - processos[i].tempoChegada;
}

void calculaTempoRespostaFCFS()
{
    for(int i = 0; i != NUM_PROCESSOS; i++) processos[i].tempoResposta = processos[i].tempoInicio - processos[i].tempoChegada;
}

int main()
{
    memset(processos, 0, sizeof(processos));
    int rc;

    rc = leArquivo();
    
    if(!rc)
    {
        printf("Erro na leitura do arquivo");

        return -1;
    }

    FCFS();
    // SJF();
    // RR();

    return 0;
}