#include <stdio.h>

// ============================================
// ESTRUTURA DE DADOS: Representa uma carta de cidade
// ============================================
typedef struct {
    char codigo[4];              // Código da carta (ex: "A01", "B02")
    unsigned long int populacao; // População (unsigned long int para Mestre; compatível com int)
    float area;                  // Área em km²
    float pib;                   // PIB em bilhões
    int pontos_turisticos;       // Número de pontos turísticos
    float densidade;             // Calculado: População / Área
    float pib_per_capita;        // Calculado: PIB / População
    float super_poder;           // Calculado no Mestre: Soma de todos + (1 / densidade)
} Carta;

// ============================================
// FUNÇÕES COMUNS A TODOS OS NÍVEIS
// ============================================

/**
 * Cadastra uma carta interativamente via terminal.
 * Lê código, população, área, PIB e pontos turísticos.
 * (Sem condicionais ou loops, conforme regras iniciais).
 */
void cadastrarCarta(Carta *carta) {
    printf("=== CADASTRO DA CARTA ===\n");
    printf("Código da carta (ex: A01): ");
    scanf("%s", carta->codigo);
    printf("População: ");
    scanf("%lu", &carta->populacao);
    printf("Área (km²): ");
    scanf("%f", &carta->area);
    printf("PIB (bilhões): ");
    scanf("%f", &carta->pib);
    printf("Pontos turísticos: ");
    scanf("%d", &carta->pontos_turisticos);
    printf("Cadastro concluído!\n\n");
}

/**
 * Calcula atributos derivados (densidade e PIB per capita).
 * Chama apenas nos níveis Aventureiro e Mestre.
 * Evita divisão por zero com valor mínimo.
 */
void calcularAtributos(Carta *carta) {
    if (carta->area > 0) {
        carta->densidade = (float)carta->populacao / carta->area;
    } else {
        carta->densidade = 0.0f;  // Evita divisão por zero
    }
    if (carta->populacao > 0) {
        carta->pib_per_capita = carta->pib / (float)carta->populacao;
    } else {
        carta->pib_per_capita = 0.0f;
    }
}

/**
 * Calcula o Super Poder: Soma de população + área + PIB + pontos + densidade + pib_per_capita + (1 / densidade).
 * Conversões para float. Evita divisão por zero (se densidade == 0, usa 0).
 * (Usado apenas no Mestre).
 */
void calcularSuperPoder(Carta *carta) {
    float inv_densidade = (carta->densidade > 0) ? 1.0f / carta->densidade : 0.0f;
    carta->super_poder = (float)carta->populacao + carta->area + carta->pib + 
                         (float)carta->pontos_turisticos + carta->densidade + 
                         carta->pib_per_capita + inv_densidade;
}

/**
 * Exibe os detalhes de uma carta de forma organizada.
 * No Novato: Apenas atributos básicos.
 * No Aventureiro+: Inclui calculados.
 * No Mestre: Inclui super_poder.
 * @param carta A struct a ser exibida.
 * @param titulo Título (ex.: "Carta 1").
 * @param nivel O nível atual (1=Novato, 2=Aventureiro, 3=Mestre).
 */
void exibirCarta(const Carta *carta, const char *titulo, int nivel) {
    printf("%s (Código: %s):\n", titulo, carta->codigo);
    printf("  População: %lu\n", carta->populacao);
    printf("  Área: %.2f km²\n", carta->area);
    printf("  PIB: %.2f bilhões\n", carta->pib);
    printf("  Pontos Turísticos: %d\n", carta->pontos_turisticos);
    
    if (nivel >= 2) {  // Aventureiro e Mestre
        printf("  Densidade Populacional: %.2f hab/km²\n", carta->densidade);
        printf("  PIB per Capita: %.2f\n", carta->pib_per_capita);
    }
    
    if (nivel == 3) {  // Mestre
        printf("  Super Poder: %.2f\n\n", carta->super_poder);
    } else {
        printf("\n");
    }
}

// ============================================
// NÍVEL NOVATO: Cadastro básico sem loops/condicionais
// ============================================

/**
 * Nível Novato: Cadastra e exibe 2 cartas básicas.
 * Apenas scanf/printf, sem cálculos extras.
 */
void nivelNovato() {
    Carta carta1, carta2;
    printf("🎮 NÍVEL NOVATO - Cadastro Básico\n\n");
    
    printf("Cadastrando Carta 1...\n");
    cadastrarCarta(&carta1);
    exibirCarta(&carta1, "Carta 1", 1);
    
    printf("Cadastrando Carta 2...\n");
    cadastrarCarta(&carta2);
    exibirCarta(&carta2, "Carta 2", 1);
}

// ============================================
// NÍVEL AVENTUREIRO: Cálculo de atributos sem loops/condicionais
// ============================================

/**
 * Nível Aventureiro: Cadastra 2 cartas, calcula e exibe densidade + PIB per capita.
 */
void nivelAventureiro() {
    Carta carta1, carta2;
    printf("🛡️ NÍVEL AVENTUREIRO - Cálculo de Atributos\n\n");
    
    printf("Cadastrando Carta 1...\n");
    cadastrarCarta(&carta1);
    calcularAtributos(&carta1);
    exibirCarta(&carta1, "Carta 1", 2);
    
    printf("Cadastrando Carta 2...\n");
    cadastrarCarta(&carta2);
    calcularAtributos(&carta2);
    exibirCarta(&carta2, "Carta 2", 2);
}

// ============================================
// NÍVEL MESTRE: Comparação e Super Poder
// ============================================

/**
 * Compara dois atributos entre cartas e exibe vencedor (1 ou 0).
 * Para densidade: menor vence.
 * Para outros: maior vence.
 * @param c1 Carta 1.
 * @param c2 Carta 2.
 * @param tipo_atributo 1=pop, 2=area, 3=pib, 4=pontos, 5=densidade, 6=pib_per_capita, 7=super_poder.
 */
void compararAtributo(const Carta *c1, const Carta *c2, int tipo_atributo) {
    float val1, val2;
    int menorVence = 0;
    const char *nome_atributo;
    
    // Define valores e nome (if simples para Mestre)
    if (tipo_atributo == 1) {
        val1 = (float)c1->populacao;
        val2 = (float)c2->populacao;
        nome_atributo = "População";
    } else if (tipo_atributo == 2) {
        val1 = c1->area;
        val2 = c2->area;
        nome_atributo = "Área";
    } else if (tipo_atributo == 3) {
        val1 = c1->pib;
        val2 = c2->pib;
        nome_atributo = "PIB";
    } else if (tipo_atributo == 4) {
        val1 = (float)c1->pontos_turisticos;
        val2 = (float)c2->pontos_turisticos;
        nome_atributo = "Pontos Turísticos";
    } else if (tipo_atributo == 5) {
        val1 = c1->densidade;
        val2 = c2->densidade;
        nome_atributo = "Densidade Populacional";
        menorVence = 1;  // Menor vence
    } else if (tipo_atributo == 6) {
        val1 = c1->pib_per_capita;
        val2 = c2->pib_per_capita;
        nome_atributo = "PIB per Capita";
    } else {  // 7: Super Poder
        val1 = c1->super_poder;
        val2 = c2->super_poder;
        nome_atributo = "Super Poder";
    }
    
    // Decide vencedor (if simples)
    printf("  %s: ", nome_atributo);
    if (menorVence) {
        if (val1 < val2) {
            printf("1 (Carta 1 vence)\n");
        } else if (val2 < val1) {
            printf("0 (Carta 2 vence)\n");
        } else {
            printf("Empate\n");
        }
    } else {
        if (val1 > val2) {
            printf("1 (Carta 1 vence)\n");
        } else if (val2 > val1) {
            printf("0 (Carta 2 vence)\n");
        } else {
            printf("Empate\n");
        }
    }
}

/**
 * Nível Mestre: Cadastra 2 cartas, calcula tudo, exibe e compara todos os atributos.
 */
void nivelMestre() {
    Carta carta1, carta2;
    printf("🏆 NÍVEL MESTRE - Comparação e Super Poder\n\n");
    
    printf("Cadastrando Carta 1...\n");
    cadastrarCarta(&carta1);
    calcularAtributos(&carta1);
    calcularSuperPoder(&carta1);
    exibirCarta(&carta1, "Carta 1", 3);
    
    printf("Cadastrando Carta 2...\n");
    cadastrarCarta(&carta2);
    calcularAtributos(&carta2);
    calcularSuperPoder(&carta2);
    exibirCarta(&carta2, "Carta 2", 3);
    
    // Comparações atributo a atributo
    printf("=== RESULTADO DAS COMPARAÇÕES ===\n");
    compararAtributo(&carta1, &carta2, 1);  // População
    compararAtributo(&carta1, &carta2, 2);  // Área
    compararAtributo(&carta1, &carta2, 3);  // PIB
    compararAtributo(&carta1, &carta2, 4);  // Pontos
    compararAtributo(&carta1, &carta2, 5);  // Densidade (menor vence)
    compararAtributo(&carta1, &carta2, 6);  // PIB per Capita
    compararAtributo(&carta1, &carta2, 7);  // Super Poder
}

// ============================================
// FUNÇÃO PRINCIPAL: Menu para escolher níveis
// ============================================

int main() {
    int nivel;
    printf("=== DESAFIO SUPER TRUNFO - PAÍSES - CADASTRO DAS CARTAS ===\n");
    printf("Escolha o nível para executar:\n");
    printf("1 - Nível Novato\n");
    printf("2 - Nível Aventureiro\n");
    printf("3 - Nível Mestre\n");
    scanf("%d", &nivel);
    
    // Switch simples para rotear (permitido, pois é estrutura de decisão básica)
    if (nivel == 1) {
        nivelNovato();
    } else if (nivel == 2) {
        nivelAventureiro();
    } else if (nivel == 3) {
        nivelMestre();
    } else {
        printf("Nível inválido! Executando Novato por padrão.\n");
        nivelNovato();
    }
    
    printf("=== Fim do Desafio ===\n");
    return 0;
}
