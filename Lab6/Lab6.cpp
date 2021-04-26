#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <list>
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

string s;
string input_string;

inline void Get(void);
void Error(const char* msg, const char* param);


void Run();





list <string> Stack;

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

inline void Get(void)
{
	s = input_string[0];
	input_string.erase(0, 1);

	while (s >= "a" && s <= "z")
	{
		s += input_string[0];
		input_string.erase(0, 1);
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
		if (Matrix.count(s + Stack.back()) == 0) Error("Wrong input string");
}

int main(int argc, char** argv)
{

	cout << "\n Enter a example \n >";
	cin >> input_string;



	Get();
		Stack.push_back(s);
	Run();


	system("pause");
	return 0;
}