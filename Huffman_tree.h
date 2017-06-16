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
#ifndef  _Huffman_tree
#define  _Huffman_tree
#include <iostream>
#include <vector> 
// I am including <vector> because i wanted to make the project work 
//and then to write implementation for template class vector 
using namespace std;
struct Huffman_tree
{
	unsigned char symbol;
	unsigned __int32 frequency;
	Huffman_tree * left;
	Huffman_tree * right;

	///build huffman tree from file
	Huffman_tree* build(const char*); //returns pointer to the builded tree from file;


	///generate structure of the tree -> 1 if current is leaf and 0 if it's not
	bool generate_binary_structure(Huffman_tree*root, vector<bool>& tree_structure, vector<unsigned char>& leafs);


	/// get symbol's code -> 0-for left 1-for right;
	bool get_symbol_code(Huffman_tree*, unsigned char, vector<bool>&); 

	/// get symbol by it's code 
	void return_file_content(Huffman_tree*, vector<bool>&, vector<unsigned char>&, unsigned&);

	///print
	void print();

	///build huffman tree form bool structure and leafs[]
	Huffman_tree* build_from_structure(Huffman_tree*, vector<bool>&, vector<unsigned char>&, unsigned&, unsigned&);

	 
	///compare for priority queue
	struct compare {
		bool operator()(Huffman_tree* a, Huffman_tree* b)
		{
			return a->frequency > b->frequency;
		}
	};

	Huffman_tree();
	Huffman_tree(unsigned char, unsigned __int32);
	Huffman_tree(unsigned __int32, Huffman_tree *&l, Huffman_tree*&r);
	~Huffman_tree();

 
};


#endif // !_Huffman_tree
