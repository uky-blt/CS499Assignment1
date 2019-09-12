/*
Created By:	Ben Tonges
Date:		8/15/2018
Description:This .h file contains most things for profile used by the main program.
*/
#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Foods.h"
#include "Utility.h"

using namespace std;

struct FoodTrack
	//Struct used to hold a food and the number of servings of said food used.
{
	string foodName;
	float numServings;
};

struct MealTrack
	//Struct used to hold a meal, including the meal name and a vector of food structs used in the meal.
{
	string mealName;
	vector<FoodTrack> mealFoods;
	string getName() { return mealName; }
};

struct MealPlan
	//Struct to hold a meal plan. Includes the plan name, and a vector of the meals used in the 
{
	string planName;
	vector<unsigned int> meals;
	string getName() { return planName; }
};

class Profile
	//Profile class, holds the meals used by the profile, the meal plans planned by the profile, the name of the profile, and a series of functions useful in the profile.
{
public:
	vector<MealTrack> meals;
	vector<MealPlan> mealPlans;
private:
	string name;
//	vector<FoodTrack> totalFoods;

public:
	Profile(string name);
	bool changeName(vector<Profile> profileList);
	void changeName(string name);
	string getName() { return name; }
	void addMeal(vector<Foods> Food);
	void addMeal(string name, vector<FoodTrack> meals);
	//void changeMeal(vector<Foods> Food);
};

