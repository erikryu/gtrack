 #include <stdio.h>
#include <string.h>

#define MAXNAMESIZE 20
#define MAXEXERCISENUM 10

typedef struct {
    int maxw;
    char name[MAXNAMESIZE];
} Exercise;

typedef struct {
    int exercise_num;
    Exercise exercises[MAXEXERCISENUM];
} TrainingDay;

int txt(char *str, int lim)
{
    if (!fgets(str, lim, stdin)) {
        return -1;
    }

    int len = strlen(str);

    if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
    else if (len == lim - 1) while (getchar()!='\n' && getchar()!=EOF);

    return 0;
}

int addExercise(Exercise *ex)
{
    printf("Digite o nome do exercício: ");
    if (txt(ex->name, MAXNAMESIZE)==-1)
    {
        printf("Algo de errado não está certo ao registrar exercícios.");
        return -1;
    }

    printf("Digite a carga máxima do exercício: ");
    if (!scanf_s("%d", &ex->maxw))
    {
        printf("Algo de errado não está certo ao salvar cargas.");
        return -1;
    }

    while (getchar()!='\n');

    return 0;
}

int addTrainingDay(TrainingDay *td)
{
    int i;

    printf("Digite a quantidade de exercícios feitos: ");
    if (scanf_s("%d", &td->exercise_num) != 1 || td->exercise_num < 1 || td->exercise_num > MAXEXERCISENUM)
    {
        printf("Número de exercícios acima do esperado(20)");
        return -1;
    }

    while(getchar()!='\n');

    for (i = 0; i < td->exercise_num; ++i)
    {
        if(addExercise(&td->exercises[i])==-1)
        {
            printf("Erro ao registrar exercício %d\n", i + 1);
            return -1;
        }
    }
    return 0;
}

// Tudo funcionando legal, falta implementar a função de listagem de exercícios
// Também implementar o registro em arquivo
int main(void)
{
    int i;
    TrainingDay tday = {0};

    addTrainingDay(&tday);

    for (i = 0; i < tday.exercise_num; ++i)
    {
        printf("%s - %d\n", tday.exercises[i].name, tday.exercises[i].maxw);
    }
}