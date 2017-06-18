#include "Huffman_tree.h"
#include <fstream>
#include<iostream>
#include <queue>  
using namespace std;
Huffman_tree::Huffman_tree()
{
	symbol = '\0';
	frequency = 0;
	left = nullptr;
	right = nullptr;
}

Huffman_tree::Huffman_tree(unsigned char symb, unsigned __int32 freq)
{
	symbol = symb;
	frequency = freq;
	left = nullptr;
	right = nullptr;
}

Huffman_tree::Huffman_tree(unsigned __int32 fr, Huffman_tree *& l, Huffman_tree *& r)
{
	symbol = '\0';
	frequency = fr;
	left = l;
	right = r;
}

Huffman_tree::~Huffman_tree()
{
	delete left;
	delete right;
}

Huffman_tree* Huffman_tree:: build(const char * file_name)
{
	ifstream file(file_name, ios::binary);
	// Reading every symbol from file and counting it's frequency
	struct  Data
	{
		unsigned char symbol;
		unsigned __int32 frequency;
		Data() :symbol('\0'), frequency(0) {};
	};
	int capacity = 0;
	Data current;
	Data arr[256];
	while (!file.eof())
	{
		file.read((char*)&current.symbol, 1);
		if (file.eof())
			break;
		arr[current.symbol].symbol = current.symbol;
		if (arr[current.symbol].frequency == 0)
			capacity++;
		arr[current.symbol].frequency += 1;
	}
	if (capacity == 0)
		return nullptr;
	file.close();
	// Creating priority queue from every symbol from file and it's frequency
	priority_queue<Huffman_tree*, vector<Huffman_tree*>, Huffman_tree::compare> que;
	for (int i = 0;i < 256;i++)
	{
		if (arr[i].frequency != 0)
		{
			Huffman_tree* tmp = new Huffman_tree(arr[i].symbol, arr[i].frequency);
			que.push(tmp);
		}
	}

	Huffman_tree* root = nullptr;
	while (que.size() > 1)
	{
		Huffman_tree * tmp_left;
		Huffman_tree * tmp_right;
		tmp_left = que.top();
		que.pop();
		tmp_right = que.top();
		que.pop();
		root = new Huffman_tree((tmp_left->frequency + tmp_right->frequency), tmp_left, tmp_right);
		que.push(root);
	}
	root = que.top();
	return root;
}

bool Huffman_tree::generate_binary_structure(Huffman_tree * current, vector<bool>& tree_structure, vector<unsigned char>& leafs)
{ 
	if (current->left == nullptr&&current->right == nullptr)
	{
		tree_structure.push_back(1);
		leafs.push_back(current->symbol);
		return true;
	}
	 
	tree_structure.push_back(0);

	generate_binary_structure(current->left, tree_structure, leafs);
	generate_binary_structure(current->right, tree_structure, leafs);
	 
	return true; 
}

void Huffman_tree::print()
{
	/*
	cout << "\t";

	cout << "Symbol : " << symbol << "Frequency : " << frequency << endl;

	cout << "Left: ";
	if (left != nullptr)
	{
		cout << "\t";

		left->print();
		cout << endl;

	}
	cout << "Right: ";
	if (right != nullptr)
	{
		cout << "\t";
		right->print();
		cout << endl;
	}
	cout << endl;
	*/

}

Huffman_tree * Huffman_tree::build_from_structure(Huffman_tree * current, vector<bool>& bit_structure, vector<unsigned char>& leafs, unsigned & i, unsigned & j)
{
	if (bit_structure.at(i) == 0)
	{
		current = new Huffman_tree;
		i++;
		current->left = build_from_structure(current->left, bit_structure, leafs, i, j);
		current->right = build_from_structure(current->right, bit_structure, leafs, i, j);
		return current;

	}
	else if (bit_structure.at(i) == 1)
	{
		current = new Huffman_tree;
		current->symbol = leafs.at(j);
		i++;
		j++;
		return current;
	}
}

bool Huffman_tree::get_symbol_code(Huffman_tree * current, unsigned char searching_symb, vector<bool>& result)
{
	if (current->left == nullptr&&current->right == nullptr)
	{
		if (current->symbol == searching_symb)
			return true;
		else
		{
			return false;
		}
	}
	else
	{
		if (get_symbol_code(current->left, searching_symb, result))
		{
			result.push_back(0);
			return true;
		}
		if (get_symbol_code(current->right, searching_symb, result))
		{
			result.push_back(1);
			return true;
		}
	}
}


void Huffman_tree::return_file_content(Huffman_tree* current, vector<bool>& encoded_data, vector<unsigned char>& data, unsigned & i)
{
	if (i >= encoded_data.size())
	{
		i++;
		return;
	}
	if (current->left == nullptr&current->right == nullptr)
	{
		data.push_back(current->symbol);
		//i++;

		return;
	}
	if (encoded_data.at(i) == 0)
	{
		i++;
		return_file_content(current->left, encoded_data, data, i);
		return;

	}
	if (encoded_data.at(i) == 1)
	{
		i++;
		return_file_content(current->right, encoded_data, data, i);
		return;
	}
}
///////////////////////////////////////////////////////////////--------------------------------------------------------------------------------------------------------------------------------
/*bool Huffman_tree::read_huffman_tree(const char * file_name)
{
	Byte_ifstream file;
	file.open(file_name);
	
	size = 0;
	vector < bool> bit_structure;
	vector<unsigned char> leafs;
	file.read_huffman_tree(size, bit_structure, leafs);
	cout << "?!?!?!?!?!?!?!?!------ READ HUFFMAN TREE ------?!?!?!?!?!?!?!??!!" << endl;
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
	cout << "?!?!?!?!?!?!?!?!?!?!?!?!?!??!?!?!?!?!?!?!??!?!?!?!?!?!?!?!?!?!?!?!?!?" << endl;

	return true;
}

Huffman_tree* Huffman_tree::build_huffman_tree_from_file(Huffman_tree * current, vector<bool>& bit_structure, vector<unsigned char>& leafs, unsigned & i, unsigned & j)
{
	


}


Huffman_tree* Huffman_tree::read_huffman_tree_from_file(const char* file_name)
{

	Byte_ifstream file;
	file.open(file_name);
	__int16 size_in_bits;
	vector<bool> bit_structure;
	vector<unsigned char> leafs;
	file.read_huffman_tree(size_in_bits, bit_structure, leafs);

	cout << "?!?!?!?!?!?!?!?!------ READ HUFFMAN TREE ------?!?!?!?!?!?!?!??!!" << endl;
	cout << "size " << size_in_bits << endl;
	for (size_t i = 0; i < bit_structure.size(); i++)
	{
		cout << bit_structure.at(i);
	}
	cout << endl;
	for (size_t i = 0; i < leafs.size(); i++)
	{
		cout << "Leaf " << i << " " << leafs.at(i) << endl;
	}
	cout << "?!?!?!?!?!?!?!?!?!?!?!?!?!??!?!?!?!?!?!?!??!?!?!?!?!?!?!?!?!?!?!?!?!?" << endl;


	unsigned i = 0;
	unsigned j = 0;
	return build_huffman_tree_from_file(this, bit_structure, leafs, i, j);

}

void Huffman_tree::return_file_content(Huffman_tree* current, vector<bool>& encoded_data, vector<unsigned char>& data, unsigned & i)
{
	if (i == encoded_data.size())
		return;
	if (current->left == nullptr&current->right == nullptr)
	{
		i++;
		data.push_back(current->symbol);
	}
	if (encoded_data.at(i) == 0)
	{
		i++;
		return_file_content(current->left, encoded_data, data, i);
	}
	if (encoded_data.at(i) == 1)
	{
		i++;
		return_file_content(current->right, encoded_data, data, i);
	}
}

bool Huffman_tree::encode(const char * original_file, const char * result_file)
{
	Huffman_tree* tree = build(original_file);
	tree->save_huffman_tree(result_file);
	ifstream read_file(original_file, ios::binary);
	if (!read_file.is_open())
		throw 45194;

	Byte_ofstream save_file;
	save_file.open(result_file);
	//save_file.save_numb_chars(tree->frequency);

	while (!read_file.eof())
	{
		vector<bool> symbol_code;
		unsigned char tmp;
		read_file.read((char*)&tmp, sizeof(unsigned char));
		get_symbol_code(tree, tmp, symbol_code);
		save_file.add_bool_arr(symbol_code);
	}
	save_file.close();
	read_file.close();



	return false;
}

bool Huffman_tree::decode(const char * encoded_file, const char *decoded_file)
{
	return false;

}
*/