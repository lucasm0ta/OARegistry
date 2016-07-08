#include <iostream>
#include <fstream>
#include <vector>

int sortFile(std::string filename)
{
	using namespace std;
	string line;
	vector<string> key;
	ifstream infile;
	ofstream outfile;

	infile.open(filename.c_str());
	while(getline(infile, line))
	{
		key.push_back(line.substr(0,5));
		cout << key.back() << endl;
	}

	return 0;
}

int readList(char* argv)
{
	using namespace std;
	int i;
	string line, nomesaida;

	nomesaida = "index_";
	nomesaida.append(argv);
	cout << nomesaida << endl;

	ifstream infile;
	ofstream outfile;

	infile.open(argv);
	outfile.open(nomesaida.c_str());
	i = 0;
	while(getline(infile, line))
	{
		outfile << line.substr(0,5) << " " << i << endl;
		i++;
	}
	outfile.close();
	infile.close();

	sortFile(nomesaida);

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

	return 0;
}
