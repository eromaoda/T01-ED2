/*
 * UFSCar - Sorocaba
 * Estruturas de Dados 2 - 2015
 * Trabalho 01
 * Eduardo Romao da Rocha - 408468
 * Matheus Gomes Barbieri - 408344
 * */
 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 192
#define TOT 10000

//Definindo a estrutura dos registros
typedef struct reg{
	char chave[8];
	char mvp[39];
	char winner[39];
	int rrn;
} Registro;

//Definindo a estrutura das partidas
typedef struct partida{
	char nAzul[39];
	char nVerm[39];
	char nWinner[39];
	char data[10];
	char duracao[5];
	char plAz[2];
	char plVe[2];
	char mvp[39];
} Partida;

//Funcao de apresentar o menu principal
void printMenu();
//Verifica a data informada
int verificaData(char *data);
//Verifica a duracao informada
int verificaDuracao(char *duracao);
//Verifica o placar informado
int verificaPlacar(char *placar);
//Checa se o vencedor informado bate com os placares informados
int verificaVencedor(char *nomeAzul, char *nomeVermelho, char *winner, char *placarAzul, char *placarVermelho);
//Realiza a insercao no arquivo de dados
void insereArq(FILE *f, char *na, char *nv, char *data, char *dur, char *win, char *pla, char *plv, char *mvp, char *chave);
int getTamanhoArq(FILE *f);
void carregaVetor(FILE *f, Registro *v);
void criaIndicePrim(FILE *f, Registro *v);
//Verifica se a chave ja foi inserida no arquivo de dados
int chaveJaExiste(Registro *v, char *ch, int k);
void geraIndice(char *rgStr, Registro *v1, Registro *v2, Registro *v3, int k);
void atualizaDados(Registro *v, FILE *f);
//Ordenacoes utilizando o algoritmo de Selection Sort
void ordenaPorChave(Registro *v, int n);
void ordenaPorVenc(Registro *v, int n);
void ordenaPorMVP(Registro *v, int n);
//Imprime os dados do registro
void printDados(char *s);
