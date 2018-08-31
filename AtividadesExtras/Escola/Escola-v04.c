/* 

Escola-v04.c, 29/08/2018, Autor: Renato Novais

Descrição: esta versão tem:
- lista encadeada

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAM_LISTA_ALUNO 5
#define SUCESSO_CADASTRO 1
#define ERRO_CADASTRO_MATRICULA 2
#define ERRO_CADASTRO_SEXO 3


typedef struct dma {
  int dia;
  int mes;
  int ano; 
} Data; 

/*Criando a struct aluno */
typedef struct dados_aluno
{
  int matricula;
  char nome[50];
  char sexo; //M - Masculino, F - Feminino
  Data data_nascimento;
  char cpf[15];
  struct dados_aluno *prox;
    
} Aluno;

int opcaoMenuPrincipal();
int inserirAluno(Aluno* inicio, int qtd_alunos);
void listarAlunos(Aluno* inicio, int qtd_alunos);
void finalizar(Aluno* inicio, int qtd_alunos);

int main(void)
{    
 
  Aluno aluno; /*Criando a variável aluno que será do tipo struct Ficha_Aluno */
  Aluno* inicioLista = NULL; // 
  int qtd_alunos = 0; // variável para controlar a quantidade de alunos cadastrados

  int opcao, retorno;
  int sair = 0;
  
  while (!sair){
    
    opcao = opcaoMenuPrincipal();
    
    switch(opcao){
      case 0:{
        printf("Finalizando Escola\n");
        sair = 1;
        break;
      }
      case 1: {
        retorno = inserirAluno(inicioLista, qtd_alunos);
        if (retorno == SUCESSO_CADASTRO){
            printf("Cadastro realizado com sucesso\n");
            qtd_alunos++;
        }else{
            switch(retorno) {
                case ERRO_CADASTRO_MATRICULA:{
                    printf("Matrícula Inválida");
                    break;
                }
                case ERRO_CADASTRO_SEXO:{
                    printf("Sexo Inválido");
                    break;
                }
                default:{
                    printf("Erro desconhecido!");
                }
               
            }
           printf("Não foi possível fazer o cadastro\n"); 
            
        }    
        break;
      }
      case 2: {
        listarAlunos(inicioLista, qtd_alunos);
        break;
      }
      default:{
        printf("Opção Inválida\n");
      }
    }
  }

  finalizar(inicioLista, qtd_alunos);
  return 1;

}

int opcaoMenuPrincipal(){
    int opcao;
    printf("Digite a opção:\n");
    printf("0 - Sair\n");
    printf("1 - Inserir Aluno\n");
    printf("2 - Listar Alunos\n");
    scanf("%d",&opcao);
    return opcao;
}


int inserirAlunoNaLista(Aluno* inicio, Aluno* novoAluno){
    Aluno *atual;
    
    if (inicio == NULL)
        inicio = novoAluno;
    else{
        atual = inicio;

        while(atual->prox != NULL)
            atual = atual->prox;
        
        atual->prox = novoAluno;
        
    }
    
    novoAluno->prox = NULL;
    
    
}

int inserirAluno(Aluno* inicio, int qtd_alunos){
    
    //criar o aluno
    Aluno* novoAluno = (Aluno *)malloc(sizeof(Aluno));
    
    inserirAlunoNaLista(inicio, novoAluno);
    inicio = novoAluno;
    
    printf("\n### Cadastro de Aluno ###\n");
    printf("Digite a matrícula: ");
    //scanf("%d", &lista_aluno[qtd_alunos].matricula);
    scanf("%d", &novoAluno->matricula);
    getchar();
    
    if (novoAluno->matricula <= 0) {
        return ERRO_CADASTRO_MATRICULA;
    }    
    
    printf("Digite o nome: ");
    fgets(novoAluno->nome, 50, stdin); 
    /*o fgets é uma das funções mais indicadas para ler string do teclado. 
    Ela controla o tamanho do buffer, e não deixa o buffer com lixo. 
    Entretanto ela guarda o \n ao final da string, por isso é preciso removê-lo, como feito a seguir*/
    size_t ln = strlen(novoAluno->nome) - 1; //size_t = unsigned integer type
    if (novoAluno->nome[ln] == '\n')
        novoAluno->nome[ln] = '\0';
    
    printf("Digite o sexo: ");
    scanf("%c", &novoAluno->sexo);
    
    novoAluno->sexo = toupper(novoAluno->sexo);
    if (novoAluno->sexo != 'M' && novoAluno->sexo != 'F') {
        return ERRO_CADASTRO_SEXO;
    }
    
    /* obs. a data nascimento será recuperada separadamente o dia, mês e ano, 
        mas depois tem que mudar para informar uma string dd/mm/aaaa, e validar a data*/
    printf("Digite o dia de nascimento: ");
    scanf("%d", &novoAluno->data_nascimento.dia);

    printf("Digite o mês de nascimento: ");
    scanf("%d", &novoAluno->data_nascimento.mes);

    printf("Digite o ano de nascimento: ");
    scanf("%d", &novoAluno->data_nascimento.ano);
    getchar();

    printf("Digite o CPF: ");
    fgets(novoAluno->cpf, 15, stdin); 
    ln = strlen(novoAluno->cpf) - 1; 
    if (novoAluno->cpf[ln] == '\n')
        novoAluno->cpf[ln] = '\0';

    printf("\n");
    
    return SUCESSO_CADASTRO;
    
    
}

void listarAlunos(Aluno* inicio, int qtd_alunos){
    printf("\n### Alunos Cadastrasdos ####\n");
    int i;
    Aluno* alunoAtual = inicio;
    if (inicio == NULL){
        printf("Lista Vazia\n");
        
    }else{
    
        do{
            printf("-----\n");
            printf("Matrícula: %d\n", alunoAtual->matricula);
            printf("Nome: %s\n", alunoAtual->nome);
            printf("Sexo: %c\n", alunoAtual->sexo);
            printf("Data Nascimento: %d/%d/%d\n", alunoAtual->data_nascimento.dia, alunoAtual->data_nascimento.mes, alunoAtual->data_nascimento.ano);
            printf("CPF: %s\n", alunoAtual->cpf);
            
            alunoAtual = alunoAtual->prox;

        }while (alunoAtual != NULL);
    }    
    printf("-----\n\n");
}


void finalizar(Aluno* inicio, int qtd_alunos){
    
    Aluno* alunoAtual;
    Aluno* alunoProx;
    
    if (inicio != NULL){
        alunoAtual = inicio;
        do{
            alunoProx = alunoAtual->prox;
            free(alunoAtual);
            alunoAtual = alunoProx;
        }while(alunoAtual != NULL);    
    }
        
}
