/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author  Elizabet Mihaylova
* @idnumber 45194
* @task 2
* @compiler VC
*
*/
#ifndef _Byte_ifstream
#define _Byte_ifstream
using namespace std;
#include <iostream>
#include <fstream>
#include <vector> 

#include"Huffman_tree.h"
 

class Byte_ifstream
{
public:
	Byte_ifstream();
	~Byte_ifstream();

	vector<bool> read_byte_into_arr();
	void read_byte();
	void read_bit_arr(unsigned, vector<bool>&);
	bool get_bit();

	void open(const char* file_name) { file.open(file_name, ios::binary); };
	streampos get_tellg();
	
	void set_seekg(unsigned long);
	unsigned get_frequency();


	unsigned long get_size_of_readed_information(); 
	vector<bool> get_rest_of_the_data();


	Huffman_tree*& read_huffman_tree();
private:
	void read_data_for_building_tree(__int16&, vector<bool>&, vector<unsigned char>&);
	 
private:
	ifstream file;
	unsigned char last_readed_byte;
	__int16 bit_position;


};


#endif // ! 