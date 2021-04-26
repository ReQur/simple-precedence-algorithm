#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <list>
#include <iterator>
#include <map>


/*
   S' -> TST
   S -> (I, E)
   E -> "E | T"  |  T
   T -> T & M  |  M
   M -> ~M	 |  (E)  |  I  |  C


   C = {true, false}
   I = {a, b, c, ..., z}
*/


using namespace std;

string az = "qwertyuiopasdfhjklzxcvbnm";

string s;
string input_string;

inline void Get(void);
void Error(const char* msg, const char* param);


void Run();





list <string> Stack;
list <string> ::iterator pos_begin, pos_end;
map <string, string> ::iterator act;
map <string, string> Matrix = {
								{"TS", "="}, {"I,", "="}, {"(E", "="}, {"(E", "<"},
								{"(I", "="}, {"(I", "<"}, {"~M", "="}, {"&M", "="},
								{"|T", "="}, {",E", "="}, {",E", "<"}, {"T&", "="},
								{"E|", "="}, {"E)", "="}, {"ST", "="},

								{"TC", "<"}, {"T(", "<"}, {"(M", "<"}, {"(~", "<"},
								{"((", "<"}, {"(C", "<"}, {"~~", "<"}, {"~(", "<"},
								{"~I", "<"}, {"~C", "<"}, {"&~", "<"}, {"&(", "<"},
								{"&I", "<"}, {"&C", "<"}, {"|M", "<"}, {"|~", "<"},
								{"|(", "<"}, {"|I", "<"}, {"|C", "<"}, {",T", "<"},
								{",M", "<"}, {",~", "<"}, {",(", "<"}, {",I", "<"},
								{",C", "<"},

								{")T", ">"}, {"T)", ">"}, {"M)", ">"}, {"))", ">"},
								{"I)", ">"}, {"C)", ">"}, {"T|", ">"}, {"M|", ">"},
								{")|", ">"}, {"C|", ">"}, {"I|", ">"}, {"M&", ">"},
								{")&", ">"}, {"I&", ">"}, {"C&", ">"}
};

void Get(void)
{
	if (input_string[0] == ' ')
		input_string.erase(0, 1);

	s = input_string[0];
	input_string.erase(0, 1);

	while (s >= "a" && s <= "z" && input_string[0] != ',')
	{
		s = s + input_string[0];
		input_string.erase(0, 1);
		if (az.find(input_string[0]) == std::string::npos)
			break;
	}

	if (s.length() > 1)
		if (s == "true" or s == "false") s = "C";
		else s = "I";
	
}

void Error(const char* msg)
{
	cout << "Error: " << msg << endl;
	system("pause");
	exit(7);
}


void Run()
{
	Get();
	string cup = Stack.back() + s;
	if (Matrix.count(cup) == 0) Error("Wrong input string");
	
	if (Matrix.count(cup) == 1)
	{
		act = Matrix.find(cup);
		Stack.push_back(act->second);
		Stack.push_back(s);
	}

	if (input_string.size() != 0)
		Run();
		
}

int main(int argc, char** argv)
{

	cout << "\n Enter a example \n >";
	getline(cin, input_string);



	Get();
		Stack.push_back(s);
	Run();
	for (auto i = Stack.begin(); i != Stack.end(); ++i) cout << *i;

	system("pause");
	return 0;
}