#include "Byte_ifstream.h"
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

Byte_ifstream::Byte_ifstream()
{
	bit_position = -1;
	last_readed_byte = 0x00;
}

Byte_ifstream::~Byte_ifstream()
{
	file.close();
}

vector<bool> Byte_ifstream::read_byte_into_arr()
{
	vector<bool> result;
	bit_position = 0;
	unsigned char ch;
	file.read((char*)&ch, sizeof(ch));
	for (int i = 0;i < 8;i++)
	{
		result.push_back(ch&(1 << (7 - i)));
	}
	return result;
}

void Byte_ifstream::read_byte()
{
	bit_position = 0; 
	file.read((char*)&last_readed_byte, sizeof(last_readed_byte));
}

void Byte_ifstream::read_bit_arr(unsigned size, vector<bool>&result)
{
	for (int i = 0;i < size;i++)
	{
		result.push_back(get_bit());
	}

}

bool Byte_ifstream::get_bit()
{
	bool tmp;
	if (bit_position == -1)
		read_byte();

	tmp = (last_readed_byte&(1 << (7 - bit_position)));
	bit_position++;
	if (bit_position > 7)
		read_byte();
	return tmp;
}

void Byte_ifstream::set_seekg(unsigned long size)
{
	streampos pos;
	pos = file.tellg();
	pos += size;
	file.seekg(pos);
}

unsigned Byte_ifstream::get_frequency()
{
	unsigned frequency;
	file.read((char*)&frequency, sizeof(unsigned)); 
	return frequency;
}

void Byte_ifstream::read_data_for_building_tree(__int16 & size, vector<bool>& bit_structure, vector<unsigned char>& leafs)
{

	file.read((char*)&size, sizeof(__int16));
	read_bit_arr(size, bit_structure);
	__int16 count_leafs = 0;
	for (int i = 0;i < bit_structure.size();i++)
		if (bit_structure.at(i) == 1)
			count_leafs++;
	unsigned char tmp;
	for (int i = 0;i < count_leafs;i++)
	{
		file.read((char*)&tmp, sizeof(unsigned char));
		leafs.push_back(tmp);
	}
}

Huffman_tree *& Byte_ifstream::read_huffman_tree()
{ 
	__int16 size = 0;
	vector < bool> bit_structure;
	vector<unsigned char> leafs;
	read_data_for_building_tree(size, bit_structure, leafs);
	Huffman_tree* result=new Huffman_tree;
	unsigned i = 0, j = 0;
	result = result->build_from_structure(result,bit_structure, leafs, i, j);
	/*
	cout << "?!?!?!?!?!?!?!?!------ READ HUFFMAN TREE --- BYTE IFSTREAM---?!?!?!?!?!?!?!??!!" << endl;
	cout << "size " << size << endl;
	for (size_t i = 0; i < bit_structure.size(); i++)
	{
		cout << bit_structure.at(i);
	}
	cout << endl;
	for (size_t i = 0; i < leafs.size(); i++)
	{
		cout << "Leaf " << i << " " << leafs.at(i) << endl;
	} 
	cout << endl;
	cout << "?!?!?!?!?!?!?!?!?!?!?!?!?!??!?!?!?!?!?!?!??!?!?!?!?!?!?!?!?!?!?!?!?!?" << endl;
	*/

	return result;

}

streampos Byte_ifstream::get_tellg()
{
	return file.tellg();
}
unsigned long Byte_ifstream::get_size_of_readed_information()
{
	streampos pos;
	pos = file.tellg();
	file.seekg(ios::beg, 0);
	unsigned long result;
	result = file.tellg() - pos;
	return pos;
}

vector<bool> Byte_ifstream::get_rest_of_the_data()
{
	 get_bit();
	vector<bool> data;
	while (!file.eof())
	{ 
		data.push_back(get_bit()); 
	} 
	return data;
}
