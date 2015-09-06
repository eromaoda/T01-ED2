#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 192

void printMenu();
int verificaData(char *data);
int verificaDuracao(char *duracao);
int verificaPlacar(char *placar);
int verificaVencedor(char *nomeWinner, char *nomeAzul, char *nomeVermelho, char *placarAzul, char *placarVerm);
void adicionaDados(FILE *f, char *nomeAzul, char *nomeVerm, char *nomeWinner, char *plAz, char *plVe, char *data, char *dur, char *mvp);

int main(){
	FILE *indicePrimario, *matches;
	FILE *indiceVencedor, *indiceMVP;
	char *nomeVermelho, *nomeAzul, *nomeWinner;
	char placarAzul[2], placarVerm[2], *apelidoMVP;
	char data[10], chavePrim[8], duracao[5], lixo;
	int opcao, tamTotal = MAX, op2;
	
	tamTotal -= 10 + 2 + 2 + 8 + 5;
	nomeAzul = malloc(sizeof(char) * tamTotal + 1);
	if(nomeAzul == NULL) exit(1);
	
	//ainda tem q abrir os arquivos e mais um monte de coisa ...
	indicePrimario = fopen("iprimary.idx", "a+");
	indiceVencedor = fopen("iwinner.idx", "a+");
	indiceMVP = fopen("imvp.idx", "a+");
	matches = fopen("matches.dat", "a+");
	
	
	while(1){
		printMenu();
		scanf("%d", &opcao);
		switch(opcao){
			//Insere nova partida
			case 1:
				//Le o nome da equipe azul
				getchar();
				fgets(nomeAzul, tamTotal, stdin);
				nomeAzul[strlen(nomeAzul) - 1] = '\0'; //fgets nao remove a quebra de linha da string

				//Le o nome da equipe vermelha
				nomeVermelho = malloc(sizeof(char) * (tamTotal - strlen(nomeAzul)) + 1);
				if(nomeVermelho == NULL) exit(1);
				tamTotal -= strlen(nomeAzul);

				fgets(nomeVermelho, tamTotal, stdin);
				nomeVermelho[strlen(nomeVermelho) - 1] = '\0';
				tamTotal -= strlen(nomeVermelho);
				
				//Le a data da partida, e verifica se esta correta
				fgets(data, 10, stdin);
				data[strlen(data) - 1] = '\0';
				while(verificaData(data) != 1){
					printf("Campo invalido ! Tente novamente: ");
					scanf("%s", data);
				}

				//Le a duracao da partida, e verifica se possui 5 bytes
				scanf("%s", duracao);
				while(verificaDuracao(duracao) != 1){
					printf("Campo invalido ! Tente novamente: ");
					scanf("%s", duracao);
				}

				//Le o nome da equipe vencedora
				nomeWinner = malloc(sizeof(char) * tamTotal + 1);
				if(nomeWinner == NULL) exit(1);
				getchar();
				fgets(nomeWinner, tamTotal, stdin);
				nomeWinner[strlen(nomeWinner) - 1] = '\0';
				
				//Le o placar da equipe azul, seguido pelo do vermelho, sempre verificando sua validade
				scanf("%s", placarAzul);
				while(verificaPlacar(placarAzul) != 1){
					printf("Campo invalido ! Informe novamente: ");
					scanf("%s", placarAzul);
				}
				
				scanf("%s", placarVerm);
				while(verificaPlacar(placarAzul) != 1){
					printf("Campo invalido ! Informe novamente: ");
					scanf("%s", placarVerm);
				}
				
				getchar();
				
				//Verifica se o vencedor informado eh o vencedor real
				while(verificaVencedor(nomeWinner, nomeAzul, nomeVermelho, placarAzul, placarVerm) != 1){
					printf("Campo invalido ! Informe novamente: ");
					fgets(nomeWinner, tamTotal, stdin);
					nomeWinner[strlen(nomeWinner) - 1] = '\0';
				}
				
				//Le o apelido do MVP
				apelidoMVP = malloc(sizeof(char) * (tamTotal - strlen(nomeWinner)) + 1);
				if(apelidoMVP == NULL) exit(1);
				//scanf("%[^\n]", apelidoMVP);
				tamTotal -= strlen(nomeWinner);
				fgets(apelidoMVP, tamTotal, stdin);

				break;
			//Remove partida
			case 2:
				scanf("%s", chavePrim);
				break;
			//Modifica duracao
			case 3:
				scanf("%s", chavePrim);
				break;
			//Busca partida
			case 4: 
				printf("1) Chave Primaria\n2) Nome da equipe vencedora\n3) Apelido do MVP\n");
				scanf("%d", &op2);
				//Decide o tipo de busca para cada uma das opcoes
				
				break;
			//Lista partidas
			case 5:
				printf("1) Codigo\n2) Nome da equipe vencedora\n3) Apelido do MVP\n");
				scanf("%d", &op2);
				break;
			//Libera espaco
			case 6: 
				break;
			//Finaliza execucao
			case 7:
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
