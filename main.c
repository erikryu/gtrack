#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXNAMESIZE 20
#define MAXEXERCISENUM 10

typedef struct {
    int maxw;
    char name[MAXNAMESIZE];
} Exercise;

typedef struct {
    int daynum;
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

int listExercises(TrainingDay *td)
{
    int i;
    for (i=0; i<td->exercise_num; ++i)
    {
        printf("%s - %d\n", td->exercises[i].name, td->exercises[i].maxw);
    }

    return 0;
}

int write(FILE *fp, TrainingDay *td)
{
    int i;

    time_t t;
    struct tm tm;

    time(&t);
    localtime_s(&tm, &t);

    char dt[50];

    strftime(dt, sizeof(dt), "%c", &tm);
    fprintf(fp, "%s\n", dt);

    for (i = 0; i < td->exercise_num; ++i)
    {
        fprintf(fp, "%d: %s - %dkg\n",i + 1, td->exercises[i].name, td->exercises[i].maxw);
    }
    fclose(fp);

    return 0;
}

// Implementar o registro em arquivo
// Armazenar hora e data dentro da estrutura TrainingDay
//
// Registro em arquivo pode ser:
//
// day_num = x
// Hora = x.y.z(hr - min - sec) a.b.c(day - month - year)
// nome do exercício - carga máxima

int main(void)
{
    FILE *filepoint;
    TrainingDay tday = {0};

    int error = fopen_s(&filepoint, "example.txt", "w");

    addTrainingDay(&tday);
    listExercises(&tday);

    write(filepoint, &tday);

    return 0;
}