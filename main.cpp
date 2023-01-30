
// #include "node.cpp"
#include "lexer.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>
#include <array>
using namespace std;


int main() 
{

	//Create new fstream instance
	fstream newfile;

	//Open file
	newfile.open("filetest.txt", ios::in);
	if (newfile.is_open()){

		//Line varible for each line and full for the whole document
		string line;
		string full;

		//Just realised I could have probably dfined the array inside the
		//loop and called parser inside the loop so it would call line
		//by line and then the array would re assign each loop based on the size
		//of that line. This way might be better though.
		
		//Get individual line from newFile and assign it to line variable
		getline(newfile, line);
		
		//Concatonate line to full add a space at the end and get a new line
		while (line != "")
		{

			full = full + line;
			full = full + ' ';
			getline(newfile, line);

		}

		//Pass to lexer
		lex(full);

		newfile.close();
	}


	return 0;
}