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
								{"E|", "="}, {"E)", "="}, {"S$", "="},

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
									{"<=E=|=T>", "E"}, {"<T>", "E"},
									{"<T=&=M>", "T"}, {"<M>", "T"},
									{"<~=M>", "M"}, {"<(<=E=)>", "M"}, {"<C>", "M"}, {"<I>", "M"}
									};

void Error(const string msg, const string cup)
{
	string Errmes = "Error: " + msg + ", " + "\"" + cup + "\"" + " is unkown couple of elements";
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

	if (cupMatrix.count(cup) == 0) Error("Wrong input string", cup);

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
	string phrase;

	for (auto i = Stack.end(); *i != "<"; --i)
	{
		phrase = Stack.back() + phrase;
		Stack.pop_back();

	}
	Stack.pop_back();
	phrase = "<" + phrase;

	cout << phrase << endl;

	if (phrase[0] == '=')
	{
		Stack.pop_back();
		phrase = "<" + phrase;

		cout << phrase << endl;


		list <string> tmpStack = Stack;
		string extphrase = phrase;
		for (auto i = tmpStack.end(); *i != "<" and *i != "$"; --i)
		{
			extphrase = tmpStack.back() + extphrase;
			tmpStack.pop_back();
		}
		
		if (tmpStack.back() == "<")
		{
			extphrase = tmpStack.back() + extphrase;
			tmpStack.pop_back();
			if (phraseMatrix.count(extphrase) != 0)
			{
				phrs = phraseMatrix.find(extphrase);
				s = phrs->second;
			}
			else
			{
				phrs = phraseMatrix.find(phrase);
				s = phrs->second;
			}
		}
		else
		{
			phrs = phraseMatrix.find(phrase);
			s = phrs->second;
		}

	}
	else
	{
		Stack.pop_back();
		phrase = "<" + phrase;

		cout << phrase << endl;


		phrs = phraseMatrix.find(phrase);
		s = phrs->second;
	}

	

}

int main(int argc, char** argv)
{

	cout << "\n Enter a example \n >";
	getline(cin, input_string);



	Get();
		Stack.push_back(s);
	Run();

	for (auto i = Stack.begin(); i != Stack.end(); ++i) cout << *i;
	cout << endl;

	system("pause");
	return 0;
}