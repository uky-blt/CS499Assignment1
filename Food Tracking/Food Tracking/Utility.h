#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "Foods.h"
#include "BinaryTree.h"
#include "Profile.h"

struct NutList
{
	string name;
	string units;
	unsigned int ID;
	float recAmnt;

	string getName() { return name; }
};

template <class T>
void displayVec(vector<T> &stuff, int tabs =2)
{
	//	if (stuff.size() > 0) {
	printf("\n");
	for (int i = 0; i < stuff.size(); i++) {
		for (int j = 0; j < tabs; j++)
			printf("\t");
		printf("%*u) %s\n", 3, i + 1, stuff[i].getName().c_str());
	}
	//	}
	//	else {
	//		for (int i = 0; i < tabs; i++)
	//			printf("\t");
	//		printf("Database is empty.");
	//	}
}

template <class T>
int getItem(vector<T> &stuff, string line, int tabs = 2)
{
	int pos;
	bool number;
	do {
		if (line == "q" || line == "Q")
			return -1;
		number = true;
		for (int i = 0; i < line.size(); i++)
			if (line[i] < '0' || line[i] > '9') {
				number = false;
				break;
			}
		if (number && line != "")
			pos = stoi(line) - 1;
		else pos = checkVec(stuff, line);
		if (pos > stuff.size() - 1 || pos < 0) {
			pos = -1;
			for (int i = 0; i < tabs; i++)
				printf("\t");
			printf("Improper input. Please select an existing item. ");
			getline(cin, line);
		}
	} while (pos == -1);
	return pos;
}

template <class T>
int checkVec(vector<T> &stuff, string line)
{
	for (int i = 0; i < stuff.size(); i++)
		if (stuff[i].getName() == line) {
			return i;
		}
	return -1;
}

