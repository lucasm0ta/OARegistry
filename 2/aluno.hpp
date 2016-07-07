#include <string>
class Aluno{
private:
    unsigned int _id;
    std::string _nome;
public:
    //construtor
    Aluno(std::string nome);

    Aluno(std::string nome, unsigned int id);

    ~Aluno();

    //retorna o nome do
    std::string getName();

    //retorn o id
    unsigned int getId();

    //compara os alunos
    static bool compare(Aluno *a1, Aluno *a2);
};
