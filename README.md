# Sistemas Operacionais I

##### <hr/> Projeto 01
# Algoritmos-Escalonamento



## Objetivo:

* Implementação de um conjunto de algoritmos de escalonamento de CPU e escrever um programa que calcula uma série de estatísticas baseado nestes algoritmos.

* Os algoritmos de escalonamento a serem implementados são os seguintes:

<br/>

```
FCFS: First-Come, First-Served
SJF: Shortest Job First
RR: Round Robin (com quantum = 2)
```
<br/>

##### O programa deverá ler de um arquivo uma lista de processos com seus respectivos tempos de chegada e de duração e deverá imprimir na tela uma tabela contendo os valores para as seguintes métricas:

```
Tempo de retorno médio
Tempo de resposta médio
Tempo de espera médio
```

### Descrição da entrada:

##### A entrada é composta por uma série de pares de números inteiros separados por um espaço em branco indicando o tempo de chegada e a duração de cada processo. A entrada termina com o fim do arquivo. 

<br/>

####  Exemplo de entrada:

```
0 20
0 10
4 6
4 8
```

### Descrição da saída:

##### A saída é composta por linhas contendo a sigla de cada um dos três algoritmos e os valores das três métricas solicitadas. 
##### Cada linha apresenta a sigla do algoritmo e os valores médios (com uma casa decimal) para tempo de retorno,  tempo de resposta e tempo de espera, exatamente nesta ordem, separados por um espaço em branco.

<br/>

#### Exemplo de saída:

```
FCFS 30,5 19,5 19,
SJF 21,5 10,5 10,
RR 31,5 2,0 20,
```