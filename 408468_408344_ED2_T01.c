/*
 * UFSCar - Sorocaba
 * Estruturas de Dados 2 - 2015
 * Trabalho 01
 * Eduardo Romao da Rocha - 408468
 * Matheus Gomes Barbieri - 408344
 * */
 
 #include "408468_408344_ED2_T01.h"
 
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
	fseek(f, 0L, SEEK_END);
	//Passando os valores formatados para uma srting auxiliar,
	//e a imprimindo no arquivo
	sprintf(aux, "%s@%s@%s@%s@%s@%s@%s@%s@%s@", chave, na, nv, data, dur, win, pla, plv, mvp);
	fprintf(f, "%s", aux);
	
	//Comletando com #'s
	for(i = 0; i < (192 - strlen(aux)); i++) fprintf(f, "#");
	fseek(f, 0L, SEEK_SET);
}

int getTamanhoArq(FILE *f){
	int tam;
	
	fseek(f, 0L, SEEK_END);
	tam = ftell(f);
	fseek(f, 0L, SEEK_SET);
	
	return tam;
}

void carregaVetor(FILE *f, Registro *v){
	
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

//Verifica no arquivo de dados se uma dada chave ja foi inserida
int chaveJaExiste(Registro *v, char *ch, int k){
	int i;
	for(i = 0; i < k; i++){
		if(strcmp(ch, v[i].chave) == 0) return 1;
	}
	
	return 0;
}

void geraIndice(char *rgStr, Registro *v1, Registro *v2, Registro *v3, int k){
	char aux[192], *ch, *c1, *w, *m;
	int i = 0;
	
	ch = malloc(sizeof(char) * 39 + 1);
	if(ch == NULL) exit(1);
	
	c1 = malloc(sizeof(char) * 39 + 1);
	if(c1 == NULL) exit(1);
	
	w = malloc(sizeof(char) * 39 + 1);
	if(w == NULL) exit(1);
	
	m = malloc(sizeof(char) * 39 + 1);
	if(m == NULL) exit(1);
	
	while(rgStr[i] != '#') aux[i++] = rgStr[i];
	aux[i] = '\0';
	
	ch = strtok(aux, "@");
	c1 = strtok(NULL, "@");
	c1 = strtok(NULL, "@");
	c1 = strtok(NULL, "@");
	c1 = strtok(NULL, "@");
	w = strtok(NULL, "@");
	c1 = strtok(NULL, "@");
	c1 = strtok(NULL, "@");
	m = strtok(NULL, "@");
	
	strcpy(v1[k].chave, ch);
	strcpy(v2[k].chave, ch);
	strcpy(v3[k].chave, ch);
	
	free(ch);
	free(c1);
	free(w);
	free(m);
}

//As funcoes de ordenacao abaixo sao implementacoes do algoritmo de Selection Sort
void ordenaPorChave(Registro *v, int n){
	int i,j, min;
	Registro aux;
	for(i = 0; i < n; i++){
		min = i;
		for(j = i + 1; j < n; j++){
			if(strcmp(v[j].chave, v[min].chave) < 0) min = j;
		}
		aux = v[i];
		v[i] = v[min];
		v[min] = aux;
	}
}

void ordenaPorVenc(Registro *v, int n){
	int i,j, min;
	Registro aux;
	for(i = 0; i < n; i++){
		min = i;
		for(j = i + 1; j < n; j++){
			if(strcmp(v[j].winner, v[min].winner) < 0) min = j;
		}
		aux = v[i];
		v[i] = v[min];
		v[min] = aux;
	}
}

void ordenaPorMVP(Registro *v, int n){
	int i,j, min;
	Registro aux;
	for(i = 0; i < n; i++){
		min = i;
		for(j = i + 1; j < n; j++){
			if(strcmp(v[j].mvp, v[min].mvp) < 0) min = j;
		}
		aux = v[i];
		v[i] = v[min];
		v[min] = aux;
	}
}

//Imprime cada campo do registro, separando por linha
void printDados(char *s){
	printf("%s\n", strtok(s, "@"));
	printf("%s\n", strtok(NULL, "@"));
	printf("%s\n", strtok(NULL, "@"));
	printf("%s\n", strtok(NULL, "@"));
	printf("%s\n", strtok(NULL, "@"));
	printf("%s\n", strtok(NULL, "@"));
	printf("%s\n", strtok(NULL, "@"));
	printf("%s\n", strtok(NULL, "@"));
	printf("%s\n", strtok(NULL, "@"));
	printf("\n");
}
