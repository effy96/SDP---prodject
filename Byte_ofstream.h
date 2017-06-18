#ifndef _Byte_ofstream
#define _Byte_ofstream
using namespace std;
#include <iostream>
#include <fstream>
#include <vector>
#include"Huffman_tree.h"
class Byte_ofstream
{
public:
	Byte_ofstream();
	~Byte_ofstream();

	void open(const char* file_name);
	void close();

	void save_byte_buff();
	void add_bit(const bool);
	void add_bool_arr(const vector<bool>&);

	void save_numb_chars(unsigned __int32); 

	//saving boolean structure of the huffman tree and it's leafs
	
	bool save_huffman_tree(Huffman_tree*&);
private:
	void save_information_for_huffman_tree(vector<bool>&, vector<unsigned char>&);
private:
	ofstream file;
	unsigned char byte_buffer;
	__int16 bit_position;


};
#endif