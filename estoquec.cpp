#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
 
const int MAX = 50; // variável global
int ordenado = 0;   // global - auxiliar na busca de produtos cadastrados
 
typedef struct TProduto
{
    long int codigo;
    int quantidade;
    float valor;
    int grupo;
    char descricao[41];
    char unidade[3];
    char fornecedor[41];
    float pr_compra;
    float pr_venda;
    float lucro;
 
} Tproduto;
// escopo das funções básicas
void leitura(Tproduto estoque[], int *tamanho); // Não mexer
void gravacao(Tproduto estoque[], int tamanho); // Não mexer
void cadastrar(Tproduto estoque[], int *tamanho);
void excluir(Tproduto estoque[], int *tamanho);
int vazio(int tamanho);                                          // Não mexer
int pesquisabinaria(Tproduto estoque[], int chave, int tamanho); // Não mexer
void mostra(Tproduto estoque[], int chave);
void classifica(Tproduto estoque[], int tamanho); // Não mexer
void MenuPrincipal();
void relatorio_geral(Tproduto estoque[], int tamanho);
void alterar(Tproduto estoque[], int *tamanho);
void consulta(Tproduto estoque[], int tamanho);
 
int main()
{
    MenuPrincipal();
    return 0;
}
 
void MenuPrincipal()
{
    Tproduto estoque[MAX];
    int tamanho = 0, opcao;
    char nome[20];
    leitura(estoque, &tamanho); // abre o arquivo da base de dados
    do
    {
        printf("\n=============== MENU ===============\n");
        printf("\n 1 - Incluir\n");
        printf(" 2 - Excluir\n");
        printf(" 3 - Relatório Geral\n");
        printf(" 4 - Alteração\n");
        printf(" 5 - Consulta\n");
        printf(" 6 - Compra de Produtos\n");
        printf(" 7 - Produtos\n");
        printf(" 8 - Lista de Preços\n");
        printf(" 9 - Relatório de Prejuízo\n");
        printf(" 10 - Ajuda\n");
        printf(" 0 - Sair\n");
        printf("\nEscolha a opção que deseja: ");
        scanf("%d", &opcao);
        system("cls");
        switch (opcao)
        {
        case 1:
        {
            cadastrar(estoque, &tamanho);
            gravacao(estoque, tamanho); // grava após realizada as operações
            break;
        }
        case 2:
        {
            excluir(estoque, &tamanho);
            gravacao(estoque, tamanho); // grava após realizada as operações
            break;
        }
        case 3:
        {
            relatorio_geral(estoque, tamanho);
            break;
        }
        case 4:
        {
            alterar(estoque, &tamanho);
            gravacao(estoque, tamanho);
            break;
        }
        /* case 5:
        {
            consulta(estoque, tamanho);
            break;
        }
        case 6:
        {
            compra_de_produtos(estoque, tamanho);
            gravacao(estoque, tamanho);
            break;
        }
        case 7:
        {
            relatorio_de_Produtos(estoque, tamanho);
            break;
        }
        case 8:
        {
            relatorio_de_lista_de_preco(estoque, tamanho);
            break;
        }
        case 9:
        {
            relatorio_de_prejuizo(estoque, tamanho);
            break;
        }
        case 10:
        {
            ajuda(estoque, tamanho);
            break;
        }
        */
        case 0:
        {
            exit(0);
            break;
        }
        default:
            printf("OPCAO INVALIDA!");
        }
    } while (opcao != 0);
}
 
void cadastrar(Tproduto estoque[], int *tamanho) {
    if (*tamanho == MAX) {
        printf("\n ERRO! \n ARQUIVO CHEIO.\n");
        return;
    }
    
    Tproduto aux;
    char correto = 'n';
    
    do {
        printf("Codigo ..............................: ");
        scanf("%ld", &aux.codigo);
        while (getchar() != '\n');  // Limpa o buffer de entrada
    } while (aux.codigo <= 0);
    
    do {
        printf("Quantidade do produto ...............: ");
        scanf("%i", &aux.quantidade);
        while (getchar() != '\n');
    } while (aux.quantidade < 0);
    
    do {
        printf("Valor do produto .....................: ");
        scanf("%f", &aux.valor);
        while (getchar() != '\n');
    } while (aux.valor < 0);
    
    do {
        printf("Grupo ...............................: ");
        scanf("%i", &aux.grupo);
        while (getchar() != '\n');
    } while (aux.grupo < 0);
    
    printf("Descrição ...........................: ");
    fgets(aux.descricao, sizeof(aux.descricao), stdin);
    produto.descricao[strcspn(produto.descricao, "\n")] = '\0';  // Remove a nova linha
    
    printf("Unidade .............................: ");
    fgets(aux.unidade, sizeof(aux.unidade), stdin);
    aux.unidade[strcspn(aux.unidade, "\n")] = '\0';
    
    printf("Fornecedor ..........................: ");
    fgets(aux.fornecedor, sizeof(aux.fornecedor), stdin);
    aux.fornecedor[strcspn(aux.fornecedor, "\n")] = '\0';

    // Limpeza do buffer antes de ler `pr_compra`
    while (getchar() != '\n');
    
    do {
        printf("Preço de compra .....................: ");
        scanf("%f", &aux.pr_compra);
        while (getchar() != '\n');
    } while (aux.pr_compra < 0);
    
    do {
        printf("Preço de venda ......................: ");
        scanf("%f", &aux.pr_venda);
        while (getchar() != '\n');
    } while (aux.pr_venda < 0);
    
    do {
        printf("Lucro ...............................: ");
        scanf("%f", &aux.lucro);
        while (getchar() != '\n');
    } while (aux.lucro < 0);
    
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
 
void excluir(Tproduto estoque[], int *tamanho)
{
    if (*tamanho == 0)
    { // verifica se existe produto cadastrado na base de dados
        printf("\nREGISTRO VAZIO!\n\n");
        return;
    }
    int posicao, i, codigo;
    char confirma = 'n';
    printf("Codigo a ser excluido......:");
    scanf("%d", &codigo);
    fflush(stdin);
    posicao = pesquisabinaria(estoque, codigo, *tamanho); // função auxiliar que faz a busca do produto no vetor
    if (posicao >= 0)
    {                             // encontrou registro
        mostra(estoque, posicao); // função auxiliar que apresenta os dados do produto solicitado
        printf("Confirma a exclusao do registro desse produto? (S/N) ");
        fflush(stdin);
        confirma = getchar();
        fflush(stdin);
        if (confirma == 's' || confirma == 'S')
        {
            for (i = posicao; i < (*tamanho) - 1; i++) // copia os dados do proximo registro para o anterior
                estoque[i] = estoque[i + 1];
            (*tamanho)--;
            printf("REGISTRO REMOVIDO!\n\n");
        }
        else
            printf("\n O REGRISTRO NAO FOI EXCLUIDO!\n\n");
    }
    else
        printf("O REGRISTRO NAO FOI LOCALIZADO!\n\n");
    printf("APERTE ENTER PARA VOLTAR AO MENU");
    getchar();
    system("cls");
    return;
}
 
void alterar(Tproduto estoque[], int *tamanho)
{
    if (*tamanho == 0)
    { // verifica se existe produto cadastrado na base de dados
        printf("\nREGISTRO VAZIO!\n\n");
        return;
    }
        int codigo, posicao, opc;
        printf("Digite o codigo do produto: ");
        scanf("%i", &codigo);
        posicao = pesquisabinaria(estoque, codigo, *tamanho);
    if(posicao >= 0)
    {
        mostra(estoque, posicao);
        printf("qual dado deseja alterar?\n");
        printf("1 - quantidade\n");
        printf("2 - valor\n");
        printf("3 - grupo\n");
        printf("4 - descrição\n");
        printf("5 - unidade\n");
        printf("6 - pr_compra\n");
        printf("7 - pr_venda\n");
        printf("8 - fornecedor\n");
        scanf("%i", &opc);
        switch (opc)
        {
        case 1:
        {
            printf("Digite a nova quantidade:");
            scanf("%i", &estoque[posicao].quantidade);
            break;
        }
        case 2:
        {
            printf("Digite o novo valor:");
            scanf("%f", &estoque[posicao].valor);
            break;
        }
        case 3:
        {
            printf("Digite o novo grupo");
            scanf("%i", &estoque[posicao].grupo);
            break;
        }
        case 4:
        {
            printf("Digite a nova descrição");
            scanf("%i", &estoque[posicao].descricao);
            break;
        }
        case 5:
        {
            printf("Digite a nova unidade");
            scanf("%i", &estoque[posicao].unidade);
            break;
        }
        case 6:
        {
            printf("Digite a nova pr_compra");
            scanf("%i", &estoque[posicao].pr_compra);
            break;
        }
        case 7:
        {
            printf("Digite a nova pr_venda");
            scanf("%i", &estoque[posicao].pr_venda);
            break;
        }
        case 8:
        {
            printf("Digite o novo fornecedor");
            scanf("%i", &estoque[posicao].fornecedor);
            break;
        }
        default:
            printf("Valor invalido!");
        }
    }  
}
 
void consulta(Tproduto estoque[], int tamanho)
{
    int codigo;
    printf("\t\tControle de Estoque - Relatorio geral\n");
    printf("=======================================================================\n");
    classifica(estoque, tamanho);
    printf("Codigo\tQuantidade\t\t\t\tPreco\n");
    for (codigo = 0; codigo < tamanho; codigo++)
        printf("%ld\t%i\t\t\t\t\t%.2f\n", estoque[codigo].codigo, estoque[codigo].quantidade, estoque[codigo].valor);
    printf("-----------------------------------------------------------------------\n\n");
    fflush(stdin);
    printf("APERTE ENTER PARA VOLTAR AO MENU");
    getchar();
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
    printf("Codigo...............................:%ld\n", estoque[chave].codigo);
    printf("Quantidade...........................:%i\n", estoque[chave].quantidade);
    printf("Valor................................:%.2f\n", estoque[chave].valor);
    printf("grupo...........................:%i\n", estoque[chave].grupo);
    printf("descrição...........................:%s\n", estoque[chave].descricao);
    printf("unidade...........................:%s\n", estoque[chave].unidade);
    printf("fornecedor...........................:%s\n", estoque[chave].fornecedor);
    printf("pr_compra...........................:%2f\n", estoque[chave].pr_compra);
    printf("pr_venda...........................:%2f\n", estoque[chave].pr_venda);
    return;
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
 
void relatorio_geral(Tproduto estoque[], int tamanho)
{
    int codigo;
    printf("\t\tControle de Estoque - Relatorio geral\n");
    printf("=======================================================================\n");
    classifica(estoque, tamanho);
    printf("Codigo\tQuantidade\t\t\t\tPreco\n");
    for (codigo = 0; codigo < tamanho; codigo++)
        printf("%ld\t%i\t\t\t\t\t%.2f\n", estoque[codigo].codigo, estoque[codigo].quantidade, estoque[codigo].valor);
    printf("-----------------------------------------------------------------------\n\n");
    fflush(stdin);
    printf("APERTE ENTER PARA VOLTAR AO MENU");
    getchar();
    system("cls");
}
 
// printf ("Escolha a opção que deseja alterar:\n\n");
//     printf (" 1 - Quantidade do Produto\n");
//     printf (" 2 - Valor\n");
//     printf (" 3 - Grupo\n");
//     printf (" 4 - Descrição\n");
//     printf (" 5 - Unidade\n");
//     printf (" 5 - Unidade\n");
//     printf (" 6 - Pr_compra\n");
//     printf (" 7 - Pr_venda\n");
//     printf (" 8 - Lucro\n");
//     printf ("\nEscolha a opção que deseja: ");
//     scanf ("%d",&opcao);
//     system("cls");
//     switch (opcao){
//         case 1:{
//          cadastrar(estoque,&tamanho);
//          gravacao(estoque, tamanho);// grava após realizada as operações
//          break;
//      }
//  }
