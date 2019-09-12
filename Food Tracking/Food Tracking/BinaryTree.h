#pragma once
#include <string>

using namespace std;

struct node
{
public:
	node* parent = nullptr;
	node* childL = nullptr;
	node* childR = nullptr;
	int value;
	string name;
	int pos;
};

class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();
	void addNode(int number, string name, int pos);
	node* nextNode(node* curr);
	string getNode(node* curr);
	node* firstNode();
	node* root() { return Root; }

private:
	node* Root;
};