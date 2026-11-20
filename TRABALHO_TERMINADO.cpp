#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//////////////// Processsos de alocacao de memorias
int* alocacao(int tamanho, int min, int max){
int i=0;
// Aloca memória dinamicamente para o vetor
    int* vetor = (int*)malloc(tamanho * sizeof(int));
   
    // Verifica se a alocação foi bem-sucedida
    if (vetor == NULL) {
        printf("Erro de alocação de memória.\n");
        return NULL;
    }

    for ( i; i < tamanho; i++) {
        // Gera um número aleatório no intervalo [minimo, maximo]
        vetor[i] = min + rand() % (max - min + 1);
    }

    return vetor;
}

int* fazer_copia(int tamanho, int* vetor) {
    int* copia = (int*)malloc(tamanho * sizeof(int));
   
    if (copia == NULL) {
        printf("Erro de alocação de memória na cópia.\n");
        return NULL;
    }
   
    for (int i = 0; i < tamanho; i++) {
        copia[i] = vetor[i];
    }
    return copia;
}
//////////////// Processsos de alocacao de memorias

//////////////// Algoritmo automatizacao das chamadas de funcoes e saida de dados
// Recebe a função de ordenação, o vetor cópia, o tamanho e o nome do algoritmo
void exibicao(void (*algoritmo)(int*, int), int* vetor, int tamanho, const char* nome_algoritmo) {
    clock_t inicio, fim;
    double tempo_gasto;
    
    // 1. Marca o início e roda o algoritmo passado por parâmetro
    inicio = clock();
    algoritmo(vetor, tamanho);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000;
    printf("Tempo de ordenacao %s: %f milissegundos\n\n", nome_algoritmo, tempo_gasto);
    
    // 4. Libera a memória da cópia usada
    free(vetor);
}


//////////////// Processsos de ordenacao baseados em comparaçao
void bubbleSort(int* vetor, int tamanho) {
    int i, j, temp;
   
    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}
void insertSort(int* vetor, int tamanho){
   int i, j, aux;
    for (j = 1; j < tamanho; j++) {
        aux = vetor[j];
        i = j - 1;
       
        while (i >= 0 && vetor[i] > aux) {
            vetor[i + 1] = vetor[i];
            i = i - 1;
        }
        vetor[i + 1] = aux;
    }
}

void selectionSort(int* vetor, int tamanho){
int i, j, min_idx, aux;
   
    // Percorre todo o vetor até o penúltimo elemento
    for (i = 0; i < tamanho - 1; i++) {
        min_idx = i; // Assume que o atual é o menor
       
        // Procura o menor elemento na parte restante do vetor
        for (j = i + 1; j < tamanho; j++) {
            if (vetor[j] < vetor[min_idx]) {
                min_idx = j; // Atualiza o índice do menor valor encontrado
            }
        }
       
        // Realiza a troca se encontrar um valor menor
        if (min_idx != i) {
            aux = vetor[i];
            vetor[i] = vetor[min_idx];
            vetor[min_idx] = aux;
        }
    }
}
void mergeSort(int* vetor, int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        
        // Chamadas recursivas dividindo o vetor
        mergeSort(vetor, esq, meio);
        mergeSort(vetor, meio + 1, dir);
        
        // --- INÍCIO DA LÓGICA DE MESCLAGEM (INLINE) ---
        int i, j, k;
        int n1 = meio - esq + 1;
        int n2 = dir - meio;
        
        int* L = (int*)malloc(n1 * sizeof(int));
        int* R = (int*)malloc(n2 * sizeof(int));
        
        for (i = 0; i < n1; i++) L[i] = vetor[esq + i];
        for (j = 0; j < n2; j++) R[j] = vetor[meio + 1 + j];
            
        i = 0; 
        j = 0; 
        k = esq; 
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                vetor[k] = L[i];
                i++;
            } else {
                vetor[k] = R[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) {
            vetor[k] = L[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            vetor[k] = R[j];
            j++;
            k++;
        }
        
        free(L);
        free(R);
        // --- FIM DA LÓGICA DE MESCLAGEM ---
    }
}

// 2. adaptador para o Merge Sort
void adaptadorMergeSort(int* vetor, int tamanho) {
    if (tamanho > 0) {
        mergeSort(vetor, 0, tamanho - 1); // ou mergeSortUnico
    }
}


void quickSort(int* vetor, int baixo, int alto) {
    if (baixo < alto) {
        // --- INÍCIO DA LÓGICA DE PARTIÇÃO (INLINE) ---
        int pivo = vetor[alto];
        int i = (baixo - 1);
        int j, temp;

        for (j = baixo; j < alto; j++) {
            if (vetor[j] <= pivo) {
                i++;
                // Troca
                temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
            }
        }
        // Coloca o pivô no lugar
        temp = vetor[i + 1];
        vetor[i + 1] = vetor[alto];
        vetor[alto] = temp;
        
        int pi = i + 1; // Índice final do pivô
        // --- FIM DA LÓGICA DE PARTIÇÃO ---

        // Chamadas recursivas para a esquerda e para a direita do pivô
        quickSort(vetor, baixo, pi - 1);
        quickSort(vetor, pi + 1, alto);
    }
}
// Adaptador para o Quick Sort funcionar na rotina universal de exibicao
void adaptadorQuickSort(int* vetor, int tamanho) {
    if (tamanho > 0) {
        // Chama a sua função passando 0 como 'baixo' e tamanho-1 como 'alto'
        quickSort(vetor, 0, tamanho - 1);
    }
}
/////////// Algoritmo Heap Sort (duas funções)

// 1. Função auxiliar que organiza a "árvore" (Max-Heap)
void heapify(int* vetor, int tamanho, int i) {
    int maior = i;           // Inicializa a raiz como o maior
    int esq = 2 * i + 1;     // Filho da esquerda
    int dir = 2 * i + 2;     // Filho da direita
    int temp;

    // Se o filho da esquerda for maior que a raiz
    if (esq < tamanho && vetor[esq] > vetor[maior]) {
        maior = esq;
    }

    // Se o filho da direita for maior que o "maior" atual
    if (dir < tamanho && vetor[dir] > vetor[maior]) {
        maior = dir;
    }

    // Se o maior número não for a raiz, fazemos a troca
    if (maior != i) {
        temp = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = temp;

        // Chama recursivamente para a sub-árvore afetada
        heapify(vetor, tamanho, maior);
    }
}

// 2. Função principal para manter o padrão void(vetor, tamanho)
void heapSort(int* vetor, int tamanho) {
    int i, temp;

    // Constrói a Max-Heap (reorganiza o vetor inteiro como uma árvore)
    for (i = tamanho / 2 - 1; i >= 0; i--) {
        heapify(vetor, tamanho, i);
    }

    // Extrai os elementos um por um da árvore
    for (i = tamanho - 1; i > 0; i--) {
        // Move a raiz atual (o maior número) para o fim do vetor
        temp = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = temp;

        // Chama o heapify na árvore reduzida para encontrar o novo maior
        heapify(vetor, i, 0);
    }
}
/////////// Algoritmo Counting Sort
void countingSort(int* vetor, int tamanho) {
    // Se o vetor tiver 1 ou 0 elementos, já está ordenado
    if (tamanho <= 1) return; 

    int i;
    int max = vetor[0];
    int min = vetor[0];

    // 1. Encontra o maior e o menor elemento no vetor original
    for (i = 1; i < tamanho; i++) {
        if (vetor[i] > max) max = vetor[i];
        if (vetor[i] < min) min = vetor[i];
    }

    // A amplitude do intervalo (ex: de 0 a 1.000.000, temos 1.000.001 números possíveis)
    int amplitude = max - min + 1;

    // 2. Aloca os vetores auxiliares
    // Utilizamos calloc no 'contagem' pois ele já cria o vetor preenchido com ZEROs
    int* contagem = (int*)calloc(amplitude, sizeof(int));
    int* saida = (int*)malloc(tamanho * sizeof(int));

    // Proteção caso falte memória RAM (muito raro, mas é uma boa prática)
    if (contagem == NULL || saida == NULL) {
        printf("Erro de alocacao de memoria no Counting Sort.\n");
        if (contagem) free(contagem);
        if (saida) free(saida);
        return;
    }

    // 3. Conta as ocorrências de cada número 
    // O "- min" é o deslocamento para que o menor número sempre caia no índice 0
    for (i = 0; i < tamanho; i++) {
        contagem[vetor[i] - min]++;
    }

    // 4. Transforma a contagem em posições acumuladas
    for (i = 1; i < amplitude; i++) {
        contagem[i] += contagem[i - 1];
    }

    // 5. Constrói o vetor ordenado (varrendo de trás para frente para manter estabilidade)
    for (i = tamanho - 1; i >= 0; i--) {
        saida[contagem[vetor[i] - min] - 1] = vetor[i];
        contagem[vetor[i] - min]--;
    }

    // 6. Copia os elementos ordenados de volta para o vetor original
    for (i = 0; i < tamanho; i++) {
        vetor[i] = saida[i];
    }

    // 7. Libera a memória extra que foi usada
    free(contagem);
    free(saida);
}
/////////// Fim Counting Sort

/////////// Algoritmo Radix Sort

// 1. Função auxiliar: Um mini-Counting Sort focado apenas em uma casa decimal (0 a 9)
void countingSortParaRadix(int* vetor, int tamanho, int exp) {
    int* saida = (int*)malloc(tamanho * sizeof(int));
    int contagem[10] = {0}; // Só precisamos de 10 posições (dígitos de 0 a 9)
    int i;

    // Conta a ocorrência do dígito atual (unidade, dezena, etc)
    for (i = 0; i < tamanho; i++) {
        contagem[(vetor[i] / exp) % 10]++;
    }

    // Calcula as posições acumuladas
    for (i = 1; i < 10; i++) {
        contagem[i] += contagem[i - 1];
    }

    // Constrói o vetor de saída de trás para frente (mantendo a estabilidade)
    for (i = tamanho - 1; i >= 0; i--) {
        saida[contagem[(vetor[i] / exp) % 10] - 1] = vetor[i];
        contagem[(vetor[i] / exp) % 10]--;
    }

    // Copia para o vetor original
    for (i = 0; i < tamanho; i++) {
        vetor[i] = saida[i];
    }
    
    free(saida);
}

// 2. Função principal do Radix Sort (Esta vai para a rotina de exibição)
void radixSort(int* vetor, int tamanho) {
    if (tamanho <= 1) return;

    int i;
    int min = vetor[0];
    int max = vetor[0];

    // Descobre o menor e o maior número
    for (i = 1; i < tamanho; i++) {
        if (vetor[i] < min) min = vetor[i];
        if (vetor[i] > max) max = vetor[i];
    }

    // Se houver números negativos, desloca todo o vetor para a zona positiva
    if (min < 0) {
        for (i = 0; i < tamanho; i++) vetor[i] -= min;
        max -= min; // O máximo também é deslocado
    }

    // O "exp" define a casa decimal: 1 (unidade), 10 (dezena), 100 (centena)...
    // O laço roda até processar o maior número inteiro
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSortParaRadix(vetor, tamanho, exp);
    }

    // Se deslocamos os números no início, voltamos eles para o valor negativo original
    if (min < 0) {
        for (i = 0; i < tamanho; i++) vetor[i] += min;
    }
}
/////////// Fim Radix Sort

/////////// Algoritmo Bucket Sort

// 1. Estrutura para representar cada Balde
typedef struct {
    int qtd;           // Quantidade atual de elementos no balde
    int capacidade;    // Capacidade máxima de memória alocada
    int* valores;      // Vetor dinâmico que guarda os números
} Balde;

// 2. O Bucket Sort tradicional usa o Insertion Sort para ordenar dentro de cada balde
void insertionSortParaBalde(int* vetor, int tamanho) {
    int i, j, aux;
    for (i = 1; i < tamanho; i++) {
        aux = vetor[i];
        j = i - 1;
        while (j >= 0 && vetor[j] > aux) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = aux;
    }
}

// 3. Função principal do Bucket Sort
void bucketSort(int* vetor, int tamanho) {
    if (tamanho <= 1) return;

    int i, j, k;
    int min = vetor[0], max = vetor[0];

    // Encontra o maior e o menor valor para descobrir o intervalo
    for (i = 1; i < tamanho; i++) {
        if (vetor[i] < min) min = vetor[i];
        if (vetor[i] > max) max = vetor[i];
    }

    // Proteção: Se todos os números forem iguais, já está ordenado
    if (min == max) return; 

    // Define a quantidade de baldes (100 costuma ser um ótimo equilíbrio para memória RAM)
    int num_baldes = 100; 
    Balde* baldes = (Balde*)malloc(num_baldes * sizeof(Balde));

    // Inicializa os baldes com uma capacidade inicial pequena
    for (i = 0; i < num_baldes; i++) {
        baldes[i].qtd = 0;
        baldes[i].capacidade = 32; 
        baldes[i].valores = (int*)malloc(baldes[i].capacidade * sizeof(int));
    }

    // Distribui os elementos do vetor original nos respectivos baldes
    for (i = 0; i < tamanho; i++) {
        // Regra de três simples para descobrir em qual balde o número cai
        // O (long long) protege contra estouro de limite na multiplicação de números gigantes
        int indice = (int)(((long long)(vetor[i] - min) * (num_baldes - 1)) / (max - min));

        // Se o balde encher, o realloc dobra a capacidade dele automaticamente
        if (baldes[indice].qtd == baldes[indice].capacidade) {
            baldes[indice].capacidade *= 2;
            baldes[indice].valores = (int*)realloc(baldes[indice].valores, baldes[indice].capacidade * sizeof(int));
        }
        
        baldes[indice].valores[baldes[indice].qtd] = vetor[i];
        baldes[indice].qtd++;
    }

    // Ordena cada balde individualmente e devolve os números para o vetor original
    k = 0;
    for (i = 0; i < num_baldes; i++) {
        if (baldes[i].qtd > 0) {
            // Ordena o balde atual
            insertionSortParaBalde(baldes[i].valores, baldes[i].qtd);
            
            // Copia de volta para o vetor principal
            for (j = 0; j < baldes[i].qtd; j++) {
                vetor[k] = baldes[i].valores[j];
                k++;
            }
        }
        // Libera a memória do balde atual logo após usá-lo para poupar RAM
        free(baldes[i].valores);
    }
    
    // Libera o vetor de estruturas de baldes
    free(baldes);
}
/////////// Fim Bucket Sort

int main(){
srand(time(NULL)); /////permite que se eu rodar o progama dnv nao gere os mesmos numeros aleatorios
///// Variáveis para armazenar o tempo
    clock_t inicio, fim;
    double tempo_gasto;
    //////
int tamanho,min,max;
int i=0;

srand(time(NULL));

printf("quantos numeros aletórios deseja:");
scanf("%i", &tamanho);

printf("defina os valores min:\n");
scanf("%i", &min);
printf("defina os valores max:\n");
scanf("%i", &max);

int* vetor_original= alocacao(tamanho,min,max);

if (vetor_original != NULL) {
 
 ////////////////INICIO BUBBLESORT
        int* copia_bubble=fazer_copia(tamanho, vetor_original);
        if (copia_bubble != NULL) {
        exibicao(bubbleSort, copia_bubble, tamanho, "Bubble Sort");
}
////////////////FIM BUBBLESORT

////////////////INICIO INSERT
 int* copia_insert=fazer_copia(tamanho, vetor_original);
        if (copia_insert != NULL) {
        exibicao(insertSort, copia_insert, tamanho, "Insert Sort");
}
////////////////FIM INSERT

////////////////INICIO SELECTION
  int* copia_selection=fazer_copia(tamanho, vetor_original);
  if(copia_selection!=NULL){
  	exibicao(selectionSort, copia_selection, tamanho, "Selection Sort");
  }


	////////////////INICIO MERGE
	 int* copia_merge = fazer_copia(tamanho, vetor_original);
        if (copia_merge != NULL) exibicao(adaptadorMergeSort, copia_merge, tamanho, "Merge Sort");
    ////////////////FIM MERGE

////////////////INICIO QUICK
	 // Teste do Quick Sort
	 
    int* copia_quick = fazer_copia(tamanho, vetor_original);
    if (copia_quick != NULL) {
        exibicao(adaptadorQuickSort, copia_quick, tamanho, "Quick Sort");
    }
        ////////////////FIM QUICK

    ////////////////INICIO HEAP
    	 int* copia_heap=fazer_copia(tamanho, vetor_original);
    	  if(copia_selection!=NULL){
  	exibicao(heapSort, copia_heap, tamanho, "Heap Sort");
  }
    ////////////////FIM QUICK
    
    ////////////////INICIO COUNTING
        int* copia_counting = fazer_copia(tamanho, vetor_original);
        if (copia_counting != NULL) {
            exibicao(countingSort, copia_counting, tamanho, "Counting Sort");
        }
    ////////////////FIM COUNTING
}
////////////////INICIO RADIX LSD
// Teste do Radix Sort
        int* copia_radix = fazer_copia(tamanho, vetor_original);
        if (copia_radix != NULL) {
            exibicao(radixSort, copia_radix, tamanho, "Radix Sort");
        }
////////////////FIM RADIX LSD

////////////////INICIO BUCKET
// Teste do Bucket Sort
        int* copia_bucket = fazer_copia(tamanho, vetor_original);
        if (copia_bucket != NULL) {
            exibicao(bucketSort, copia_bucket, tamanho, "Bucket Sort");
        }
    ////////////////FIM BUCKET
     ////liberacao da memoria do vetor original
        free(vetor_original);
        return 0;
}

