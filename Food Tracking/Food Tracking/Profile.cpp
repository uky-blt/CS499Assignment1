#include "Profile.h"

Profile::Profile(string name)
	: name(name)
{ }

bool Profile::changeName(vector<Profile> profileList)
//Changes the name of the profile. If used this way, will request that the user enter a name for the profile and step them through the process of creating a new one.
{
	string line, confirm;
	bool good;
	do {
		printf("\t");
		do {			//While a profile name has not been selected:
			good = true;
			printf("What would you like the new name of your profile to be? ");		//Get the name of the profile
			getline(cin, line);
			if (line == "q" || line == "Q")		//If the user enters q, simply exit without getting the profile name,
				break;
			for (int i = 0; i < profileList.size(); i++) {		//Ensure the profile name is not already in use, if so, display error and ask again
				if (profileList[i].name == line) {
					good = false;
					break;
				}
			}
			if (!good) printf("\tThat profile name is already in use. ");
		} while (!good);
		if (line != "q" && line != "Q") {		//If the user did not enter q,

			//Confirm the profile name,
			printf("\tSo your new profile name is %s (y/n)? ", line.c_str());		
			do {
				good = true;
				getline(cin, confirm);
				if (confirm != "y" && confirm != "Y" && confirm != "n" && confirm != "N") {
					printf("\tInvalid, please enter y or n. ");
					good = false;
				}
			} while (!good);
			if (confirm == "Y" || confirm == "y") {
				name = line;
				good = false;
			}
		}
		else return false;		//If the user entered q, quit and return false, indicating the profile was not created.
	} while (good);
	return true;		//If everything worked out, return true indicating the profile name was successfully changed.
}

void Profile::changeName(string name)
{
	this->name = name;
}

void Profile::addMeal(vector<Foods> Food)
{
	int pos;
	bool ok;
	string line;
	MealTrack tempMeal;
	FoodTrack tempFood;
	printf("\n\t\tWhat is the name of this meal? ");
	getline(cin, line);
	tempMeal.mealName = line;
	displayVec(Food, 2);
	printf("\n\t\tEnter q to end selection.\n\n");
	while (line != "q" && line != "Q") {
		ok = true;
		printf("\t\tSelect a food used in this meal: ");
		getline(cin, line);
		if (line != "q" && line != "Q") {
			pos = getItem(Food, line);
			if (pos > -1) {
				tempFood.foodName = Food[pos].getName();
				do {
					printf("\t\tHow many servings of %s are in this meal? ", tempFood.foodName.c_str());
					getline(cin, line);
					for (int i = 0; i < line.size(); i++)
						if ((line[i] <'0' || line[i] > '9') && line[i] != '.') {
							ok = false;
							printf("\t\tImproper input. ");
						}
				} while (!ok);
				tempFood.numServings = stof(line);
				tempMeal.mealFoods.push_back(tempFood);
			}
			else printf("\t\tImproper input. ");
		}
	}
	meals.push_back(tempMeal);
	return;
}

void Profile::addMeal(string name, vector<FoodTrack> meals)
{
	MealTrack meal;
	meal.mealName = name;
	meal.mealFoods = meals;
	this->meals.push_back(meal);
}

