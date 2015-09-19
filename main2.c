/*
 * UFSCar - Sorocaba
 * Estruturas de Dados 2 - 2015
 * Trabalho 01
 * Eduardo Romao da Rocha - 408468
 * Matheus Gomes Barbieri - 
 * */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 192

typedef struct reg{
	char chave[8];
	int rrn;
} Registro;

void printMenu();
int verificaData(char *data);
int verificaDuracao(char *duracao);
int verificaPlacar(char *placar);
int verificaVencedor(char *nomeAzul, char *nomeVermelho, char *winner, char *placarAzul, char *placarVermelho);
void insereArq(FILE *f, char *na, char *nv, char *data, char *dur, char *win, char *pla, char *plv, char *mvp, char *chave);
int arqVazio(FILE *f);
void carregaVetor(FILE *f, Registro *v);

int RRN = 0;

int main(){
	int op, count = 0;
	char chave[8], nomeAzul[39], nomeVermelho[39];
	char data[10], duracao[5];
	char nomeWinner[39], apelidoMVP[39];
	char placarAzul[2], placarVermelho[2];
	FILE *matches, *iprim, *isec, *iwinner, *imvp;
	Registro *vetor;
	
	matches = fopen("matches.dat", "a+");
	
	vetor = malloc(sizeof(Registro) * 2);
	if(vetor == NULL) exit(1);
	
	//Se ja houver registros no matches.dat, preenche o vetor com as chaves
	if(arqVazio(matches) != 0){}
	
	while(1){
		printMenu();
		scanf("%d", &op);
		getchar();
		
		switch(op){
			//Inserir novo registro
			case 1:
				scanf("%[^\n]s", nomeAzul);
				getchar();
				
				scanf("%[^\n]s", nomeVermelho);
				getchar();

				scanf("%[^\n]s", data);
				getchar();
				//Verificar data
				while(verificaData(data) != 1){
					printf("Campo invalido ! Tente novamente: ");
					scanf("%[^\n]s", data);
					getchar();
				}
				
				scanf("%[^\n]s", duracao);
				getchar();
				//Verificar duracao
				while(verificaDuracao(duracao) != 1){
					printf("Campo invalido ! Tente novamente: ");
					scanf("%[^\n]s", duracao);
					getchar();
				}
				
				scanf("%[^\n]s", nomeWinner);
				getchar();
				
				scanf("%[^\n]s", placarAzul);
				getchar();
				//Verificar placar azul
				while(verificaPlacar(placarAzul) != 1){
					printf("Campo invalido ! Tente novamente: ");
					scanf("%[^\n]s", placarAzul);
					getchar();
				}
				
				scanf("%[^\n]s", placarVermelho);
				getchar();
				//Verificar placar vermelho
				while(verificaPlacar(placarVermelho) != 1){
					printf("Campo invalido ! Tente novamente: ");
					scanf("%[^\n]s", placarVermelho);
					getchar();
				}
				
				//Verificar validade do vencedor
				while(verificaVencedor(nomeAzul, nomeVermelho, nomeWinner, placarAzul, placarVermelho) != 1){
					printf("Campo invalido ! Tente novamente: ");
					scanf("%[^\n]s", nomeWinner);
					getchar();
				}
				
				scanf("%[^\n]s", apelidoMVP);
				getchar();
				
				//Gerar a chave primaria
				chave[0] = toupper(nomeAzul[0]);
				chave[1] = toupper(nomeVermelho[0]);
				chave[2] = toupper(apelidoMVP[0]);
				chave[3] = toupper(apelidoMVP[1]);
				chave[4] = data[0];
				chave[5] = data[1];
				chave[6] = data[3];
				chave[7] = data[4];
				chave[8] = '\0';
				
				//Inserir os valores no arquivo matches.dat
				insereArq(matches, nomeAzul, nomeVermelho, data, duracao, nomeWinner, placarAzul, placarVermelho, apelidoMVP, chave);
				
				//Passar a chave e o RRN da partida pro vetor
				vetor = realloc(vetor, sizeof(Registro) * (count + 1));
				strcpy(vetor[count].chave, chave);
				vetor[count].rrn = RRN;
				
				//Passa a chave e o RRN para o indice primario
				//...
				
				RRN++;
				
				break;
			//Remover registro
			case 2:
				break;
			//Alterar registro
			case 3:
				break;
			//Busca registro
			case 4:
				break;
			//Lista registros
			case 5:
				break;
			//Libera memoria
			case 6:
				break;
			//Finaliza operacao
			case 7:
				free(vetor);
				fclose(matches);
				return 0;
				break;
			default:
				break;
		}
	}
	return 0;
}

void printMenu(){
	printf("1. Inserir nova partida\n2. Remover partida a partir da chave primaria\n3. Modificar duracao\n4. Buscar partidas\n");
	printf("5. Listar partidas\n6. Liberar espaco\n7. Finalizar\n");
}

int verificaData(char *data){
	char dias[2], meses[2], anos[4];
	int d, m, a;
	
	//Separa os dias, o mese e o ano da data
	dias[0] = data[0];
	dias[1] = data[1];
	
	meses[0] = data[3];
	meses[1] = data[4];
	
	anos[0] = data[6];
	anos[1] = data[7];
	anos[2] = data[8];
	anos[3] = data[9];
	
	//Verifica a validade
	if(strlen(data) == 10){
		if(data[2] == '/' && data[5] == '/'){
			//Passando os valores de char para int
			//e calculando o numero certo do dia, mes e ano
			//Subtrair '0' de um caractere numerico nos da o valor inteiro que ele representa
			d = ((dias[0] - '0') * 10) + (dias[1] - '0');
			m = ((meses[0] - '0') * 10) + (meses[1] - '0');
			a = ((anos[0] - '0') * 1000) + ((anos[1] - '0') * 100) + ((anos[2] - '0') * 10) + (anos[3] - '0');
			
			if((d > 0 && d < 32) && (m > 0 && m < 13) && (a > 2010 && a < 2016)) return 1;
		}
	}
	
	return 0;
}

int verificaDuracao(char *duracao){
	if(strlen(duracao) == 5){
		if(duracao[2] == ':') return 1;
	}
	
	return 0;
}

int verificaPlacar(char *placar){
	if(strlen(placar) == 2) return 1;
	
	return 0;
}

int verificaVencedor(char *nomeAzul, char *nomeVermelho, char *winner, char *placarAzul, char *placarVermelho){
	int pa, pv;
	char *aux;
	
	aux = malloc(sizeof(char) * MAX + 1);
	if(aux == NULL) exit(1);
	
	pa = ((placarAzul[0] - '0') * 10) + (placarAzul[1] - '0');
	pv = ((placarVermelho[0] - '0') * 10) + (placarVermelho[1] - '0');
	
	if(pa > pv) strcpy(aux, nomeAzul);
	else if(pv > pa) strcpy(aux, nomeVermelho);

	if(strcmp(aux, winner) == 0){
		free(aux);
		return 1;
	}
	
	free(aux);
	return 0;
}

void insereArq(FILE *f, char *na, char *nv, char *data, char *dur, char *win, char *pla, char *plv, char *mvp, char *chave){
	char aux[MAX];
	int i;
	
	//Passando os valores formatados para uma srting auxiliar,
	//e a imprimindo no arquivo
	sprintf(aux, "%s@%s@%s@%s@%s@%s@%s@%s@%s@", chave, na, nv, data, dur, win, pla, plv, mvp);
	fprintf(f, "%s", aux);
	
	//Comletando com #'s
	for(i = 0; i < (192 - strlen(aux)); i++) fprintf(f, "#");
}

int arqVazio(FILE *f){
	int tam;
	
	fseek(f, 0L, SEEK_END);
	tam = ftell(f);
	fseek(f, 0L, SEEK_SET);
	
	if(tam == 0) return 1;
	
	return 0;
}

void carregaVetor(FILE *f, Registro *v){
	
}
