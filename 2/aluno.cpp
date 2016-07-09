#include "aluno.hpp"

//construtor
Aluno::Aluno(int pos)
{
    _pos = pos;
}

Aluno::Aluno(unsigned int id){
    _id = id;
}

Aluno::Aluno(unsigned int id, int pos)
{
    _pos = pos;
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

int Aluno::getPaperPosition(int paper)
{
    for(auto it = results.begin(); it != results.end(); it++){
        if((*it).first == paper)
            return (*it).second;
    }
    return -1;
}
