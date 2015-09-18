#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 192

typedef struct reg{
	char nomeAzul[39];
	char nomeVermelho[39];
	char data[10];
	char duracao[5];
	char placarAzul[2];
	char placarVermelho[2];
	char apelidoMVP[39];
	char nomeWinner[39];
	char chavePrimaria[8];
} Registro;

void printMenu();
int verificaData(char *data);
int verificaDuracao(char *duracao);
int verificaPlacar(char *placar);
int verificaVencedor(char *nomeWinner, char *nomeAzul, char *nomeVermelho, char *placarAzul, char *placarVerm);
void adicionaDados(FILE *f, char *nomeAzul, char *nomeVerm, char *nomeWinner, char *plAz, char *plVe, char *data, char *dur, char *mvp);
char *geraChave(char *nomeAzul, char *nomeVerm, char *nomeWinner, char *plAz, char *plVe, char *data, char *dur, char *mvp);
void removerRegistro(Registro r);
void ordenaVetor(Registro *vet, int k);
int buscaRegistro(char *chave, Registro *vet, Registro *r, int c);
void atualizar();
void listaRegistros(char *parametro, Registro *vet, int k, int op);
void povoaArquivo(Registro *vet, FILE *f);
int compara(const void *a, const void *b);
int estaVazio(FILE *f);
void printRegistro(Registro r);

int main(){
	FILE *indicePrimario, *matches;
	FILE *indiceVencedor, *indiceMVP;
	char nomeVermelho[39], nomeAzul[39], nomeWinner[39];
	char placarAzul[2], placarVerm[2], *apelidoMVP;
	char data[11], chavePrim[8], duracao[5], lixo;
	char buscaParam[MAX], cont = 0, modif[5];
	int opcao, tamTotal = MAX, op2, i;
	Registro *vetor, r, *temp;
	
	tamTotal -= 10 + 2 + 2 + 8 + 5;
	/*nomeAzul = malloc(sizeof(char) * tamTotal + 1);
	if(nomeAzul == NULL) exit(1);*/
	
	//ainda tem q abrir os arquivos e mais um monte de coisa ...
	indicePrimario = fopen("iprimary.idx", "a+");
	indiceVencedor = fopen("iwinner.idx", "a+");
	indiceMVP = fopen("imvp.idx", "a+");
	matches = fopen("matches.dat", "a+");
	
	vetor = malloc(sizeof(int) * 1);
	if(vetor == NULL) exit(1);
	
	while(1){
		printMenu();
		scanf("%d", &opcao);
		switch(opcao){
			//Insere nova partida
			case 1:
				//Caso ja exista um registro no vetor de registros
				if(cont > 0){
					temp = realloc(vetor, sizeof(Registro) * (cont + 1));
					if(temp == NULL) exit(1);
					vetor = temp;
				}
				
				//Le o nome da equipe azul
				getchar();
				fgets(vetor[cont].nomeAzul, tamTotal, stdin);
				i = 0;
				while(vetor[cont].nomeAzul[i] != '\n') i++;
				vetor[cont].nomeAzul[i] = '\0'; //fgets nao remove a quebra de linha da string
				
				//Le o nome da equipe vermelha
				tamTotal -= strlen(vetor[cont].nomeAzul);
				fgets(vetor[cont].nomeVermelho, tamTotal, stdin);
				i = 0;
				while(vetor[cont].nomeVermelho[i] != '\n') i++;	
				vetor[cont].nomeVermelho[i] = '\0';
				tamTotal -= strlen(vetor[cont].nomeVermelho);

				//Le a data da partida, e verifica se esta correta
				fgets(data, 11, stdin);
				i = 0;
				while(data[i] != '\n') i++;
				data[i] = '\0';
				//data[10] = '\0';
				printf("DATA = %s\n", data);
				while(verificaData(data) != 1){
					printf("3Campo invalido ! Tente novamente: ");
					fgets(data, 11, stdin);
					data[10] = '\0';
				}
				//printf("tam data = %d\n", strlen(data));
				//for(i = 0; i < strlen(data); i++) vetor[cont].data[i] = data[i];

				//Le a duracao da partida, e verifica se possui 5 bytes
				getchar();
				fgets(duracao, 6, stdin);
				i = 0;
				while(duracao[i] != '\n') i++;
				duracao[i] = '\0';
				while(verificaDuracao(duracao) != 1){
					printf("5Campo invalido ! Tente novamente: ");
					fgets(duracao, 6, stdin);
				}
				//for(i = 0; i < strlen(duracao); i++) vetor[cont].duracao[i] = duracao[i];
				
				//Le o nome da equipe vencedora
				printf("abababa\n");
				getchar();
				fgets(nomeWinner, 39, stdin);
				i = 0;
				while(nomeWinner[i] != '\n') i++;
				nomeWinner[i] = '\0';
				printf("nome venc = %s\n", nomeWinner);
				//getchar();
				//Le o placar da equipe azul, seguido pelo do vermelho, sempre verificando sua validade
				fgets(placarAzul, 3, stdin);
				printf("placar azul = %s\n", placarAzul);
				i = 0;
				while(placarAzul[i] != '\n') i++;
				placarAzul[i] = '\0';
				while(verificaPlacar(placarAzul) != 1){
					printf("Campo invalido ! Informe novamente: ");
					fgets(placarAzul, 3, stdin);
					i = 0;
					while(placarAzul[i] != '\n') i++;
					placarAzul[i] = '\0';
				}
				printf("placar azul = %s\n", placarAzul);
				getchar();
;
				fgets(placarVerm, 3, stdin);
				i = 0; 
				while(placarVerm[i] != '\n') i++;
				placarVerm[i] = '\0';
				//getchar();
				printf("placar verm = %s\n", placarVerm);
				while(verificaPlacar(placarVerm) != 1){
					printf("1Campo invalido ! Informe novamente: ");
					fgets(placarVerm, 3, stdin);
					i = 0; 
					while(placarVerm[i] != '\n') i++;
					placarVerm[i] = '\0';
				}
				

				//Verifica se o vencedor informado eh o vencedor real
				/*while(verificaVencedor(nomeWinner, vetor[cont].nomeAzul, vetor[cont].nomeVermelho, placarAzul, placarVerm) != 1){
					printf("Campo invalido ! Informe novamente: ");
					fgets(nomeWinner, tamTotal, stdin);
				}*/
				getchar();
				printf("mvp abaixo\n");
				//Le o apelido do MVP
				fgets(apelidoMVP, 39, stdin);
				i = 0;
				while(apelidoMVP[i] != '\n') i++;
				apelidoMVP[i] = '\0';
				
				printf("DATA = %s\n", data);
				//Passa os valores lidos para o vetor de registros
				for(i = 0; i < strlen(data); i++) vetor[cont].data[i] = data[i];
				for(i = 0; i < strlen(duracao); i++) vetor[cont].duracao[i] = duracao[i];
				for(i = 0; i < strlen(nomeWinner); i++) vetor[cont].nomeWinner[i] = nomeWinner[i];
				for(i = 0; i < strlen(placarAzul); i++) vetor[cont].placarAzul[i] = placarAzul[i];
				for(i = 0; i < strlen(placarVerm); i++) vetor[cont].placarVermelho[i] = placarVerm[i];
				for(i = 0; i < strlen(apelidoMVP); i++) vetor[cont].apelidoMVP[i] = apelidoMVP[i];
				
				printf("tam data = %d\ndata = %s\n", strlen(data), vetor[cont].data);
				//printRegistro(vetor[cont]);
				
				cont++;
				break;
			//Remove partida
			case 2:
				scanf("%s", chavePrim);
				break;
			//Modifica duracao
			case 3:
				scanf("%s", chavePrim);
				printf("%s\n", chavePrim);
				if(buscaRegistro(chavePrim, vetor, &r, cont) == 1){
					scanf("%s", modif);
					while(verificaDuracao(duracao) != 1){
						printf("Campo invalido ! Tente novamente: ");
						scanf("%s", modif);
					}
					strcpy(r.duracao, modif);
				}else printf("Registro nao encontrado !\n");
				break;
			//Busca partida
			case 4: 
				printf("1) Chave Primaria\n2) Nome da equipe vencedora\n3) Apelido do MVP\n");
				scanf("%d", &op2);
				//Decide o tipo de busca para cada uma das opcoes
				if(op2 == 1){
					//Busca por chave primaria
					scanf("%s", buscaParam);
					for(i = 0; i < cont; i++){
						if(strcmp(vetor[i].chavePrimaria, buscaParam) == 0) printRegistro(vetor[i]);
					}
				}else if(op2 == 2){
					//Busca por nome da equipe vencedora (chave secundaria)
					
				}else if(op2 == 3){
					//Busca por apelido do MVP (chave secundaria)
				} 
				break;
			//Lista partidas
			case 5:
				printf("1) Codigo\n2) Nome da equipe vencedora\n3) Apelido do MVP\n");
				scanf("%d", &op2);
				getchar();
				//fgets(buscaParam, MAX, stdin);
				scanf("%[^\n]", buscaParam);
				//buscaParam[strlen(buscaParam)] = '\0';
				//printf("PARAMETRO = %s TAM = %d\n", buscaParam, strlen(buscaParam));
				if(estaVazio(matches) != 0) listaRegistros(buscaParam, vetor, cont, op2);
				//Se o arquivo de partidas estiver vazio
				else{
					//TODO CODE...
				}
				break;
			//Libera espaco
			case 6: 
				break;
			//Finaliza execucao
			case 7:
				return 0;
				break;
			default:
				break;
		}
	}
	
	return 0;
}

/*-----------------------------Implementacao das funcoes--------------------------------*/

//Funcao que imprime o menu principal
void printMenu(){
	printf("1. Inserir nova partida\n2. Remover partida a partir da chave primaria\n3. Modificar duracao\n4. Buscar partidas\n");
	printf("5. Listar partidas\n6. Liberar espaco\n7. Finalizar\n");
}

//Verifica se uma data eh valida,
//ou seja, se seus valores de mes e ano estao dentro do intervalo correto
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
	
	//Passando os valores de char para int
	//e calculando o numero certo do dia, mes e ano
	//Subtrair '0' de um caractere numerico nos da o valor inteiro que ele representa
	d = ((dias[0] - '0') * 10) + (dias[1] - '0');
	m = ((meses[0] - '0') * 10) + (meses[1] - '0');
	a = ((anos[0] - '0') * 1000) + ((anos[1] - '0') * 100) + ((anos[2] - '0') * 10) + (anos[3] - '0');
	
	if((d > 0 && d < 32) && (m > 0 && m < 13) && (a > 2010 && a < 2016)) return 1;
	return 0;
}

//Verifica se a duracao da aprtida possui 5 bytes (caracteres) 
int verificaDuracao(char *duracao){
	if(strlen(duracao) == 5) return 1;
	return 0; 
}

//Verifica se o placar informado possui 2 bytes (caracteres)
int verificaPlacar(char *placar){
	if(strlen(placar) == 2) return 1;
	return 0;
}

//Verifica se o nome do vencedor informado bate com o do vencedor real
int verificaVencedor(char *nomeWinner, char *nomeAzul, char *nomeVermelho, char *placarAzul, char *placarVerm){
	int pa, pv;
	char *aux;
	
	aux = malloc(sizeof(char) * MAX + 1);
	if(aux == NULL) exit(1);
	
	pa = ((placarAzul[0] - '0') * 10) + (placarAzul[1] - '0');
	pv = ((placarVerm[0] - '0') * 10) + (placarVerm[1] - '0');
	
	if(pa > pv) strcpy(aux, nomeAzul);
	else if(pv > pa) strcpy(aux, nomeVermelho);

	if(strcmp(aux, nomeWinner) == 0){
		free(aux);
		return 1;
	}
	
	free(aux);
	return 0;
}

char *geraChave(char *nomeAzul, char *nomeVerm, char *nomeWinner, char *plAz, char *plVe, char *data, char *dur, char *mvp){
	char *cod = malloc(sizeof(char) * 8 + 1);
	if(cod == NULL) exit(1);
	
	//Montando o codigo identificador da partida
	cod[0] = toupper(nomeAzul[0]);
	cod[1] = toupper(nomeVerm[0]);
	cod[2] = toupper(mvp[0]);
	cod[3] = toupper(mvp[1]);
	cod[4] = data[0];
	cod[5] = data[1];
	cod[6] = data[3];
	cod[7] = data[4];
	cod[8] = '\0';
	
	return cod;
}

//Adiciona os dados da partida recem informada no arquivo de dados matches.dat
void adicionaDados(FILE *f, char *nomeAzul, char *nomeVerm, char *nomeWinner, char *plAz, char *plVe, char *data, char *dur, char *mvp){
	char cod[8], aux[MAX];
	int i;
	
	//Montando o codigo identificador da partida
	cod[0] = toupper(nomeAzul[0]);
	cod[1] = toupper(nomeVerm[0]);
	cod[2] = toupper(mvp[0]);
	cod[3] = toupper(mvp[1]);
	cod[4] = data[0];
	cod[5] = data[1];
	cod[6] = data[3];
	cod[7] = data[4];
	cod[8] = '\0';
	
	//Passando os valores formatados para uma srting auxiliar,
	//e a imprimindo no arquivo
	sprintf(aux, "%s@%s@%s@%s@%s@%s@%s@%s@%s@", cod, nomeAzul, nomeVerm, data, dur, nomeWinner, plAz, plVe, mvp);
	fprintf(f, "%s", aux);
	
	//Comletando com #'s
	for(i = 0; i < (192 - strlen(aux)); i++) fprintf(f, "#");
}

//Funcoes de comparacao para o qsort
//A primeira ordena pela chave primaria
int compara1(const void *a, const void *b){
	Registro *A = (Registro *)a;
	Registro *B = (Registro *)b;
	
	return strcmp(A->chavePrimaria, B->chavePrimaria);
}

//A segunda ordena pelo nome da equipe vencedora
int compara2(const void *a, const void *b){
	Registro *A = (Registro *)a;
	Registro *B = (Registro *)b;
	
	return strcmp(A->nomeWinner, B->nomeWinner);
}

//Ja a terceira ordena pelo apelido do MVP
int compara3(const void *a, const void *b){
	Registro *A = (Registro *)a;
	Registro *B = (Registro *)b;
	
	return strcmp(A->apelidoMVP, B->apelidoMVP);
}

/*void ordenaVetor(Registro *vet, int k){
	qsort(vet->chavePrimaria, k, sizeof(char), compara);
}*/

void printRegistro(Registro r){
	printf("%s\n%s\n%s\n", r.nomeAzul, r.nomeVermelho, r.data);
	printf("%s\n%s\n%s\n", r.duracao, r.nomeWinner, r.placarAzul);
	printf("%s\n%s\n\n", r.placarVermelho, r.apelidoMVP);
}

void listaRegistros(char *parametro, Registro *vet, int k, int op){
	int i, flag = 0;
	
	//ordenaVetor(vet, k);
	
	if(op == 1){
		//qsort(vet, k, sizeof(char), compara1);
		for(i = 0; i < k; i++){
			if(strcmp(vet->chavePrimaria, parametro) == 0){ 
				flag = 1;
				printRegistro(vet[i]);
			}
			if(flag == 0) printf("Nenhum registro encontrado !\n");
		}
	}else if(op == 2){
		qsort(vet, k, sizeof(char), compara2);
		for(i = 0; i < k; i++){
			if(strcmp(vet->nomeWinner, parametro) == 0){ 
					flag = 1;
					printRegistro(vet[i]);
			}
			if(flag == 0) printf("Nenhum registro encontrado !\n");
		}
	}else if(op == 3){
		qsort(vet, k, sizeof(char), compara3);
		for(i = 0; i < k; i++){
			if(strcmp(vet->apelidoMVP, parametro) == 0){ 
				flag = 1;
				printRegistro(vet[i]);
			}
			if(flag == 0) printf("Nenhum registro encontrado !\n");
		}
	}
}

int estaVazio(FILE *f){
	int tam;
	
	fseek(f, 0L, SEEK_END);
	tam = ftell(f);
	fseek(f, 0L, SEEK_SET);
	
	if(tam == 0) return 1;
	return 0;
}

int buscaRegistro(char *chave, Registro *vet, Registro *r, int c){
	int i, flag = 0;
	//printf("sizeof vet[0] = %d\n", sizeof(vet));
	for(i = 0; i < c; i++){
		if(strcmp(vet[i].chavePrimaria, chave) == 0){
			flag = 1;
			r = &vet[i];
		}
	}
	
	return flag;
}
