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
#include "Huffman_tree.h"
#include <fstream>
#include<iostream>
#include <queue>  
//I am including <queue> for using priority queue
//because i wanted to make the project work and then to write implementation for template priority queue
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
 