#include<stdio.h>
#include<stdio.h>

void printMenu();

int main(){
	FILE *indicePrimario, *indiceSecundario;
	FILE *indiceVencedor, *indiceMVP;
	char *nomeVermelho, *nomeAzul, *nomeWinner;
	char *placar, *apelidoMVP;
	int opcao;
	
	while(1){
		printMenu();
		scanf("%d", &opcao);
		switch(opcao){
			//Insere nova partida
			case 1:
				break;
			//Remove partida
			case 2: 
				break;
			//Modifica duracao
			case 3:
				break;
			//Busca partida
			case 4: 
				break;
			//Lista partidas
			case 5:
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

void printMenu(){
	printf("1. 	Inserir nova partida\n2. Remover partida a partir da chave primaria\n3. Modificar duracao\n4. Buscar partidas\n");
	printf("5. Listar partidas\n6. Liberar espaco\n");
}
