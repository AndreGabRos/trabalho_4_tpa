typedef struct Aluno {
  int matricula;
  char nome[50];
} Aluno;

typedef struct NoAluno {
  Aluno aluno;
  int flag;
} NoAluno;

typedef struct ArvoreBinaria {
  NoAluno alunos[100];
  int quantidade_elementos;
} ArvoreBinaria;

ArvoreBinaria criar_arvore();

int cadastrar_aluno(ArvoreBinaria *arvore, Aluno aluno, int tamanho_do_vetor);
void inserir_aluno(ArvoreBinaria *arvore, Aluno aluno, int posicao_no);
Aluno criar_aluno();

int pesquisar(ArvoreBinaria *arvore, int matricula, int tamanho_do_vetor);
void buscar_aluno(ArvoreBinaria arvore);
int verificar_aluno(ArvoreBinaria *arvore, Aluno aluno, int tamanho_do_vetor);

int remover_no_sem_filho(ArvoreBinaria *arvore, int posicao_elemento);
