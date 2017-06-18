#ifndef _functions
#define _functions
#include "Huffman_tree.h"
#include"Byte_ifstream.h"
#include"Byte_ofstream.h"
#include <bitset>
void EnCode(const char* original_file, const char* result_file)
{
	Huffman_tree* tree = new Huffman_tree();
	tree = tree->build(original_file);

	Byte_ofstream result;
	result.open(result_file);
	result.save_huffman_tree(tree);
	result.close();


	ifstream read_file(original_file, ios::binary);
	if (!read_file.is_open())
		throw 45194;

	//save_file.save_numb_chars(tree->frequency);
	Byte_ofstream res;
	res.open(result_file);

	unsigned  frequency;
	frequency = tree->frequency;
	res.save_numb_chars(frequency);


	while (!read_file.eof())
	{
		vector<bool> symbol_code;
		unsigned char tmp;
		read_file.read((char*)&tmp, sizeof(unsigned char));
		tree->get_symbol_code(tree, tmp, symbol_code);
		vector < bool> code;
		unsigned capacity = symbol_code.size();
		for (size_t i = 0; i < capacity; i++)
		{
			code.push_back(symbol_code.back());
			symbol_code.pop_back();
		}
		res.add_bool_arr(code);
		/*for (size_t i = 0; i < code.size(); i++)
		{
			
			<< code.at(i);
		}*/
	}
	//cout << endl;
	result.close();
	read_file.close();
	cout << "created :" << result_file << endl; 
}
void DeCode(const char* original_file, const char* result_file)
{
	//read the tree
	Huffman_tree* tree = new Huffman_tree();

	Byte_ifstream encoded;
	encoded.open(original_file);
	vector<bool> encoded_data;
	tree = encoded.read_huffman_tree();

	unsigned frequency = encoded.get_frequency();
	encoded_data = encoded.get_rest_of_the_data();
	/*
	for (size_t i = 0; i < encoded_data.size(); i++)
	{
		cout << encoded_data.at(i);
	}
	cout << endl;
	*/

	vector<unsigned char> data;
	unsigned i = 0;
	unsigned j=frequency;
	while (data.size() < frequency)
	{
		tree->return_file_content(tree, encoded_data, data, i);
	}
	/*cout << endl << "  DATA: ";
	for (int i = 0;i < data.size();i++)
		cout << data.at(i);*/

	ofstream result(result_file);
	for (int i = 0;i < data.size();i++)
		result.write( (char*)& data.at(i),sizeof(unsigned char));

	cout << "created :" << result_file << endl;
	 



}



#endif // !_functions
