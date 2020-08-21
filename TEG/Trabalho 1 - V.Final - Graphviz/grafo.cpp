#include "grafo.hpp"

// Construtor
Grafo::Grafo(int numVertices) {
    this->numVertices = numVertices;
    for(int i = 0; i < numVertices; i++) {
        listaAdjacencia.push_back(vector < pair<int, float>> ());
    }
}

// Função para descobrir os vizinhos de cada vértice: K pontos mais próximos
int calcularLog(int numVer) {
    int k;
    if (numVer == 0) {
        return 1;
    }
    k = log2(numVer);
    return k;
}

// Função para descobrir o peso de uma aresta entre dois pontos pela fórmula: sqrt((x – z)^2 + (y – w)^2)
float distanciaPontos(float x, float y, float z, float w) {
    float p1 = x - z;
    float p2 = y - w;
    p1 = p1*p1;
    p2 = p2*p2;
    float s = p1 + p2;
    return sqrt(s);
}


// Função para gerar números aleatórios entre 0 e 1
void gerarCoordenadasAleatorias(int numVertices, vector <pair <float, float>> &coordenadas) {
    float x, y;
    for (int i = 0; i < numVertices; i++) {
        x = 0 + 1.0*((float)(rand())/RAND_MAX);
        y = 0 + 1.0*((float)(rand())/RAND_MAX);
        pair <float, float> coordaux (x,y);
        coordenadas.push_back(coordaux); // colocar as coordenadas no fim do vetor
        printf("(%d)\n X: %.5f  Y: %.5f\n", i, coordaux.first, coordaux.second);
    }    
}

// Funções para ligar os vértices com seus respectivos vizinhos.
// ---------------------------------------------------------------

// Função para ligar os vértices que são vizinhos.
void Grafo::ligarVizinhos(int numVer, vector<pair<float, float>> &coord) {
    int quantidadeVizinhos = calcularLog(numVer); // calcular número de vizinhos de acordo com tamanho do grafo.
    int vizinhosIndice[quantidadeVizinhos]; 
    float vizinhosCoordenadas[quantidadeVizinhos];
    vector <pair <int, int>> indiceCoordenada; // vetor de pares (vertice: 2, vertice: 3), ou seja, 2 e 3 possuem uma ligação.
    for (int i = 0; i < numVer; i++) {
        descobrirVerticesProximos (coord, vizinhosIndice, vizinhosCoordenadas, i, quantidadeVizinhos); // descobrir quais são os vizinhos de acordo com a quantidade obtida pelo log2n.
        for (int j = 0; j < quantidadeVizinhos; j++) {
            pair <int, int> controleAresta (i, vizinhosIndice[j]); // par (vértice, seu vizinho)
            if (verificarIndiceIgual(indiceCoordenada, i, vizinhosIndice[j]) && i != vizinhosIndice[j]) { // um vértice não se compara com ele mesmo
                indiceCoordenada.push_back(controleAresta); // armazena no vetor de indices de coordenadas, ou seja, vértices que possuem ligação fazem um par no vetor.
            }
        }
    }
    adicionarArestas(coord, indiceCoordenada); // Aresta é adicionada no grafo
    // definindo arquivo de saída pro graphviz
    ofstream out("out.txt");
    // Printar o grafo de acordo com número de vértices, vetor de coordenadas e lista de adjacencia.
    for (int i = 0; i < numVertices; i++) {
        int total = 0;
        printf ("\n-------------------------------------------------\n");
        printf("\nVertice (%d) que possui as coordenadas (%.3f ,%.3f): \n", i, coord[i].first, coord[i].second);
        printf("\n");
        out<<i<<" ";
        printf ("Conjunto de arestas que o vértice possui conexão: \n");
        for (int j = 0; j < listaAdjacencia[i].size(); j++) { // percorre a lista de adjacência de determinado vértice.
            // Exemplo: Vertice 1 -> {(0, 0.5),(5, 0.6),(23, 0.9)}, sendo o primeiro termo o vertice que faz ligação com o vertice 1, e o segundo o peso.
            int primeiro = listaAdjacencia[i][j].first; // pega os vértices da lista de adjacência de determinado vértice para printar a ligação (aresta) pela correspondência a coordenada (float, float)
            for (int k = 0; k < coord.size(); k++) { // varre o vetor das coordenadas (float, float) para comparar com o vértice da lista de adjacência
                if(coord[k].first == coord[primeiro].first && coord[k].second == coord[primeiro].second) { // Compara x = x e y = y
                    printf("Aresta com o vertice (%d): (%.3f, %.3f) -> Peso: %.3f\n", k, coord[primeiro].first, coord[primeiro].second, listaAdjacencia[i][j].second);
                    out<<k<<" ";
                    total++;
                }
            }
        } 
        out << endl;
        printf("\nTotal de arestas ligadas ao vertice: %d\n", total);
    }
    // fechei o arquivo.
    out.close();
}

// Função auxiliar para verificar se os índices do par de vértices não são iguais.
bool verificarIndiceIgual(vector <pair <int, int>> indiceCoordenada, int first, int second) {
    for (int i = 0; i < indiceCoordenada.size(); i++) {
        if(indiceCoordenada[i].first == first && indiceCoordenada[i].second == second || indiceCoordenada[i].first == second && indiceCoordenada[i].second == first) {
            return false;
        }
    }
    return true;
}

// Função para descobrir os K vértices mais próximos pelo log2n.
void Grafo::descobrirVerticesProximos (vector <pair<float, float>> coordenada, int *vizinhosIndice, float *vizinhosCoordenadas, int vertice, int quantidadeVizinhos) {
    float auxiliar[numVertices];
    float auxiliar_2[numVertices];
    for (int i = 0; i < numVertices; i++) {
        if(vertice != i) { // Controle para não identificar o mesmo vértice.
            auxiliar[i] = distanciaPontos(coordenada[vertice].first, coordenada[vertice].second, coordenada[i].first, coordenada[i].second); 
        }
        for (int i = 0; i < numVertices; i++) {
            auxiliar_2[i] = auxiliar[i];
        }
        // ordenar pesos das arestas para fazer a equivalência com as coordenadas dos vizinhos mais próximos.
        ordenarPesos (auxiliar_2);
        for (int i = 0; i < quantidadeVizinhos; i++) {
            vizinhosCoordenadas[i] = auxiliar_2[i];
            for (int j = 0; j < numVertices; j++) {
                if(auxiliar[j] == auxiliar_2[i]) {
                    vizinhosIndice[i] = j; // armazenando em um vetor quais o índice dos vértices que são os K mais próximos.
                }
            }
        }
    }
}

// Ordenar o vetor que contêm os pesos em ordem crescente para determinar o indice dos vértices vizinhos e controlar o peso das arestas.
void Grafo::ordenarPesos (float *auxiliar_2) {
    for (int i = 0; i < numVertices; i++) {
        for (int j = i+1; j < numVertices; j++) {
            if (auxiliar_2[i] > auxiliar_2[j]) {
                float aux_aux = auxiliar_2[i];
                auxiliar_2[i] = auxiliar_2[j];
                auxiliar_2[j] = aux_aux;
            }
        }
    }
}

// Função para atribuir peso as respectivas arestas pelo calculo da distancia entre dois pontos.
// E tambem adicionar determinados vértices (com ligação por uma aresta), com seu respectivo peso, em uma lista de adjacencia.
// Exemplo: Vertice 1 -> {(0, 0.5),(5, 0.6),(23, 0.9)}, sendo o primeiro termo o vertice que faz ligação com o vertice 1, e o segundo o peso.
void Grafo::adicionarArestas (vector <pair<float, float>> coordenada, vector <pair <int, int>> indiceCoordenada) {
    float x, y, z, w, peso;
    for (int i = 0; i < indiceCoordenada.size(); i++) {
        x = coordenada[indiceCoordenada[i].first].first;
        y = coordenada[indiceCoordenada[i].first].second;
        z = coordenada[indiceCoordenada[i].second].first;
        w = coordenada[indiceCoordenada[i].second].second;
        peso = distanciaPontos(x, y, z, w); // calculando o peso entre duas arestas.
        pair <int, float> vertice_1 (indiceCoordenada[i].second, peso);
        pair <int, float> vertice_2 (indiceCoordenada[i].first, peso);
        listaAdjacencia[indiceCoordenada[i].first].push_back (vertice_1);  // Adicionando arestas
        listaAdjacencia[indiceCoordenada[i].second].push_back (vertice_2);  // Adicionando arestas
    }
}


// ---------------------------------------------------------------


// DFS
void Grafo::buscaemProfundidade() {
    cout << "\n-------------------------------------------------\n";
    cout << "\nBusca em Profundidade - DFS\n";
    cout << "\n-------------------------------------------------\n";
    int raiz = rand() % numVertices;
    stack<int> pilha;
    int visitado[numVertices];
    int j = 0;
    int achou;
    // definindo arquivo de saída pro graphviz
    ofstream out("arquivo.txt");
    printf("\nRaíz aleatória: %d\n", raiz);
    printf("\nÁrvore de profundidade [vertices]:\n\n");
    // 0 = não visitado; 1 = visitado.
    // Primeiramente, marco todos os vértices de visitados como 0 pois nenhum foi visitado.
    for (int i = 0; i < numVertices; i++) {
        visitado[i] = 0;
    }
    while(1) {
        // Se o vértice analisado não tiver sido visitado ainda:
        if (!visitado[raiz]) {
            // Defino sua posição no vetor de visitados como 1, informando que ele foi visitado.
            visitado[raiz] = 1;
            // a saída vai ser o vertice analisado no momento
            int saida = raiz;
            // escrevendo no arquivo para o dfs
            //out << saida << endl;
            // Empilho o vértice analisado na pilha.
            pilha.push(raiz);
            printf("[%d] -> ", raiz);
            out<<raiz<<endl;
        }
        achou = 0;
        // Percorrer a lista de adjacencia do vértice a ser analisado.
        for (j = 0; j < listaAdjacencia[raiz].size(); j++) {
            // se o vértice que faz ligação com o vértice analisado(raiz) não foi visitado ainda, ele é visitado e definido uma variável para informar isso.
            if (!visitado[listaAdjacencia[raiz][j].first]) {
                achou = 1;
                break;
            }
        }
        // Após visitar o vértice adjacente ao mesmo analisado, a nova raíz será esse mesmo vértice adjacente, de acordo com a sua posição j.
        if (achou) {
            raiz = listaAdjacencia[raiz][j].first;
        }
        // Caso o vértice que faz ligação com o vértice analisado já tiver sido visitado, o primeiro elemento da pilha é desempilhado, e a nova raíz é o novo primeiro elemento da pilha.
        else {
            pilha.pop();
            if (pilha.empty()) {
                break;
            }
            raiz = pilha.top();
            out<<raiz<< " ";

        }
    } 
    // fechei o arquivo.
    out.close();
}