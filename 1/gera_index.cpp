#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>


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

int readSecListVariable(char*argv)
{
	using namespace std;
	int removed = 0;

	vector<string> tok;
	string token;
	string line, nomesaida;
	stringstream rr, ss;

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
		tok.clear();
		stringstream ss(line);
		string token;
		while(getline(ss, token, '|'))
		{
			tok.push_back(token);
		}

		newsecnode = new secnode;
		newsecnode->nome = tok[2];
		newsecnode->nextsec = NULL;
		newsecnode->rootkey = NULL;
		if(rootsec == NULL)
		{
			rootsec = newsecnode;
			newsecnode->rootkey = new seckey;
			newsecnode->rootkey->key = tok[0];
			newsecnode->rootkey->nextseckey = NULL;
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
				newseckey = new seckey;
				newseckey->key = tok[0];
				newseckey->nextseckey = NULL;
				prevseckey = NULL;
				tempseckey = tempsec->rootkey;
				while(tempseckey != NULL && tempseckey->key < tok[0])
				{
					prevseckey = tempseckey;
					tempseckey = tempseckey->nextseckey;
				}
				if(!tempseckey)
				{
					prevseckey->nextseckey = newseckey;
				}
				else
				{
					if(prevseckey)
					{
						newseckey->nextseckey = prevseckey->nextseckey;
						prevseckey->nextseckey = newseckey;
					}
					else
					{
						newseckey->nextseckey = tempsec->rootkey;
						tempsec->rootkey = newseckey;
					}
				}
			}
			else
			{
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
				}
			}
			newsecnode->rootkey = new seckey;
			newsecnode->rootkey->key = tok[0];
			newsecnode->rootkey->nextseckey = NULL;
		}
	}

	outfile.open(nomesaida.c_str());
	rr << setw(3) << setfill('0') << removed;
	string r = rr.str();
	outfile << r << endl;
	for(tempsec = rootsec; tempsec != NULL; tempsec = tempsec->nextsec)
	{
		outfile << tempsec->nome;
		for(tempseckey = tempsec->rootkey; tempseckey != NULL; tempseckey = tempseckey->nextseckey)
		{
			outfile << " ";
			outfile << tempseckey->key;
		}
		outfile << endl;
	}

	infile.close();
}

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
		if(rootsec == NULL)
		{
			rootsec = newsecnode;
			newsecnode->rootkey = new seckey;
			newsecnode->rootkey->key = line.substr(0,5);
			newsecnode->rootkey->nextseckey = NULL;
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
				newseckey = new seckey;
				newseckey->key = line.substr(0,5);
				newseckey->nextseckey = NULL;
				prevseckey = NULL;
				tempseckey = tempsec->rootkey;
				while(tempseckey != NULL && tempseckey->key < line.substr(0,5))
				{
					prevseckey = tempseckey;
					tempseckey = tempseckey->nextseckey;
				}
				if(!tempseckey)
				{
					prevseckey->nextseckey = newseckey;
				}
				else
				{
					if(prevseckey)
					{
						newseckey->nextseckey = prevseckey->nextseckey;
						prevseckey->nextseckey = newseckey;
					}
					else
					{
						newseckey->nextseckey = tempsec->rootkey;
						tempsec->rootkey = newseckey;
					}
				}
			}
			else
			{
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
				}
			}
			newsecnode->rootkey = new seckey;
			newsecnode->rootkey->key = line.substr(0,5);
			newsecnode->rootkey->nextseckey = NULL;
		}
	}

	outfile.open(nomesaida.c_str());
	rr << setw(3) << setfill('0') << removed;
	string r = rr.str();
	outfile << r << endl;
	for(tempsec = rootsec; tempsec != NULL; tempsec = tempsec->nextsec)
	{
		outfile << tempsec->nome;
		for(tempseckey = tempsec->rootkey; tempseckey != NULL; tempseckey = tempseckey->nextseckey)
		{
			outfile << " ";
			outfile << tempseckey->key;
		}
		outfile << endl;
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
			i++;
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

	outfile.open(nomesaida.c_str(), ios::app);
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
	readSecListVariable(argv[2]);
	readSecListVariable(argv[3]);

	return 0;
}
