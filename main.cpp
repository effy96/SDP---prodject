#include <iostream> 
#include <fstream>
#include<vector>
#include <bitset>
#include "Byte_ifstream.h"	
#include"Byte_ofstream.h"
#include "Huffman_tree.h"
#include"Functions.h"
using namespace std;
int main()
{
	char* command = new char[1000];
	
	bool tmp = true;
	while (tmp) 
	{
		cout << "Command :";
		cin.getline(command, 1000);

		if (strcmp(command, "-Pack") == 0)
		{
			cout << endl<< "Open file :";

			char* file = new char[1000];
			cin.getline(file, 1000);
			cout <<endl<< "Archive :" ;

			char* result = new char[1000];
			cin.getline(result, 1000);
			EnCode(file, result);
			tmp = true;
			continue;
		}
		else if (strcmp(command, "-Unpack") == 0)
		{
			cout <<endl<< "Open Archive :";

			char* file = new char[1000];
			cin.getline(file, 1000);
			cout <<endl<< "Unpack to : " ;

			char* result = new char[1000];
			cin.getline(result, 1000);
			DeCode(file, result);
			tmp = true;
			continue;
		}
		else
			tmp = false;
	}
	return 0;



}