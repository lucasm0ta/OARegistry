#include "aluno.hpp"

//construtor
Aluno::Aluno(std::string nome)
{
    _name = nome;
    //seta id como maior
}
Aluno::Aluno(std::string nome, unsigned int id)
{
    _name = nome;
    _id = id;
}

bool Aluno::compare(Aluno *a1, Aluno *a2)
{
    if (a1->getId() > a2->getId()) {
        return true;
    } else {
        return false;
    }
}
