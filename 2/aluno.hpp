#include <string>
#include <list>
#include <utility>

class Aluno{
private:
    unsigned int _id;
    int _pos;

public:
    //Uma lista de pares<Materia, position>
    std::list<std::pair<int, int>> results;
    //construtor
    Aluno(int pos);

    Aluno(unsigned int id);

    Aluno(unsigned int id, int pos);

    ~Aluno();

    //retorna o nome do
    int getPosition()
    {
        return _pos;
    }

    //retorn o id
    unsigned int getId()
    {
        return _id;
    }
    //compara os alunos
    static bool compare(Aluno *a1, Aluno *a2);

    static std::string getName(unsigned int id);

    int getPaperPosition(int paper);
};
