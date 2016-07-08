#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>


struct node {
  std::string key;
  int pos;
  node *next;
};

struct seckey
{
	std::string key;
	seckey *nextseckey;
};

struct secnode
{
	std::string nome;
	seckey *rootkey;
	secnode *nextsec;
};

int readSecListFixed(char* argv)
{
	using namespace std;
	int removed = 0;
	stringstream rr;
	string line, nomesaida;

	nomesaida = "sec_";
	nomesaida.append(argv);
	cout << nomesaida << endl;

	secnode *rootsec = NULL;
	secnode *newsecnode;
	secnode *prevsecnode = new secnode;
	secnode *tempsec = new secnode;

	seckey *prevseckey = new seckey;
	seckey *tempseckey = new seckey;
	seckey *newseckey;

	ifstream infile;
	ofstream outfile;

	infile.open(argv);
	while(getline(infile, line))
	{
		newsecnode = new secnode;
		newsecnode->nome = line.substr(13, 23);
		newsecnode->nextsec = NULL;
		newsecnode->rootkey = NULL;
		cout << "INSERE: " << newsecnode->nome << endl;
		if(rootsec == NULL)
		{
			rootsec = newsecnode;
		}
		else
		{
			prevsecnode = NULL;
			tempsec = rootsec;
			while(tempsec != NULL && tempsec->nome < newsecnode->nome)
			{
				prevsecnode = tempsec;
				tempsec = tempsec->nextsec;
			}
			if((tempsec != NULL) && (tempsec->nome == newsecnode->nome))
			{
				cout << tempsec->nome << " "<< "IGUAIS" << endl;
			}
			if(!tempsec)
			{
				prevsecnode->nextsec = newsecnode;
			}
			else
			{
				if(prevsecnode)
				{
					newsecnode->nextsec = prevsecnode->nextsec;
					prevsecnode->nextsec = newsecnode;
				}
				else
				{
					newsecnode->nextsec = rootsec;
					rootsec = newsecnode;
				}
				newsecnode->rootkey = new seckey;
				newsecnode->rootkey->key = line.substr(0,5);
				newsecnode->rootkey->nextseckey = NULL;
			}

		}
	}

	outfile.open(nomesaida.c_str());
	rr << setw(3) << setfill('0') << removed;
	string r = rr.str();
	outfile << r << endl;
	for(tempsec = rootsec; tempsec != NULL; tempsec = tempsec->nextsec)
	{
		cout << tempsec->nome << endl;
	}

	infile.close();
}

int readList(char* argv)
{
	using namespace std;
	int i, j, removed = 0;
	string line, nomesaida;
	stringstream rr;

	node *root = NULL;
	node *newnode;
	node *prevnode;
	node *temp = new node;


	nomesaida = "index_";
	nomesaida.append(argv);
	cout << nomesaida << endl;

	ifstream infile;
	ofstream outfile;

	infile.open(argv);
	i = 0;
	while(getline(infile, line))
	{
		newnode = new node;
		newnode->pos = i;
		newnode->key = line.substr(0,5);
		newnode->next = NULL;
		if(root == NULL)
		{
			root = newnode;
		}
		else
		{
			temp = root;
			while(temp != NULL && temp->key < newnode->key)
			{
				prevnode = temp;
				temp = temp->next;
			}
			newnode->next = temp;
			prevnode->next = newnode;
			i++;
		}
	}

	outfile.open(nomesaida.c_str());
	rr << setw(3) << setfill('0') << removed;
	string r = rr.str();
	outfile << r << endl;
	for(temp = root; temp != NULL; temp = temp->next)
	{
		outfile << temp->key << " " << temp->pos << endl;
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
	readSecListFixed(argv[1]);

	return 0;
}
