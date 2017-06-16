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
#include "Byte_ofstream.h"

Byte_ofstream::Byte_ofstream()
{
	bit_position = 0;
	byte_buffer = 0x00;
}

Byte_ofstream::~Byte_ofstream()
{
	if (bit_position != 0)
		save_byte_buff();
	if (file.is_open())
		file.close();
}

void Byte_ofstream::open(const char * file_name)
{
	file.open(file_name, ios::binary | ios::app);
}

void Byte_ofstream::save_byte_buff()
{
	bit_position = 0;
	file.write((char*)& byte_buffer, sizeof(byte_buffer));
	byte_buffer = 0x00;

}

void Byte_ofstream::add_bit(const bool bit)
{
	if (bit == 1)
		byte_buffer |= (1 << (7 - bit_position));
	bit_position++;
	if (bit_position > 7)
		save_byte_buff();
}

void Byte_ofstream::add_bool_arr(const vector<bool>& arr)
{
	for (int i = 0;i < arr.size();i++)
		add_bit(arr.at(i));
}

void Byte_ofstream::close()
{
	if (bit_position != 0)
		save_byte_buff();

}
void Byte_ofstream::save_information_for_huffman_tree(vector<bool>& bit_structure, vector<unsigned char>& leafs)
{

	__int16 size = bit_structure.size();
	file.write((char*)&size, sizeof(__int16));
	add_bool_arr(bit_structure);
	close();
	for (int i = 0;i < leafs.size();i++)
	{
		unsigned char tmp = leafs.at(i);
		file.write((char*)&tmp, sizeof(unsigned char));
	}
}
bool Byte_ofstream::save_huffman_tree(Huffman_tree *& tree)
{

	vector<bool> binary_structure;
	vector<unsigned char> leafs;

	/// GENERATE BINARY STRUCTURE OF THE TREE////
	tree->generate_binary_structure(tree, binary_structure, leafs);

	/// SAVE SIZE OF THE STRUCTURE IN BITS
	__int16 size_in_bits = 0;
	size_in_bits = binary_structure.size();

	
	save_information_for_huffman_tree(binary_structure, leafs);

	file.close();
	//cout << endl;
	//cout << "/*/*/*/*/*/*/*/------ SAVE HUFFMAN TREE --- BYTE OFSTREAM---*/*/*/*/*/*/*/*/*/" << endl;
	/*
	cout << "Size " << size_in_bits << endl;
	for (size_t i = 0; i < binary_structure.size(); i++)
	{
		cout << binary_structure.at(i);
	}
	cout << endl;
	for (size_t i = 0; i < leafs.size(); i++)
	{
		
		
		<< "Leaf " << i << " " << leafs.at(i) << endl;
	}
	*/
	//cout << "/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/" << endl;
	





	return true;
}
void Byte_ofstream::save_numb_chars(unsigned __int32 size)
{
	unsigned __int32 sz = size;
	file.write((char*)&sz, sizeof(sz));
}
