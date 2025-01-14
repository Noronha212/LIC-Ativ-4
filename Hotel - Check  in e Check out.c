#include <stdio.h>
#include <stdlib.h>

// Declaração Funções
void fMostraMat(int m[20][14], char status[20][14]);
int fMenu();
void fCriaMat(int m[20][14], char status[20][14]);
void fCheckIn(int m[20][14], char status[20][14]);
void fCheckOut(int m[20][14], char status[20][14]);
void fMostrarQuartosLivres(int m[20][14], char status[20][14]);
void fMostrarQuartosOcupados(int m[20][14], char status[20][14]);
void clearInputBuffer();
void fRealizarCheckIn(int m[20][14], char status[20][14]);
void fRealizarCheckOut(int m[20][14], char status[20][14]);

// Declaração Variáveis Globais
int n = 1;
int m[20][14];
char status[20][14]; // Matriz para armazenar o status dos quartos
int i;
int j; 
int menu = 0;
int quarto = 1;

// Estrutura Dados Hospede - Endereco
struct stendereco
{
    char rua[100];
    char numero[5];
    char bairro[40];
    char cidade[40];
    char uf[2];            
};

// Estrutura Dados Hospede
struct stquarto
{
    char status;
    char nome[50];
    char cpf[11];
    char telefone[11];
    struct stendereco ender;    // Estrutura Dados Hospede - Endereco Aninhada
};

// FUNCAO PRINCIPAL
int main (){
    fCriaMat(m, status);
    while (1){ // Loop continuo ate o usuario optar por sair
        if (fMenu() == 5) {
            printf("Saindo do sistema.\n");
            break; // Sai do loop e termina o programa
        }
    }
    return 0;
}

// CRIAR E PREENCHER MATRIZ 
void fCriaMat(int m[20][14], char status[20][14]) {
    // Variavel para preencher a matriz
    int count = 1;

    // Preenchendo a matriz com quartos de 1 a 280 e status '.' (livre)
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 14; j++) {
            m[i][j] = count++;
            status[i][j] = '.'; // Todos os quartos comecam como livres
        }
    }
}

void fMostraMat(int m[20][14], char status[20][14]) {
	printf("Quartos: ");
	for (int k = 0; k < 14; k++) {
        printf("\t%d", k + 1);}  // Imprimindo o apartamento correspondente
    printf("\n");
	for (int i = 0; i < 20; i++) {
        printf("Andar %2d: ", 20 - i);  // Imprimindo o andar correspondente
        for (int j = 0; j < 14; j++) {
            printf("\t%c", status[19 - i][j]);
        }
        printf("\n");
    }
    printf("\n---------------------------------------------------------------------\n");
}


// FUNCAO MENU
int fMenu() {
    printf("\nBEM VINDO AO MENU PRINCIPAL DO HOTEL\n");
    printf("1 - Mostrar Mapa; 2 - Check-in; 3 - Check-out; 4 - Reserva; 5 - Sair\n");

    if (scanf("%d", &menu) != 1) {
        clearInputBuffer();
        printf("Entrada invalida! Por favor, insira um numero.\n");
        return 0; // Retorna ao menu inicial
    }

    switch (menu) {
        case 1:
            printf("\nIMPRIMINDO MAPA...\n\n");
            fMostraMat(m, status);
            break;
        case 2:
            fCheckIn(m, status);
            break;
        case 3:
            fCheckOut(m, status);
            break;
        case 4:
            printf("Opcao de reserva ainda nao implementada.\n");
            break;
        case 5:
            return 5; // Indica que o programa deve terminar
        default:
            printf("Opcao invalida! Por favor, tente novamente.\n");
    }

    return 0; // Continua no menu
}

// SUBMENU CHECK-IN
void fCheckIn(int m[20][14], char status[20][14]) {
    int subMenu;
    while (1) {
        printf("\nSUB MENU CHECK-IN\n");
        printf("1 - Realizar Check-in; 2 - Mostrar Quartos Livres; 3 - Voltar ao Menu Anterior\n");

        if (scanf("%d", &subMenu) != 1) {
            clearInputBuffer();
            printf("Entrada invalida! Por favor, insira um numero.\n");
            continue;
        }

        switch (subMenu) {
            case 1:
                fRealizarCheckIn(m, status);
                break;
            case 2:
                fMostrarQuartosLivres(m, status);
                break;
            case 3:
                return; // Retorna ao menu principal
            default:
                printf("Opcao invalida! Por favor, tente novamente.\n");
        }
    }
}

// REALIZAR CHECK-IN
void fRealizarCheckIn(int m[20][14], char status[20][14]) {
    int andarQuarto;
    int numeroQuarto;
    printf("\nDigite o numero do andar para check-in: ");

    if (scanf("%d", &andarQuarto) != 1) {
        clearInputBuffer();
        printf("Entrada invalida! Por favor, insira um numero.\n");
        return;
    }
    
    // Validar se o número do andar
    if (andarQuarto < 1 || andarQuarto > 20) {
        printf("Numero do andar invalido! Por favor, tente novamente.\n");
        return;
    }
    
    printf("\nDigite o numero do quarto para check-in: ");
    if (scanf("%d", &numeroQuarto) != 1) {
        clearInputBuffer();
        printf("Entrada invalida! Por favor, insira um numero.\n");
        return;
    }
    
    // Validar se o número do quarto é válido
    if (numeroQuarto < 1 || numeroQuarto > 14) {
        printf("Numero do quarto invalido! Por favor, tente novamente.\n");
        return;
    }

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 14; j++) {
            if (i == (andarQuarto-1) && j == (numeroQuarto-1)) {
                if (status[i][j] == '.') {
                    status[i][j] = 'O';  // Ocupado
                    printf("Check-in realizado com sucesso no quarto %d%d.\n", andarQuarto, numeroQuarto);
                } else {
                    printf("O quarto %d ja esta ocupado.\n", numeroQuarto);
                }
                return;
            }
        }
    }
    printf("Quarto %d nao encontrado.\n", numeroQuarto);
}

// MOSTRAR QUARTOS LIVRES
void fMostrarQuartosLivres(int m[20][14], char status[20][14]) {
    printf("\nQUARTOS LIVRES:\n");
    for (i = 19; i >= 0; i--) {
        for (j = 0; j < 14; j++) {
            if (status[i][j] == '.') {
                printf(" %3d ", m[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n---------------------------------------------------------------------\n");
}

// SUBMENU CHECK-OUT
void fCheckOut(int m[20][14], char status[20][14]) {
    int subMenu;
    while (1) {
        printf("\nSUB MENU CHECK-OUT\n");
        printf("1 - Realizar Check-out; 2 - Mostrar Quartos Ocupados; 3 - Voltar ao Menu Anterior\n");

        if (scanf("%d", &subMenu) != 1) {
            clearInputBuffer();
            printf("Entrada invalida! Por favor, insira um numero.\n");
            continue;
        }

        switch (subMenu) {
            case 1:
                fRealizarCheckOut(m, status);
                break;
            case 2:
                fMostrarQuartosOcupados(m, status);
                break;
            case 3:
                return; // Retorna ao menu principal
            default:
                printf("Opcao invalida! Por favor, tente novamente.\n");
        }
    }
}

// REALIZAR CHECK-OUT
void fRealizarCheckOut(int m[20][14], char status[20][14]) {
    int andarQuarto;
    int numeroQuarto;
    printf("\nDigite o numero do andar para check-out: ");

    if (scanf("%d", &andarQuarto) != 1) {
        clearInputBuffer();
        printf("Entrada invalida! Por favor, insira um numero.\n");
        return;
    }

    // Validar se o número do andar é válido
    if (andarQuarto < 1 || andarQuarto > 20) {
        printf("Numero do andar invalido! Por favor, tente novamente.\n");
        return;
    }

	printf("\nDigite o numero do quarto para check-out: ");
	    if (scanf("%d", &numeroQuarto) != 1) {
	        clearInputBuffer();
	        printf("Entrada invalida! Por favor, insira um numero.\n");
	        return;
	    }
	    
	// Validar se o número do quarto é válido
	if (numeroQuarto < 1 || numeroQuarto > 14) {
	    printf("Numero do quarto invalido! Por favor, tente novamente.\n");
	    return;
	    }
	
	    for (int i = 0; i < 20; i++) {
	        for (int j = 0; j < 14; j++) {
	            if (i == (andarQuarto-1) && j == (numeroQuarto-1)) {
	                if (status[i][j] == 'O') {	// Ocupado
	                    status[i][j] = '.';  	// Vago
	                    printf("Check-out realizado com sucesso no quarto %d%d.\n", andarQuarto, numeroQuarto);
	                } else {
	                    printf("O quarto %d ja esta livre.\n", numeroQuarto);
	                }
	                return;
	            }
	        }
	    }
	    printf("Quarto %d nao encontrado.\n", numeroQuarto);
}

// MOSTRAR QUARTOS OCUPADOS
void fMostrarQuartosOcupados(int m[20][14], char status[20][14]) {
    printf("\nQUARTOS OCUPADOS:\n");
    for (i = 19; i >= 0; i--) {
        for (j = 0; j < 14; j++) {
            if (status[i][j] == 'O') {
                printf(" %3d ", m[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n---------------------------------------------------------------------\n");
}

// Funcao para limpar o buffer de entrada
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
