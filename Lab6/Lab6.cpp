#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <list>
#include <iterator>
#include <map>



/*
   S' -> $S$
   S -> (I, E)
   E -> "E | T"  |  T
   T -> T & M  |  M
   M -> ~M	 |  (E)  |  I  |  C


   C = {true, false}
   I = {a, b, c, ..., z}

   example: (b, true|a&(false|~true))
*/


using namespace std;

string az = "qwertyuiopasdfghjklzxcvbnm";

string s;
string input_string;

inline void Get(void);
void Error(const string msg, const string param);


void Run();
void Convolution();




list <string> Stack;
list <string> ::iterator pos_begin, pos_end;
map <string, string> ::iterator act, phrs;
multimap <string, string> cupMatrix =	{
										{"$S", "="}, {"I,", "="}, {"(E", "="}, {"(E", "<"},
										{"(I", "="}, {"&M", "="}, {"~M", "="}, {"(I", "<"},
										{"|T", "="}, {",E", "="}, {"T&", "="}, {",E", "<"},
										{"E|", "="}, {"E)", "="}, {"S$", "="}, {"|T", "<"},

										{"$(", "<"}, {"(T", "<"}, {"(M", "<"}, {"(~", "<"},
										{"((", "<"}, {"(C", "<"}, {"~~", "<"}, {"~(", "<"},
										{"~I", "<"}, {"~C", "<"}, {"&~", "<"}, {"&(", "<"},
										{"&I", "<"}, {"&C", "<"}, {"|M", "<"}, {"|~", "<"},
										{"|(", "<"}, {"|I", "<"}, {"|C", "<"}, {",T", "<"},
										{",M", "<"}, {",~", "<"}, {",(", "<"}, {",I", "<"},
										{",C", "<"},

										{")$", ">"}, {"T)", ">"}, {"M)", ">"}, {"))", ">"},
										{"I)", ">"}, {"C)", ">"}, {"T|", ">"}, {"M|", ">"},
										{")|", ">"}, {"C|", ">"}, {"I|", ">"}, {"M&", ">"},
										{")&", ">"}, {"I&", ">"}, {"C&", ">"}
										};

map <string, string> phraseMatrix = {
									{"$=S=$", "G"},
									{"<(<=I=,<=E=)>", "S"},
									{"<=E=|<=T>", "E"}, {"<=T>", "E"},{"<T>", "E"},
									{"<=T=&=M>", "T"}, {"<T=&=M>", "T"},{"<M>", "T"},
									{"<~=M>", "M"}, {"<(<=E=)>", "M"}, {"<C>", "M"}, {"<I>", "M"}
									};

void Error(const string msg, const string smsg = "")
{
	string Errmes = "Error: " + msg + ", " + smsg;
	cout << Errmes << endl;
	system("pause");
	exit(7);
}


void Get(void)
{
	if (input_string[0] == ' ')
		input_string.erase(0, 1);

	s = input_string[0];
	input_string.erase(0, 1);

	while (s >= "a" && s <= "z" && az.find(input_string[0]) != std::string::npos)
	{
		s = s + input_string[0];
		input_string.erase(0, 1);
		if (az.find(input_string[0]) == std::string::npos)
			break;
	}

	if (az.find(s[0]) != std::string::npos)
		if (s == "true" or s == "false") s = "C";
		else s = "I";
	
}

void Analization()
{
	string cup = Stack.back() + s;

	if (s == "")
		return;

	if (cupMatrix.count(cup) == 0) Error("Wrong input string", "\"" + cup + "\"" + " is unkown couple of elements");

	if (cupMatrix.count(cup) == 2)
	{
		Stack.push_back("<");
		Stack.push_back("=");
		Stack.push_back(s);
	}
	else 
	if (cupMatrix.count(cup) == 1)
	{
		act = cupMatrix.find(cup);

		if (act->second != ">")
		{
			Stack.push_back(act->second);
			Stack.push_back(s);
		}
		else
		{

			Stack.push_back(act->second);

			string ths = s;
			Convolution();
			Analization();
			s = ths;
			Analization();
		}

	}
}

void Run()
{
	Get();

	Analization();


	if (input_string.size() != 0)
		Run();
		
}

void Convolution()
{
	list <string> tmpStack = Stack;
	string phrase;
	string exphrase;
	int state = 0;
	string tmps;
	bool f = true;

	auto i = tmpStack.end();

	while (f)
	{
		tmps = tmpStack.back();
		tmpStack.pop_back();
		phrase = tmps + phrase;
		switch (state) 
		{
		case 0:
			if (tmps == "=")
				state = 1;
			if (tmps == "<")
				state = 2;
			if (tmps == "$")
				state = 2;
			break;

		case 1:
			state = 0;
			if (tmps == "$")
				state = 2;
			break;

		case 2:
			f = false;
			break;

		default:
			break;
		}
	}
	tmpStack.push_back(tmps);
	while (phraseMatrix.count(phrase) == 0 && phrase.size() != 0)
	{
		while (true)
		{
			phrase.erase(0, 1);
			if (phrase[0] == '<')
				break;
		}
			
	}

	if (phrase.empty())
		Error("Wrong lexeme");

	phrs = phraseMatrix.find(phrase);
	s = phrs->second;


	Stack.resize(Stack.size() - phrase.size());

}

int main(int argc, char** argv)
{


	ifstream fin("in.txt", ios_base::in);

	if (fin.is_open() == 0)
		Error("File was not open");



	while (!fin.eof())
	{
		getline(fin, input_string);
		cout << input_string << " >> ";
		input_string.insert(input_string.begin(), '$');
		input_string.push_back('$');
		Get();
		Stack.push_back(s);
		Run();
		string result;
		for (auto i = Stack.begin(); i != Stack.end(); ++i) result = result + *i;
		if (result == "$=S=$")
			cout << "Accepted!" << endl;
		else
			cout << "Wrond lexem" << endl;
		Stack.clear();
		input_string.clear();
	}

	
	cout << "Done!" << endl;

	fin.close();
	system("pause");
	return 0;
}