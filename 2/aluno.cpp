#include "aluno.hpp"

//construtor
Aluno::Aluno(std::string nome)
{
    _nome = nome;
    //seta id como maior
}
Aluno::Aluno(std::string nome, unsigned int id)
{
    _nome = nome;
    _id = id;
}

//retorna o nome do
std::string Aluno::getName()
{
    return _nome;
}

//retorna o id
unsigned int Aluno::getId()
{
    return _id;
}

bool Aluno::compare(Aluno *a1, Aluno *a2)
{
    if (a1->getId() > a2->getId()) {
        return true;
    } else {
        return false;
    }
}
