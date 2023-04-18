#include "labirinto.hpp"

int main ()
{
    int number_of_matrix = 5;
	int linhas = MAXROWS;
	int colunas = MAXCOLS;
	string matriz_atual[MAXROWS][MAXCOLS];
	FILE *f;
	int numero_matriz = 1;
	int soma_total_matrizes = 0;
	int numero_mapa = 1;
	int pontos_totais = 0;
	int vidas = 10;
	int fase = 1;
	bool possivel = false;
	int pontos_ganhos = 0;
	int items = 0;
	int linha_atual = 0, coluna_atual = 0;
	int items_totais = 0;
	int perigos_totais = 0;
	string mapa_atual[MAXROWS][MAXCOLS];
	int pergunta = 0;
	int casas_percorridas = 0;
	bool vitoria = false;
	int mochila = 0;

	srand((unsigned)time(NULL));

	//Matrix m;
	vector<CaminhoPercorrido> posicoes_percorridas;

    /*SetMatrixSignature();
	for(int i=0; i<NUMAT; i++)
		SaveMatrix(&m);*/

	fstream arquivo("dataset/input.data");
	//Ler matrizes e fazer "checkpoints" em arquivos separados
	for (int i=0; i<NUMAT; i++) {
    	LerMatriz(matriz_atual, linhas, colunas, arquivo);
		EscreverMatriz(matriz_atual, &numero_mapa, &pontos_totais, &posicoes_percorridas);
	}
	
	do {
		//Todo processo de andar
		PercorrerMatriz(mapa_atual, linhas, colunas, &vidas, &pontos_ganhos, &pontos_totais, &fase, &possivel, &linha_atual, &coluna_atual, &items, &items_totais, &perigos_totais, &casas_percorridas, &vitoria, &mochila, &posicoes_percorridas);
		if (vitoria == true) {
			cout << endl << "----------------------------------------------- VICTORY -----------------------------------------------" << endl;
			cout << endl << "-> ATENÇÃO: O PERSONAGEM DEU UMA VOLTA COMPLETA POR TODOS OS MAPAS SEM PEGAR NENHUM ITEM E GANHOU O JOGO!" << endl;
			cout << endl << "-> O JOGO POSSUÍA " << pontos_totais << " ITENS PARA SEREM CONQUISTADOS! " << endl;
			cout << endl << "-> O PERSONAGEM GANHOU O JOGO CONQUISTANDO " << pontos_ganhos << " PONTOS (ITENS) DURANTE O JOGO!" << endl;
			cout << endl << "-> O PERSONAGEM ANDOU POR " << casas_percorridas << " VEZES DURANTE O JOGO, DENTRE CASAS COM PERIGOS E ITENS" << endl;
			cout << endl << "-> O PERSONAGEM ENFRENTOU PERIGOS " << perigos_totais << " VEZES DURANTE TODO O JOGO" << endl;
			pergunta = 1;
			break;
		}
		if (vidas == 0) {
			cout << endl << "----------------------------------------------- GAME OVER -----------------------------------------------" << endl;
			cout << endl << "-> ATENÇÃO: O PERSONAGEM PERDEU TODAS AS VIDAS E MORREU!" << endl;
			cout << endl << "-> O JOGO POSSUÍA " << pontos_totais << " ITENS PARA SEREM CONQUISTADOS! " << endl;
			cout << endl << "-> O PERSONAGEM PERDEU O JOGO CONQUISTANDO " << pontos_ganhos << " PONTOS (ITENS) DURANTE O JOGO!" << endl;
			cout << endl << "-> O PERSONAGEM ANDOU POR " << casas_percorridas << " VEZES DURANTE O JOGO, DENTRE PERIGOS E ITENS" << endl;
			cout << endl << "-> O PERSONAGEM ENFRENTOU PERIGOS " << perigos_totais << " VEZES DURANTE TODO O JOGO" << endl;
			pergunta = 1;
			break;
		}
	} while (pergunta == 0);

	//Função responsável por verificar posições que foram buscadas pelo personagem
	SetarCaminhos(&posicoes_percorridas);
}