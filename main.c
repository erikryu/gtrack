#include <stdio.h>
#include <string.h>

#define MAXNAMESIZE 20

typedef struct {
    int maxw;
    char name[MAXNAMESIZE];
} Exercise;

typedef struct {
    int exercise_num;
    Exercise exercises[2];
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
    txt(ex->name, MAXNAMESIZE);

    printf("Digite a carga máxima do exercício: ");
    scanf_s("%d", &ex->maxw);

    while (getchar()!='\n');

    return 0;
}

int main(void)
{
    TrainingDay tday = {0};

    addExercise(&tday.exercises[0]);
    addExercise(&tday.exercises[1]);

    printf("%s %d\n", tday.exercises[0].name, tday.exercises[0].maxw);
    printf("%s %d", tday.exercises[1].name, tday.exercises[1].maxw);
}