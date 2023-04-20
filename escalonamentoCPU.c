#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RR_QUANTUM 2

typedef struct processos
{
    int tempoChegada;
    int tempoDuracao;
    int tempoInicio;
    int tempoFim;
    int tempoExecucao;
    int tempoResposta;
    int tempoRetorno;
    int tempoEspera;
} Processo;

int leArquivo();

void FCFS();
void calculaTempoEsperaFCFS(Processo *aux, int *tempoEspera);
void calculaTempoRetornoFCFS(Processo *aux, int *tempoRetorno);
void calculaTempoRespostaFCFS(Processo *aux, int *tempoResposta);

void SJF();
void calculaTempoEsperaSJF(Processo *aux, int *tempoEspera);
void calculaTempoRetornoSJF(Processo *aux, int *tempoRetorno);
void calculaTempoRespostaSJF(Processo *aux, int *tempoResposta);

void RR();
void calculaTempoEsperaRR(Processo *aux, int *tempoEspera);
void calculaTempoRetornoRR(Processo *aux, int *tempoRetorno);
void calculaTempoRespostaRR(Processo *aux, int *tempoResposta);

Processo *processos     = NULL;
float    NUM_PROCESSOS  = 0.0;

int leArquivo()
{
    FILE *arq    = NULL;
    char *result = NULL;
    char aux[10] = {'\0'};
    int  i       = 0;
    int  linhas  = 0;

    arq = fopen("processos.txt", "r");
    
    if (arq == NULL)
    {
        printf("Problemas na abertura do arquivo");
        return 0;
    }
    
    fseek(arq, 0, SEEK_END);
    linhas = ftell(arq);
    rewind(arq);

    processos = (Processo *) calloc(linhas, sizeof(Processo));
    
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
void FCFS()
{
    Processo* aux       = NULL;
    int tempoTotal      = 0;
    int tempoRetorno    = 0;
    int tempoResposta   = 0;
    int tempoEspera     = 0;
    
    aux = malloc(sizeof(Processo) * NUM_PROCESSOS);
    if(!aux) return;
    
    memcpy(aux, processos, sizeof(Processo) * NUM_PROCESSOS);

    
    aux[0].tempoInicio = 0;
    aux[0].tempoFim    = aux[0].tempoDuracao;

    for(int i = 1; i < NUM_PROCESSOS; i++) aux[i].tempoInicio = aux[i-1].tempoInicio + aux[i-1].tempoDuracao;
    for(int i = 1; i < NUM_PROCESSOS; i++) aux[i].tempoFim    = aux[i].tempoInicio   + aux[i].tempoDuracao;
    
    calculaTempoEsperaFCFS(aux, &tempoEspera);
    calculaTempoRetornoFCFS(aux, &tempoRetorno);
    calculaTempoRespostaFCFS(aux, &tempoResposta);

    printf("FCFS %.1f %.1f %.1f\n", tempoRetorno/NUM_PROCESSOS, tempoResposta/NUM_PROCESSOS, tempoEspera/NUM_PROCESSOS);

    free(aux);
}

void calculaTempoEsperaFCFS(Processo *aux, int *tempoEspera)
{
    for(int i = 0; i != NUM_PROCESSOS; i++) 
    {
        aux[i].tempoEspera = aux[i].tempoInicio - aux[i].tempoChegada;
        *tempoEspera += aux[i].tempoEspera;
    }
}

void calculaTempoRetornoFCFS(Processo *aux, int *tempoRetorno)
{
    for(int i = 0; i != NUM_PROCESSOS; i++)
    {
        aux[i].tempoRetorno = aux[i].tempoFim - aux[i].tempoChegada;
        *tempoRetorno += aux[i].tempoRetorno;
    } 
}

void calculaTempoRespostaFCFS(Processo *aux, int *tempoResposta)
{
    for(int i = 0; i != NUM_PROCESSOS; i++)
    {
        aux[i].tempoResposta = aux[i].tempoInicio - aux[i].tempoChegada;
        *tempoResposta += aux[i].tempoResposta;
    } 
}

// SJF - Shortest Job First
void SJF()
{
    Processo* aux       = NULL;
    int tempoTotal      = 0;
    int tempoRetorno    = 0;
    int tempoResposta   = 0;
    int tempoEspera     = 0;
    int tempoAtual      = 0;
    int restantes       = NUM_PROCESSOS;

    aux = malloc(sizeof(Processo) * NUM_PROCESSOS);
    if(!aux) return;

    memcpy(aux, processos, sizeof(Processo) * NUM_PROCESSOS);
    int *duracao = NULL;

    while(restantes > 0)
    {
        int proximo = -1;
        int duracaoProx = -1;

        for(int i = 0; i < NUM_PROCESSOS; i++)
        {
            int duracaoAuxI = aux[i].tempoDuracao;

            if(aux[i].tempoChegada <= tempoAtual && duracaoAuxI > 0)
            {
                if(proximo == -1 || duracaoAuxI < duracaoProx)
                {
                    proximo = i;
                    duracaoProx = duracaoAuxI;
                }
            }
        }

        if(proximo == -1) tempoAtual++;
        else
        {
            tempoAtual++;
            
            aux[proximo].tempoInicio = tempoAtual;
            aux[proximo].tempoExecucao++;
            aux[proximo].tempoDuracao--;

            if(aux[proximo].tempoDuracao == 0)
            {
                aux[proximo].tempoFim = tempoAtual;
                restantes--;
            }
        }
    }

    calculaTempoEsperaSJF(aux, &tempoEspera);
    calculaTempoRetornoSJF(aux, &tempoRetorno);
    calculaTempoRespostaSJF(aux, &tempoResposta);

    printf("SJF %.1f %.1f %.1f\n", tempoRetorno/NUM_PROCESSOS, tempoResposta/NUM_PROCESSOS, tempoEspera/NUM_PROCESSOS);

    free(aux);
}

void calculaTempoEsperaSJF(Processo *aux, int *tempoEspera)
{
    for(int i = 0; i != NUM_PROCESSOS; i++)
    {
        aux[i].tempoEspera = aux[i].tempoInicio - aux[i].tempoChegada - aux[i].tempoExecucao;
        *tempoEspera += aux[i].tempoEspera;
    } 
}

void calculaTempoRetornoSJF(Processo *aux, int *tempoRetorno)
{
    for(int i = 0; i != NUM_PROCESSOS; i++)
    {
        aux[i].tempoRetorno = aux[i].tempoFim - aux[i].tempoChegada;
        *tempoRetorno += aux[i].tempoRetorno;
    } 
}

void calculaTempoRespostaSJF(Processo *aux, int *tempoResposta)
{
    for(int i = 0; i != NUM_PROCESSOS; i++)
    {
        aux[i].tempoResposta = aux[i].tempoFim - aux[i].tempoChegada - aux[i].tempoExecucao;
        *tempoResposta += aux[i].tempoResposta;
    } 
}

// RR - Round Robin
void RR()
{
    Processo* aux       = NULL;
    int tempoRetorno    = 0;
    int tempoResposta   = 0;
    int tempoEspera     = 0;
    int tempoAtual      = 0;
    int restantes       = NUM_PROCESSOS;

    aux = malloc(sizeof(Processo) * NUM_PROCESSOS);
    if(!aux) return;

    memcpy(aux, processos, sizeof(Processo) * NUM_PROCESSOS);

    while (restantes > 0) 
    {

        for (int i = 0; i < NUM_PROCESSOS; i++) 
        {
            if (aux[i].tempoChegada > tempoAtual || aux[i].tempoDuracao == 0) continue;

            if (aux[i].tempoDuracao <= RR_QUANTUM)
            {
                if (aux[i].tempoInicio == 0) aux[i].tempoInicio = tempoAtual;

                tempoAtual          += aux[i].tempoDuracao;
                aux[i].tempoDuracao = 0;
                aux[i].tempoFim     = tempoAtual;
                restantes--;
            } 
            else 
            {   
                if (aux[i].tempoInicio == 0) aux[i].tempoInicio = tempoAtual; 

                tempoAtual           += RR_QUANTUM;
                aux[i].tempoExecucao += RR_QUANTUM;
                aux[i].tempoDuracao  -= RR_QUANTUM;
            }

            for (int j = 0; j < NUM_PROCESSOS; j++)
            {
                if (j == i || aux[j].tempoDuracao == 0) continue;

                aux[j].tempoEspera += RR_QUANTUM;
            }
        }
    }

    calculaTempoEsperaRR(aux, &tempoEspera);
    calculaTempoRetornoRR(aux, &tempoRetorno);
    calculaTempoRespostaRR(aux, &tempoResposta);

    printf("RR %.1f %.1f %.1f\n", tempoRetorno/NUM_PROCESSOS, tempoResposta/NUM_PROCESSOS, tempoEspera/NUM_PROCESSOS);

    free(aux);
}

void calculaTempoEsperaRR(Processo *aux, int *tempoEspera)
{
    for (int i = 0; i < NUM_PROCESSOS; i++) *tempoEspera += aux[i].tempoEspera;
}

void calculaTempoRetornoRR(Processo *aux, int *tempoRetorno)
{
    for (int i = 0; i < NUM_PROCESSOS; i++) 
    {
        aux[i].tempoRetorno = aux[i].tempoFim - aux[i].tempoChegada;
        *tempoRetorno += aux[i].tempoRetorno;
    }
}

void calculaTempoRespostaRR(Processo *aux, int *tempoResposta)
{
    for (int i = 0; i < NUM_PROCESSOS; i++) 
    {
        aux[i].tempoResposta = aux[i].tempoInicio - aux[i].tempoChegada;
        *tempoResposta += aux[i].tempoResposta;
    }
}

int main()
{
    int rc;

    rc = leArquivo();
    
    if(!rc)
    {
        printf("Erro na leitura do arquivo");

        return -1;
    }

    FCFS();
    SJF();
    RR();

    free(processos);

    return 0;
}