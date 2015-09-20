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
	char mvp[39];
	char winner[39];
	int rrn;
} Registro;

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

void printMenu();
int verificaData(char *data);
int verificaDuracao(char *duracao);
int verificaPlacar(char *placar);
int verificaVencedor(char *nomeAzul, char *nomeVermelho, char *winner, char *placarAzul, char *placarVermelho);
void insereArq(FILE *f, char *na, char *nv, char *data, char *dur, char *win, char *pla, char *plv, char *mvp, char *chave);
int arqVazio(FILE *f);
void carregaVetor(FILE *f, Registro *v);
void criaIndicePrim(FILE *f, Registro *v);
void criaIndiceWin(FILE *f, Registro *v);
void criaIndiceMVP(FILE *f, Registro *v);
int comp(const void *a, const void *b);
int comp2(const void *a, const void *b);
int comp3(const void *a, const void *b);

int RRN = 0;
int flagWinnerConsistente = 0;
int flagMVPConsistente = 0;

int main(){
	int op, count = 0;
	int encontrado = 0, rrnDeletar, i;
	int op2, enc = 0;
	char dadosArq[192];
	char chBusca[39];
	char chave[8], nomeAzul[39], nomeVermelho[39];
	char data[10], duracao[5];
	char nomeWinner[39], apelidoMVP[39];
	char placarAzul[2], placarVermelho[2];
	FILE *matches, *iprim, *isec, *iwinner, *imvp;
	Registro *vetorPrim, *vetorWinner, *vetorMVP;
	
	matches = fopen("matches.dat", "a+");
	iprim = fopen("iprimary.idx", "a+");
	iwinner = fopen("iwinner.idx", "a+");
	imvp = fopen("imvp.idx", "a+");
	
	vetorPrim = malloc(sizeof(Registro) * 2);
	if(vetorPrim == NULL) exit(1);
	
	vetorWinner = malloc(sizeof(Registro) * 2);
	if(vetorWinner == NULL) exit(1);
	
	vetorMVP = malloc(sizeof(Registro) * 2);
	if(vetorMVP == NULL) exit(1);
	
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
				
				//Passar a chave e o RRN da partida pro vetor primario
				vetorPrim = realloc(vetorPrim, sizeof(Registro) * (count + 1));
				strcpy(vetorPrim[count].chave, chave);
				vetorPrim[count].rrn = RRN;
				
				//Passando o nome do vencedor e a chave primaria para o vetor de vencedores
				vetorWinner = realloc(vetorWinner, sizeof(Registro) * (count + 1));
				strcpy(vetorWinner[count].winner, nomeWinner);
				strcpy(vetorWinner[count].chave, chave);
				
				//Passando o apelido do MVP e a chave primaria para o vetor dos MVP's
				vetorMVP = realloc(vetorMVP, sizeof(Registro) * (count + 1));
				strcpy(vetorMVP[count].mvp, nomeWinner);
				strcpy(vetorMVP[count].chave, chave);
				
				//Passa a chave e o RRN para o indice primario
				//Primeiro, ordena-se o vetor pela chave primaria
				qsort(vetorPrim, count + 1, sizeof(char), comp);
				//Em seguida, escrevemos os valores corretos no indice primario
				fprintf(iprim, "%s %d\n", vetorPrim[count].chave, vetorPrim[count].rrn);
				
				//Passando para os indices secundarios
				//Ordena os vetores secundarios (nome do vencedor e apelido do MVP)
				qsort(vetorWinner, count + 1, sizeof(char), comp2);
				qsort(vetorMVP, count + 1, sizeof(char), comp3);
				//Indice do nome do vencedor
				fprintf(iwinner, "%s %s\n", vetorWinner[count].winner, vetorWinner[count].chave);
				//Indice do MVP
				fprintf(imvp, "%s %s\n", vetorMVP[count].mvp, vetorMVP[count].chave);
				
				RRN += 192;
				count++;
				
				break;
			//Remover registro
			case 2:
				//int encontrado = 0, rrnDeletar, i;
				scanf("%[^\n]s", chBusca);
				getchar();
				
				for(i = 0; i < count; i++){
					if(strcmp(vetorPrim[i].chave, chBusca) == 0){
						encontrado = 1;
						rrnDeletar = vetorPrim[i].rrn;
						vetorPrim[i].rrn = -1;
						vetorPrim[i].chave[0] = '*';
						vetorPrim[i].chave[1] = '|';
					}
				}
				
				if(encontrado == 0) printf("Registro nao encontrado!\n");
				
				break;
			//Alterar registro
			case 3:
				scanf("%[^\n]", chBusca);
				int enc = 0, rrnBusca;
				char novaDur[5];
				
				for(i = 0; i < count; i++){
					if(strcmp(vetorPrim[i].chave, chBusca) == 0){
						enc = 1;
						rrnBusca = vetorPrim[i].rrn;
						scanf("%[^\n]s", novaDur);
						getchar();
						while(verificaDuracao(novaDur) != 1){
							printf("Campo invalido ! Tente novamente: ");
							scanf("%[^\n]s", novaDur);
							getchar();
						}
		
						//substituir a duracao com base no rrn
						//como faz ?
						
						
						break;
					}
				}
				
				if(enc == 0) printf("Registro nao encontrado!\n");
				
				break;
			//Busca registro
			case 4:
				//char dadosArq[192];
				//int op2, enc = 0, i;
				printf("1. Busca por Codigo\n2. Busca por Nome da Equipe Vencedora\n3. Busca por Apelido do MVP\n");
				scanf("%d", &op2);
				getchar();
				if(op2 == 1){
					int rrnBusca, j;
					enc = 0;
					scanf("%[^\n]s", chBusca);
					getchar();
					
					for(i = 0; i < count; i++){
						if(strcmp(vetorPrim[i].chave, chBusca) == 0){
							enc = 1;
							rrnBusca = vetorPrim[i].rrn;
							
							//Se o arquivo de dados nao esta vazio
							if(arqVazio(matches) == 0){
								fseek(matches, rrnBusca, SEEK_SET);
								for(j = 0; j < 191; i++) dadosArq[i] = fgetc(matches);
								dadosArq[192] = '\0';
								printf("string louca: %s\n", dadosArq);
							}
						}
					}
					
					if(enc == 0) printf("Registro nao encontrado!\n");
				}else if(op2 == 2){
					int j, rrnBusca;
					char ch[8];
					enc = 0;
					scanf("%[^\n]s", chBusca);
					getchar();
					
					for(i = 0; i < count; i++){
						if(strcmp(vetorWinner[i].winner, chBusca) == 0){
							enc = 1;
							strcpy(ch, vetorWinner[i].chave);
							for(j = 0; j < count; j++){
								if(strcmp(vetorPrim[j].chave, ch) == 0){
									rrnBusca = vetorPrim[j].rrn;
								}
							}
						}
						
					}
				}else if(op2 == 3){
				
				}
				
				break;
			//Lista registros
			case 5:
				break;
			//Libera memoria
			case 6:
				break;
			//Finaliza operacao
			case 7:
				free(vetorPrim);
				free(vetorWinner);
				free(vetorMVP);
				fclose(iprim);
				fclose(iwinner);
				fclose(imvp);
				fclose(matches);
				return 0;
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
	
	//Separa os dias, os meses e o ano da data
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

int comp(const void *a, const void *b){
	Registro *aux1 = (Registro *) a;
	Registro *aux2 = (Registro *) b;
	
	return (strcmp(aux1->chave, aux2->chave));
}

int comp2(const void *a, const void *b){
	Registro *aux1 = (Registro *) a;
	Registro *aux2 = (Registro *) b;
	
	return (strcmp(aux1->winner, aux2->winner));
}

int comp3(const void *a, const void *b){
	Registro *aux1 = (Registro *) a;
	Registro *aux2 = (Registro *) b;
	
	return (strcmp(aux1->mvp, aux2->mvp));
}

void criaIndicePrim(FILE *f, Registro *v){
	int tam, i, j, cont = 0;
	char aux[192];
	
	fseek(f, 0L, SEEK_END);
	tam = ftell(f);
	fseek(f, 0L, SEEK_SET);
	
	for(i = 0; i < tam; i += 192){
		for(j = 0; j < 7; i++) v[i].chave[i] = fgetc(f);
		aux[8] = '\0';
		v[i].rrn = i;
	}
}

void criaIndiceWin(FILE *f, Registro *v){

}

void criaIndiceMVP(FILE *f, Registro *v){

}
