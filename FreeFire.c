#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Novato
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Nível: Mestre

#define MAX_ITENS 10
#define TAM_NOME 30
@@ -16,28 +15,94 @@ typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
    int prioridade; // de 1 a 5

} Item;

//Enumerador para a ordenação
typedef enum {
    ORDENADO_NENHUM,
    ORDENADO_NOME,
    ORDENADO_TIPO,
    ORDENADO_PRIORIDADE
} CriterioOrdenacao;

//Variável Global
Item mochila[MAX_ITENS];
int totalItens = 0;
CriterioOrdenacao estadoOrdenacao = ORDENADO_NENHUM;

// Função de ordenação por Insertion Sort
int ordenarMochila(CriterioOrdenacao criterio) {
    int comparacoes = 0;
    for (int i = 1; i < totalItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            bool condicao;
            comparacoes++;

            if (criterio == ORDENADO_NOME)
                condicao = strcmp(mochila[j].nome, chave.nome) > 0;
            else if (criterio == ORDENADO_TIPO)
                condicao = strcmp(mochila[j].tipo, chave.tipo) > 0;
            else
                condicao = mochila[j].prioridade > chave.prioridade;

            if (!condicao) break;

            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }

    estadoOrdenacao = criterio;
    return comparacoes;
}

// Busca binária por nome
int buscaBinariaPorNome(char nomeBuscado[]) {
    if (estadoOrdenacao != ORDENADO_NOME) {
        printf("A mochila precisa estar ordenada por nome para realizar a busca binaria.\n");
        return -1;
    }

    int inicio = 0, fim = totalItens - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(mochila[meio].nome, nomeBuscado);

        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }

    return -1;
}

// Função para efetuar limpeza do buffer
void limparBufferEntrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    do {
        printf("\n==== MOCHILA ====\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item por nome\n");
        printf("4. Buscar item por nome (sequencial)\n");
        printf("5. Ordenar mochila\n");
        printf("6. Buscar item por nome (binária)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        limparBufferEntrada(); // Limpa o buffer do teclado

        switch (opcao) {
@@ -57,71 +122,107 @@ int main() {
                    scanf("%d", &mochila[totalItens].quantidade);
                    limparBufferEntrada(); // Limpa o buffer

                    printf("Prioridade (1 a 5): ");
                    scanf("%d", &mochila[totalItens].prioridade);
                    limparBufferEntrada(); // Limpa o buffer

                    totalItens++;
                    estadoOrdenacao = ORDENADO_NENHUM;
                    printf("Item adicionado com sucesso!\n");
                }
                break;

            case 2: {
                char nomeRemover[TAM_NOME];
                int encontrado = 0;

                printf("Digite o nome do item a remover: ");
                printf("Nome do item a remover: ");
                fgets(nomeRemover, TAM_NOME, stdin);
                nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

                bool encontrado = false;
                for (int i = 0; i < totalItens; i++) {
                    if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                        for (int j = i; j < totalItens - 1; j++) {
                            mochila[j] = mochila[j + 1];
                        }
                        totalItens--;
                        encontrado = 1;
                        printf("Item removido com sucesso!\n");
                        estadoOrdenacao = ORDENADO_NENHUM;
                        encontrado = true;
                        printf("== Item removido! ==\n");
                        break;
                    }
                }

                if (!encontrado) {
                    printf("\n === Item não encontrado. ===\n");
                }
                if (!encontrado) printf("== Item não encontrado. ==\n");
                break;
            }

            case 3: {
                if (totalItens == 0) {
                    printf("A mochila está vazia.\n");
                } else {

                    printf("\n%-30s %-20s %-10s\n", "Nome", "Tipo", "Quantidade");
                    printf("\n%-20s %-15s %-10s %-10s\n", "Nome", "Tipo", "Qtd", "Prioridade");
                    printf("-------------------------------------------------------------\n");
                    for (int i = 0; i < totalItens; i++) {
                        printf("%-30s %-20s %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
                        printf("%-20s %-15s %-10d %-10d\n",
                               mochila[i].nome,
                               mochila[i].tipo,
                               mochila[i].quantidade,
                               mochila[i].prioridade);
                    }
                }
                break;
            }
            case 4: {
                char nomeBusca[TAM_NOME];
                int encontrado = 0;

                printf("Digite o nome do item para buscar: ");
                printf("Nome do item a buscar: ");
                fgets(nomeBusca, TAM_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                bool encontrado = false;
                for (int i = 0; i < totalItens; i++) {
                    if (strcmp(mochila[i].nome, nomeBusca) == 0) {
                        printf("\nItem encontrado:\n");
                        printf("Nome      : %s\n", mochila[i].nome);
                        printf("Tipo      : %s\n", mochila[i].tipo);
                        printf("Quantidade: %d\n", mochila[i].quantidade);
                        encontrado = 1;
                        printf("Prioridade: %d\n", mochila[i].prioridade);
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) printf("\n === Item não encontrado na mochila. ===\n");
                break;
            }
            case 5: {
                int criterio;
                printf("Ordenar por:\n1. Nome\n2. Tipo\n3. Prioridade\nEscolha: ");
                scanf("%d", &criterio);
                getchar();

                CriterioOrdenacao c;
                if (criterio == 1) c = ORDENADO_NOME;
                else if (criterio == 2) c = ORDENADO_TIPO;
                else c = ORDENADO_PRIORIDADE;

                int comparacoes = ordenarMochila(c);
                printf("Mochila ordenada! Comparacoes realizadas: %d\n", comparacoes);
                break;
            }

            case 6: {
                char nomeBusca[TAM_NOME];
                printf("Nome do item a buscar (binaria): ");
                fgets(nomeBusca, TAM_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                if (!encontrado) {
                    printf("\n === Item não encontrado na mochila. ===\n");
                int pos = buscaBinariaPorNome(nomeBusca);
                if (pos != -1) {
                    printf("\nItem encontrado:\n");
                    printf("Nome      : %s\n", mochila[pos].nome);
                    printf("Tipo      : %s\n", mochila[pos].tipo);
                    printf("Quantidade: %d\n", mochila[pos].quantidade);
                    printf("Prioridade: %d\n", mochila[pos].prioridade);
                } else {
                    printf("Item nao encontrado.\n");
                }
                break;
            }