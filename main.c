#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Define os limites de tamanho de nome de arquivo e de número de exercícios
#define MAXNAMESIZE 20
#define MAXEXERCISENUM 10

//Define a estrutura básica de um exercício
typedef struct {
    int maxw;
    char name[MAXNAMESIZE];
} Exercise;

//Estrutura de um dia de treino, número de exercícios e quais exercícios foram feitos
typedef struct {
    int exercise_num;
    Exercise exercises[MAXEXERCISENUM];
} TrainingDay;

int txt(char *str, int lim)
{
    int c;
    //Função de entrada de texto
    if (!fgets(str, lim, stdin)) {
        return -1;
    }

    int len = strlen(str);

    if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
    else if (len == lim - 1) while ((c=getchar())!='\n' && c!=EOF);

    return 0;
}

int addExercise(Exercise *ex)
{
    //Função que adiciona grava exercícios
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
    //Utiliza da gravação de exercícios para gravar todos os exercícios de um dia de treino
    int i;

    printf("Digite a quantidade de exercícios feitos: ");
    if (scanf_s("%d", &td->exercise_num) != 1 || td->exercise_num < 1 || td->exercise_num > MAXEXERCISENUM)
    {
        printf("Número de exercícios acima do esperado(10)");
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
    //Lista exercícios do dia de treino
    int i;
    for (i=0; i<td->exercise_num; ++i)
    {
        printf("%s - %d\n", td->exercises[i].name, td->exercises[i].maxw);
    }

    return 0;
}

int write(TrainingDay *td)
{
    //Escreve o dia de treino dentro de um arquivo junto com a data e hora em que foi escrito
    int i;
    FILE *fp;

    time_t t;
    struct tm tm;

    time(&t);
    localtime_s(&tm, &t);

    char dt[50];
    int error = fopen_s(&fp, "example.txt", "a");

    if (error==0) {
        strftime(dt, sizeof(dt), "%c", &tm);
        fprintf(fp, "%s\n", dt);

        for (i = 0; i < td->exercise_num; ++i)
        {
            fprintf(fp, "%d: %s - %dkg\n",i + 1, td->exercises[i].name, td->exercises[i].maxw);
        }
        fprintf(fp, "\n");
        fclose(fp);

    return 0;
    } else return -1;
}

int main(void)
{
    TrainingDay tday = {0};
    int r;

    do {
        system("cls");
        printf("\n---------------|Bem-Vindo ao GymTrack|---------------\n");
        printf("--------------- 1. Adicionar         |---------------\n");
        printf("--------------- 2. Remover         |---------------\n");
        printf("--------------- 3. Listar         |---------------\n");
        printf("--------------- 4. Sair         |---------------\n");

        printf("Digite a opção escolhida: ");
        if (scanf_s("%d", &r) != 1)
        {
            while (getchar()!='\n');
            continue;
        }

        switch (r) {
            case 1:
                system("cls");
                if (addTrainingDay(&tday)==0)
                {
                    write(&tday);
                }
                break;

            case 2:
                break;

            case 3:
                system("cls");
                listExercises(&tday);
                break;

            case 4:
                break;
        
        }
    } while (r!=4);
    
    return 0;
}