#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 192

void printMenu();
int verificaData(char *data);

int main(){
	FILE *indicePrimario, *indiceSecundario;
	FILE *indiceVencedor, *indiceMVP;
	char *nomeVermelho, *nomeAzul, *nomeWinner;
	char placarAzul[2], placarVerm[2], *apelidoMVP;
	char data[10], chavePrim[8], duracao[5];
	int opcao, tamTotal = MAX, op2;
	
	tamTotal -= 10 + 2 + 2 + 8 + 5;
	nomeAzul = malloc(sizeof(char) * tamTotal + 1);
	if(nomeAzul == NULL) exit(1);
	
	//ainda tem q abrir os arquivos e mais um monte de coisa ...
	
	while(1){
		printMenu();
		scanf("%d", &opcao);
		switch(opcao){
			//Insere nova partida
			case 1:
				//Le o nome da equipe azul
				scanf("%[^\n]", nomeAzul);
				//Le o nome da equipe vermelha
				nomeVermelho = malloc(sizeof(char) * (tamTotal - strlen(nomeAzul)) + 1);
				if(nomeVermelho == NULL) exit(1);
				tamTotal -= strlen(nomeAzul);
				scanf("%[^\n]", nomeVermelho);
				//Le a data da partida
				scanf("%s", data);
				//Le a duracao da partida
				scanf("%s", duracao);
				//Le o nome da equipe vencedora
				scanf("%[^\n]", nomeWinner);
				//Le o placar da equipe azul, seguido pelo do vermelho
				scanf("%s", placarAzul);
				scanf("%s", placarVerm);
				//Le o apelido do MVP
				apelidoMVP = malloc(sizeof(char) * (tamTotal - strlen(nomeVermelho)) + 1);
				if(apelidoMVP == NULL) exit(1);
				scanf("%[^\n]", apelidoMVP);
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
	printf("5. Listar partidas\n6. Liberar espaco\n");
}

//ainda tem q implementar lolol
int verificaData(char *data){
	return 1;
}
