#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 100
typedef struct _aluno
{
    unsigned int matricula;
    char nome[30];
    double nota1;
    double nota2;
    double media;
} Aluno;

//"Construtor" para aluno.
Aluno *criarAluno(int matricula, char *nome, double nota1, double nota2)
{
    Aluno *aluno = calloc(1, sizeof(Aluno));
    aluno->matricula = matricula;
    strcpy(aluno->nome, nome);
    aluno->nota1 = nota1;
    aluno->nota2 = nota2;
    aluno->media = (nota1 + nota2) / 2;
    return aluno;
}

Aluno *consultarAlunoPorMatricula(Aluno **alunos, int numAlunos, int matricula)
{
    for (int i = 0; i < numAlunos; i++)
    {
        if (alunos[i]->matricula == matricula)
        {
            return alunos[i];
        }
    }
    return NULL;
}

void deletarAluno(Aluno *aluno)
{
    free(aluno);
}

void deletarAlunoPorMatricula(Aluno **alunos, int *numAlunos, int matricula)
{
    for (int i = 0; i < *numAlunos; i++)
    {
        if (alunos[i]->matricula == matricula)
        {
            deletarAluno(alunos[i]);
            // Move os alunos restantes para preencher o espaço vazio
            for (int j = i; j < *numAlunos - 1; j++)
            {
                alunos[j] = alunos[j + 1];
            }
            (*numAlunos)--;
            printf("Aluno com matricula %d deletado.\n", matricula);
            return;
        }
    }
    printf("Aluno com matricula %d nao encontrado.\n", matricula);
}

void mostrarAluno(const Aluno *aluno)
{
    printf("Matricula: %d\n", aluno->matricula);
    printf("Nome: %s\n", aluno->nome);
    printf("Primeira nota: %.2lf\n", aluno->nota1);
    printf("Segunda nota: %.2lf\n", aluno->nota2);
    printf("Media: %.2lf\n", aluno->media);
}

int main()
{
    Aluno **alunos = malloc(MAX_ALUNOS * sizeof(struct Aluno *));
    int numAlunos = 0;
    int matricula;
    char nome[30];
    double nota1;
    double nota2;
    int op;
    do
    {
        printf("[1] - Adicionar aluno.\n[2] - Deletar aluno.\n[3] - Consultar aluno.\n");
        printf("Digite a sua opcao: ");
        scanf("%d", &op);
        system("cls");
        switch (op)
        {
        case 1:
            printf("===== Adicionar aluno =====\n");
            printf("Digite a matricula do aluno: ");
            scanf("%d", &matricula);
            printf("Digite o nome do aluno: ");
            scanf("%s", &nome);
            printf("Digite a primeira nota do aluno: ");
            scanf("%lf", &nota1);
            printf("Digite a segunda nota do aluno: ");
            scanf("%lf", &nota2);

            Aluno *aluno = criarAluno(matricula, nome, nota1, nota2);
            alunos[numAlunos++] = aluno;
            printf("ALUNO CRIADO COM SUCESSO.\n");
            printf("DIGITE QUALQUER TECLADA PARA O MENU ANTERIOR.\n");
            getchar();
            break;

        case 2:
            printf("Digite a matrícula do aluno a ser deletado: ");
            scanf("%d", &matricula);
            deletarAlunoPorMatricula(alunos, &numAlunos, matricula);
            printf("DIGITE QUALQUER TECLADA PARA O MENU ANTERIOR.\n");
            getchar();
            break;

        case 3:
            printf("Digite a matricula do aluno a ser consultado: ");
            scanf("%d", &matricula);
            Aluno *alunoConsulta = consultarAlunoPorMatricula(alunos, numAlunos, matricula);
            if (alunoConsulta != NULL)
            {
                mostrarAluno(alunoConsulta);
            }
            else
            {
                printf("Aluno com matricula %d nao encontrado.\n", matricula);
            }
            printf("DIGITE QUALQUER TECLADA PARA O MENU ANTERIOR.\n");
            getchar();
            break;

        case 0:
            printf("Finalizando o programa");
            break;

        default:
            printf("Opcao invalida, tente novamente.");
            break;
        }
        getchar();
        system("cls");
    } while (op != 0);

    return 0;
}