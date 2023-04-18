#include "labirinto.hpp"


void GenerateMatrix(Matrix *mat){
	int data = 0;

	for(int i=0; i<MAXROWS; i++)
        for(int j=0; j<MAXCOLS; j++){
        	data = rand()%20;
        	if(data <= 10)
            	mat->m[i][j].val = (1 + rand()%5) + '0'; 
            else if ((data > 10) && (data < 16))
            	mat->m[i][j].val = '*';
            else
            	mat->m[i][j].val = '#';
        }
}

void SetMatrixSignature(){
	FILE *f;

	if ((f = fopen("dataset/input.data", "w")) == NULL){
		printf("file could not be opened");
    	exit(-1);
    }

    fprintf(f,"%d %d %d", MAXROWS, MAXCOLS, NUMAT); 
    fprintf(f,"\n");
    fclose(f);

}

void SaveMatrix(Matrix *mat){
	
	FILE *f;

	if ((f = fopen("dataset/input.data", "a")) == NULL){
		printf("file could not be opened");
    	exit(-1);
    }

    GenerateMatrix(mat);

	for (int i=0;i<MAXROWS;i++){
        for (int j=0;j<MAXCOLS;j++)
             fprintf(f,"%c ", mat->m[i][j].val); 
        fprintf(f,"\n");
	}
	fprintf(f,"\n");
	fclose(f);
}


void LerMatriz(string matriz_atual[MAXROWS][MAXCOLS], int linhas, int colunas, fstream &arquivo)
{
	int j=0;
	
	if (arquivo.is_open()) 
	{
		string linha;
		int c=0;

		getline(arquivo, linha);

		for (int i=0; i<linhas; i++)
		{
			getline(arquivo, linha);
			stringstream ss(linha);
			string substr;
			vector <string> substrings;
			
			while (getline(ss, substr, ' '))
			{
				substrings.push_back(substr);
				matriz_atual[i][c] = substr;
				c++;
			}
			c=0;
		}
	}
}

void EscreverMatriz(string matriz_atual[MAXROWS][MAXCOLS], int *numero_mapa, int *pontos_totais, vector<CaminhoPercorrido>*posicoes_percorridas)
{
	string nome_arquivo;
	CaminhoPercorrido pp;

	nome_arquivo = "input" + to_string(*numero_mapa) + ".data";
	//cout << endl << "teste: " << nome_arquivo << endl;
	pp.nomeArquivo = nome_arquivo;
	(*posicoes_percorridas).push_back(pp);

	string diretorio = "dataset/" + nome_arquivo;
	ofstream arquivo(diretorio);

	for (int i=0; i<MAXROWS; i++) {
		for (int j=0; j<MAXCOLS; j++) {
			arquivo << matriz_atual[i][j] << " ";
		}
		arquivo << endl;
	}

	for (int i=0; i<MAXROWS; i++) {
		for (int j=0; j<MAXCOLS; j++) {
			if (matriz_atual[i][j] != "#" && matriz_atual[i][j] != "*") {
				*pontos_totais += stoi(matriz_atual[i][j]);
			}
		}
	}

	nome_arquivo.clear();
	*numero_mapa += 1;
}

void PercorrerMatriz(string mapa_atual[MAXROWS][MAXCOLS], int linhas, int colunas, int *vidas, int *pontos_ganhos, int *pontos_totais, int *fase, bool *possivel, int *linha_atual, int *coluna_atual, int *items, int *items_totais, int *perigos_totais, int *casas_percorridas, bool *vitoria, int *mochila, vector<CaminhoPercorrido>*posicoes_percorridas)
{
	int linha_inicial, coluna_inicial;
	int possivel_direcao;
	int matriz_atual_posicao;
	CaminhoPercorrido cp;

	//Ler o arquivo referente à fase que o personagem está
	string nome_arquivo_fase = "input" + to_string(*fase) + ".data";
	string diretorio = "dataset/" + nome_arquivo_fase;
	fstream arquivo(diretorio);
	bool proximo_passo = false;

	for (int i=0; i<(*posicoes_percorridas).size(); i++) {
		if (nome_arquivo_fase == (*posicoes_percorridas)[i].nomeArquivo){
			matriz_atual_posicao = i;
		}
	}

	if (arquivo.is_open()) 
	{
		//Lendo o arquivo e passando ele para uma variável de matriz que será trabalhada
		string linha;
		int c=0;
			for (int i=0; i<linhas; i++)
		{
			getline(arquivo, linha);
			stringstream ss(linha);
			string substr;
			vector <string> substrings;
			
			while (getline(ss, substr, ' '))
			{
				substrings.push_back(substr);
				mapa_atual[i][c] = substr;
				c++;
			}
			c=0;
		}

		//Verificando se já existe uma posição inicial nesse mapa
		if (*possivel == false) {
			//Se "possivel" for "false", ele irá randomizar uma posição inicial no novo mapa
			do {
				linha_inicial = rand() % MAXROWS;
				coluna_inicial = rand () % MAXCOLS;

				//Setando posição inicial de um novo mapa
				//A posição inicial deverá ser diferente de uma parede, de um perigo e não pode se localizar na última coluna
				if (((mapa_atual[linha_inicial][coluna_inicial] != "#") && (mapa_atual[linha_inicial][coluna_inicial] != "*") && (coluna_inicial < MAXCOLS-1))) {
					*linha_atual = linha_inicial;
					*coluna_atual = coluna_inicial;
					*possivel = true;
					cout << endl << "-------------------------------------";
					cout << endl << "---------- MAPA " << *fase << "----------";
					cout << endl << "NOVO MAPA! - NOVA FASE! - FASE " << *fase << "!" << endl;
					cout << "POSIÇÃO INICIAL -> [" << *linha_atual << "] [" << *coluna_atual << "]" << endl << endl;

				

					for (int i=0; i<linhas; i++) {
						for (int j=0; j<colunas; j++) {
							cout << mapa_atual[i][j] << " ";
						}			
					cout << endl;
					}
					//Setar coordenada que foi passada
					(*posicoes_percorridas)[matriz_atual_posicao].caminho.insert(make_pair(*linha_atual, *coluna_atual));
				}
			} while(*possivel == false); 
		}

		//Andando para a proxima posição
		if (*vidas > 0) {
			do {
				possivel_direcao = rand()%8+1;
				//cout << endl << endl << endl << "-> Número da possível direção: " << possivel_direcao << endl << endl << endl;

				//norte
				if (possivel_direcao == 1) {
					//Verifica se a posição existe e se não existe uma parede nela
					if (*linha_atual > 0 && mapa_atual[*linha_atual-1][*coluna_atual] != "#") {
						cout << endl << "-> VAI PARA O NORTE" << endl;
						*linha_atual = *linha_atual -1;
						*casas_percorridas = *casas_percorridas +1;
						proximo_passo = true;
						//Verifica se a posição têm um perigo
						if (mapa_atual[*linha_atual][*coluna_atual] == "*") {
							*vidas = *vidas -1;
							*perigos_totais = *perigos_totais +1;
							cout << endl << "------------------------------------------------------------------------------------";
							cout << endl << "------ Andou para posição [" << *linha_atual << "] [" << *coluna_atual << "] -------";
							cout << endl << "------ Perdeu uma vida ------------- Total de vidas: [" << *vidas << "] ------------";
							cout << endl << "MOCHILA " << *mochila << endl;
						}
						//Posição tem um numero
						else {
							//Verifica se a posição tem items para serem pegos
							if ((mapa_atual[*linha_atual][*coluna_atual] != "0") && (mapa_atual[*linha_atual][*coluna_atual] != "*")) {
								int novo_valor_posicao;
								*pontos_ganhos = *pontos_ganhos +1;
								*mochila = *mochila +1;

								novo_valor_posicao = stoi(mapa_atual[*linha_atual][*coluna_atual]);
								novo_valor_posicao = novo_valor_posicao -1;

								mapa_atual[*linha_atual][*coluna_atual] = to_string(novo_valor_posicao);
								cout << endl << "NOVO VALOR DA POSIÇÃO: " << to_string(novo_valor_posicao) << endl << endl;

								*items = *items +1;
								*items_totais = *items_totais +1;
								cout << endl;
								cout << endl << "------------------------------------------------------------------------------------";
								cout << endl << "------ Andou para posição [" << *linha_atual << "] [" << *coluna_atual << "] -------";
								cout << endl << "------ Pegou um item ------------- Total de itens: [" << *items << "] --------------";
								cout << endl << "------ PONTOS NO TOTAL = [" << *pontos_ganhos << "] ---------------------------------";
								cout << endl << "MOCHILA " << *mochila << endl;
								cout << endl;
								if (*items == 4) {
									//Verifica se ele já tem o máximo de vidas
									if (*vidas == 10) {
										cout << endl << endl << "-> Você coletou 4 items, porém já possui o número máximo de vida!" << endl;
										*items = 0;
									}
									//Recebe uma vida caso não tenha o máximo de vidas
									else {
										*vidas = *vidas +1;
										*items = 0;
										cout << endl << endl << "-> Você coletou 4 items e ganhou uma vida!";
										cout << endl << "Total de vidas: [" << *vidas << "]";
									}
								}
							}
							else {
								cout << endl << endl << "-> Você chegou em uma posição sem perigos, porém não há itens para serem coletados!" << endl;
							}
						}
					} 
				}
				//nordeste
				else if (possivel_direcao == 2) {
					//Verifica se a posição existe e se não existe uma parede nela
					if ((*linha_atual > 0) && (*coluna_atual < MAXCOLS-1) && (mapa_atual[*linha_atual-1][*coluna_atual+1] != "#")) {
						cout << endl << "-> VOU PARA O NORDESTE" << endl;
						*linha_atual = *linha_atual -1;
						*coluna_atual = *coluna_atual +1;
						proximo_passo = true;
						*casas_percorridas = *casas_percorridas +1;
						//Verifica se a posição têm um perigo
						if (mapa_atual[*linha_atual][*coluna_atual] == "*") {
							*vidas = *vidas -1;
							*perigos_totais = *perigos_totais +1;
							cout << endl << "------------------------------------------------------------------------------------";
							cout << endl << "------ Andou para posição [" << *linha_atual << "] [" << *coluna_atual << "] -------";
							cout << endl << "------ Perdeu uma vida ------------- Total de vidas: [" << *vidas << "] ------------";
							cout << endl << "MOCHILA " << *mochila << endl;
						}
						//Posição tem um numero
						else {
							//Verifica se a posição tem items para serem pegos
							if ((mapa_atual[*linha_atual][*coluna_atual] != "0") && (mapa_atual[*linha_atual][*coluna_atual] != "*")) {
								int novo_valor_posicao;
								*pontos_ganhos = *pontos_ganhos +1;

								novo_valor_posicao = stoi(mapa_atual[*linha_atual][*coluna_atual]);
								novo_valor_posicao = novo_valor_posicao -1;

								mapa_atual[*linha_atual][*coluna_atual] = to_string(novo_valor_posicao);
								cout << endl << "NOVO VALOR DA POSIÇÃO: " << to_string(novo_valor_posicao) << endl << endl;

								*items = *items +1;
								*items_totais = *items_totais +1;
								cout << endl;
								cout << endl << "------------------------------------------------------------------------------------";
								cout << endl << "------ Andou para posição [" << *linha_atual << "] [" << *coluna_atual << "] -------";
								cout << endl << "------ Pegou um item ------------- Total de itens: [" << *items << "] --------------";
								cout << endl << "------ PONTOS NO TOTAL = [" << *pontos_ganhos << "] ---------------------------------";
								cout << endl << "MOCHILA " << *mochila << endl;
								cout << endl;
								if (*items == 4) {
									//Verifica se ele já tem o máximo de vidas
									if (*vidas == 10) {
										cout << endl << endl << "-> Você coletou 4 items, porém já possui o número máximo de vida!" << endl;
										*items = 0;
									}
									//Recebe uma vida caso não tenha o máximo de vidas
									else {
										*vidas = *vidas +1;
										*items = 0;
										cout << endl << endl << "-> Você coletou 4 items e ganhou uma vida!";
										cout << endl << "Total de vidas: [" << *vidas << "]";
									}
								}
							}
							else {
								cout << endl << endl << "-> Você chegou em uma posição sem perigos, porém não há itens para serem coletados!" << endl;
							}
						}
						//Verificando se o personagem atingiu a última coluna, caso tenha atingido ele irá se teletransportar para a "fase 2" (próxima matriz)
						if (*coluna_atual == MAXCOLS-1) {
							if (*fase == NUMAT) {
								*fase = 1;
								*possivel = false;
								if (*mochila == 0) {
									*vitoria = true;
								}
								*mochila = 0;
							}
							else {
								*fase = *fase +1;
								*possivel = false;
							}
						}
					} 
				}
				//leste
				else if (possivel_direcao == 3) {
					//Verifica se a posição existe e se não existe uma parede nela
					if ((*coluna_atual < MAXCOLS-1) && (mapa_atual[*linha_atual][*coluna_atual+1] != "#")) {
						cout << endl << "-> VOU PARA O LESTE" << endl;
						*coluna_atual = *coluna_atual +1;
						proximo_passo = true;
						*casas_percorridas = *casas_percorridas +1;
						//Verifica se a posição têm um perigo
						if (mapa_atual[*linha_atual][*coluna_atual] == "*") {
							*vidas = *vidas -1;
							*perigos_totais = *perigos_totais +1;
							cout << endl << "------------------------------------------------------------------------------------";
							cout << endl << "------ Andou para posição [" << *linha_atual << "] [" << *coluna_atual << "] -------";
							cout << endl << "------ Perdeu uma vida ------------- Total de vidas: [" << *vidas << "] ------------";
							cout << endl << "MOCHILA " << *mochila << endl;
						}
						//Posição tem um numero
						else {
							//Verifica se a posição tem items para serem pegos
							if ((mapa_atual[*linha_atual][*coluna_atual] != "0") && (mapa_atual[*linha_atual][*coluna_atual] != "*")) {
								int novo_valor_posicao;
								*pontos_ganhos = *pontos_ganhos +1;
								*mochila = *mochila +1;

								novo_valor_posicao = stoi(mapa_atual[*linha_atual][*coluna_atual]);
								novo_valor_posicao = novo_valor_posicao -1;

								mapa_atual[*linha_atual][*coluna_atual] = to_string(novo_valor_posicao);
								cout << endl << "NOVO VALOR DA POSIÇÃO: " << to_string(novo_valor_posicao) << endl << endl;

								*items = *items +1;
								*items_totais = *items_totais +1;
								cout << endl;
								cout << endl << "------------------------------------------------------------------------------------";
								cout << endl << "------ Andou para posição [" << *linha_atual << "] [" << *coluna_atual << "] -------";
								cout << endl << "------ Pegou um item ------------- Total de itens: [" << *items << "] --------------";
								cout << endl << "------ PONTOS NO TOTAL = [" << *pontos_ganhos << "] ---------------------------------";
								cout << endl << "MOCHILA " << *mochila << endl;
								cout << endl;
								if (*items == 4) {
									//Verifica se ele já tem o máximo de vidas
									if (*vidas == 10) {
										cout << endl << endl << "-> Você coletou 4 items, porém já possui o número máximo de vida!" << endl;
										*items = 0;
									}
									//Recebe uma vida caso não tenha o máximo de vidas
									else {
										*vidas = *vidas +1;
										*items = 0;
										cout << endl << endl << "-> Você coletou 4 items e ganhou uma vida!";
										cout << endl << "Total de vidas: [" << *vidas << "]";
									}
								}
							}
							else {
								cout << endl << endl << "-> Você chegou em uma posição sem perigos, porém não há itens para serem coletados!" << endl;
							}
						}
						//Verificando se o personagem atingiu a última coluna, caso tenha atingido ele irá se teletransportar para a "fase 2" (próxima matriz)
						if (*coluna_atual == MAXCOLS-1) {
							if (*fase == NUMAT) {
								*fase = 1;
								*possivel = false;
								if (*mochila == 0) {
									*vitoria = true;
								}
								*mochila = 0;
							}
							else {
								*fase = *fase +1;
								*possivel = false;
							}
						}
					} 
				}
				//sudeste
				else if (possivel_direcao == 4) {
					//Verifica se a posição existe e se não existe uma parede nela
					if ((*linha_atual < MAXROWS-1) && (*coluna_atual < MAXCOLS-1) && (mapa_atual[*linha_atual+1][*coluna_atual+1] != "#")) {
						cout << endl << "-> VOU PARA O SUDESTE" << endl;
						*coluna_atual = *coluna_atual +1;
						*linha_atual = *linha_atual +1;
						proximo_passo = true;
						*casas_percorridas = *casas_percorridas +1;
						//Verifica se a posição têm um perigo
						if (mapa_atual[*linha_atual][*coluna_atual] == "*") {
							*vidas = *vidas -1;
							*perigos_totais = *perigos_totais +1;
							cout << endl << "------------------------------------------------------------------------------------";
							cout << endl << "------ Andou para posição [" << *linha_atual << "] [" << *coluna_atual << "] -------";
							cout << endl << "------ Perdeu uma vida ------------- Total de vidas: [" << *vidas << "] ------------";
							cout << endl << "MOCHILA " << *mochila << endl;
						}
						//Posição tem um numero
						else {
							//Verifica se a posição tem items para serem pegos
							if ((mapa_atual[*linha_atual][*coluna_atual] != "0") && (mapa_atual[*linha_atual][*coluna_atual] != "*")) {
								int novo_valor_posicao;
								*pontos_ganhos = *pontos_ganhos +1;
								*mochila = *mochila +1;

								novo_valor_posicao = stoi(mapa_atual[*linha_atual][*coluna_atual]);
								novo_valor_posicao = novo_valor_posicao -1;

								mapa_atual[*linha_atual][*coluna_atual] = to_string(novo_valor_posicao);
								cout << endl << "NOVO VALOR DA POSIÇÃO: " << to_string(novo_valor_posicao) << endl << endl;

								*items = *items +1;
								*items_totais = *items_totais +1;
								cout << endl;
								cout << endl << "------------------------------------------------------------------------------------";
								cout << endl << "------ Andou para posição [" << *linha_atual << "] [" << *coluna_atual << "] -------";
								cout << endl << "------ Pegou um item ------------- Total de itens: [" << *items << "] --------------";
								cout << endl << "------ PONTOS NO TOTAL = [" << *pontos_ganhos << "] ---------------------------------";
								cout << endl << "MOCHILA " << *mochila << endl;
								cout << endl;
								if (*items == 4) {
									//Verifica se ele já tem o máximo de vidas
									if (*vidas == 10) {
										cout << endl << endl << "-> Você coletou 4 items, porém já possui o número máximo de vida!" << endl;
										*items = 0;
									}
									//Recebe uma vida caso não tenha o máximo de vidas
									else {
										*vidas = *vidas+1;
										*items = 0;
										cout << endl << endl << "-> Você coletou 4 items e ganhou uma vida!";
										cout << endl << "Total de vidas: [" << *vidas << "]";
									}
								}
							}
							else {
								cout << endl << endl << "-> Você chegou em uma posição sem perigos, porém não há itens para serem coletados!" << endl;
							}
						}
						//Verificando se o personagem atingiu a última coluna, caso tenha atingido ele irá se teletransportar para a "fase 2" (próxima matriz) no próximo passo
						if (*coluna_atual == MAXCOLS-1) {
							if (*fase == NUMAT) {
								*fase = 1;
								*possivel = false;
								if (*mochila == 0) {
									*vitoria = true;
								}
								*mochila = 0;
							}
							else {
								*fase = *fase +1;
								*possivel = false;
							}
						}
					} 
				}
				//sul
				else if (possivel_direcao == 5) {
					//Verifica se a posição existe e se não existe uma parede nela
					if ((*linha_atual < MAXROWS-1) && (mapa_atual[*linha_atual+1][*coluna_atual] != "#")) {
						cout << endl << "-> VOU PARA O SUL" << endl;
						*linha_atual = *linha_atual +1;
						proximo_passo = true;
						*casas_percorridas = *casas_percorridas +1;
						//Verifica se a posição têm um perigo
						if (mapa_atual[*linha_atual][*coluna_atual] == "*") {
							*vidas = *vidas -1;
							*perigos_totais = *perigos_totais +1;
							cout << endl << "------------------------------------------------------------------------------------";
							cout << endl << "------ Andou para posição [" << *linha_atual << "] [" << *coluna_atual << "] -------";
							cout << endl << "------ Perdeu uma vida ------------- Total de vidas: [" << *vidas << "] ------------";
							cout << endl << "MOCHILA " << *mochila << endl;
						}
						//Posição tem um numero
						else {
							//Verifica se a posição tem items para serem pegos
							if ((mapa_atual[*linha_atual][*coluna_atual] != "0") && (mapa_atual[*linha_atual][*coluna_atual] != "*")) {
								int novo_valor_posicao;
								*pontos_ganhos = *pontos_ganhos +1;
								*mochila = *mochila +1;

								novo_valor_posicao = stoi(mapa_atual[*linha_atual][*coluna_atual]);
								novo_valor_posicao = novo_valor_posicao -1;

								mapa_atual[*linha_atual][*coluna_atual] = to_string(novo_valor_posicao);
								cout << endl << "NOVO VALOR DA POSIÇÃO: " << to_string(novo_valor_posicao) << endl << endl;

								*items = *items +1;
								*items_totais = *items_totais +1;
								cout << endl;
								cout << endl << "------------------------------------------------------------------------------------";
								cout << endl << "------ Andou para posição [" << *linha_atual << "] [" << *coluna_atual << "] -------";
								cout << endl << "------ Pegou um item ------------- Total de itens: [" << *items << "] --------------";
								cout << endl << "------ PONTOS NO TOTAL = [" << *pontos_ganhos << "] ---------------------------------";
								cout << endl << "MOCHILA " << *mochila << endl;
								cout << endl;
								if (*items == 4) {
									//Verifica se ele já tem o máximo de vidas
									if (*vidas == 10) {
										cout << endl << endl << "-> Você coletou 4 items, porém já possui o número máximo de vida!" << endl;
										*items = 0;
									}
									//Recebe uma vida caso não tenha o máximo de vidas
									else {
										*vidas = *vidas+1;
										*items = 0;
										cout << endl << endl << "-> Você coletou 4 items e ganhou uma vida!";
										cout << endl << "Total de vidas: [" << *vidas << "]";
									}
								}
							}
							else {
								cout << endl << endl << "-> Você chegou em uma posição sem perigos, porém não há itens para serem coletados!" << endl;
							}
						}
					} 
				}
				//sudoeste
				else if (possivel_direcao == 6) {
					//Verifica se a posição existe e se não existe uma parede nela
					if ((*linha_atual < MAXROWS-1) && (*coluna_atual > 0) && (mapa_atual[*linha_atual+1][*coluna_atual-1] != "#")) {
						cout << endl << "-> VOU PARA O SUDOESTE" << endl;
						*linha_atual = *linha_atual +1;
						*coluna_atual = *coluna_atual -1;
						proximo_passo = true;
						*casas_percorridas = *casas_percorridas +1;
						//Verifica se a posição têm um perigo
						if (mapa_atual[*linha_atual][*coluna_atual] == "*") {
							*vidas = *vidas -1;
							*perigos_totais = *perigos_totais +1;
							cout << endl << "------------------------------------------------------------------------------------";
							cout << endl << "------ Andou para posição [" << *linha_atual << "] [" << *coluna_atual << "] -------";
							cout << endl << "------ Perdeu uma vida ------------- Total de vidas: [" << *vidas << "] ------------";
							cout << endl << "MOCHILA " << *mochila << endl;
						}
						//Posição tem um numero
						else {
							//Verifica se a posição tem items para serem pegos
							if ((mapa_atual[*linha_atual][*coluna_atual] != "0") && (mapa_atual[*linha_atual][*coluna_atual] != "*")) {
								int novo_valor_posicao;
								*pontos_ganhos = *pontos_ganhos +1;
								*mochila = *mochila +1;

								novo_valor_posicao = stoi(mapa_atual[*linha_atual][*coluna_atual]);
								novo_valor_posicao = novo_valor_posicao -1;

								mapa_atual[*linha_atual][*coluna_atual] = to_string(novo_valor_posicao);
								cout << endl << "NOVO VALOR DA POSIÇÃO: " << to_string(novo_valor_posicao) << endl << endl;

								*items = *items +1;
								*items_totais = *items_totais +1;
								cout << endl;
								cout << endl << "------------------------------------------------------------------------------------";
								cout << endl << "------ Andou para posição [" << *linha_atual << "] [" << *coluna_atual << "] -------";
								cout << endl << "------ Pegou um item ------------- Total de itens: [" << *items << "] --------------";
								cout << endl << "------ PONTOS NO TOTAL = [" << *pontos_ganhos << "] ---------------------------------";
								cout << endl << "MOCHILA " << *mochila << endl;
								cout << endl;
								if (*items == 4) {
									//Verifica se ele já tem o máximo de vidas
									if (*vidas == 10) {
										cout << endl << endl << "-> Você coletou 4 items, porém já possui o número máximo de vida!" << endl;
										*items = 0;
									}
									//Recebe uma vida caso não tenha o máximo de vidas
									else {
										*vidas = *vidas +1;
										*items = 0;
										cout << endl << endl << "-> Você coletou 4 items e ganhou uma vida!";
										cout << endl << "Total de vidas: [" << *vidas << "]";
									}
								}
							}
							else {
								cout << endl << endl << "-> Você chegou em uma posição sem perigos, porém não há itens para serem coletados!" << endl;
							}
						}
					} 
				}
				//oeste
				else if (possivel_direcao == 7) {
					//Verifica se a posição existe e se não existe uma parede nela
					if ((*coluna_atual > 0) && (mapa_atual[*linha_atual][*coluna_atual-1] != "#")) {
						cout << "-> VOU PARA O OESTE" << endl;
						*coluna_atual = *coluna_atual -1;
						proximo_passo = true;
						*casas_percorridas = *casas_percorridas +1;
						//Verifica se a posição têm um perigo
						if (mapa_atual[*linha_atual][*coluna_atual] == "*") {
							*vidas = *vidas -1;
							*perigos_totais = *perigos_totais +1;
							cout << endl << "------------------------------------------------------------------------------------";
							cout << endl << "------ Andou para posição [" << *linha_atual << "] [" << *coluna_atual << "] -------";
							cout << endl << "------ Perdeu uma vida ------------- Total de vidas: [" << *vidas << "] ------------";
							cout << endl << "MOCHILA " << *mochila << endl;
						}
						//Posição tem um numero
						else {
							//Verifica se a posição tem items para serem pegos
							if ((mapa_atual[*linha_atual][*coluna_atual] != "0") && (mapa_atual[*linha_atual][*coluna_atual] != "*")) {
								int novo_valor_posicao;
								*pontos_ganhos = *pontos_ganhos +1;
								*mochila = *mochila +1;

								novo_valor_posicao = stoi(mapa_atual[*linha_atual][*coluna_atual]);
								novo_valor_posicao = novo_valor_posicao -1;

								mapa_atual[*linha_atual][*coluna_atual] = to_string(novo_valor_posicao);
								cout << endl << "NOVO VALOR DA POSIÇÃO: " << to_string(novo_valor_posicao) << endl << endl;

								*items = *items +1;
								*items_totais = *items_totais +1;
								cout << endl;
								cout << endl << "------------------------------------------------------------------------------------";
								cout << endl << "------ Andou para posição [" << *linha_atual << "] [" << *coluna_atual << "] -------";
								cout << endl << "------ Pegou um item ------------- Total de itens: [" << *items << "] --------------";
								cout << endl << "------ PONTOS NO TOTAL = [" << *pontos_ganhos << "] ---------------------------------";
								cout << endl << "MOCHILA " << *mochila << endl;
								cout << endl;
								if (*items == 4) {
									//Verifica se ele já tem o máximo de vidas
									if (*vidas == 10) {
										cout << endl << endl << "-> Você coletou 4 items, porém já possui o número máximo de vida!" << endl;
										*items = 0;
									}
									//Recebe uma vida caso não tenha o máximo de vidas
									else {
										*vidas = *vidas +1;
										*items = 0;
										cout << endl << endl << "-> Você coletou 4 items e ganhou uma vida!";
										cout << endl << "Total de vidas: [" << *vidas << "]";
									}
								}
							}
							else {
								cout << endl << endl << "-> Você chegou em uma posição sem perigos, porém não há itens para serem coletados!" << endl;
							}
						}
					} 
				}
				//noroeste
				else if (possivel_direcao == 8) {
					//Verifica se a posição existe e se não existe uma parede nela
					if ((*linha_atual > 0) && (*coluna_atual > 0) && (mapa_atual[*linha_atual-1][*coluna_atual-1] != "#")) {
						cout << endl << "-> VOU PARA O NOROESTE" << endl;
						*linha_atual = *linha_atual -1;
						*coluna_atual = *coluna_atual -1;
						proximo_passo = true;
						*casas_percorridas = *casas_percorridas +1;
						//Verifica se a posição têm um perigo
						if (mapa_atual[*linha_atual][*coluna_atual] == "*") {
							*vidas = *vidas -1;
							*perigos_totais = *perigos_totais +1;
							cout << endl << "------------------------------------------------------------------------------------";
							cout << endl << "------ Andou para posição [" << *linha_atual << "] [" << *coluna_atual << "] -------";
							cout << endl << "------ Perdeu uma vida ------------- Total de vidas: [" << *vidas << "] ------------";
							cout << endl << "MOCHILA " << *mochila << endl;
						}
						//Posição tem um numero
						else {
							//Verifica se a posição tem items para serem pegos
							if ((mapa_atual[*linha_atual][*coluna_atual] != "0") && (mapa_atual[*linha_atual][*coluna_atual] != "*")) {
								int novo_valor_posicao;
								*pontos_ganhos = *pontos_ganhos +1;
								*mochila = *mochila +1;

								novo_valor_posicao = stoi(mapa_atual[*linha_atual][*coluna_atual]);
								novo_valor_posicao = novo_valor_posicao -1;

								mapa_atual[*linha_atual][*coluna_atual] = to_string(novo_valor_posicao);
								cout << endl << "NOVO VALOR DA POSIÇÃO: " << to_string(novo_valor_posicao) << endl << endl;

								*items = *items +1;
								*items_totais = *items_totais +1;
								cout << endl;
								cout << endl << "------------------------------------------------------------------------------------";
								cout << endl << "------ Andou para posição [" << *linha_atual << "] [" << *coluna_atual << "] -------";
								cout << endl << "------ Pegou um item ------------- Total de itens: [" << *items << "] --------------";
								cout << endl << "------ PONTOS NO TOTAL = [" << *pontos_ganhos << "] ---------------------------------";
								cout << endl << "MOCHILA " << *mochila << endl;
								cout << endl;
								if (*items == 4) {
									//Verifica se ele já tem o máximo de vidas
									if (*vidas == 10) {
										cout << endl << endl << "-> Você coletou 4 items, porém já possui o número máximo de vida!" << endl;
										*items = 0;
									}
									//Recebe uma vida caso não tenha o máximo de vidas
									else {
										*vidas = *vidas +1;
										*items = 0;
										cout << endl << endl << "-> Você coletou 4 items e ganhou uma vida!";
										cout << endl << "Total de vidas: [" << *vidas << "]";
									}
								}
							}
							else {
								cout << endl << endl << "-> Você chegou em uma posição sem perigos, porém não há itens para serem coletados!" << endl;
							}
						}
					} 
				}
			}while(proximo_passo == false);
			//Setar a coordenada que foi passada
			(*posicoes_percorridas)[matriz_atual_posicao].caminho.insert(make_pair(*linha_atual, *coluna_atual));
		}

	//Escrever a matriz atualizada com próximo passo no arquivo
	ofstream arquivo(diretorio);

	for (int i=0; i<MAXROWS; i++) {
		for (int j=0; j<MAXCOLS; j++) {
			arquivo << mapa_atual[i][j] << " ";
		}
		arquivo << endl;
	}

	//Printar o mapa atualizado após mudanças de coleta de item
	cout << endl << endl << "-------------- MAPA ATUALIZADO ------------" << endl;
	for (int i=0; i<linhas; i++) {
			for (int j=0; j<colunas; j++) {
				cout << mapa_atual[i][j] << " ";
			}
			cout << endl;
		}

	}
	
	//Caso o arquivo não abra corretamente ele apresenta erro
	else {
		cout << endl << "erro na abertura do arquivo!" << endl;
	}
	cout << endl << endl << "==============================================================================================================================" << endl << endl;
}

//Fazer os calculos das casas percorridas e não percorridas
void SetarCaminhos(vector<CaminhoPercorrido> *casas_percorridas) {
	int total_de_posicoes=0;
	int posicoes_percorridas=0;
	int casas_nao_exploradas=0;

	total_de_posicoes = NUMAT*(MAXCOLS*MAXROWS);

	for (int i=0; i<(*casas_percorridas).size(); i++) {
		posicoes_percorridas += (*casas_percorridas)[i].caminho.size();
	}

	casas_nao_exploradas = total_de_posicoes - posicoes_percorridas;
	cout << endl << "-> O JOGO POSSUÍA " << total_de_posicoes << " POSIÇÕES EM TODAS AS SUAS MATRIZES" << endl;
	cout << endl << "-> O PERSONAGEM VISITOU " << posicoes_percorridas << " POSIÇÕES AO LONGO DE SUA AVENTURA" << endl;
	cout << endl << "-> O PERSONAGEM DEIXOU DE VISITAR " << casas_nao_exploradas << " POSIÇÕES AO LONGO DE TODA SUA AVENTURA!" << endl << endl;
}
