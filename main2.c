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

void printMenu();

int main(){
	int op;
	char chave[8], nomeAzul[39], nomeVermelho[39];
	char data[10], duracao[5];
	char nomeWinner[39], apelidoMVP[39];
	char placarAzul[2], placarVermelho[2];
	
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
				//...
				
				scanf("%[^\n]s", duracao);
				getchar();
				//Verificar duracao
				//...
				
				scanf("%[^\n]s", nomeWinner);
				getchar();
				
				scanf("%[^\n]s", placarAzul);
				getchar();
				//Verificar placar azul
				//...
				
				scanf("%[^\n]s", placarVermelho);
				getchar();
				//Verificar placar vermelho
				//...
				
				//Verificar validade do vencedor
				//...
				
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
				
				printf("chave = %s\n", chave);
				
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
			//Fianliza operacao
			case 7:
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
