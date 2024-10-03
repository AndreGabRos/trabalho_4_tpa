#include "arvore_binaria_vetor.h"
#include <stdio.h>
#include <string.h>


int main() {
  int opcao;
  ArvoreBinaria arvore = criar_arvore();
  Aluno aluno;
  int opcao_imprimir = 0;
  int matricula = 0;

  ler_dados_do_arquivo(&arvore, TAMANHO_VETOR);

  do {
    printf("\nMenu:\n");
    printf("1. Inserir novo aluno\n");
    printf("2. Remover aluno\n");
    printf("3. Buscar aluno\n");
    printf("4. Salvar base de dados\n");
    printf("5. Imprimir alunos\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      cadastrar_aluno(&arvore, criar_aluno(), TAMANHO_VETOR);
      break;
    case 2:
      printf("Qual aluno deseja remover: ");
      scanf("%d", &matricula);
      remover_aluno(&arvore, matricula);
      break;

    case 3:
      buscar_aluno(arvore);
      break;
    case 4:
      salvar_arvore_arquivo(&arvore);
      break;

    case 5:
      imprimir_alunos(&arvore);
      break;

    case 0:
      printf("Saindo...\n");
      break;

    default:
      printf("Opcao invalida. Tente novamente.\n");
    }
  } while (opcao != 0);
  printf("Teste: %d\n", arvore.alunos[0].aluno.matricula);
  printf("Teste: %d\n", arvore.alunos[2].aluno.matricula);
}

ArvoreBinaria criar_arvore() {
  ArvoreBinaria arvore;
  arvore.quantidade_elementos = 0;

  return arvore;
}

void cadastrar_aluno(ArvoreBinaria *arvore, Aluno aluno, int tamanho_do_vetor) {
  if (pesquisar(arvore, aluno.matricula, tamanho_do_vetor) != -1) {
    printf("Aluno ja cadastrado.\n");
    return;
  }

  if (aluno.matricula < 0) {
    printf("Matricula invalida.\n");
    return;
  }


  int posicao_no = 0; // Começamos pela raiz da árvore
  while (1)           // Loop até encontrar uma posição livre
  {
    if (posicao_no >= tamanho_do_vetor) {
      printf("Árvore cheia. Não é possível inserir mais alunos.\n");
      return;
    }

    if (arvore->alunos[posicao_no].flag == 0) // Se a posição está livre
    {
      inserir_aluno(arvore, aluno, posicao_no);
      printf("Aluno inserido com sucesso.\n");
      return;
    }

    // Decide se deve ir para a esquerda ou direita
    if (aluno.matricula < arvore->alunos[posicao_no].aluno.matricula) {
      posicao_no = 2 * posicao_no + 1; // Filho esquerdo
    } else {
      posicao_no = 2 * posicao_no + 2; // Filho direito
    }
  }
}

void inserir_aluno(ArvoreBinaria *arvore, Aluno aluno, int posicao_no) {
  arvore->alunos[posicao_no].flag = 1;
  arvore->alunos[posicao_no].aluno.matricula = aluno.matricula;
  strcpy(arvore->alunos[posicao_no].aluno.nome, aluno.nome);
  return;
}

Aluno criar_aluno() {
  Aluno aluno;
  printf("Digite a matricula: ");
  scanf("%d", &aluno.matricula);
  getchar();

  printf("Digite o nome: ");
  scanf(" %[^\n]", aluno.nome); // Le string com espacos
  getchar();

  return aluno;
}

int validar_aluno(ArvoreBinaria *arvore, Aluno aluno, int tamanho_do_vetor) {
  if (pesquisar(arvore, aluno.matricula, tamanho_do_vetor) != -1) {
    printf("Elemento ja inserido.\n");
    return -1;
  }

  return 0;
}

int pesquisar(ArvoreBinaria *arvore, int matricula, int tamanho_do_vetor) {
  int pos_elemento = 0;
  while (pos_elemento < tamanho_do_vetor) {
    if (arvore->alunos[pos_elemento].flag == 0) { // Elemento nao encontrado
      return -1;
    }
    if (matricula == arvore->alunos[pos_elemento].aluno.matricula) {
      return pos_elemento;
    } else if (matricula > arvore->alunos[pos_elemento].aluno.matricula) {
      pos_elemento = 2 * pos_elemento + 2;
    } else {
      pos_elemento = 2 * pos_elemento + 1;
    }
  }

  return -1;
}

void buscar_aluno(ArvoreBinaria arvore) {
  int matricula;
  printf("Digite a matricula: ");
  scanf("%d", &matricula);

  if (pesquisar(&arvore, matricula, 100) != -1) {
    printf("Aluno encontrado.\n");
  } else {
    printf("Aluno nao encontrado.\n");
  }
}

void remover_no_folha(ArvoreBinaria *arvore, int posicao_elemento) {
    arvore->alunos[posicao_elemento].flag = 0;
    arvore->quantidade_elementos--;
    printf("Aluno removido (nó folha).\n");
}

void remover_no_com_um_filho_direito(ArvoreBinaria *arvore, int posicao_elemento) {
  int filho_direito = posicao_elemento * 2 + 2;

  arvore->alunos[posicao_elemento] = arvore->alunos[filho_direito];
  arvore->alunos[filho_direito].flag = 0; // Marca o nó como removido
  arvore->quantidade_elementos--;

  printf("Aluno removido e substituído pelo filho direito.\n");
}

void remover_no_com_um_filho_esquerdo(ArvoreBinaria *arvore, int posicao_elemento) {
  int filho_esquerdo = posicao_elemento * 2 + 1;

  arvore->alunos[posicao_elemento] = arvore->alunos[filho_esquerdo];
  arvore->alunos[filho_esquerdo].flag = 0; // Marca o nó como removido
  arvore->quantidade_elementos--;

  printf("Aluno removido e substituído pelo filho esquerdo.\n");
}

void remover_no_com_dois_filhos(ArvoreBinaria *arvore, int posicao_elemento) {
  int filho_direito = posicao_elemento * 2 + 2;
  // Encontra o sucessor (menor nó da subárvore direita)
  int sucessor = filho_direito;
  int pai_sucessor = posicao_elemento; // Pai do sucessor para remanejar se necessário

  // Percorre à esquerda até encontrar o sucessor (o menor valor na subárvore direita)
  while (2 * sucessor + 1 < TAMANHO_VETOR && arvore->alunos[2 * sucessor + 1].flag == 1) {
    pai_sucessor = sucessor; // Guarda o pai do sucessor
    sucessor = 2 * sucessor + 1;
  }

  // Substitui o nó pela matrícula e nome do sucessor
  arvore->alunos[posicao_elemento] = arvore->alunos[sucessor];

  // Verifica o filho direito do sucessor (se existir)
  int filho_direito_sucessor = 2 * sucessor + 2;
  if (filho_direito_sucessor < 100 && arvore->alunos[filho_direito_sucessor].flag == 1) {

    // Se o sucessor tiver um filho à direita, conectamos o pai do sucessor ao filho direito do sucessor
    if (pai_sucessor == posicao_elemento) {
      // Se o sucessor era filho direto do nó a ser removido, o filho direito do sucessor toma o lugar do sucessor
      arvore->alunos[sucessor] = arvore->alunos[filho_direito_sucessor];
    } else {
      // Caso contrário, o filho esquerdo do pai do sucessor deve apontar para o filho direito do sucessor
      arvore->alunos[2 * pai_sucessor + 1] = arvore->alunos[filho_direito_sucessor];
    }

  }

  // Marca o nó do sucessor original como removido
  arvore->alunos[sucessor].flag = 0;

  printf("Aluno removido e substituído pelo sucessor.\n");

}

void remover_aluno(ArvoreBinaria *arvore, int matricula) {
  int pos = pesquisar(arvore, matricula, TAMANHO_VETOR); // Encontra a posição do aluno
  if (pos == -1) {
    printf("Aluno não encontrado.\n");
    return;
  }

  // Verifica se é uma folha
  int filho_esquerdo = 2 * pos + 1;
  int filho_direito = 2 * pos + 2;

  // Caso 1: Nó folha
  if ((filho_esquerdo >= TAMANHO_VETOR || arvore->alunos[filho_esquerdo].flag == 0) && (filho_direito >= TAMANHO_VETOR || arvore->alunos[filho_direito].flag == 0)) {
    remover_no_folha(arvore, pos);
  }

  // Caso 2: Nó com um filho
  else if ((filho_esquerdo < TAMANHO_VETOR && arvore->alunos[filho_esquerdo].flag == 1) && (filho_direito >= TAMANHO_VETOR || arvore->alunos[filho_direito].flag == 0)) {
    remover_no_com_um_filho_esquerdo(arvore, pos);
  } else if ((filho_direito < 100 && arvore->alunos[filho_direito].flag == 1) && (filho_esquerdo >= 100 || arvore->alunos[filho_esquerdo].flag == 0)) {
    remover_no_com_um_filho_direito(arvore, pos);
  }

  // Caso 3: Nó com dois filhos
  else if (filho_esquerdo < 100 && filho_direito < 100 && arvore->alunos[filho_esquerdo].flag == 1 && arvore->alunos[filho_direito].flag == 1) {
    remover_no_com_dois_filhos(arvore, pos);
  }
}

void imprimir_em_ordem(ArvoreBinaria *arvore, int pos) {
  if (pos < 100 && arvore->alunos[pos].flag == 1) {
    // Chama recursivamente para o filho esquerdo
    imprimir_em_ordem(arvore, 2 * pos + 1);

    // Imprime o aluno na posição atual
    printf("Matrícula: %d, Nome: %s\n", arvore->alunos[pos].aluno.matricula,
           arvore->alunos[pos].aluno.nome);

    // Chama recursivamente para o filho direito
    imprimir_em_ordem(arvore, 2 * pos + 2);
  }
}

void imprimir_alunos(ArvoreBinaria *arvore) {
  printf("Lista de alunos:\n");
  imprimir_em_ordem(arvore, 0);
}

void salvar_arvore_arquivo(ArvoreBinaria *arvore) {
  FILE *file = fopen("arquivo.txt", "w");
  if (file == NULL) {
      printf("Erro ao abrir o arquivo para salvar.\n");
      return;
  }

  printf("quantidade de elementos: %d\n", arvore->quantidade_elementos);
  
  for (int i = 0; i < 100; i++) {  // Percorre todo o vetor
      if (arvore->alunos[i].flag == 1) {  // Verifica se o aluno está ativo
          fprintf(file, "%s\n%d\n", arvore->alunos[i].aluno.nome, arvore->alunos[i].aluno.matricula);
      }
  }

  fclose(file);
  printf("Arvore salva com sucesso.\n");
}

void ler_dados_do_arquivo(ArvoreBinaria *arvore, int tamanho_do_vetor) {
  FILE *file = fopen("./arquivo.txt", "r");
  if (file == NULL) {
      printf("Erro ao abrir o arquivo para leitura.\n");
      return;
  }

  char nome[50];
  int matricula;

  while (!feof(file)) { 
    fscanf(file, " %[^\n]", nome);
    fscanf(file, "%d\n", &matricula);

    Aluno aluno;
    strcpy(aluno.nome, nome);
    aluno.matricula = matricula;

    printf("b\n");
    cadastrar_aluno(arvore, aluno, tamanho_do_vetor);
  }

  fclose(file);
  printf("Arquivo carregado com sucesso.\n");
}
