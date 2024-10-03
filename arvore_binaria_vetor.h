const int TAMANHO_VETOR = 200;

typedef struct Aluno {
  int matricula;
  char nome[50];
} Aluno;

typedef struct NoAluno {
  Aluno aluno;
  int flag;
} NoAluno;

typedef struct ArvoreBinaria {
  NoAluno alunos[200];
  int quantidade_elementos;
} ArvoreBinaria;


ArvoreBinaria criar_arvore();

void cadastrar_aluno(ArvoreBinaria *arvore, Aluno aluno, int tamanho_do_vetor);
void inserir_aluno(ArvoreBinaria *arvore, Aluno aluno, int posicao_no);
Aluno criar_aluno();

int pesquisar(ArvoreBinaria *arvore, int matricula, int tamanho_do_vetor);
void buscar_aluno(ArvoreBinaria arvore);
int verificar_aluno(ArvoreBinaria *arvore, Aluno aluno, int tamanho_do_vetor);
void imprimir_alunos(ArvoreBinaria *arvore);
void imprimir_em_ordem(ArvoreBinaria *arvore, int pos);
void imprimir_array_alunos(ArvoreBinaria *arvore);
void salvar_arvore(ArvoreBinaria *arvore);


// FUNÇÕES DE REMOÇÃO
void remover_aluno(ArvoreBinaria *arvore, int matricula);
void remover_no_folha(ArvoreBinaria *arvore, int posicao_elemento);
void remover_no_com_um_filho_direito(ArvoreBinaria *arvore, int posicao_elemento);
void remover_no_com_um_filho_esquerdo(ArvoreBinaria *arvore, int posicao_elemento);
void remover_no_com_dois_filhos(ArvoreBinaria *arvore, int posicao_elemento);
