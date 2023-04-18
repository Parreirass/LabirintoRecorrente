#ifndef LABIRINTO_HPP 
#define LABIRINTO_HPP

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>

using namespace std;

#define MAXCOLS 4
#define MAXROWS 4
#define NUMAT   2

typedef struct Item{
	char val;
}Item;

typedef struct Matrix{
	Item m[MAXROWS][MAXCOLS];
}Matrix;

typedef struct CaminhoPercorrido {
	string nomeArquivo;
	set <pair<int, int>> caminho;
}CaminhoPercorrido;

void GenerateMatrix(Matrix *mat);
void SetMatrixSignature();
void SaveMatrix(Matrix *mat);

void LerMatriz(string matriz_atual[MAXROWS][MAXCOLS], int linhas, int colunas, fstream &arquivo);
void EscreverMatriz(string matriz_atual[MAXROWS][MAXCOLS], int *numero_mapa, int *pontos_totais, vector<CaminhoPercorrido>*posicoes_percorridas);
void PercorrerMatriz(string mapa_atual[MAXROWS][MAXCOLS], int linhas, int colunas, int *vidas, int *pontos_ganhos, int *pontos_totais, int *fase, bool *possivel, int *linha_atual, int *coluna_atual, int *items, int *items_totais, int *perigos_totais, int *casas_percorridas, bool *vitoria, int *mochila, vector<CaminhoPercorrido>*posicoes_percorridas);
void SetarCaminhos(vector<CaminhoPercorrido> *casas_percorridas);

#endif