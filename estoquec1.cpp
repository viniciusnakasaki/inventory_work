
/*Bibiltecas do Compilador*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

/*Constante simbólica*/
#define MAX_ITENS 100
#define MAX_NOME 50

/**Estrutura para armazenar dados do relatório.*/
typedef struct {
    char nome[MAX_NOME];
    int quantidadeRetirada;
} Relatorio;

/*Estrutura para representar um produto no estoque.*/
typedef struct TProduto {
    long int codigo;
    int quantidade;
    int grupo;
    char descricao[41];
    char unidade[3];
    char fornecedor[41];
    float pr_compra;
    float pr_venda;
    float lucro;
    char validade[11];
} Tproduto;

/* Variáveis globais */
const int MAX = 50;               /* Tamanho máximo do estoque */
int ordenado = 0;                 /* Auxiliar para busca de produtos */
int totalCantina = 0;             /* Contador de itens retirados para cantina */
int totalGastronomia = 0;         /* Contador de itens retirados para gastronomia */
Relatorio relatorioCantina[MAX_ITENS]; /* Relatório de retiradas para cantina */
Relatorio relatorioGastronomia[MAX_ITENS]; /* Relatório de retiradas para gastronomia */

/* Declaração das funções */
void leitura(Tproduto estoque[], int *tamanho); /* Leitura do arquivo de produtos */
void gravacao(Tproduto estoque[], int tamanho); /* Gravação no arquivo de produtos */
void cadastrar(Tproduto estoque[], int *tamanho); /* Cadastro de produtos */
void excluir(Tproduto estoque[], int *tamanho); /* Exclusão de produtos */
int vazio(int tamanho); /* Verifica se o estoque está vazio */
int pesquisabinaria(Tproduto estoque[], int chave, int tamanho); /* Busca binária */
void mostra(Tproduto estoque[], int chave); /* Mostra informações de um produto */
void mostra_compra(Tproduto estoque[], int chave); /* Mostra informações de compra */
void classifica(Tproduto estoque[], int tamanho); /* Ordenação do estoque */
void MenuPrincipal(); /* Exibe o menu principal */
void alterar(Tproduto estoque[], int *tamanho); /* Alteração de produtos */
void consulta_codigo(Tproduto estoque[], int tamanho); /* Consulta por código */
void consulta_descricao(Tproduto estoque[], int tamanho); /* Consulta por descrição */
void compra_produtos(Tproduto estoque[], int tamanho); /* Registro de compra de produtos */
void relatorio_produtos(Tproduto estoque[], int tamanho); /* Relatório de produtos */
void lista_precos(Tproduto estoque[], int tamanho); /* Lista de preços */
void relatorio_prejuizo(Tproduto estoque[], int tamanho); /* Relatório de prejuízo */
void exibirRelatorio(Relatorio relatorio[], int total, const char *departamento); /* Exibição de relatórios */
void retirarItem(Tproduto estoque[], int *tamanho); /* Retirada de itens */
void carregarRelatorio(Relatorio relatorio[], int *total, const char *arquivo); /* Carregar relatórios */
void exibirRelatorioC(Relatorio relatorio[], int total, const char *departamento); /* Exibição do relatório da cantina */
void exibirRelatorioG(Relatorio relatorio[], int total, const char *departamento); /* Exibição do relatório de gastronomia */

 
int main() {
    /* Configura a localização para suporte ao idioma Português */
    setlocale(LC_ALL, "Portuguese_Brazil");
    MenuPrincipal(); /* Chama o menu principal */
    return 0;
}

/*Função para gravar os dados de um relatório em um arquivo.*/
void gravarRelatorio(Relatorio relatorio[], int total, const char *arquivo) {
    FILE *fp = fopen(arquivo, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para gravação do relatório.\n");
        return;
    }
    for (int i = 0; i < total; i++) {
        fprintf(fp, "%s;%d\n", relatorio[i].nome, relatorio[i].quantidadeRetirada);
    }
    fclose(fp);
}
 
 /*Função que exibe o menu principal e permite ao usuário navegar pelas opções.*/
void MenuPrincipal() {
    Tproduto estoque[MAX];
    int tamanho = 0, opcao;
    leitura(estoque, &tamanho); /*Abre o arquivo de leitura de dados*/
    do {
        printf("\033[44;36m\n================ MENU ================\033[0m\n");
        printf(" 1  - Incluir\n");
        printf(" 2  - Excluir\n");
        printf(" 3  - Alteração\n");
        printf(" 4  - Consulta por Código\n");
        printf(" 5  - Consulta por Descrição\n");
        printf(" 6  - Relatório de Produtos\n");
        printf(" 7  - Lista de Preços\n");
        printf(" 8  - Relatório de Prejuízo\n");
        printf(" 9  - Compra de Produtos\n");
        printf(" 10 - Relatório da Cantina\n");
        printf(" 11 - Relatório da Gastronomia\n");
        printf(" 12 - Retirar Item\n");
        printf(" 0  - Sair\n");
        printf("\n======================================\n");
        printf("\nEscolha a opção que deseja: ");
        scanf("%d", &opcao);
       
        system("cls");
       
       
        switch (opcao) {
            case 1: /*Cadastra os produtos do estoque e grava a informação*/
                cadastrar(estoque, &tamanho); 
                gravacao(estoque, tamanho); 
                break;
            case 2: /*Exclui o produto escolhido gravado*/
                excluir(estoque, &tamanho);
                gravacao(estoque, tamanho);
                break;
            case 3: /*Altera dados do produtos cadastrado conforme escolhido*/
                alterar(estoque, &tamanho);
                gravacao(estoque, tamanho);
                break;
            case 4: /*Consulta os produtos por código*/
                consulta_codigo(estoque, tamanho);
                break;
            case 5:  /*Consulta os produtos por descrição*/
                consulta_descricao(estoque, tamanho);
                break;
            case 6: /*Relatório de produtos(2 por página)*/
                relatorio_produtos(estoque, tamanho);
                break;
            case 7: /*Mostra todos produtos, com preço*/
                lista_precos(estoque, tamanho);
                break;
            case 8: /*Relatório de prejuízo | específico*/
                relatorio_prejuizo(estoque, tamanho);
                break;
            case 9: 
                compra_produtos(estoque, tamanho);
                gravacao(estoque, tamanho);
                break;
            case 10: /*Exibe os Relatórios | Cantina*/
                exibirRelatorioC(relatorioCantina, totalCantina, "Cantina");
                break;
            case 11:  /*Exibe os Relatórios | Gasttonomia*/
                exibirRelatorioG(relatorioGastronomia, totalGastronomia, "Gastronomia");
                break;
            case 12:  /*Retira os itens para cantina ou gastronomia e grava um relatório*/
                retirarItem(estoque, &tamanho);
                gravacao(estoque, tamanho);
                gravarRelatorio(relatorioCantina, totalCantina, "relatorio_cantina.dat");
                gravarRelatorio(relatorioGastronomia, totalGastronomia, "relatorio_gastronomia.dat");
                break;
            case 0: /*Saída - Normal*/
                exit(0);
                break;
            default:
                printf("\033[31mOPÇÃO INVÁLIDA!\033[0m");
        }
    } while (opcao != 0);
}
void cadastrar(Tproduto estoque[], int *tamanho) {
    Tproduto produto;
    if (*tamanho == MAX) {
        printf("\n ERRO! \n ARQUIVO CHEIO.\n");
        return;
    }
 
    Tproduto aux;
    char correto = 'n';
    printf("\n===================== Cadastrar =====================\n\n");
   do {
    printf("Código ..............................: ");
    scanf("%ld", &aux.codigo);
    while (getchar() != '\n');  // Limpa o buffer de entrada
 
    // Verifica se o código já está em uso
    int codigo_duplicado = 0;
    for (int i = 0; i < *tamanho; i++) {  // Corrigido:tamanho
        if (estoque[i].codigo == aux.codigo) {
            printf("Erro: Código já está em uso. Digite um novo código.\n");
            codigo_duplicado = 1;
            break;
        }
    }
 
    if (!codigo_duplicado) break; // Sai do loop caso o código seja único
} while (1);
 
    do {
        printf("Quantidade do produto ...............: ");
        scanf("%i", &aux.quantidade);
        while (getchar() != '\n');
    } while (aux.quantidade < 0);
    do {
        printf("Grupo ...............................: ");
        scanf("%i", &aux.grupo);
        while (getchar() != '\n');
    } while (aux.grupo < 0);
 
    do {
        printf("Preço de compra .....................: R$");
        scanf("%f", &aux.pr_compra);
        while (getchar() != '\n');
    } while (aux.pr_compra < 0);
 
    do {
        printf("Preço de venda ......................: R$");
        scanf("%f", &aux.pr_venda);
        while (getchar() != '\n');
    } while (aux.pr_venda < 0);
 
    printf("Validade ............................: ");
    fgets(aux.validade, sizeof(aux.validade), stdin);
    aux.validade[strcspn(aux.validade, "\n")] = '\0';
    while (getchar() != '\n');
 
    printf("Descrição ...........................: ");
    fgets(aux.descricao, sizeof(aux.descricao), stdin);
    aux.descricao[strcspn(aux.descricao, "\n")] = '\0';  // Remove o \n
 
     printf("Unidade .............................: ");
    fgets(aux.unidade, sizeof(aux.unidade), stdin);
    aux.unidade[strcspn(aux.unidade, "\n")] = '\0';
    while (getchar() != '\n');
 
     printf("Fornecedor ..........................: ");
    fgets(aux.fornecedor, sizeof(aux.fornecedor), stdin);
    aux.fornecedor[strcspn(aux.fornecedor, "\n")] = '\0';
 
     printf("\n=====================================================\n");
     printf("Os dados estão corretos? (S/N): ");
    correto = getchar();
    while (getchar() != '\n');  // Limpa o buffer de entrada
 
    if (correto == 's' || correto == 'S') {
        estoque[*tamanho] = aux;
        (*tamanho)++;
        printf("\tO PRODUTO FOI INCLUÍDO!\n");
    }
 
    printf("\tAPERTE ENTER PARA VOLTAR AO MENU");
    getchar();  // Aguarda a tecla Enter
    system("cls");
}
 
 
void excluir(Tproduto estoque[], int *tamanho) {
    long int codigo;
    int i, j, encontrado = 0;
 
    printf("\n===================== Excluir Item =====================\n");
    printf("Digite o código do produto a ser excluído: ");
    scanf("%ld", &codigo);
 
    for (i = 0; i < *tamanho; i++) {
        if (estoque[i].codigo == codigo) {
            encontrado = 1;
            for (j = i; j < *tamanho - 1; j++) {
                estoque[j] = estoque[j + 1]; // Move todos os elementos para a esquerda
            }
            (*tamanho)--; // Reduz o tamanho do array
            printf("\nItem excluído com sucesso.\n");
            break;
        }
    }
 
    if (!encontrado) {
        printf("\nItem não encontrado.\n");
    }
 
    printf("\tAPERTE ENTER PARA VOLTAR AO MENU");
    getchar(); // Para capturar o ENTER pressionado
    getchar();
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
 
void carregarRelatorio(Relatorio relatorio[], int *total, const char *arquivo) {
    FILE *fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s para leitura.\n", arquivo);
        return;
    }
 
    *total = 0;
    while (fscanf(fp, "%49[^;];%d\n", relatorio[*total].nome, &relatorio[*total].quantidadeRetirada) == 2) {
        (*total)++;
    }
 
    fclose(fp);
}
 
void exibirRelatorioC(Relatorio relatorio[], int total, const char *departamento) {
    // Carregar o relatório do arquivo antes de exibir
    carregarRelatorio(relatorioCantina, &totalCantina, "relatorio_cantina.dat");
 
    // Limpa a tela para exibir o relatório em uma página única
    system("cls");  // Comando para limpar a tela no Windows
 
    // Exibe o relatório
    printf("\n====================== Relatório de %s =====================\n\n", departamento);
    for (int i = 0; i < totalCantina; i++) {
        printf("%d. %s - Quantidade retirada: %d\n", i + 1, relatorioCantina[i].nome, relatorioCantina[i].quantidadeRetirada);
    }
    printf("\n=====================================================================\n");
    // Pausa para que o usuário possa ler o relatório
    printf("\nPressione Enter para continuar...");
    getchar();  // Captura a tecla Enter pressionada
    getchar();  // Captura o Enter adicional que pode ser deixado pelo `scanf` anterior, se for o caso
 
    // Limpa a tela antes de exibir o menu
    system("cls");
}
 
 
void exibirRelatorioG(Relatorio relatorio[], int total, const char *departamento) {
    // Carregar o relatório do arquivo antes de exibir
    carregarRelatorio(relatorioGastronomia, &totalGastronomia, "relatorio_gastronomia.dat");
 
    // Limpa a tela para exibir o relatório em uma página única
    system("cls");  // Comando para limpar a tela no Windows
 
    // Exibe o relatório
    printf("\n====================== Relatório de %s =====================\n\n", departamento);
    for (int i = 0; i < totalGastronomia; i++) {
        printf("%d. %s - Quantidade retirada: %d\n", i + 1, relatorioGastronomia[i].nome, relatorioGastronomia[i].quantidadeRetirada);
    }
    printf("\n=====================================================================\n");
    // Pausa para que o usuário possa ler o relatório
    printf("\nPressione Enter para continuar...");
    getchar();  // Captura a tecla Enter pressionada
    getchar();  // Captura o Enter adicional que pode ser deixado pelo `scanf` anterior, se for o caso
 
    // Limpa a tela antes de exibir o menu
    system("cls");
}
 
 
void retirarItem(Tproduto estoque[], int *tamanho) {
    long int codigo;
    int quantidade;
    int encontrado = 0;
 
    printf("\n===================== Retirar Item =====================\n");
    printf("Digite o código do produto...........: ");
    scanf("%ld", &codigo);
    printf("Digite a quantidade a ser retirada...: ");
    scanf("%d", &quantidade);
 
    for (int i = 0; i < *tamanho; i++) {
        if (estoque[i].codigo == codigo) {
            encontrado = 1;
            if (estoque[i].quantidade >= quantidade) {
                // Atualiza a quantidade no estoque
                estoque[i].quantidade -= quantidade;
 
                // Solicita o destino do item
                int destino;
                printf("\nPara onde o item será enviado?\n");
                printf("1 - Cantina\n");
                printf("2 - Gastronomia\n");
                printf("Escolha a opção: ");
                scanf("%d", &destino);
 
                if (destino == 1) {
                    printf("Item retirado para a Cantina.\n");
                    // Adiciona a quantidade retirada ao relatório da Cantina
                    int encontradoCantina = 0;
                    for (int j = 0; j < totalCantina; j++) {
                        if (strcmp(relatorioCantina[j].nome, estoque[i].descricao) == 0) {
                            relatorioCantina[j].quantidadeRetirada += quantidade;
                            encontradoCantina = 1;
                            break;
                        }
                    }
                    if (!encontradoCantina && totalCantina < MAX_ITENS) {
                        strcpy(relatorioCantina[totalCantina].nome, estoque[i].descricao);
                        relatorioCantina[totalCantina].quantidadeRetirada = quantidade;
                        totalCantina++;
                    }
                } else if (destino == 2) {
                    printf("Item retirado para a Gastronomia.\n");
                    // Adiciona a quantidade retirada ao relatório da Gastronomia
                    int encontradoGastronomia = 0;
                    for (int j = 0; j < totalGastronomia; j++) {
                        if (strcmp(relatorioGastronomia[j].nome, estoque[i].descricao) == 0) {
                            relatorioGastronomia[j].quantidadeRetirada += quantidade;
                            encontradoGastronomia = 1;
                            break;
                        }
                    }
                    if (!encontradoGastronomia && totalGastronomia < MAX_ITENS) {
                        strcpy(relatorioGastronomia[totalGastronomia].nome, estoque[i].descricao);
                        relatorioGastronomia[totalGastronomia].quantidadeRetirada = quantidade;
                        totalGastronomia++;
                    }
                } else {
                    printf("Destino inválido!\n");
                }
            } else {
                printf("Erro: Quantidade insuficiente para retirada.\n");
            }
            break;
        }
    }
 
    if (!encontrado) {
        printf("Erro: Produto não encontrado.\n");
    }
    printf("\n========================================================\n");
    printf("\tAPERTE ENTER PARA VOLTAR AO MENU");
    getchar(); // Para capturar o ENTER pressionado
    getchar();
    system("cls");
}

void alterar(Tproduto estoque[], int *tamanho)
{
    if (*tamanho == 0)
    { // verifica se existe produto cadastrado na base de dados
        printf("\nREGISTRO VAZIO!\n\n");
        return;
    }
        int codigo, posicao, opc, alterar_novamente;
        printf("\n===================== Alterar =====================\n\n");
        printf("Digite o código do produto: ");
        scanf("%d", &codigo);
        posicao = pesquisabinaria(estoque, codigo, *tamanho);
        system("cls");
        printf("\n===================== Alterar =====================\n\n");
    if(posicao >= 0)
    do {
        mostra(estoque, posicao);
        printf("1 - Quantidade\n");
        printf("2 - Grupo\n");
        printf("3 - Preço de compra\n");
        printf("4 - Preço de venda\n");
        printf("5 - Descrição\n");
        printf("6 - Unidade\n");
        printf("7 - Fornecedor\n");
        printf("0 - Voltar ao Menu\n");
        printf("\n==============================================\n");
        printf("Qual dado deseja alterar?\n");
        scanf("%d", &opc);
        system ("cls");
        switch (opc)
        {
        case 1:
        {
            printf("Digite a nova quantidade: ");
            scanf("%i", &estoque[posicao].quantidade);
            break;
        }
        case 2:
        {
            printf("Digite o novo grupo: ");
            scanf("%i", &estoque[posicao].grupo);
            break;
        }
        case 3:
        {
            printf("Digite o novo preço de compra: R$");
            scanf("%f", &estoque[posicao].pr_compra);
            break;
        }
        case 4:
        {
            printf("Digite o novo preço de venda: R$");
            scanf("%f", &estoque[posicao].pr_venda);
            break;
        }
        case 5:
        {
            printf("Digite a nova descrição: ");
            scanf("%s", &estoque[posicao].descricao);
            break;
        }
        case 6:
        {
            printf("Digite a nova unidade: ");
            scanf("%s", &estoque[posicao].unidade);
            break;
        }
        case 7:
        {
            printf("Digite o novo fornecedor: ");
            scanf("%s", &estoque[posicao].fornecedor);
            break;
        }
        case 0:
        {
            return;
		}
        default:
        	printf("Valor inválido!");
        }
        printf("\nDeseja alterar outro dado? (1 - Sim, 0 - Não): ");
        scanf("%d", &alterar_novamente);
        if (alterar_novamente == 0) {
            break; // Sai do loop se a resposta for 0
        }

        system("cls"); // Limpa a tela antes de mostrar a próxima opção

        } while (opc != 0);
    else {
    	system("cls");
        printf("Produto não encontrado!\n");
    }
}


void consulta_codigo(Tproduto estoque[], int tamanho)
{
    if (tamanho == 0) {
        // Verifica se há produtos cadastrados
        printf("\nREGISTRO VAZIO!\n\n");
        return ;
    }

  int codigo, posicao;
    printf("\n===================== Consultar =====================\n");
    printf("\nDigite o código do produto.......: ");
    scanf("%d", &codigo);

    // Realiza a busca binária
    posicao = pesquisabinaria(estoque, codigo, tamanho);
    system("cls");
    printf("\n===================== Consultar =====================\n\n");
    if (posicao >= 0) {
        // Produto encontrado
        mostra(estoque, posicao);
    } else {
    system("cls");
    printf("Produto não encontrado!\n");
    }

    printf("=====================================================\n");
    // Mensagem para continuar
    printf("Pressione ENTER para voltar ao menu.");
    getchar(); // Aguarda entrada do usuário
    getchar(); // Limpa buffer
    system("cls");
}

void consulta_descricao(Tproduto estoque[], int tamanho) {
    if (tamanho == 0) {
        // Verifica se há produtos cadastrados
        printf("\nREGISTRO VAZIO!\n\n");
        return;
    }

    char descricao_busca[100];
    int encontrou = 0;

    printf("\n===================== Consultar =====================\n");
    printf("\nDigite parte da descrição do produto: ");
    while (getchar() != '\n'); // Limpa o buffer de entrada
    fgets(descricao_busca, sizeof(descricao_busca), stdin);
    descricao_busca[strcspn(descricao_busca, "\n")] = '\0';  // Remove o '\n' do final

    printf("\nProdutos encontrados: \n\n");

    for (int i = 0; i < tamanho; i++) {
        if (strstr(estoque[i].descricao, descricao_busca) != NULL) {
            // Produto encontrado
            mostra(estoque, i);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum produto encontrado com a descrição '%s'.\n", descricao_busca);
    }

    printf("======================================================\n");
    printf("Pressione ENTER para voltar ao menu.");
    getchar(); // Aguarda entrada do usuário para continuar
    system("cls");
}

void leitura(Tproduto estoque[], int *tamanho)
{
    FILE *arquivo;
    arquivo = fopen("estoque.dat", "a+b"); /* abrimos para anexar, binário */
    if (!arquivo)
    {
        printf("Erro ao abrir arquivo!");
        return;
    }
    // le os dados do arquivo
    while (!feof(arquivo))
    {
        fread(&estoque[*tamanho], sizeof(Tproduto), 1, arquivo);
        (*tamanho)++;
    }
    (*tamanho)--;
    // fecha o arquivo
    fclose(arquivo);
    return;
}

void gravacao(Tproduto estoque[], int tamanho)
{
    FILE *arquivo;
    int i;
    arquivo = fopen("estoque.dat", "w+b"); /* abre e apaga o conteúdo do arquivo,binário */
    if (!arquivo)
    {
        printf("Erro ao abrir arquivo!");
        return;
    }
    // grava a estrutura no arquivo
    for (i = 0; i < tamanho; i++)
        fwrite(&estoque[i], sizeof(Tproduto), 1, arquivo);
    // Fecha o arquivo de dados
    fclose(arquivo);
    return;
}

void mostra(Tproduto estoque[], int chave)
{
    printf("Código...........................: %ld\n", estoque[chave].codigo);
    printf("Quantidade.......................: %i\n", estoque[chave].quantidade);
    printf("Grupo............................: %i\n", estoque[chave].grupo);
    printf("Preço de compra..................: R$%.2f\n", estoque[chave].pr_compra);
    printf("Preço de venda...................: R$%.2f\n", estoque[chave].pr_venda);
    printf("Validade ........................: %s\n", estoque[chave].validade);
    printf("Descrição........................: %s\n", estoque[chave].descricao);
    printf("Unidade..........................: %s\n", estoque[chave].unidade);
    printf("Fornecedor.......................: %s\n\n", estoque[chave].fornecedor);
    return;
}

void mostra_compra(Tproduto estoque[], int chave)
{
    printf("Descrição..............................: %s\n", estoque[chave].descricao);
    printf("Unidade................................: %s\n", estoque[chave].unidade);
    printf("Fornecedor.............................: %s\n\n", estoque[chave].fornecedor);
    return;
}

void relatorio_produtos(Tproduto estoque[], int tamanho)
{
    if (tamanho == 0) {
        printf("\nREGISTRO VAZIO!\n\n");
        return;
    }

    int opcao;
    int produtos_por_pagina = 2; // Define o número de produtos exibidos por página

    printf("\t\tControle de Estoque - Relatório Geral\n");
    printf("=======================================================================\n");
    classifica(estoque, tamanho);

    for (int i = 0; i < tamanho; i++) {
        printf("\n-----------------------------------------------------------------------\n");
        printf("Código: %ld\t\t\t\t\t\t    Grupo: %i\n", estoque[i].codigo, estoque[i].grupo);
        printf("Descrição: %s\t\t\t\t    Unidade: %s\n", estoque[i].descricao, estoque[i].unidade);
        printf("Fornecedor: %s\n", estoque[i].fornecedor);
        printf("Preço de Compra: %.2f\t     Preço de Venda: %.2f\tLucro: %.2f%%\n", estoque[i].pr_compra, estoque[i].pr_venda, (estoque[i].lucro = (estoque[i].pr_venda - estoque[i].pr_compra) / estoque[i].pr_compra * 100));
        printf("Quantidade em Estoque: %i\t\tQuantidade Mínima: 20\n", estoque[i].quantidade);
        printf("Validade: %s\n", estoque[i].validade);
        printf("\n-----------------------------------------------------------------------\n");

        // Pausa após exibir o número definido de produtos
        if ((i + 1) % produtos_por_pagina == 0 || i == tamanho - 1) {
            printf("\nDigite 1 para continuar ou 0 para voltar ao menu: ");
            scanf("%d", &opcao);
            system("cls");

            if (opcao == 0) {
                printf("\nVoltando ao menu...\n");
                system("cls");
                return;
            }
        }
    }

    printf("\nFim do relatório.\n");
    printf("Pressione ENTER para voltar ao menu.");
    getchar(); // Aguarda o ENTER final
    getchar(); // Limpa buffer
    system("cls");
}

void lista_precos(Tproduto estoque[], int tamanho)
{
	if (tamanho == 0) {
        printf("\nREGISTRO VAZIO!\n\n");
        return;
    }

    int codigo;
    int produtos_por_pagina = 15;  // Define o número de produtos exibidos por página
    int opcao;
    int i;

    printf("\n=========================== Lista de Preços ===========================\n\n");

    classifica(estoque, tamanho);  // Assumindo que a função classifica organiza o estoque

    // Exibe cabeçalho
    printf("Código\tDescrição\t\t\t\t\t       Preço\n");

    // Exibe os produtos em páginas
    for (i = 0; i < tamanho; i++) {
        // Exibe os dados do produto
        printf(" %ld\t%s\t\t\t\t\t\t       %.2f\n", estoque[i].codigo, estoque[i].descricao, estoque[i].pr_venda);

        // Pausa após exibir 15 produtos
        if ((i + 1) % produtos_por_pagina == 0 || i == tamanho - 1) {
        	printf("\n-----------------------------------------------------------------------\n");
            printf("\nDigite 1 para continuar ou 0 para voltar ao menu: ");
            scanf("%d", &opcao);
            system("cls");
            printf("\n=========================== Lista de Preços ===========================\n\n");
            printf("Código\tDescrição\t\t\t\t\t       Preço\n");

            if (opcao == 0) {
                // Se o usuário escolher 0, retorna ao menu
                printf("\nVoltando ao menu...\n");
                system("cls");
                return;
            }
        }
    }

    printf("-----------------------------------------------------------------------\n\n");
    fflush(stdin);
    printf("APERTE ENTER PARA VOLTAR AO MENU");
    getchar();  // Aguarda ENTER final
    getchar();  // Limpa o buffer
    system("cls");
}

void relatorio_prejuizo(Tproduto estoque[], int tamanho) {
    if (tamanho == 0) {
        printf("\nREGISTRO VAZIO!\n\n");
        return;
    }

    printf("\n======================== Relátorio de Prejuízo ========================\n\n");
    printf("Código\t  Quantidade\t Preço Compra\t  Preço Venda\t  Prejuízo\n");

    int prejuizo_encontrado = 0;

    for (int i = 0; i < tamanho; i++) {
        if (estoque[i].pr_compra > estoque[i].pr_venda) {
            float diferenca = estoque[i].pr_compra - estoque[i].pr_venda;
            printf("%ld\t  %d\t\t %.2f\t\t  %.2f\t\t  %.2f\n",
                   estoque[i].codigo,
                   estoque[i].quantidade,
                   estoque[i].pr_compra,
                   estoque[i].pr_venda,
                   diferenca);
            prejuizo_encontrado = 1;
        }
    }

    if (!prejuizo_encontrado) {
        printf("\nNenhum produto com prejuízo foi encontrado.\n");
    }

    printf("\n-----------------------------------------------------------------------\n\n");
    printf("APERTE ENTER PARA VOLTAR AO MENU");
    getchar();
    getchar();
    system("cls");
}

void compra_produtos(Tproduto estoque[], int tamanho) {
    if (tamanho == 0) {
        printf("\nREGISTRO VAZIO!\n\n");
        return;
    }

    int codigo, quantidade;
    float pr_compra;
    char fornecedor[41];

    printf("\n===================== Comprar =====================\n");
    printf("\nDigite o código do produto que deseja comprar: ");
    scanf("%d",&codigo);

    int posicao = pesquisabinaria(estoque, codigo, tamanho);
    system("cls");

    if (posicao >= 0) {
    	printf("\n===================== Comprar =====================\n");
    	printf("\nCódigo do produto digitado: %d\n", codigo);
        mostra_compra(estoque, posicao);  // Mostra os dados do produto encontrado

        // Pergunta o fornecedor da compra
        printf("Digite o fornecedor do produto.........: ");
        getchar();  // Para consumir o '\n' residual do scanf
        fgets(fornecedor, sizeof(fornecedor), stdin);
        fornecedor[strcspn(fornecedor, "\n")] = '\0';  // Remove o '\n' da string

        // Pergunta a quantidade a ser comprada
        printf("Digite a quantidade a ser comprada.....: ");
        scanf("%i", &quantidade);

        // Pergunta o preço de compra
        printf("Digite o preço de compra do produto....: R$ ");
        scanf("%f", &pr_compra);
    printf("\n---------------------------------------------------\n");

        if (quantidade > 0 && pr_compra > 0) {
            // Atualiza os dados do produto
            estoque[posicao].quantidade += quantidade;
            strcpy(estoque[posicao].fornecedor, fornecedor);  // Atualiza fornecedor
            estoque[posicao].pr_compra = pr_compra;  // Atualiza o preço de compra
            printf("\nEstoque atualizado com sucesso!\n");
        } else {
            printf("\nQuantidade ou preço inválidos! Operação cancelada.\n");
        }
    } else {
        printf("\nProduto não encontrado!\n");
    }

    printf("APERTE ENTER PARA VOLTAR AO MENU");
    getchar();
    getchar();
    system("cls");
}


int pesquisabinaria(Tproduto estoque[], int chave, int tamanho)
{
    if (vazio(tamanho))
        return -1;
    if (!ordenado)
    {
        classifica(estoque, tamanho);
        ordenado = 1;
    }
    int inicio = 0, final = tamanho, meio;
    while (inicio <= final)
    {
        meio = (int)(inicio + final) / 2;
        if (estoque[meio].codigo == chave)
            return meio; // encontrou
        if (estoque[meio].codigo < chave)
            inicio = meio + 1;
        else
            final = meio - 1;
        printf("%d\n", meio);
    }
    return -1; // não encontrou
}

int vazio(int tamanho)
{
    if (tamanho == 0)
    {
        printf("\nREGISTRO VAZIO!\n");
        return 1;
    }
    return 0;
}

void classifica(Tproduto estoque[], int tamanho)
{ // ordena os cadastros por código
    int i, j;
    Tproduto aux;
    for (i = 0; i < tamanho - 1; i++)
        for (j = i + 1; j < tamanho; j++)
            if (estoque[i].codigo > estoque[j].codigo)
            {
                aux = estoque[i];
                estoque[i] = estoque[j];
                estoque[j] = aux;
            }
}


