#include "aluno.hpp"
#include <list>

void populate();

//insert student in registry file
int insertStudent();

/*O	 programa deve simplesmente colocar -1 na posição da NRR no arquivo	 de	 índice	 primários. O programa deve incrementar a quantidade de arquivos apagados no arquivo de	índices	primário. Caso existir mais de 5 registros apagados, o programa	deve	então	apagar
todos	 as	 entradas	 nos	 arquivos	 benchmarks	 (lista1.txt,	 lista2.txt	 e	 lista3.txt)	 referentes	 aos	 registros
apagados	e	refazer	os	arquivos	de	índice	(chamando	o	programa	'gera_index'	já	implementado).*/
int removeStudent();

int gradeStudent();

int report();

int search();

//Get heighest id in the registry file
unsigned int getHighId();

unsigned int getIdFromLine(std::string buffer);

std::string getNameFromLine(std::string buffer);

void printAll();
