#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//VARIÁVEL DISPONÍVEL PARA LIMPAR A TELA
char limpar[6];

void jogar(int x, int y, int q_bomba);

//FUNÇÃO QUE MODIFICA A VARIÁVEL 'LIMPAR' DE ACORDO COM O SO
void inicio(){
	//COMANDO LINUX, COMANDO WINDOWS
	int y = system("clear"), x = system("cls");

	if(!x){
		limpar[0] = 'c';
		limpar[1] = 'l';
		limpar[2] = 's';
		limpar[3] = '\0';
	}
	else if(!y){
		limpar[0] = 'c';
		limpar[1] = 'l';
		limpar[2] = 'e';
		limpar[3] = 'a';
		limpar[4] = 'r';
		limpar[5] = '\0';
		system("clear");
	}
}

//ENSINA O USUÁRIO A JOGAR
void como_jogar(){
	int i, j;
	system(limpar);
	printf("##INTRODUCAO##\n\n");
	printf("#No jogo existem 3 dificuldades, quanto maior a dificuldade, maior o tamanho\ndo campo e número de bombas.\n");
	printf("#Para vencer o jogo, voce precisa cavar todas as posicoes que nao sejam bombas.\n");
	printf("#As coordenadas desconhecidas sao representadas por 'X', as conhecidas sao\nrepresentadas pelo numero de bombas adjacentes a ela e as marcadas sao representadas com 'M'.\n");
	printf("#Dentro da partida, voce pode realizar 4 comandos: Cavar, Marcar, Desmarcar e Especial.\n");
	printf("\n##COMANDOS##\n\n");
	printf("#Cavar     -> cava o lugar desejado e, se houver bomba, voce perde.\n");
	printf("#Marcar    -> marca a posicao desejada, permitindo-lhe marcar possiveis bombas.\n");
	printf("#Desmarcar -> desmarca uma posicao ja marcada.\n");
	printf("#Especial  -> permite que voce cave todas as posicoes adjacentes a uma posicao\nja cavada caso haja uma quantidade de marcacoes adjacentes a ele iguais ao numero de bombas\nadjacentes.\n");
	printf("\n");
	//MAPA
	printf("-------------------->\n");
	printf("|  ");
	for(i = 0; i < 9; i++)
		printf("%d ", i + 1);
	printf("\n");
	for(i = 0; i < 9; i++){
		printf("|%d ", i + 1);
		for(j = 0; j < 9; j++)
			printf("X ");
		printf("\n");
	}
	printf("V\n");
	//MAPA
	printf("\n##REGRAS##\n\n");
	printf("#Primeiro voce digita a inicial da acao em minuscula, depois a coordenada x da posicao\ndesejada e logo apos a coordenada y.\n");
	printf("#Vale ressaltar que o eixo y cresce de cima para baixo como mostrado no esquema acima.\n");
	printf("#Exemplo de comando que cava a posicao x = 2, y = 4: c 2 4\n");
	printf("#Durante a partida, será mostrado o número de posições marcadas como 'bombas', caso voce\nmarque um numero de posicoes maior que a quantidade de bombas, este passará a ser negativo.\n");
	printf("#Obrigado por usar nosso jogo!\n");
	printf("#Pressione <ENTER> para voltar ao menu.\n");
	getchar();
}

//FUNÇÃO ONDE O USUÁRIO ESCOLHE A DIFICULDADE
int dificuldade(){
	int opcao, errado = 0, continuar = 1;

	while(continuar){

		system(limpar);

		if(errado)
			printf("Por favor, digite uma opcao valida!\n");
		errado = 0;

		printf("###DIFICULDADE###\n");
		printf("1.Facil:   (09 x 09)\n");
		printf("2.Medio:   (16 x 16)\n");
		printf("3.Dificil: (30 x 16)\n");
		printf("4.Menu--------------\n");

		printf("Digite a opcao escolhida: ");
		scanf("%d", &opcao);
		getchar(); //CAPTURA O <ENTER>

		switch(opcao){
			case 1:
				jogar( 9,  9, 10);
				break;
			case 2:
				jogar(16, 16, 40);
				break;
			case 3:
				jogar(16, 30, 99);
				break;
			case 4:
				continuar = 0;
				break;
			default:
				errado = 1;
				break;
		}
	}
	return 0;
}

//FUNÇÃO MAIN
int main(){
	int opcao, errado = 0, continuar = 1;
	inicio();

	while(continuar){

		system(limpar);

		if(errado)
			printf("Por favor, digite um valor valido!\n");
		errado = 0;

		printf("###INICIO###\n");
		printf("1.Jogar-----\n");
		printf("2.Como Jogar\n");
		printf("3.Sair------\n");

		printf("Digite a opcao escolhida: ");
		scanf("%d", &opcao);
		getchar(); // CAPTURA O <ENTER>

		switch(opcao){
			case 1:
				dificuldade();
				break;
			case 2:
				como_jogar();
				break;
			case 3:
				continuar = 0;
				break;
			default:
				errado = 1;
				break;
		}
	}
	return 0;
}

//GERA DIFERENTES E ALEÁTORIAS COORDENADAS PARA AS BOMBAS
void gerar_bombas(int* bombas, int tam, int maximo){
	int i, j, numero, achou;

	srand(time(NULL));

	for(i = 0; i < tam; i++){
		do{
			achou = 0;
			numero = rand() % maximo;
			for(j = 0; j <= i; j++){
				if(numero == *(bombas + j)){
					achou = 1; //NÚMERO ALEATÓRIO JÁ EXISTE
					break;
				}
			}
		}while(achou);
		*(bombas + i) = numero;
	}
	return;
}

//PREENCHE O CAMPO COM DETALHES
void preencher_campo(int** campo, int x, int y){
	int i, j, q_bomba_lado;
	for(i = 0; i < y; i++){
		for(j = 0; j < x; j++){
			if(campo[i][j] == -1)
				continue;
			q_bomba_lado = 0;
			if((i > 0) && (campo[i - 1][j] == -1))
				q_bomba_lado++;
			if((i < y - 1) && (campo[i + 1][j] == -1))
				q_bomba_lado++;
			if((j > 0) && (campo[i][j - 1] == -1))
				q_bomba_lado++;
			if((j < x - 1) && (campo[i][j + 1] == -1))
				q_bomba_lado++;
			if(((i > 0) && (j > 0)) && (campo[i - 1][j - 1] == -1))
				q_bomba_lado++;
			if(((i > 0) && (j < x - 1)) && (campo[i - 1][j + 1] == -1))
				q_bomba_lado++;
			if(((i < y - 1) && (j > 0)) && (campo[i + 1][j - 1] == -1))
				q_bomba_lado++;
			if(((i < y - 1) && (j < x - 1)) && (campo[i + 1][j + 1] == -1))
				q_bomba_lado++;
			campo[i][j] = q_bomba_lado;
		}
	}
}

//FUNÇÃO QUE REVELA A POSIÇÃO ZERO
void cavar_zero(int** campo, char** campo_real, int i, int j, int x, int y, int* cavados){
	campo[i][j] = -2;
	campo_real[i][j] = '0';
	*(cavados) -= 1;
	if(i > 0){
		if(campo[i - 1][j] == 0){
			cavar_zero(campo, campo_real, i - 1, j, x, y, cavados);
		}
		else if((campo[i - 1][j] != -2) && (campo_real[i - 1][j] == 'X')){
			campo_real[i - 1][j] = campo[i - 1][j] + '0';
			*cavados -= 1;
		}
	}
	if(i < y - 1){
		if(campo[i + 1][j] == 0){
			cavar_zero(campo, campo_real, i + 1, j, x, y, cavados);
		}
		else if((campo[i + 1][j] != -2) && (campo_real[i + 1][j] == 'X')){
			campo_real[i + 1][j] = campo[i + 1][j] + '0';
			*cavados -= 1;
		}
	}
	if(j > 0){
		if(campo[i][j - 1] == 0){
			cavar_zero(campo, campo_real, i, j - 1, x, y, cavados);
		}
		else if((campo[i][j - 1] != -2) && (campo_real[i][j - 1] == 'X')){
			campo_real[i][j - 1] = campo[i][j - 1] + '0';
			*cavados -= 1;
		}
	}
	if(j < x - 1){
		if(campo[i][j + 1] == 0){
			cavar_zero(campo, campo_real, i, j + 1, x, y, cavados);
		}
		else if((campo[i][j + 1] != -2) && (campo_real[i][j + 1] == 'X')){
			campo_real[i][j + 1] = campo[i][j + 1] + '0';
			*cavados -= 1;
		}
	}
	if((i > 0) && (j > 0)){
		if(campo[i - 1][j - 1] == 0){
			cavar_zero(campo, campo_real, i - 1, j - 1, x, y, cavados);
		}
		else if((campo[i - 1][j - 1] != -2) && (campo_real[i - 1][j - 1] == 'X')){
			campo_real[i - 1][j - 1] = campo[i - 1][j - 1] + '0';
			*cavados -= 1;
		}
	}
	if((i > 0) && (j < x - 1)){
		if(campo[i - 1][j + 1] == 0){
			cavar_zero(campo, campo_real, i - 1, j + 1, x, y, cavados);
		}
		else if((campo[i - 1][j + 1] != -2) && (campo_real[i - 1][j + 1] == 'X')){
			campo_real[i - 1][j + 1] = campo[i - 1][j + 1] + '0';
			*cavados -= 1;
		}
	}
	if((i < y - 1) && (j > 0)){
		if(campo[i + 1][j - 1] == 0){
			cavar_zero(campo, campo_real, i + 1, j - 1, x, y, cavados);
		}
		else if((campo[i + 1][j - 1] != -2) && (campo_real[i + 1][j - 1] == 'X')){
			campo_real[i + 1][j - 1] = campo[i + 1][j - 1] + '0';
			*cavados -= 1;
		}
	}
	if((i < y - 1) && (j < x - 1)){
		if(campo[i + 1][j + 1] == 0){
			cavar_zero(campo, campo_real, i + 1, j + 1, x, y, cavados);
		}
		else if((campo[i + 1][j + 1] != -2) && (campo_real[i + 1][j + 1] == 'X')){
			campo_real[i + 1][j + 1] = campo[i + 1][j + 1] + '0';
			*cavados -= 1;
		}
	}
}

//CAVA AS CASAS ADJACENTES DE ACORDO COM AS BOMBAS MARCADAS
int cavar_especial(int** campo, char** campo_real, int i, int j, int x, int y, int* cavados){
	int k;
	int n_x[8], n_y[8], l = 0;//COORDENADAS PARA LUGARE SEM BOMBA E MARCAÇÃO
	int b_x[8], b_y[8], b = 0;//COORDENADAS PARA LUGARES COM BOMBA OU MARCAÇÃO
	int q_certa = 0;		  //QUANTIDADE DE BOMBAS MARCADAS
	int q_marca = 0;		  //QUANTIDADE DE MARCAÇÕES EM NÃO BOMBAS
	int q_bomba = 0;		  //QUANTIDADE DE BOMBAS SEM MARCAÇÃO
	if(i < y - 1){
		if((campo[i + 1][j] == -1) || (campo_real[i + 1][j] == 'M')){
			b_x[b] = j; b_y[b] = i + 1; b++;
		}
		else if((campo[i + 1][j] >= 0) && (campo_real[i + 1][j] == 'X')){
			n_x[l] = j; n_y[l] = i + 1; l++;
		}
	}
	if(i > 0){
		if((campo[i - 1][j] == -1) || (campo_real[i - 1][j] == 'M')){
			b_x[b] = j; b_y[b] = i - 1; b++;
		}
		else if((campo[i - 1][j] >= 0) && (campo_real[i - 1][j] == 'X')){
			n_x[l] = j; n_y[l] = i - 1; l++;
		}
	}
	if(j < x - 1){
		if((campo[i][j + 1] == -1) || (campo_real[i][j + 1] == 'M')){
			b_x[b] = j + 1; b_y[b] = i; b++;
		}
		else if((campo[i][j + 1] >= 0) && (campo_real[i][j + 1] == 'X')){
			n_x[l] = j + 1; n_y[l] = i; l++;
		}	
	}
	if(j > 0){
		if((campo[i][j - 1] == -1) || (campo_real[i][j - 1] == 'M')){
			b_x[b] = j - 1; b_y[b] = i; b++;
		}
		else if((campo[i][j - 1] >= 0) && (campo_real[i][j - 1] == 'X')){
			n_x[l] = j - 1; n_y[l] = i; l++;
		}	
	}
	if((j > 0) && (i > 0)){
		if((campo[i - 1][j - 1] == -1) || (campo_real[i - 1][j - 1] == 'M')){
			b_x[b] = j - 1; b_y[b] = i - 1; b++;
		}
		else if((campo[i - 1][j - 1] >= 0) && (campo_real[i - 1][j - 1] == 'X')){
			n_x[l] = j - 1; n_y[l] = i - 1; l++;
		}	
	}
	if((j < x - 1) && (i > 0)){
		if((campo[i - 1][j + 1] == -1) || (campo_real[i - 1][j + 1] == 'M')){
			b_x[b] = j + 1; b_y[b] = i - 1; b++;
		}
		else if((campo[i - 1][j + 1] >= 0) && (campo_real[i - 1][j + 1] == 'X')){
			n_x[l] = j + 1; n_y[l] = i - 1; l++;
		}	
	}
	if((j < x - 1) && (i < y - 1)){
		if((campo[i + 1][j + 1] == -1) || (campo_real[i + 1][j + 1] == 'M')){
			b_x[b] = j + 1; b_y[b] = i + 1; b++;
		}
		else if((campo[i + 1][j + 1] >= 0) && (campo_real[i + 1][j + 1] == 'X')){
			n_x[l] = j + 1; n_y[l] = i + 1; l++;
		}	
	}
	if((j > 0) && (i < y - 1)){
		if((campo[i + 1][j - 1] == -1) || (campo_real[i + 1][j - 1] == 'M')){
			b_x[b] = j - 1; b_y[b] = i + 1; b++;
		}
		else if((campo[i + 1][j - 1] >= 0) && (campo_real[i + 1][j - 1] == 'X')){
			n_x[l] = j - 1; n_y[l] = i + 1; l++;
		}	
	}
	for(k = 0; k < b; k++){
		if((campo[b_y[k]][b_x[k]] == -1) && (campo_real[b_y[k]][b_x[k]] == 'M')){
			q_certa++;
		}
		else if((campo[b_y[k]][b_x[k]] == -1) && (campo_real[b_y[k]][b_x[k]] != 'M')){
			q_bomba++;
		}
		else if((campo[b_y[k]][b_x[k]] != -1) && (campo_real[b_y[k]][b_x[k]] == 'M')){
			q_marca++;
		}
	}
	if(q_certa == campo[i][j]){
		for(k = 0; k < l; k++){
			if(campo[n_y[k]][n_x[k]] == 0){
				cavar_zero(campo, campo_real, n_y[k], n_x[k], x, y, cavados);
			}
			else if(campo[n_y[k]][n_x[k]] > 0){
				campo_real[n_y[k]][n_x[k]] = campo[n_y[k]][n_x[k]] + '0';
				*cavados -= 1;
			}
		}
		return 1;//AÇÃO VÁLIDA
	}
	else if((q_certa != campo[i][j]) && (q_marca == q_bomba) && (q_bomba + q_certa == campo[i][j])){
		return -1;//AÇÃO VÁLIDA, PORÉM ERRADA, PERDEU O JOGO
	}
	else{
		return 0;//AÇÃO INVÁLIDA
	}
}

//FUNÇÃO ONDE A PARTIDA OCORRERÁ
void jogar(int alt, int lar, int q_bomba){
	int i, j, k, continuar = 1;
	int certo_marcado = 0; 				//BOMBAS MARCADAS CORRETAMENTE
	int errado_marcado = 0;				//MARCAÇÕES ERRADAS
	int errado = 0;						//VARIÁVEL QUE GUARDA 1 QUANDO OCORRE UM ERRO
	int co_x, co_y;						//COORDENADAS ESCOLHIDAS
	char comando;						//COMANDO ESCOLHIDO
	int nao_bomba = alt * lar - q_bomba;//CASAS SEGURAS A SEREM CAVADAS

	//ALOCAÇÃO DE MEMÓRIA DINÃMICA
	int *coordenadas = (int*) calloc(q_bomba, sizeof(int));		//VETOR QUE GUARDA AS COORDENADAS DAS BOMBAS
	char **campo_real = (char**) malloc(alt * sizeof(char*));	//MATRIZ USADA COMO INTERFACE
	int **campo = (int**) malloc(alt * sizeof(int*));			//MATRIZ USADA PARA MANIPULACÃO

	for(i = 0; i < alt; i++){
		//ALOCA ESPAÇOS PARA CADA LINHA
		*(campo + i) = (int*) calloc(lar, sizeof(int));
		*(campo_real + i) = (char*) malloc(lar * sizeof(char));
		//PREENCHE A LINHA DO CAMPO_REAL COM 'X'S
		for(j = 0; j < lar; j++){
			campo_real[i][j] = 'X';
		}
	}
	//

	//GERA DIFERENTES E ALEÁTORIAS COORDENADAS PARA AS BOMBAS
	gerar_bombas(coordenadas, q_bomba, lar * alt);

	//PREENCHE A MATRIZ COM AS COORDENADAS DAS BOMBAS GERADAS ANTERIORMENTE
	for(i = 0; i < q_bomba; i++){
		j = *(coordenadas + i) % lar;
		k = (*(coordenadas + i) - j) / lar;
		campo[k][j] = -1;
	}
	free(coordenadas);

	//PREENCHE O CAMPO COM DETALHES
	preencher_campo(campo, lar, alt);

	while(continuar){//O JOGO
		system(limpar);
		//INTERFACE DO USUÁRIO
		if(errado){
			printf("Por favor, digite um comando válido!\n");
		} errado = 0;
		printf("= = =\n");
		printf("   ");
		for(i = 0; i < lar; i++)
			printf("%02d ", i + 1);
		printf("\n");
		for(i = 0; i < alt; i++){
			printf("%02d ", i + 1);
			for(j = 0; j < lar; j++)
				printf("%02c ", campo_real[i][j]);
			printf("\n");
		}
		printf("= = =\n");
		printf("bombas = %d\n", q_bomba - certo_marcado - errado_marcado);
		//
		printf("comando: ");
		scanf("%c %d %d", &comando, &co_x, &co_y);
		getchar();//CAPTURA O <ENTER>

		//VERIFICA SE VALORES ESTÃO DENTRO DO ACEITÁVEL
		if((co_x > lar) || (co_x < 1) || (co_y > alt) || (co_y < 1)){
			errado = 1;
			continue;
		}
		//VERIFICA SE O COMANDO ESCOLHIDO É ACEITÁVEL
		if(!((comando == 'm') || (comando == 'c') || (comando == 'd') || (comando == 'e'))){
			errado = 1;
			continue;
		}
		co_y--;
		co_x--;
		if(campo[co_y][co_x] == -1){
			switch(comando){
				case 'm':
					if(campo_real[co_y][co_x] == 'X'){
						certo_marcado++;
						campo_real[co_y][co_x] = 'M';
					}
					else
						errado = 1;
					break;
				case 'd':
					if(campo_real[co_y][co_x] == 'M'){
						certo_marcado--;
						campo_real[co_y][co_x] = 'X';
					}
					else
						errado = 1;
					break;
				case 'c':
					continuar = 0;
					break;
				case 'e':
					errado = 1;
					break;
			}
		}
		else if((campo[co_y][co_x] > 0) && (campo[co_y][co_x] < 9)){
			switch(comando){
				case 'm':
					if(campo_real[co_y][co_x] == 'X'){
						errado_marcado++;
						campo_real[co_y][co_x] = 'M';
					}
					else
						errado = 1;
					break;
				case 'd':
					if(campo_real[co_y][co_x] == 'M'){
						errado_marcado--;
						campo_real[co_y][co_x] = 'X';
					}
					else
						errado = 1;
					break;
				case 'c':
					nao_bomba--;
					campo_real[co_y][co_x] = campo[co_y][co_x] + '0';
					break;
				case 'e':
					if((campo_real[co_y][co_x] != 'X') && (campo_real[co_y][co_x] != 'M') && (campo_real[co_y][co_x] != '0')){
						int res = cavar_especial(campo, campo_real, co_y, co_x, lar, alt, &nao_bomba);
						if(!res){
							errado = 1;
						}
						else if(res == -1){
							continuar = 0;
						}
					}
					else
						errado = 1;
					break;

			}
		}
		else if(campo[co_y][co_x] == 0){
			switch(comando){
				case 'm':
					if(campo_real[co_y][co_x] == 'X'){
						errado_marcado++;
						campo_real[co_y][co_x] = 'M';
					}
					else
						errado = 1;
					break;
				case 'd':
					if(campo_real[co_y][co_x] == 'M'){
						errado_marcado--;
						campo_real[co_y][co_x] = 'X';
					}
					else
						errado = 1;
					break;
				case 'c':
					if((campo[co_y][co_x] == 0) && (campo_real[co_y][co_x] == 'X')){
						cavar_zero(campo, campo_real, co_y, co_x, lar, alt, &nao_bomba);
					}
					else
						errado = 1;
					break;
				case 'e':
					errado = 1;
					break;
			}
		}
		else if(campo[co_y][co_x] == -2){
			errado = 1;
		}
		if(nao_bomba == 0){
			continuar = 0;
		}
	}
	system(limpar);
	if(nao_bomba > 0){
		printf("Voce Perdeu!\n");
	}
	else{
		printf("Voce Ganhou!\n");
	}
	printf("Pressione <Enter> para continuar.\n");
	getchar();
	free(campo);
	free(campo_real);
	return;
}
