#include <string>
#include <list>
#include <utility>

class Aluno{
private:
    unsigned int _id;
    std::string _name;

    //Uma lista de pares<Materia, Nota>
public:
    std::list<std::pair<std::string, float>> results;
    //construtor
    Aluno(std::string name);

    Aluno(std::string name, unsigned int id);

    ~Aluno();

    //retorna o nome do
    std::string getName()
    {
        return _name;
    }


    //retorn o id
    unsigned int getId()
    {
        return _id;
    }
    //compara os alunos
    static bool compare(Aluno *a1, Aluno *a2);
};
