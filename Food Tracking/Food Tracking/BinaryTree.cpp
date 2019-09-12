#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	Root = nullptr;
}

BinaryTree::~BinaryTree()
{
	node *prev, *curr;
	curr = Root;
	while (curr != Root && curr->childR != nullptr && curr->childL != nullptr) {
		if (curr->childL != nullptr)
			curr = curr->childL;
		else if (curr->childR != nullptr)
			curr = curr->childR;
		else if (curr->childL == nullptr && curr->childR == nullptr) {
			prev = curr;
			curr = curr->parent;
			delete[] prev;
		}
	}

}

void BinaryTree::addNode(int number, string name, int pos)
{
	node* temp = new node;
	node *prev = Root;
	node *curr = Root;
	temp->value = number;
	temp->name = name;
	temp->pos = pos;
	if (Root == nullptr) {
		Root = temp;
		return;
	}
	while (curr != nullptr) {
		prev = curr;
		if (curr->value < number)
			curr = curr->childL;
		else if (curr->value > number)
			curr = curr->childR;
		else
			if (curr->name > name)
				curr = curr->childL;
			else if (curr->name < name)
				curr = curr->childR;
			else printf("Error. Multiple with same name: %s\n", name.c_str());
	}
	temp->parent = prev;
	if (prev->value < number)
		prev->childL = temp;
	else if (prev->value > number)
		prev->childR = temp;
	else if (prev->value == number)
		if (prev->name > name)
			prev->childL = temp;
		else if (prev->name < name)
			prev->childR = temp;
		else printf("Error. Multiple with same name: %s\n", name.c_str());
	return;
}

node* BinaryTree::nextNode(node* curr)
{
	node temp;
	temp.name = curr->name;
	temp.value = curr->value;
	if (curr->childR != nullptr) {
		curr = curr->childR;
		while (curr->childL != nullptr)
			curr = curr->childL;
		return curr;
	}
	if (curr->childR == nullptr) {
		curr = curr->parent;
		while (curr != nullptr && (curr->value > temp.value || (curr->value == temp.value && curr->name < temp.name)))
			if (curr->value > temp.value)
				curr = curr->parent;
			else if (curr->value == temp.value && curr->name < temp.name)
				curr = curr->parent;
	}
	return curr;
}

string BinaryTree::getNode(node* curr)
{
	return curr->name;
}

node* BinaryTree::firstNode()
{
	node* curr = Root;
	while (curr->childL != nullptr)
		curr = curr->childL;
	return curr;
}
