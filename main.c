/*
 * UFSCar - Sorocaba
 * Estruturas de Dados 2 - 2015
 * Trabalho 01
 * Eduardo Romao da Rocha - 408468
 * Matheus Gomes Barbieri - 408344
 * */

#include "408468_408344_ED2_T01.h"

int RRN = 0;
int count = 0;
int flagWinnerConsistente = 0;
int flagMVPConsistente = 0;

int main(){
	int op, count = 0, tam;
	int encontrado = 0, rrnDeletar, i, j;
	int op2, enc = 0;
	char dadosArq[192], aux[2], str[192];
	char chBusca[39], rgStr[192];
	char chave[8], nomeAzul[39], nomeVermelho[39];
	char data[10], duracao[5];
	char nomeWinner[39], apelidoMVP[39];
	char placarAzul[2], placarVermelho[2];
	FILE *matches, *iprim, *isec, *iwinner, *imvp;
	FILE *auxFile;
	Registro vetorPrim[TOT], vetorWinner[TOT], vetorMVP[TOT];
	
	matches = fopen("matches.dat", "r+");
	if(matches == NULL){
		matches = fopen("matches.dat", "w+");
	}
	
	iprim = fopen("iprimary.idx", "r+");
	if(iprim == NULL){
		iprim = fopen("iprimary.idx", "w+");
	}
	
	iwinner = fopen("iwinner.idx", "r+");
	if(iwinner == NULL){
		iwinner = fopen("iwinner.idx", "w+");
	}
	
	imvp = fopen("imvp.idx", "r+");
	if(imvp == NULL){
		imvp = fopen("imvp.idx", "w+");
	}
	
	fseek(matches, 0L, SEEK_END);
	int fileLen = ftell(matches);
	fseek(matches, 0L, SEEK_SET);
	
	//Se ja houver registros no matches.dat, preenche os vetores de indice com as chaves
	if(fileLen != 0){
		int t;
		char aux1[39], aux2[39], aux3[39];
		char aux4[39], aux5[39], aux6[39];
		
		fseek(matches, 0L, SEEK_END);
		t = ftell(matches);
		fseek(matches, 0L, SEEK_SET);
		
		for(i = 0; i < t; i += 192){
			fseek(matches, i, SEEK_SET);
			for(j = 0; j < 192; j++){
				rgStr[j] = fgetc(matches);
			}			
			rgStr[192] = '\0';

			char auxiliar[192], *ch, *c1, *w, *m;
			int x = 0;
			
			ch = malloc(sizeof(char) * 39 + 1);
			if(ch == NULL) exit(1);
			
			c1 = malloc(sizeof(char) * 39 + 1);
			if(c1 == NULL) exit(1);
			
			w = malloc(sizeof(char) * 39 + 1);
			if(w == NULL) exit(1);
			
			m = malloc(sizeof(char) * 39 + 1);
			if(m == NULL) exit(1);
			
			while(rgStr[x] != '#'){
				auxiliar[x] = rgStr[x];
				x++;
			}
			auxiliar[x] = '\0';
			
			ch = strtok(auxiliar, "@");
			c1 = strtok(NULL, "@");
			c1 = strtok(NULL, "@");
			c1 = strtok(NULL, "@");
			c1 = strtok(NULL, "@");
			w = strtok(NULL, "@");
			c1 = strtok(NULL, "@");
			c1 = strtok(NULL, "@");
			m = strtok(NULL, "@");
			
			int k;
			for(k = 0; k < strlen(ch); k++) vetorPrim[count].chave[k] = ch[k];
			vetorPrim[count].rrn = i;
			
			for(k = 0; k < strlen(ch); k++) vetorWinner[count].chave[k] = ch[k];
			for(k = 0; k < strlen(w); k++) vetorWinner[count].winner[k] = w[k];
			for(k = 0; k < strlen(ch); k++) vetorMVP[count].chave[k] = ch[k];
			for(k = 0; k < strlen(m); k++) vetorMVP[count].mvp[k] = m[k];

			vetorPrim[count].rrn = i;
			count++;
		}
		fseek(iprim, 0L, SEEK_SET);
		
		//Se os indices ja existirem
		if(getTamanhoArq(iprim) != 0){
			//Se nao estiverem consistentes com o arquivo de dados
			if(fgetc(iprim) == '0'){
				remove("iprimary.idx");
				fclose(iprim);
				iprim = fopen("iprimary.idx", "r+");
				if(iprim == NULL) iprim = fopen("iprimary.idx", "w+");
				fputs("1\n", iprim);
				int i;
				for(i = 0; i < count; i++){
					int t = getTamanhoArq(iprim);
					fseek(iprim, t, SEEK_SET);
					fprintf(iprim, "%s %d lol\n", vetorPrim[i].chave, vetorPrim[i].rrn);
				}
			}
		}
		
	}else printf("Arquivo de dados vazio!\n");
	fseek(matches, 0L, SEEK_SET);	
	fclose(matches);	
	fclose(iprim);
	fclose(iwinner);
	fclose(imvp);
	
	while(1){
		printMenu();
		scanf("%d", &op);
		getchar();
		
		switch(op){
			//Inserir novo registro
			case 1:
				matches = fopen("matches.dat", "r+");
				if(matches == NULL){
					matches = fopen("matches.dat", "w+");
				}
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
				
				if(chaveJaExiste(vetorPrim, chave, count) == 1) printf("ERRO: Já existe um registro com a chave primária %s.\n", chave);
				else{
					//Inserir os valores no arquivo matches.dat
					insereArq(matches, nomeAzul, nomeVermelho, data, duracao, nomeWinner, placarAzul, placarVermelho, apelidoMVP, chave);
					
					//Passar a chave e o RRN da partida pro vetor primario
					strcpy(vetorPrim[count].chave, chave);
					vetorPrim[count].rrn = RRN;
					
					//Passando o nome do vencedor e a chave primaria para o vetor de vencedores
					strcpy(vetorWinner[count].winner, nomeWinner);
					strcpy(vetorWinner[count].chave, chave);
					
					//Passando o apelido do MVP e a chave primaria para o vetor dos MVP's
					strcpy(vetorMVP[count].mvp, nomeWinner);
					strcpy(vetorMVP[count].chave, chave);
					
					//Passa a chave e o RRN para o indice primario
					//Em seguida, escrevemos os valores corretos no indice primario
					fprintf(iprim, "%s %d\n", vetorPrim[count].chave, vetorPrim[count].rrn);
					
					//Passando para os indices secundarios
					//Indice do nome do vencedor
					fprintf(iwinner, "%s %s\n", vetorWinner[count].winner, vetorWinner[count].chave);
					//Indice do MVP
					fprintf(imvp, "%s %s\n", vetorMVP[count].mvp, vetorMVP[count].chave);
					
					RRN += 192;
					count++;
				}
				fclose(matches);
				break;
			//Remover registro
			case 2:
				//int encontrado = 0, rrnDeletar, i;
				matches = fopen("matches.dat", "r+");
				if(matches == NULL){
					matches = fopen("matches.dat", "w+");
				}
				scanf("%[^\n]s", chBusca);
				getchar();
				
				for(i = 0; i < count; i++){
					if(strcmp(vetorPrim[i].chave, chBusca) == 0){
						encontrado = 1;
						rrnDeletar = vetorPrim[i].rrn;
						//vetorPrim[i].rrn = -1;
						vetorPrim[i].chave[0] = '*';
						vetorPrim[i].chave[1] = '|';
						printf("rrn delete = %d\n", rrnDeletar);
						fseek(matches, rrnDeletar, SEEK_SET);
						fputc('*', matches);
						fputc('|', matches);
						vetorPrim[i].rrn = -1;
					}
				}
				
				if(encontrado == 0) printf("Registro nao encontrado!\n");
				fclose(matches);
				break;
			//Alterar registro
			case 3:
				matches = fopen("matches.dat", "r+");
				if(matches == NULL){
					matches = fopen("matches.dat", "w+");
				}
				
				scanf("%[^\n]s", chBusca);
				getchar();
				int enc = 0, rrnBusca, contador = 0;
				char novaDur[5];
				
				for(i = 0; i < count; i++){
					if(strcmp(vetorPrim[i].chave, chBusca) == 0){
						enc = 1;
						rrnBusca = vetorPrim[i].rrn;
						break;
					}
				}
				
				//Se o registro for encontrado no arquivo de dados
				if(enc == 1){
					scanf("%[^\n]s", novaDur);
					getchar();
					while(verificaDuracao(novaDur) != 1){
						printf("Campo invalido ! Tente novamente: ");
						scanf("%[^\n]s", novaDur);
						getchar();
					}
					fseek(matches, rrnBusca, SEEK_SET);
					//Conta o numero de @'s ate chegar no campo de duracao da partida
					while(contador != 4){
						char c = fgetc(matches);
						if(c == '@') contador++;
					}
					//Insere os novos valores da duracao
					fputc(novaDur[0], matches);
					fputc(novaDur[1], matches);
					fputc(novaDur[2], matches);
					fputc(novaDur[3], matches);
					fputc(novaDur[4], matches);
				}else printf("Registro nao encontrado!\n");
				
				fclose(matches);
				
				break;
			//Busca registro
			case 4:
				matches = fopen("matches.dat", "r+");
				if(matches == NULL){
					matches = fopen("matches.dat", "w+");
				}
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
							break;
						}
					}
					if(enc == 1){
						//Se o arquivo de dados nao esta vazio
						if(getTamanhoArq(matches) != 0){	
							fseek(matches, rrnBusca, SEEK_SET);
							for(j = 0; j < 191; j++){
								dadosArq[j] = fgetc(matches);
							}
							dadosArq[192] = '\0';
							//printf("string louca: %s\n", dadosArq);
							int x = 0;
							char a[192];
							while(dadosArq[x] != '#'){
								a[x] = dadosArq[x];
								x++;
							}
							a[x] = '\0';
							
							printDados(a);
						}
						}else printf("Registro nao encontrado!\n");
					fseek(matches, 0L, SEEK_SET);
				}else if(op2 == 2){
					int j, rrnBusca, vai = 0;
					char ch[8];
					enc = 0;
					scanf("%[^\n]s", chBusca);
					getchar();
					for(i = 0; i < count; i++){
						if(strcmp(vetorWinner[i].winner, chBusca) == 0){
							enc = 1;
							strcpy(ch, vetorWinner[i].chave);
								for(j = 0; j < count; j++){
									if((strcmp(vetorPrim[j].chave, ch)) == 0){
										vai = 1;
										rrnBusca = vetorPrim[j].rrn;
									}
									fseek(matches, 0L, SEEK_END);
									fileLen = ftell(matches);
									fseek(matches, 0L, SEEK_SET);
									if(vai == 1){
										if(fileLen != 0){
											fseek(matches, rrnBusca, SEEK_SET);
											for(j = 0; j < 191; j++){
												dadosArq[j] = fgetc(matches);
											}
											dadosArq[192] = '\0';
											int x = 0;
											char a[192];
											while(dadosArq[x] != '#'){
												a[x] = dadosArq[x];
												x++;
											}
											a[x] = '\0';
											printDados(a);
										}
									} 
									vai = 0;
								}
							}
						}
					if(enc == 0) printf("Registro nao encontrado!\n");	
				}else if(op2 == 3){
					int j, rrnBusca, vai = 0;
					char ch[8];
					enc = 0;
					scanf("%[^\n]s", chBusca);
					getchar();
					for(i = 0; i < count; i++){
						if(strcmp(vetorMVP[i].mvp, chBusca) == 0){
							enc = 1;
							vetorMVP[i].chave[8] = '\0';
							strcpy(ch, vetorMVP[i].chave);
							for(j = 0; j < count; j++){
								if((strcmp(vetorPrim[j].chave, ch)) == 0){
									vai = 1;
									rrnBusca = vetorPrim[j].rrn;
								}
								fseek(matches, 0L, SEEK_END);
								fileLen = ftell(matches);
								fseek(matches, 0L, SEEK_SET);
								if(vai == 1){
									if(fileLen != 0){
										fseek(matches, rrnBusca, SEEK_SET);
										for(j = 0; j < 191; j++){
											dadosArq[j] = fgetc(matches);
										}
										dadosArq[192] = '\0';
										int x = 0;
										char a[192];
										while(dadosArq[x] != '#'){
											a[x] = dadosArq[x];
											x++;
										}
										a[x] = '\0';
										printDados(a);
									}
								} 
								vai = 0;
							}
						}
					}
					if(enc == 0) printf("Registro nao encontrado!\n");						
				}else printf("Opcao invalida!\n");
				fclose(matches);
				break;
			//Lista registros
			case 5:
				matches = fopen("matches.dat", "r+");
				if(matches == NULL){
					matches = fopen("matches.dat", "w+");
				}
				if(getTamanhoArq(matches) == 0) printf("Arquivo vazio!\n");
				else{
					printf("1. Listagem por codigo\n2. Listagem por nome da equipe vencedora\n3. Listagem por apelido do MVP\n");
					scanf("%d", &op2);
					Registro *vAux;
					vAux = malloc(sizeof(Registro) * count);
					if(vAux == NULL) exit(1);
					//Busca pela chave primaria
					if(op2 == 1){
						int rrnBusca, enc = 0, j;
						char aux[192], dados[192];
						
						for(i = 0; i < count; i++) vAux[i] = vetorPrim[i];
						
						ordenaPorChave(vAux, count);

						for(i = 0; i < count; i++){
							if(vAux[i].rrn != -1){
								rrnBusca = vAux[i].rrn;
								fseek(matches, rrnBusca, SEEK_SET);
								for(j = 0; j < 192; j++) dados[j] = fgetc(matches);
								j = 0;
								while(dados[j] != '#'){
									aux[j] = dados[j];
									j++;
								}
								aux[j] = '\0';
								
								printDados(aux);
							}
						}
						fseek(matches, 0L, SEEK_SET);
					//Busca pelo nome da equipe vencedora
					}else if(op2 == 2){
						char chav[8], aux[192], dados[192], c;
						int r, x, j;
						
						for(i = 0; i < count; i++) vAux[i] = vetorWinner[i];
						
						ordenaPorVenc(vAux, count);
						for(i = 0; i < count; i++) printf("nome win = %s\n", vAux[i].winner);
						printf("\n");
						
						for(i = 0; i < count; i++){
							strcpy(chav, vAux[i].chave);
							for(j = 0; j < count; j++){
								if(strcmp(chav, vetorPrim[j].chave) == 0) r = vetorPrim[j].rrn;
								if(r != -1){
									fseek(matches, r, SEEK_SET);
									for(x = 0; x < 192; x++){
										dados[x] = fgetc(matches);
									}
									x = 0;
									while(dados[x] != '#'){
										aux[x] = dados[x];
										x++;
									}
									aux[x] = '\0';
									}
								}
								printDados(aux);
							}
						
						fseek(matches, 0L, SEEK_SET);
					}else if(op2 == 3){
						char chav[8], aux[192], dados[192], c;
						int r, x, j;
						for(i = 0; i < count; i++) vAux[i] = vetorMVP[i];

						ordenaPorMVP(vAux, count);

						for(i = 0; i < count; i++){
							vAux[i].chave[8] = '\0';
							strcpy(chav, vAux[i].chave);
							for(j = 0; j < count; j++){
								if(strcmp(chav, vetorPrim[j].chave) == 0) r = vetorPrim[j].rrn;
								if(r != -1){
									fseek(matches, r, SEEK_SET);
									for(x = 0; x < 192; x++){
										dados[x] = fgetc(matches);
									}
									x = 0;
									while(dados[x] != '#'){
										aux[x] = dados[x];
										x++;
									}
									aux[x] = '\0';
								}
							}
							printDados(aux);
						}
						fseek(matches, 0L, SEEK_SET);
					}else printf("Opcao invalida!\n");
					
					fseek(matches, 0L, SEEK_SET);
				}
				/*matches = fopen("matches.dat", "r+");
				if(matches == NULL){
					matches = fopen("matches.dat", "w+");
				}*/
				
				fclose(matches);
				
				break;
			//Libera memoria
			case 6:
				matches = fopen("matches.dat", "r+");
				if(matches == NULL){
					matches = fopen("matches.dat", "w+");
				}
				
				auxFile = fopen("auxfile.dat", "a+");

				//Verifica quem esta marcado para remocao (*|) e finaliza a op
				fseek(matches, 0L, SEEK_END);
				tam = ftell(matches);
				fseek(matches, 0L, SEEK_SET);
				
				for(i = 0; i < tam; i += 192){
					int cont = 0;
					char c;
					
					fseek(matches, i, SEEK_SET);
					
					c = fgetc(matches);
					if(c == '*') cont++;
					c = fgetc(matches);
					if(c == '|') cont++;
					
					fseek(matches, i, SEEK_SET);
					
					if(cont != 2){
						char dadosAux[192];
						int j;
						for(j = 0; j < 192; j++) dadosAux[j] = fgetc(matches);
						dadosAux[192] = '\0';
						j = 0;
						fputs(dadosAux, auxFile);
						fseek(auxFile, (i * 192), SEEK_SET);
					}
				}
				
				fclose(matches);
				remove("matches.dat");
				
				matches = fopen("matches.dat", "r+");
				if(matches == NULL) matches = fopen("matches.dat", "w+");
				
				for(i = 0; i < (getTamanhoArq(auxFile) / 192); i++){
					fseek(auxFile, (i * 192), SEEK_SET);
					int j;
					for(j = 0; j < 192; j++) str[j] = fgetc(auxFile);
					str[192] = '\0';
					fseek(matches, (i * 192), SEEK_SET);
					fputs(str, matches);
				}
				
				fclose(auxFile);
				remove("auxfile.dat");
				
				fclose(matches);
				
				break;
			//Finaliza operacao
			case 7:
				remove("iprimary.idx");
				remove("iwinner.idx");
				remove("imvp.idx");
				
				iprim = fopen("iprimary.idx", "r+");
				if(iprim == NULL){
					iprim = fopen("iprimary.idx", "w+");
				}
				
				iwinner = fopen("iwinner.idx", "r+");
				if(iwinner == NULL){
					iwinner = fopen("iwinner.idx", "w+");
				}
				
				imvp = fopen("imvp.idx", "r+");
				if(imvp == NULL){
					imvp = fopen("imvp.idx", "w+");
				}
				
				//Atualizando os indices no disco
				atualizaPrim(vetorPrim, iprim, count);
				atualizaWinner(vetorWinner, iwinner, count);
				atualizaMVP(vetorMVP, imvp, count);

				fclose(iprim);
				fclose(iwinner);	
				fclose(imvp);
				
				return 0;
			default:
				break;
		}
	}
	return 0;
}
