#include "main.hpp"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <regex>
#include <math.h>
#include "gera_index.cpp"

std::list<Aluno*> alunos;
bool sorted = false;
int removed = 0;

int main()
{
    populate();//read files and populate
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
                // printAll();
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
    std::ifstream infile("index_lista1.txt");
    if (infile) {
        while (std::getline(infile, line)) {
            if(line.size() > 4) {
                // line is now in buffer
                unsigned int id = getUserIdFromLine(line);//get ID
                int pos = getPositionFromLine(line);
                // std::string name = getNameFromLine(line);//get name
                std::cout << id << "~" << pos << std::endl;
                alunos.push_back(new Aluno(id, pos));
            }
        }
    }
    infile.close();

    //Read paper file
    line = "";
    std::ifstream infile2("index_lista2.txt");
    if (infile2) {
        while (std::getline(infile2, line)) {
            if(line.size() > 4) {
                // std::cout << "*" <<line << std::endl;
                unsigned int id = getUserIdFromLine(line);//get ID
                int pos = getPositionFromLine(line);//get name
                int paper = 1;//getPaperIdFromLine(line);//get name
                std::cout << id << "-" << paper << "-" << pos << std::endl;
                for(auto it = alunos.begin(); it != alunos.end(); it++){
                    if ((*it)->getId() == id) {
                        std::pair<int, int> par(paper, pos);
                        (*it)->results.push_front(par);
                    }
                }
            }
        }
    }
    infile2.close();

    line = "";
    std::ifstream infile3("index_lista3.txt");
    if (infile3) {
        while (std::getline(infile3, line)) {
            if(line.size() > 4) {
                // std::cout << "*" <<line << std::endl;
                unsigned int id = getUserIdFromLine(line);//get ID
                int pos = getPositionFromLine(line);//get name
                int paper = 2;//getPaperIdFromLine(line);//get name
                std::cout << id << "-" << paper << "-" << pos << std::endl;
                for(auto it = alunos.begin(); it != alunos.end(); it++){
                    if ((*it)->getId() == id) {
                        std::pair<int, int> par(paper, pos);
                        (*it)->results.push_front(par);
                    }
                }
            }
        }
    }
    infile3.close();
    alunos.sort(Aluno::compare);
    sorted = true;
}
int insertStudent()
{
    //lê entrada do usuario
    printf("Insira o seu nome: ");
    std::string name;
    std::cin >> name;
    std::ostringstream final;
    //checar reg e pegar maior id e incrementar
    unsigned int id = (alunos.size() > 0) ? getHighId() + 1: 0;
    final << "\nID" << std::setfill('0') << std::setw(3) << id;
    final << " 111111 ";
    final << std::left << std::setw(24) << std::setfill(' ') << name << "34    G         AB";

    insertAtEnd("lista1.txt", final.str());
    int pos = 0;
    std::string line;
    std::ifstream myfile("lista1.txt");

    while (std::getline(myfile, line))
        ++pos;
    alunos.push_back(new Aluno(id, pos-1));
    alunos.sort(Aluno::compare);

    readList("lista1.txt");

    //insere ele na lista1
    // alunos.push_front(new Aluno(name, reg));
    // *fp = fopen("lista1.txt","w+");
}

unsigned int getHighId()
{
    if (!sorted) {
        alunos.sort(Aluno::compare);
        sorted = true;
    }
    if(alunos.size())
        return alunos.front()->getId();
}
void printAll()
{
    for(auto it = alunos.begin(); it != alunos.end(); it++){
        unsigned int id = (*it)->getId();
        std::cout << "ID" << std::setfill('0') << std::setw(3) << id << '\t' << getName(id) << std::endl;
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

int getPositionFromLine(std::string const line)
{
    std::string val = line.substr(6,line.size()-6);
    std::string::size_type sz;
    return std::stoi (val,&sz);
}


int removeStudent()
{
    int id;
    std::cout << "Insira o ID do aluno a ser removido(ex: 001):" << std::endl;
    std::cin >> id;
    for(auto it = alunos.begin(); it != alunos.end(); it++) {
        if((*it)->getId() == id) {
            alunos.erase(it);
            break;
        }
    }
}

int gradeStudent()
{
    int id;
    std::list<Aluno*>::iterator al;
    std::cout << "Insira o ID do aluno (ex: 001):" << std::endl;
    std::cin >> id;
    for(auto it = alunos.begin(); it != alunos.end(); it++) {
        al = it;
        if((*it)->getId() == id) {
            break;
        }
    }
    if(al != alunos.end()){
        std::cout << "Insira o id da materia (1 ou 2):" << std::endl;
        int paper;
        std::cin >> paper;
        if (paper == 1 || paper == 2) {
            std::cout << "Insira o a nota(ex: 7.8):" << std::endl;
            float grade;
            std::cin >> grade;
            grade = floorf(grade * 10) / 10;

            std::ostringstream final;
            final << "\nID" << std::setfill('0') << std::setw(3) << id;
            final << "|024312|" << getName(id) << "|";
            final << grade;

            std::string fileName = "lista" + std::to_string(paper+1) + ".txt";
            insertAtEnd(fileName, final.str());
            
            char file[1024];
            strcpy(file, fileName.c_str());
            readList(file);
            

        } else {
            std::cout << "Matéria inválida!" << std::endl;
        }
    } else {
        std::cout << "ID não encontrado." << std::endl;
    }
}

int report()
{
    for(auto it = alunos.begin(); it != alunos.end(); it++) {
        unsigned int id = (*it)->getId();
        std::cout << "ID" << std::setfill('0') << std::setw(3) << id << '\t' << getName(id) << std::endl;
        for(auto it2 = (*it)->results.begin(); it2 != (*it)->results.end(); it2++) {
            std::cout << '\t' <<"Materia: " << (*it2).first << " Nota: " << getGrade((*it2).first, (*it2).second) << std::endl;
        }
    }
}

int search()
{

}

float getGrade(int file, unsigned int pos) {
    if (file == 1) {
        return getGradeFromLine(readNthLine("lista2.txt", pos));
    } else {
        return getGradeFromLine(readNthLine("lista2.txt", pos));
    }
}
std::string getName(unsigned int id)
{
    for(auto it = alunos.begin(); it != alunos.end(); it++) {
        unsigned int auxid = (*it)->getId();
        if (auxid == id) {
            return getNameFromLine(readNthLine("lista1.txt", ((*it)->getPosition())));
        }
    }
    return nullptr;
}
std::string getNameFromLine(std::string buffer){
    std::string nome = buffer.substr(13,24);
    nome = std::regex_replace(nome, std::regex("^ +| +$|( ) +"), "$1");
    return nome;
}

float getGradeFromLine(std::string input) {
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


std::string readNthLine(const std::string& filename, int N)
{
    std::ifstream in(filename.c_str());
    std::string s;
    s.reserve(300);

    //skip N lines
    for(int i = 0; i < N; ++i)
        std::getline(in, s);

    std::getline(in,s);
    return s;
}

void insertAtEnd(const std::string& filename, const std::string& data)
{
   std::ofstream out(filename.c_str(), std::ios::app);
   out << data;
   out.close();
}
