#include "arvore_binaria_vetor.h"
#include <stdio.h>
#include <string.h>

int main() {
  int opcao;
  int tamanho_do_vetor = 100;
  ArvoreBinaria arvore = criar_arvore();
  Aluno aluno;
  printf("quantidade: %d\n", arvore.quantidade_elementos);

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

      if (cadastrar_aluno(&arvore, criar_aluno(), tamanho_do_vetor) != -1) {
        printf("Aluno inserido com sucesso!\n");
      } else {
        printf("Falha ao inserir aluno.\n");
      }
      break;

    case 2:
      // printf("Digite a matricula do aluno a remover: ");
      // scanf("%d", &matricula);
      // removerAluno(&arvore, matricula);
      break;

    case 3:
      buscar_aluno(arvore);
      break;
    case 4:
      // salvarBaseDados(&arvore);
      break;

    case 5:
      // imprimirAlunos(&arvore);
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

int cadastrar_aluno(ArvoreBinaria *arvore, Aluno aluno, int tamanho_do_vetor) {
  if (verificar_aluno(arvore, aluno, tamanho_do_vetor) == -1) {
    printf("Aluno ja cadastrado.\n");
    return -1;
  }

  int posicao_no = 0;
  while (posicao_no != -1) {
    if (posicao_no >= tamanho_do_vetor) {
      return -1;
    }
    if (arvore->alunos[posicao_no].flag == 0) {
      inserir_aluno(arvore, aluno, posicao_no);
      posicao_no = -1;
    }

    if (aluno.matricula < arvore->alunos[posicao_no].aluno.matricula) {
      posicao_no = 2 * posicao_no + 1;
    } else {
      posicao_no = 2 * posicao_no + 2;
    }
  }

  arvore->alunos[arvore->quantidade_elementos].aluno = aluno;
  arvore->quantidade_elementos++;

  return arvore->quantidade_elementos;
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

int verificar_aluno(ArvoreBinaria *arvore, Aluno aluno, int tamanho_do_vetor) {
  if (pesquisar(arvore, aluno.matricula, tamanho_do_vetor) != -1) {
    printf("Elemento ja inserido.\n");
    return -1;
  }

  return 0;
}

int pesquisar(ArvoreBinaria *arvore, int matricula, int tamanho_do_vetor) {
  int pos_elemento = 0;
  while (pos_elemento < tamanho_do_vetor && pos_elemento != -1) {
    if (arvore->alunos[pos_elemento].flag == 0) { // Elemento nao encontrado
      pos_elemento = -1;
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

// Remover um elemento é basicamente
int remover_no_sem_filho(ArvoreBinaria *arvore, int posicao_elemento) {
  arvore->alunos[posicao_elemento].flag = 0;
  arvore->quantidade_elementos--;

  return 0;
}
