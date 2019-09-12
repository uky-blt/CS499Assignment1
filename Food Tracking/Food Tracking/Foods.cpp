#include "Foods.h"

using namespace std;

Foods::Foods(string name)
	: name(name)
{ }

void Foods::addnutrient(unsigned int ID, string name, bool interact)
//Adds a nutrient
{
	if (interact) {		//If interact is true (indicating it wants the user to be involved in the process):
		string line;
		float num;
		do {
			//Get the number of units of the nutrient in the food and ensure the user enters a proper input.
			printf("How many typical units of %s are in %s? ", name.c_str(), this->name.c_str());
			getline(cin, line);
			for (int i = 0; i < line.size(); i++)
				if ((line[i] < '0' || line[i] >'9') && line[i] != '.') {
					printf("Invalid number, try again. ");
					line = "-1";
				}
			if (line == "")
				num = 0;
			else num = stof(line);
		} while (num < 0);

		//Create the temporary nutrient to store the information
		Nutrient temp;
		temp.ID = ID;
		temp.amount = num;

		//Add that nutrient to the food.
		this->nutrients.push_back(temp);
	}
	else {
		//If the user is not to be involved, simply create have the food have no value for that nutrient
		Nutrient temp;
		temp.ID = ID;
		temp.amount = 0;
		this->nutrients.push_back(temp);
	}
}

void Foods::addnutrient(Nutrient nutrient)
//In this version, the amount of nutrient is supplied and directly input to the food.
{
	nutrients.push_back(nutrient);
}

void Foods::changeNut(unsigned int ID, string nutName)
//The information about the food is displayed and the user is asked what they want to change.
{
	string line;
	int num;
	//Strange way of selecting the nutrient. Basically there is a chance the ID is not the position (bad move, but is ingrained in the system now) (also the IDs will always be in chronological order).
	//		First try the ID as the position. If it is not correct, simply move closer one nutrient at a time.
	if (ID > nutrients.size() - 1)
		num = nutrients.size() - 1;
	else num = ID;
	while (nutrients[num].ID != ID) {
		if (nutrients[num].ID > ID)
			num++;
		else num--;
	}
	do {		//When nutrients[num] == ID, ask the user for the new amount, ensure it is a proper input, then apply the new value.
		printf("\tWhat is the amount of %s in this food? ", nutName.c_str());
		getline(cin, line);
		for (int i = 0; i < line.size(); i++)
			if ((line[i] < '0' || line[i]>'9') && line[i] != '.')
				line = "-1";
		if (line == "")
			nutrients[num].amount = 0;
		else
			nutrients[num].amount = stof(line);
	} while (num < 0);
}

void Foods::changeNut(unsigned int pos, unsigned int newID)
//If a new ID is supplied for a position, change the ID at that position. It is up to the main program not to make 2 nutrients the same ID and to ensure they stay chronological.
{
	nutrients[pos].ID = newID;
	return;
}

float Foods::getNutrient(unsigned int ID)
//Find the nutrient by iterating over the nutrients and finding which one matches the ID.
{
	for (int i = 0; i < nutrients.size(); i++)
		if (nutrients[i].ID == ID)
			return nutrients[i].amount;
	return -1;
}

int Foods::getNutPos(unsigned int ID)
//Get the position of the nutrient by finding the nutrient that matches the ID, then return the position of that.
{
	int num;
	if (ID > nutrients.size() - 1)
		num = nutrients.size() - 1;
	else num = ID;
	while (nutrients[num].ID != ID) {
		if (nutrients[num].ID > ID)
			num++;
		else num--;
	}
	return num;
}

void Foods::removeNutrient(unsigned int ID)
//Remove a nutrient with the ID provided.
{
	int pos = this->getNutPos(ID);
	nutrients.erase(nutrients.begin() + pos);
	return;
}

void Foods::swapNutrient(unsigned int pos1, unsigned int pos2) 
//swap the nutrients at 2 given positions.
{
	Nutrient temp;
	temp = nutrients[pos1];
	nutrients[pos1] = nutrients[pos2];
	nutrients[pos2] = temp;
	nutrients[pos2].ID = nutrients[pos1].ID;
	nutrients[pos1].ID = temp.ID;
	return;
}

void Foods::accumNut(unsigned int nutID, float amnt)
//Add the amount into the amount of the nutrient with ID nutID.
{
	int pos = this->getNutPos(nutID);
	this->nutrients[pos].amount += amnt;
}

void Foods::accumNut(Foods food)
//Add the nutrients from all foods for all nutrients (all nutrients have the same ID in the same position, so just adding position to position should be fine).
{
	for (int i = 0; i < food.nutrients.size(); i++)
		this->nutrients[i].amount += food.nutrients[i].amount;
	return;
}

void Foods::clear()
//For all nutrients, set the nutrient to 0.
{
	for (int i = 0; i < nutrients.size(); i++)
		nutrients[i].amount = 0;
}

void Foods::changeName(string name)
//Change the name to the name provided.
{
	this->name = name;
}