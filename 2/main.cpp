#include "main.h"

int main()
{
    int flag = 1;
    while (flag) {
        int input = 0;
        printf("1. Inserir novo aluno na UnB\n2. Jubilar um aluno da UnB\n
                3. Dar nota ao aluno numa disciplina\n4. Relatório\n5. Buscar\n6. Sair\n");
        scanf("%d", &input);
        switch (input) {
            case 1: //Inserir
                insertStudent()
                break;
            case 2: //Jubilar
                removeStudent();
                break;
            case 3: //Dar Note
                gradeStudent();
                break;
            case 4: //Relatório
                report();
                break;
            case 5: //Buscar
                search();
                break;
            case 6: //Sair
                flag = 0;
                break;
            default:
                printf("Entrada inválida\n");
                break;
        }
    }
    return 0;
}
