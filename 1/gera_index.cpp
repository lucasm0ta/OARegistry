#include <iostream>
#include <fstream>

// int writetoFile(std:string filename, std::string key, int reference)
// {
// 	using namespace std;
// 	string line;
// 	vector<string> key;
//
// 	oftream outfile;
// 	outfile.open(nomesaida.c_str());
// 	outfile.close();
// }

struct node {
  std::string key;
  int pos;
  node *next;
};

int readList(char* argv)
{
	using namespace std;
	int i, j;
	string line, nomesaida;

	node *root;
	root = new node;
	root->key = "0";
	root->next = 0;
	root->pos = 0;

	node *cur;
	cur = root;

	node* newnode;

	nomesaida = "index_";
	nomesaida.append(argv);
	cout << nomesaida << endl;

	ifstream infile;
	ofstream outfile;

	infile.open(argv);
	i = 0;
	while(getline(infile, line))
	{
		for(cur; cur->next != 0 && cur->next->key < line.substr(0,5); cur = cur->next);
		newnode = new node;
		newnode->next = cur->next;
		newnode->pos = i;
		newnode->key = line.substr(0,5);
		cur->next = newnode;
		i++;
	}

	if(root->next != 0)
		cur = root->next;
	outfile.open(nomesaida.c_str());
	for(cur; cur->next != 0; cur = cur->next)
	{
		outfile << cur->key << " " << cur->pos << endl;
	}
	infile.close();
	return 0;
}

int main(int argc, char** argv)
{
	using namespace std;
	int i;

    cout << "Have " << argc-1 << " arguments:" << endl;
    for(i = 1; i < argc; ++i)
	{
        cout << argv[i] << endl;
    }

	for(i = 1; i < 4; ++i)
	{
		ifstream infile;
		infile.open(argv[i]);
		if(!infile)
		{
			cout << "Arquivo " << i << " nao existe." << endl;
			return -1;
		}
		infile.close();
	}

	readList(argv[1]);
	readList(argv[2]);
	readList(argv[3]);

	return 0;
}
