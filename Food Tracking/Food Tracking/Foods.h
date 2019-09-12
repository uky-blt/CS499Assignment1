#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Nutrient
	//Stores the nutrient in the food, identified by ID and amount so it can be very small.
{
	unsigned int ID;
	float amount;
};

class Foods
	//A food, storing the name of the food and a vector of nutrients (as defined above), as well as a bunch of utility functions created for the convinience of the main function.
{
private:
	string name;
	vector<Nutrient> nutrients;

public:
	Foods(string name);
	void addnutrient(unsigned int ID, string name, bool interact);
	void addnutrient(Nutrient nutrient);
	string getName() { return name; }
	void changeNut(unsigned int ID, string nutName);
	void changeNut(unsigned int pos, unsigned int newID);
	float getNutrient(unsigned int ID);
	int getNutPos(unsigned int ID);
	void removeNutrient(unsigned int ID);
	void swapNutrient(unsigned int ID1, unsigned int ID2);
	void accumNut(unsigned int nutID, float amnt);
	void accumNut(Foods food);
	void clear();
	void changeName(string name);
};

