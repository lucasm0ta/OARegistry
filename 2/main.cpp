#include "main.hpp"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <regex>

std::list<Aluno*> alns;
bool sorted = false;

int main()
{
    populate();
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
            case 3: //Dar Nota
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

void populate()
{
    std::string line;
    //Read students file
    std::ifstream infile("lista1.txt");
    if (infile) {
        while (std::getline(infile, line)) {
            // line is now in buffer
            unsigned int id = getUserIdFromLine(line);//get ID
            std::string name = getNameFromLine(line);//get name
            // std::cout << id<<"~"<<name << std::endl;
            alns.push_back(new Aluno(name, id));
        }
    }
    infile.close();

    //Read paper file
    std::ifstream infile2("lista2.txt");
    if (infile2) {
        while (std::getline(infile2, line)) {
            // line is now in buffer
            // std::cout << line << std::endl;
            unsigned int id = getUserIdFromLine(line);//get ID
            float res = getGrade(line);//get name
            std::string paper = getPaperIdFromLine(line);//get name
            // std::cout << id << "-" << paper << "-" << res << std::endl;
            for(auto it = alns.begin(); it != alns.end(); it++){
                if ((*it)->getId() == id) {
                    std::pair<std::string, float> par(paper,res);
                    (*it)->results.push_front(par);
                }
            }
            // sorted = false;
        }
    }
    infile2.close();

    std::ifstream infile3("lista3.txt");
    if (infile3) {
        while (std::getline(infile3, line)) {
            // line is now in buffer
            // std::cout << line << std::endl;
            unsigned int id = getUserIdFromLine(line);//get ID
            float res = getGrade(line);//get name
            std::string paper = getPaperIdFromLine(line);//get name
            // std::cout << id << "-" << paper << "-" << res << std::endl;
            for(auto it = alns.begin(); it != alns.end(); it++){
                if ((*it)->getId() == id) {
                    std::pair<std::string, float> par(paper,res);
                    (*it)->results.push_front(par);
                }
            }
            // sorted = false;
        }
    }
    infile3.close();
    alns.sort(Aluno::compare);
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
    alns.push_front(new Aluno(name, reg));
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
        std::cout << "ID" << std::setfill('0') << std::setw(3) << (*it)->getId() << '\t' << (*it)->getName() << std::endl;
    }
}

unsigned int getUserIdFromLine(std::string const buffer)
{
    std::string val = buffer.substr(2, 3);
    std::string::size_type sz;
    int final = std::stoi (val,&sz);
    return (unsigned int) final;
}

std::string getPaperIdFromLine(std::string const input)
{
    std::istringstream iss(input);
    std::string token,ret;
    int i = 0;
    while (std::getline(iss, token, '|') && i < 2)
    {
        ret = token;
        i++;
    }
    return ret;
}

int removeStudent()
{

}

int gradeStudent()
{

}

int report()
{
    for(auto it = alns.begin(); it != alns.end(); it++) {
        std::cout << "ID" << std::setfill('0') << std::setw(3) << (*it)->getId() << '\t' << (*it)->getName() << std::endl;
        for(auto it2 = (*it)->results.begin(); it2 != (*it)->results.end(); it2++) {
            std::cout << '\t' <<"Materia: " << (*it2).first << " Nota: " <<(*it2).second<<std::endl;
        }
    }
}

int search()
{

}

std::string getNameFromLine(std::string buffer){
    std::string nome = buffer.substr(13,24);
    nome = std::regex_replace(nome, std::regex("^ +| +$|( ) +"), "$1");
    return nome;
}

float getGrade(std::string const &input) {
    std::istringstream iss(input);
    std::string token,ret;
    while (std::getline(iss, token, '|'))
    {
        ret = token;
    }
    if(ret.size() > 0) {
        std::size_t found = ret.find(",");
        if (found != std::string::npos)
            ret.replace(found, 1, ".");
    }
    return std::stof(ret);
}
