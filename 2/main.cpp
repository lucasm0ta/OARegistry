#include "main.hpp"
#include <stdio.h>
#include <iostream>

std::list<Aluno*> alns;
bool sorted = false;

int main()
{
    int flag = 1;
    while (flag) {
        int input = 0;
        printf("1. Inserir novo aluno na UnB\n2. Jubilar um aluno da UnB\n"
               "3. Dar nota ao aluno numa disciplina\n4. Relatório\n5. Buscar\n6. Sair\n");
        scanf("%d", &input);
        switch (input) {
            case 1: //Inserir
                insertStudent();
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
                printAll();
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

std::list<Aluno> populate()
{
    int c, pos, size = 1024;
    char *buffer = (char *)malloc(size);
    FILE *fp = fopen("lista1.txt","w+");
    do { // read all lines in file
        pos = 0;
        do{ // read one line
            c = fgetc(fp);
            if(c != EOF) buffer[pos++] = (char)c;
            if(pos >= size - 1) { // increase buffer length - leave room for 0
                size *=2;
                buffer = (char*)realloc(buffer, size);
            }
        }while(c != EOF && c != '\n');
        buffer[pos] = 0;
        // line is now in buffer
        std::string buff(buffer);
        unsigned int id = getIdFromLine(buff);//get ID
        std::string name = getNameFromLine(buff);//get name
        alns.push_back(new Aluno(name, id));
        sorted = false;
    } while(c != EOF);
}
int insertStudent()
{
    //lê entrada do usuario
    printf("Insira o seu nome: ");
    std::string name;
    std::cin >> name;
    //checar reg e pegar maior id e incrementar
    unsigned int reg = (alns.size()>0) ? getHighId() + 1: 0;

    //insere ele na lista1
    alns.push_back(new Aluno(name, reg));
    // *fp = fopen("lista1.txt","w+");
}

unsigned int getHighId()
{
    if (!sorted) {
        alns.sort(Aluno::compare);
        sorted = true;
    }
    if(alns.size())
    return alns.front()->getId();
}
void printAll()
{
    for(auto it = alns.begin(); it != alns.end(); it++){
        std::cout << "ID" << (*it)->getId() << '\t' << (*it)->getName() << std::endl;
    }
}

unsigned int getIdFromLine(std::string buffer)
{
    std::string val = buffer.substr(2, 3);
    std::string::size_type sz;
    int final = std::stoi (val,&sz);
    return (unsigned int) final;
}

int removeStudent()
{

}

int gradeStudent()
{

}

int report()
{

}

int search()
{

}

std::string getNameFromLine(std::string buffer){

}
