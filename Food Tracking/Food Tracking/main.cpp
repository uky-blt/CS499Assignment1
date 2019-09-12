/*
Creator: Ben Tonges
This project is meant to be a basic food tracking system. 
The database will hold nutritional information on different foods.
The user will be able to create profiles where they select foods to be in their diet.
They will then be able to use the software to calculate total calorie and nutritional inputs.
Will also be able to determine total nutritional completness of diet. Can tell user what percentage of each nutrition is being fulfilled, point out deficiencies.
Potential calorie count as well. 
Maybe a cost analysis per meal or something way later.

NOTE: This program uses a Binary Search Tree I created. I did it mainly because I felt like it, as it is used very inefficiently in this program.
	Theoretically I could have a number of trees for each Nutritional node that would be more efficient, but that could end up memory intensive and I only wanted practice making the tree, so I don't care that it is currently inefficient.

TO DO:
In user Profile:
	Allow for editing of meals and mealplans.
		Adding meals, changing the makeup/amounts of meals, etc.
	Look for other errors.

	Potential Features:
	Potentially get a weekly plan and average the sum of the week by 7 days to get a daily average, then recommend foods based on those deficiencies.
	Calorie calculations?

Flesh out everything.
*/


#include <iostream>
#include <string>
#include <fstream>

//#include "Foods.h"
//#include "BinaryTree.h"
//#include "Profile.h"
#include "Utility.h"

using namespace std;

int getnum(int max, bool Qabil);
void saveFile(vector<NutList> &Nutrients, vector<Foods> &Food, vector<Profile> &profileList, bool choose);
void loadFile(vector<NutList> &NutrientList, vector<Foods> &Food, vector<Profile> &profileList, bool choose);
string confirmation();
void displayFood(vector<Foods> food, vector<NutList> &Nutrients);

/*
struct NutList
{
	string name;
	string units;
	unsigned int ID;
	unsigned int recAmnt;

	string getName()
	{
		return name;
	}
};

int getnum(int max, bool Qabil);
template <class T>
void displayVec(vector<T> &Food, int num);
template <class T>
int getItem(vector<T> &stuff, string line);
template <class T>
int checkVec(vector<T> &stuff, string line);
string confirmation();
/*  OLD AND POTENTIALLY USELESS
int checkVec(vector<Foods> &Food, string line);
int checkVec(vector<NutList> &Nutrient, string line);

int getItem(vector<Foods> &Food, string line);
int getItem(vector<NutList> &Nutrients, string line);
*/

int main()
{
	vector<Foods> Food;
	vector<NutList> NutrientList;
	vector<Profile> profileList;
	Profile activeProfile("Default");
	string line, confirm;
	bool flag;
	int num, pos, activeProfilePos;


	system("mode 237");
	loadFile(NutrientList, Food, profileList, false);
	cout << "Welcome to the food tracking program.";
	cout << "\nWhat would you like to do (enter Q to quit):\n\n1)\tView Food Database.\n2)\tEdit Food Database.\n3)\tEnter Profile.\n:";
	num = getnum(3, true);

	while (num != 0) {

		if (num == 1) {
			printf("\n\tWhat would you like to do:\n\t1)\tDisplay the Food Database.\n\t2)\tDisplay the Nutrient Database.\n\t3)\tSort the Database.\n\t:");
			num = getnum(3, true);
			while (num != 0) {

				if (num == 1) {
					if (Food.size() > 0) {
						printf("\n\t\tWould you like to display the foods:\n\t\t1)\tWith Nutrients.\n\t\t2)\tWithout Nutrients.\n\t\t:");
						num = getnum(2, true);
						if (num == 1) {
							if (Food.size() == 0)
								printf("\t\tThe database is empty.\n");
							else {
								displayFood(Food, NutrientList);
								/*
								int counter = Food.size();
								int round = 0;
								while (counter > 13) {
									printf("\n%*s", 15, "-");
									for (int i = 0; i < 13; i++)
										printf(" %s%*s-", (Food[13 * round + i].getName().size() > 15) ? Food[13 * round + i].getName().substr(0, 15).c_str() : Food[13 * round + i].getName().c_str(), (Food[13 * round + i].getName().size() > 15) ? 0 : 15 - Food[13 * round + i].getName().size(), "");
									for (int i = 0; i < NutrientList.size(); i++) {
										printf("\n%s%*s-", NutrientList[i].name.c_str(), 14 - NutrientList[i].name.size(), "");
										for (int j = 0; j < 13; j++)
											printf("%*.0f %s%*s-", 9, Food[13 * round + j].getNutrient(NutrientList[i].ID), NutrientList[i].units.c_str(), 6 - NutrientList[i].units.size(), "");
									}
									printf("\n");
									cin.ignore();
									counter -= 13;
									round++;
								}
								if (counter > 0) {
									printf("\n%*s", 15, "-");
									for (int i = 0; i < counter; i++)
										printf(" %s%*s-", (Food[13*round+i].getName().size() > 15)? Food[13 * round + i].getName().substr(0,15).c_str() : Food[13 * round + i].getName().c_str(), (Food[13 * round + i].getName().size() > 15) ? 0: 15 - Food[13 * round + i].getName().size(), "");
									for (int i = 0; i < NutrientList.size(); i++) {
										printf("\n%s%*s-", NutrientList[i].name.c_str(), 14 - NutrientList[i].name.size(), "");
										for (int j = 0; j < counter; j++)
											printf("%*.0f %s%*s-", 9, Food[13 * round + j].getNutrient(NutrientList[i].ID), NutrientList[i].units.c_str(), 6 - NutrientList[i].units.size(), "");
									}
									printf("\n\n");
								}
								*/
							}
						}
						else if (num == 2) {
							printf("\t\t");
							displayVec(Food, 0);
							printf("\n");
						}
					}
					else printf("\tThere are no foods to display.\n");
				}

				else if (num == 2) {
					printf("\n Nutrient           : Reccommended Amount\n");
					printf(" -------------------|--------------------\n");
					for (int i = 0; i < NutrientList.size(); i++) {
						printf(" %s%*s: %*.1f %s\n", NutrientList[i].name.c_str(), 19 - NutrientList[i].name.size(), "", 7, NutrientList[i].recAmnt, NutrientList[i].units.c_str());
					}
				}

				else if (num == 3) {
					printf("\n\t\tWould you like to:\n\t\t1)\tSort the Foods.\n\t\t2)\tSort the Nutrients.\n\t\t:");
					num = getnum(2, true);
					if (num == 1) {
						if (Food.size() > 0) {
							printf("\t\t\tHow would you like to sort the Food database?\n\t\t\t1)\tAlphabetically.\n\t\t\t2)\tBy Nutrient Content.\n\t\t\t:");
							num = getnum(2, true);
							if (num == 1) {
								BinaryTree tree;
								for (int i = 0; i < Food.size(); i++)
									tree.addNode(0, Food[i].getName(), i);

								node* place = tree.firstNode();
								vector <Foods> temp;
								printf("\n");
								while (place != nullptr) {
									printf("\t\t\t%s\n", place->name.c_str());
									place = tree.nextNode(place);
								}

								printf("\n\t\t\tWould you like to save this as the order Foods are displayed in (y/n)? ");
								confirm = confirmation();
								if (confirm == "y" || confirm == "Y") {
									vector<Foods> temp;
									place = tree.firstNode();
									while (place != nullptr) {
										temp.push_back(Food[place->pos]);
										place = tree.nextNode(place);
									}
									for (int i = 0; i < profileList.size(); i++) {
										printf("TODO?: SORT STUFF IN PROFILES??");
									}
									swap(temp, Food);
									printf("\t\t\tFood database successfully sorted.");
									cin.ignore();
								}
								tree.~BinaryTree();
							}
							else if (num == 2) {
								displayVec(NutrientList, 3);
								printf("\n\t\t\tWhich nutrient would you like to sort by? ");
								getline(cin, line);
								pos = getItem(NutrientList, line, 3);
								if (pos != -1) {
									num = NutrientList[pos].ID;
									BinaryTree tree;
									for (int i = 0; i < Food.size(); i++)
										tree.addNode(Food[i].getNutrient(num), Food[i].getName(), i);

									node* place = tree.firstNode();
									while (place != nullptr) {
										printf("\n\t\t\t%*s%*d %s", 15, place->name.size() < 15 ? place->name.c_str() :  place->name.substr(0,14).c_str(), 5, place->value, NutrientList[pos].units.c_str());
										place = tree.nextNode(place);
									}

									printf("\n\n\t\t\tWould you like to save this as the order Foods are displayed in (y/n)? ");
									confirm = confirmation();
									if (confirm == "y" || confirm == "Y") {
										vector<Foods> temp;
										place = tree.firstNode();
										while (place != nullptr) {
											temp.push_back(Food[place->pos]);
											place = tree.nextNode(place);
										}
										swap(temp, Food);
										printf("\t\t\tFood database successfully sorted.\n");
										cin.ignore();
									}
									tree.~BinaryTree();
								}
							}
						}
						else printf("\t\tThere are no foods in the database to be sorted.\n");
					}
					else if (num == 2) {
						if (NutrientList.size() > 0) {
							printf("\n\t\t\tHow would you like to order the nutrients?\n\t\t\t1)\tAlphabetically.\n\t\t\t2)\tBy Selection.\n\t\t\t:");
							num = getnum(2, true);
							if (num == 1) {
								BinaryTree tree;
								for (int i = 0; i < NutrientList.size(); i++)
									tree.addNode(0, NutrientList[i].name, i);
								node* place = tree.firstNode();
								while (place != nullptr) {
									printf("\n\t\t\t%s", place->name.c_str());
									place = tree.nextNode(place);
								}
								printf("\n\n\t\t\tWould you like to save the current Nutrient ordering (y/n)? ");
								confirm = confirmation();
								if (confirm == "y" || confirm == "Y") {
									place = tree.firstNode();
									int count = 0;
									while (place != nullptr) {
										line = place->name;
										for (int i = 0; i < NutrientList.size(); i++) {
											if (NutrientList[i].name == line) {
												for (int j = 0; j < Food.size(); j++)
													Food[j].swapNutrient(i, count);
												NutList temp;
												temp = NutrientList[count];
												NutrientList[count] = NutrientList[i];
												NutrientList[i] = temp;
												NutrientList[count].ID = count;
												NutrientList[i].ID = i;
												break;
											}
										}
										count++;
										place = tree.nextNode(place);
									}
									for (int i = 0; i < NutrientList.size(); i++) {
										for (int j = 0; j < Food.size(); j++)
											Food[j].changeNut(i, i);
										NutrientList[i].ID = i;
									}
									printf("\n\t\t\tNutrient order saved.");
									cin.ignore();
								}
							}
							else if (num == 2) {  //	SEEMS INEFFICIENT. IF BECOMES A PROBLEM, REWORK.
								displayVec(NutrientList, 3);
								printf("\t\t\t%*d) Set the rest in alphabetical order.\n", 3, NutrientList.size() + 1);

								vector<int> list;
								BinaryTree tree;
								bool ok;
								printf("\n\t\t\tWhich Nutrient would you like to be first? ");
								int i = 0;
								while (i < NutrientList.size()) {
									do {
										do {
											getline(cin, line);
											ok = true;
											for (int j = 0; j < line.size(); j++)
												if (line[j] < '0' || line[j] > '9' || line == "")
													ok = false;
											if (ok)
												num = stoi(line);
											else
												num = getItem(NutrientList, line, 3) + 1;
											if (!ok || num > NutrientList.size() + 1 || num < 1)
												printf("\n\t\t\tThat is an invalid input, please try again. ");
										} while (!ok);
										ok = true;
										for (int j = 0; j < list.size(); j++)
											if (list[j] == num)
												ok = false;
										if (!ok)
											printf("\t\t\tThat nutrient has already been selected. Which Next? ");
									} while (!ok);

									if (num != NutrientList.size() + 1) {
										tree.addNode(NutrientList.size() - i, NutrientList[num - 1].name, num - 1);
										list.push_back(num);
										i++;
									}

									else {
										for (int j = 0; j < NutrientList.size(); j++) {
											ok = true;
											for (int k = 0; k < list.size(); k++)
												if (list[k] == j + 1) {
													ok = false;
													break;
												}
											if (ok) {
												tree.addNode(0, NutrientList[j].name, j);
												i++;
											}
										}
									}

									if (i != NutrientList.size())
										printf("\t\t\tWhich Next? ");
								}

								node* place = tree.firstNode();
								while (place != nullptr) {
									printf("\n\t\t\t%s", place->name.c_str());
									place = tree.nextNode(place);
								}
								printf("\n\n\t\t\tWould you like to save the current Nutrient ordering (y/n)? ");
								confirm = confirmation();
								if (confirm == "y" || confirm == "Y") {
									place = tree.firstNode();
									int count = 0;
									while (place != nullptr) {
										line = place->name;
										for (int i = 0; i < NutrientList.size(); i++) {
											if (NutrientList[i].name == line) {
												for (int j = 0; j < Food.size(); j++)
													Food[j].swapNutrient(i, count);
												NutList temp;
												temp = NutrientList[count];
												NutrientList[count] = NutrientList[i];
												NutrientList[i] = temp;
												NutrientList[count].ID = count;
												NutrientList[i].ID = i;
												break;
											}
										}
										count++;
										place = tree.nextNode(place);
									}
									printf("\n\t\t\tNutrient order successfully saved.\n");
								}
								else
									printf("\n\t\t\tNutrient order not saved.\n");
								cin.ignore();
							}
						}
						else printf("\t\tThere are currently no nutrients to sort.\n");
					}
				}

				printf("\n\tWhat would you like to do:\n\t1)\tDisplay the Food Database.\n\t2)\tDisplay the Nutrient Database.\n\t3)\tSort the Database.\n\t:");
				num = getnum(3, true);
			}
		}

		else if (num == 2) {
			while (num != 0) {
				cout << "\n\tWhat would you like to do (enter Q to quit):\n\n\t1)\tAdd Food.\n\t2)\tEdit Food.\n\t3)\tRemove Food.\n\t4)\tAdd Nutrient.\n\t5)\tRemove Nutrient.\n\t6)\tLoad Database.\n\t7)\tSave Database.\n\t:";
				num = getnum(7, true);

				if (num == 1) {
					cout << "\n\tFood Name: ";
					getline(cin, line);
					printf("\tWould you like to add food named %s to database (y/n)? ", line.c_str());
					confirm = confirmation();
					if (confirm == "y" || confirm == "Y") {
						pos = checkVec(Food, line);
						if (pos == -1) {
							Foods temp(line);
							Food.push_back(temp);
							printf("\tWould you like to add all nutrients manually (y/n)? ");
							confirm = confirmation();
							if (confirm == "y" || confirm == "Y")
								for (int i = 0; i < NutrientList.size(); i++) {
									printf("\t");
									Food[Food.size() - 1].addnutrient(NutrientList[i].ID, NutrientList[i].name, true);
								}
							else {
								Nutrient tempNut;
								tempNut.amount = 0;
								for (int i = 0; i < NutrientList.size(); i++) {
									printf("\t");
									tempNut.ID = NutrientList[i].ID;
									Food[Food.size() - 1].addnutrient(tempNut);
								}
							}
						}
						else
							printf("\t%s already exists within the database.", line.c_str());
					}
				}

				else if (num == 2) {
					if (Food.size() > 0) {
						displayVec(Food, 1);
						if (Food.size() > 0) {
							cout << "\n\tWhich food would you like to edit? ";
							getline(cin, line);
							pos = getItem(Food, line, 1);
							int temp = pos;
							if (pos != -1) {
								while (pos != -1) {
									for (int i = 0; i < NutrientList.size(); i++)
										printf("\n\t%*d) %s%*s%*.1f %s", 3, i + 1, NutrientList[i].name.c_str(), 20 - NutrientList[i].name.size(), "", 7, Food[temp].getNutrient(NutrientList[i].ID), NutrientList[i].units.c_str());
									printf("\n\n\tWhich nutrient needs to be changed for %s? ", Food[temp].getName().c_str());
									getline(cin, line);
									pos = getItem(NutrientList, line, 1);
									if (pos != -1)
										Food[temp].changeNut(NutrientList[pos].ID, NutrientList[pos].name);
								}
							}
						}
					}
					else printf("\tThere are no foods in the database to edit.\n");
				}

				else if (num == 3) {
					if (Food.size() == 0)
						printf("\tThere are no foods in the database to remove.\n");
					else {
						displayVec(Food, 1);
						cout << "\tWhich Food would you like to delete? ";
						getline(cin, line);
						pos = getItem(Food, line);
						if (pos != -1) {
							printf("\tAre you sure you want to delete %s permanantly (y/n)? ", Food[pos].getName().c_str());
							confirm = confirmation();
							if (confirm == "Y" || confirm == "y") {
								Food.erase(Food.begin() + pos);
							}
						}
						else
							cout << "\tThis food does not exist within the database.";
					}
				}

				else if (num == 4) {
					printf("\n\tWhat is the name of the Nutrient would you like to add? ");
					getline(cin, line);
					pos = checkVec(NutrientList, line);
					if (pos > 0)
						printf("\tThe nutrient is already accounted for.");
					else {
						NutList nutrient;
						nutrient.name = line;
						float tempnum;
						if (NutrientList.size() > 0)
							nutrient.ID = NutrientList[NutrientList.size() - 1].ID + 1;
						else nutrient.ID = 0;
						printf("\tWhat is the nutrient typically measured in? ");
						getline(cin, confirm);
						nutrient.units = confirm;
						do {
							printf("\tWhat is the reccommended daily amount of the nutrient? ");
							getline(cin, confirm);
							for (int i = 0; i < confirm.size(); i++)
								if ((confirm[i] < '0' || confirm[i] > '9') && confirm[i] != '.') {
									confirm = "-1";
									break;
								}
							tempnum = stof(confirm);
						} while (tempnum < 0);
						nutrient.recAmnt = tempnum;
						printf("\n\tNutrient Name: %s\n\tReccommended Daily Amount: %.1f %s\n", nutrient.name.c_str(), nutrient.recAmnt, nutrient.units.c_str());
						printf("\n\tAre you sure you want to add this nutrient (y/n)? ");
						confirm = confirmation();
						if (confirm == "Y" || confirm == "y") {
							NutrientList.push_back(nutrient);

							printf("\tWould you like to manually add this nutrient in all foods (y/n)? ");
							confirm = confirmation();
							if (confirm == "y" || confirm == "Y")
								for (int i = 0; i < Food.size(); i++) {
									printf("\t");
									Food[i].addnutrient(num, line, true);
								}
							else
								for (int i = 0; i < Food.size(); i++)
									Food[i].addnutrient(num, line, false);
						}
					}
				}

				else if (num == 5) {
					if (NutrientList.size() > 0) {
						displayVec(NutrientList, 1);
						printf("\n\n\tWhich nutrient would you like to remove ? ");
						getline(cin, line);
						pos = getItem(NutrientList, line, 1);
						printf("\tAre you sure you want to remove this nutrient permanantly (y/n)? ");
						confirm = confirmation();
						if (confirm == "y" || confirm == "Y") {
							int nutID = NutrientList[pos].ID;
							for (int i = 0; i < Food.size(); i++)
								Food[i].removeNutrient(nutID);
							NutrientList.erase(NutrientList.begin() + pos);
							printf("\tNutrient Successfully Removed.\n");
						}
					}
					else printf("\tThere are no nutrients availible to delete.\n");
				}

				else if (num == 6) {
					printf("Would you like to load the default database (y/n)? ");
					line = confirmation();
					bool choose = true;
					if (line == "y" || line == "Y")
						choose = false;
					loadFile(NutrientList, Food, profileList, choose);
				}

				else if (num == 7) {
					printf("Would you like to store this as the default database (y/n)? ");
					line = confirmation();
					bool choose = true;
					if (line == "y" || line == "Y")
						choose = false;
					saveFile(NutrientList, Food, profileList, choose);
				}
			}
		}

		else if (num == 3) {
			while (num != 0) {
				printf("\n\tWhat would you like to do:\n\t1)\tEnter a profile.\n\t2)\tCreate New Profile.\n\t3)\tDelete Profile.\n\t:");
				num = getnum(3, true);

				if (num == 1) {
					printf("\n\tWhat profile would you like to enter? ");
					getline(cin, line);
					pos = checkVec(profileList, line);
					if (pos == -1) {
						printf("\tThat profile name was not found, would you like to create it now (y/n)? ");
						confirm = confirmation();
						if (confirm == "Y" || confirm == "y") {
							Profile temp(line);
							profileList.push_back(temp);
							printf("\n\tProfile successfully created.");
						}
						printf("\n");
					}
					else {

						activeProfile = profileList[pos];
						activeProfilePos = pos;
						printf("\n\nENTERING PROFILE...\n\n");
						cin.ignore();
						printf("Welcome to your profile %s!\n", activeProfile.getName().c_str());
						printf("\nWhat would you like to do?\n1)\tView Nutritional Information.\n2)\tEdit Profile.\n:");
						num = getnum(2, true);
						while (num != 0) {
							
							if (num == 1) {
								if (activeProfile.meals.size() > 0) {
									printf("\n\t1)\tView Mealplan.\n\t2)\tView Single Meal.\n\t3)???\n\t:");
									num = getnum(2, true);
									while (num != 0) {

										if (num == 1) {
											if (activeProfile.mealPlans.size() > 0) {
												displayVec(activeProfile.mealPlans, 1);
												printf("\n\tWhich meal plan would you like to display? ");
												getline(cin, line);
												int mealPos = getItem(activeProfile.mealPlans, line, 1);
												if (mealPos > -1) {
													if (activeProfile.mealPlans[mealPos].meals.size() > 0) {
														Foods total("Total"), temp("temp");
														Nutrient tempNut;
														vector<Foods> meals;
														tempNut.amount = 0;
														for (int i = 0; i < NutrientList.size(); i++) {
															tempNut.ID = NutrientList[i].ID;
															total.addnutrient(tempNut);
															temp.addnutrient(tempNut);
														}
														int pos2;
														for (int i = 0; i < activeProfile.mealPlans[mealPos].meals.size(); i++) {
															pos = activeProfile.mealPlans[mealPos].meals[i];
															for (int j = 0; j < activeProfile.meals[pos].mealFoods.size(); j++) {
																pos2 = getItem(Food, activeProfile.meals[pos].mealFoods[j].foodName);
																for (int k = 0; k < NutrientList.size(); k++)
																	temp.accumNut(NutrientList[k].ID, Food[pos2].getNutrient(NutrientList[k].ID)*activeProfile.meals[pos].mealFoods[j].numServings);
															}
															temp.changeName(activeProfile.meals[activeProfile.mealPlans[mealPos].meals[i]].mealName);
															meals.push_back(temp);
															total.accumNut(temp);
															temp.clear();
														}
														displayFood(meals, NutrientList);
														
														printf("%*s-Total Nutrients -   Percentage   - Reccommended Food\n", 15, "");
														for (int i = 0; i < NutrientList.size(); i++) {
															printf("%s%*s%*.1f %s%*s-%*.1f %%      - ", (NutrientList[i].name.size() > 15) ? NutrientList[i].name.substr(0, 15).c_str() : NutrientList[i].name.c_str(), 16 - NutrientList[i].name.size(), "-", 9, total.getNutrient(NutrientList[i].ID), NutrientList[i].units.c_str(), 6 - NutrientList[i].units.size(), "", 9, total.getNutrient(NutrientList[i].ID) / NutrientList[i].recAmnt * 100.0f);

															if (total.getNutrient(NutrientList[i].ID) / NutrientList[i].recAmnt * 100.0f < 100.0f) {
																pos = 0;
																for (int j = 0; j < Food.size(); j++)
																	if (Food[j].getNutrient(NutrientList[i].ID) > Food[pos].getNutrient(NutrientList[i].ID))
																		pos = j;
																printf("%s\n", (pos == 0 && Food[pos].getNutrient(NutrientList[i].ID) == 0.0f) ? "None" : Food[pos].getName().c_str());
															}
															else printf("\n");
														}

														/*
														printf("\nTotal Nutrients in %s:\n", activeProfile.mealPlans[mealPos].planName.c_str());
														vector<int> deficiencies;
														for (int i = 0; i < NutrientList.size(); i++) {
															printf("%*s: %*.1f %*s  %*.1f%%\n", 15, NutrientList[i].name.c_str(), 7, total.getNutrient(NutrientList[i].ID), 3, NutrientList[i].units.c_str(), 7, total.getNutrient(NutrientList[i].ID) / NutrientList[i].recAmnt * 100.0f);
															if (total.getNutrient(NutrientList[i].ID) / NutrientList[i].recAmnt * 100.0f < 100.0f)
																deficiencies.push_back(i);
														}
														vector<int> deficReccom(deficiencies.size(), 0);
														for (int i = 0; i < Food.size(); i++) {
															for (int j = 0; j < deficiencies.size(); j++) {
																if (Food[i].getNutrient(deficiencies[j]) > Food[deficReccom[j]].getNutrient(deficiencies[j]))
																	deficReccom[j] = i;
															}
														}
														printf("\nYou are deficient in:\n");
														for (int i = 0; i < deficiencies.size(); i++)
															printf("%s%*s\tReccommended Food: %s\n", NutrientList[deficiencies[i]].name.c_str(), 25- NutrientList[deficiencies[i]].name.size(), "", (deficReccom[i] == 0 && Food[0].getNutrient(NutrientList[deficiencies[i]].ID) == 0) ? "None" : Food[deficReccom[i]].getName().c_str());
														*/
													}
													else printf("\n\tThe mealplan is currently empty.\n");
												}
											}
											else printf("\n\tThere are currently no Meal Plans.\n");
										}

										else if (num == 2) {
											displayVec(activeProfile.meals, 1);
											printf("\n\tWhich meal would you like to view? ");
											getline(cin, line);
											pos = getItem(activeProfile.meals, line, 1);
											if (pos > -1) {
												Foods total("Total");
												Nutrient tempNut;
												tempNut.amount = 0;
												for (int i = 0; i < NutrientList.size(); i++) {
													tempNut.ID = NutrientList[i].ID;
													total.addnutrient(tempNut);
												}
												int pos2;
												for (int i = 0; i < activeProfile.meals[pos].mealFoods.size(); i++) {
													pos2 = getItem(Food, activeProfile.meals[pos].mealFoods[i].foodName);
													for (int j = 0; j < NutrientList.size(); j++)
														total.accumNut(NutrientList[j].ID, Food[pos2].getNutrient(NutrientList[j].ID)*activeProfile.meals[pos].mealFoods[i].numServings);
												}
												printf("\n%*s-Total Nutrients -   Percentage\n", 15, "");
												for (int i = 0; i < NutrientList.size(); i++)
													printf("%s%*s%*.1f %s%*s-%*.1f %%\n", (NutrientList[i].name.size() > 15) ? NutrientList[i].name.substr(0, 15).c_str() : NutrientList[i].name.c_str(), 16 - NutrientList[i].name.size(), "-", 9, total.getNutrient(NutrientList[i].ID), NutrientList[i].units.c_str(), 6 - NutrientList[i].units.size(), "", 9, total.getNutrient(NutrientList[i].ID) / NutrientList[i].recAmnt * 100.0f);
												printf("\n");
											}
										}

										printf("\n\t1)\tView Mealplan.\n\t2)\tView Single Meal.\n\t:");
										num = getnum(2, true);
									}
								}
								else printf("\n\tThere are no meals yet.\n");
							}

							else if (num == 2) {
								printf("\n\tHow would you like to edit the profile?\n\t1)\tEdit Meal Archive.\n\t2)\tEdit Meal Plans.\n\t3)\tChange Profile Name.\n\t:");
								num = getnum(3, true);
								while (num != 0) {

									if (num == 1) {
										printf("\n\t\tWhat would you like to do?\n\t\t1)\tAdd meal to archive.\n\t\t2)\tRemove Meal from archive.\n\t\t:");
										num = getnum(2, true);
										if (num == 1)
											activeProfile.addMeal(Food);

										else if (num == 2) {
											if (activeProfile.meals.size() > 0) {
												displayVec(activeProfile.meals, 2);
												printf("\n\t\tWhich meal would you like to remove? ");
												getline(cin, line);
												pos = getItem(activeProfile.meals, line, 2);
												if (pos > -1) {
													printf("\t\tRemoving this meal will automatically remove it from any Meal Plans utilizing it. Are you sure you would like to delete the meal %s permanantly (y/n)? ", activeProfile.meals[pos].mealName.c_str());
													confirm = confirmation();
													if (confirm == "y" || confirm == "Y") {
														for (int i = 0; i < activeProfile.mealPlans.size(); i++)
															for (int j = activeProfile.mealPlans[i].meals.size() - 1; j >= 0; j--)
																if (activeProfile.mealPlans[i].meals[j] == pos)
																	activeProfile.mealPlans[i].meals.erase(activeProfile.mealPlans[i].meals.begin() + j);
																else if (activeProfile.mealPlans[i].meals[j] > pos) activeProfile.mealPlans[i].meals[j]--;
														activeProfile.meals.erase(activeProfile.meals.begin() + pos);
														printf("\n\t\tMeal was removed successfully.\n");
													}
													else printf("\n\t\tMeal was not removed.\n");
												}
											}
											else printf("\n\t\tThere were no meals to delete.\n");
										}

									}
									/*		CHANGE MEAL. DECIDED ITS EASIER JUST TO HAVE USER DELETE AND REDO MEAL.
									else if (num == 2) {
										displayVec(activeProfile.meals, 1);
										printf("\tWhich meal would you like to change? ");
										getline(cin, line);
										pos = getItem(activeProfile.meals, line);
										if (pos > -1) {
											printf("\tWhat would you like to change?\n\t1)\tMeal Name.\n\t2)\tFoods in Meal.\n\t:");
											getline(cin, line);
											getnum(2, true);
											if (num == 1) {
												printf("What would you like the meal name to be? ");
												getline(cin, line);
												activeProfile.meals[pos].mealName = line;
											}
											else if (num == 2) {
												printf("\n\t\tWould you like to\n\t\t1)\tAdd food to meal.\n\t\t2)\tDelete food from meal.\n\t\t:");
												num = getnum(2, true);
												if (num == 1) {

												}
												else if (num == 2) {

												}
											}
										}
									}
									*/

									else if (num == 2) {
										printf("\n\t\tWould you like to:\n\t\t1)\tEdit an existing meal plan.\n\t\t2)\tAdd a new meal plan.\n\t\t3)\tDelete an existing meal plan.\n\t\t:");
										num = getnum(3, true);
										while (num != 0) {

											if (num == 1) {
												if (activeProfile.mealPlans.size() > 0) {
													displayVec(activeProfile.mealPlans, 2);
													printf("\n\t\tWhich meal plan would you like to edit? ");
													getline(cin, line);
													int mealPos = getItem(activeProfile.mealPlans, line, 2);
													if (mealPos > -1) {
														printf("\n\t\t\tWhat would you like to do?\n\t\t\t1)\tAdd meal to meal plan.\n\t\t\t2)\tRemove meal from meal plan.\n\t\t\t:");
														num = getnum(2, true);

														if (num == 1) {
															displayVec(activeProfile.meals, 3);
															do {
																printf("\n\t\t\tWhat meal would you like to add to the meal plan? ");
																getline(cin, line);
																pos = getItem(activeProfile.meals, line, 3);
																if (pos > -1) {
																	activeProfile.mealPlans[mealPos].meals.push_back(pos);
																	printf("\t\t\tMeal Added.\n");
																}
															} while (pos > -1);
														}

														else if (num == 2) {
															if (activeProfile.mealPlans[mealPos].meals.size() != 0) {
																vector<MealTrack> temp;
																for (int i = 0; i < activeProfile.mealPlans[mealPos].meals.size(); i++)
																	temp.push_back(activeProfile.meals[activeProfile.mealPlans[mealPos].meals[i]]);
																displayVec(temp, 3);
																printf("\n\t\t\tWhich meal would you like to delete from the meal plan? ");
																getline(cin, line);
																pos = getItem(temp, line, 3);
																if (pos > -1) {
																	pos = activeProfile.mealPlans[mealPos].meals[pos];
																	printf("\n\t\t\tAre you sure you would like to delete %s from the meal plan permanantly (y/n)? ", activeProfile.meals[activeProfile.mealPlans[mealPos].meals[pos]].mealName.c_str());
																	confirm = confirmation();
																	pos = getItem(temp, line, 3);
																	if (confirm == "y" || confirm == "Y") {
																		activeProfile.mealPlans[mealPos].meals.erase(activeProfile.mealPlans[mealPos].meals.begin() + pos);
																		printf("\n\t\t\tMeal was deleted successfully.\n");
																	}
																	else printf("\n\t\t\tMeal was not deleted.\n");
																}
															}
															else printf("\n\t\t\tThere were no meals in the plan to delete.\n");
														}
													}
												}
											}

											else if (num == 2) {
												printf("\n\t\tWhat would you like to name the new Meal Plan? ");
												getline(cin, line);
												MealPlan temp;
												temp.planName = line;
												activeProfile.mealPlans.push_back(temp);
											}

											else if (num == 3) {
												displayVec(activeProfile.mealPlans, 2);
												printf("\n\t\tWhich plan would you like to delete? ");
												getline(cin, line);
												pos = getItem(activeProfile.mealPlans, line, 3);
												if (pos > -1) {
													printf("\t\tAre you sure you want to delete the meal plan %s (y/n)? ", activeProfile.mealPlans[pos].planName.c_str());
													confirm = confirmation();
													if (confirm == "y" || confirm == "Y") {
														activeProfile.mealPlans.erase(activeProfile.mealPlans.begin() + pos);
														printf("\n\t\tMeal plan erased.\n");
													}
													else printf("\n\t\tMeal Plan not erased.\n");
												}
											}

											printf("\n\t\tWould you like to:\n\t\t1)\tEdit an existing meal plan.\n\t\t2)\tAdd a new meal plan.\n\t\t3)\tDelete an existing meal plan.\n\t\t:");
											num = getnum(3, true);
										}
									}

									else if (num == 3) {
										activeProfile.changeName(profileList);
									}


									printf("\n\tHow would you like to edit the profile?\n\t1)\tEdit Meal Archive.\n\t2)\tEdit Meal Plans.\n\t3)\tChange Profile Name.\n\t:");
									num = getnum(3, true);
								}
							}

							printf("\nWhat would you like to do?\n1)\tView Nutritional Intake.\n2)\tEdit Profile.\n:");
							num = getnum(2, true);
						}
						printf("\n\nYou are now exiting your profile. Would you like to apply any changes made (y/n)? ");
						confirm = confirmation();
						if (confirm == "y" || confirm == "Y") {
							profileList[activeProfilePos] = activeProfile;
							printf("All changes were saved.\n");
						}
						else printf("No changes were saved.\n");
					}
				}

				else if (num == 2) {
					printf("\n");
					Profile temp("Default");
					if (temp.changeName(profileList)) {
						profileList.push_back(temp);
						printf("\n\tProfile %s successfully created.\n", profileList[profileList.size() - 1].getName().c_str());
					}
					else printf("\tProfile not created.\n");
				}

				else if (num == 3) {
					if (profileList.size() > 0) {
						printf("\tWhich profile would you like to delete? ");
						getline(cin, line);
						pos = checkVec(profileList, line);
						if (pos != -1) {
							printf("\n\tAre you sure you would like to permanantly delete this profile (y/n)? ");
							confirm = confirmation();
							if (confirm == "Y" || confirm == "y") {
								profileList.erase(profileList.begin() + pos);
								printf("\n\tProfile successfully deleted.\n");
							}
						}
						else printf("\n\tThere is no profile by that name.\n");
					}
					else printf("\n\tThere are currently no profiles.\n");
				}
			}
		}

		cout << "\nWhat would you like to do (enter Q to quit):\n\n1)\tView Food Database.\n2)\tEdit Food Database.\n3)\tEnter Profile.\n:";
		num = getnum(3, true);
	}

	printf("\nWould you like to save the default database and profiles before quitting (y/n)? ");
	confirm = confirmation();
	if (confirm == "Y" || confirm == "y")
		saveFile(NutrientList, Food, profileList, false);

	return 0;
}

int getnum(int max, bool Qabil)
//This function gets a number input from the user. The max number is specified in 'max' (min being 1) and Qabil represents the ability to quit (exit with 0) by entering 'q' or 'Q'.
{
	int num = 0;
	string line;
	do {
		getline(cin, line);									//Get the user input
		if (Qabil && (line == "q" || line == "Q")) {		//If Qabil is true and user enters q, the function num is 0 (theoretically not a number option) and breaks out of the loop
			num = 0;
			break;
		}
		else if (line == "")								//If the line is empty, make it invalid (-1)
			line = "-1";

		//Check all characters to ensure they are all digits. If not, make line invalid (-1)
		for (int i = 0; i < line.size(); i++)
			if (line[i] < '0' || line[i] > '9') {
				line = "-1";
				break;
			}
		num = stoi(line);									//Convert the input (which even if invalid before has been changed to a number) to a number.

		//If the input is not a valid number (not a number or out of range), display a message informing the user that their selection was invalid.
		if (num < 1 || num > max) {
			printf("That is an invalid number. Please enter a number between 1 and %d", max);
			if (Qabil)
				printf(" or press Q to quit. ");
			else
				printf(". ");
			num = -1;
		}
	} while (num == -1);		//Continue this validation process until a valid number is input.

	return num;		//Return the valid number (either a selected valid number or the 
}

void saveFile(vector<NutList> &Nutrients, vector<Foods> &Food, vector<Profile> &profileList, bool choose)
//Saves the database (both nutrients, foods, and profiles) with proper formatting to a .db file, which can be chosen if the variable choose is true, otherwise it saves to the default db.db
{
	string line;
	//If choose is true, allow user to choose the db name, else just set it to db.
	if (choose) {
		printf("What file would you like to store the database in? ");
		getline(cin, line);
	}
	else line = "db";

	//Create and ensure the file is good. If not, display an error message.
	fstream file;
	file.open(line + ".db", fstream::out);
	if (file.fail()) {
		printf("File failed to open.");
		return;
	}
	else {
		//Begin sending the Nutrient information to the file.
		file << Nutrients.size() << "\n";
		for (int i = 0; i < Nutrients.size(); i++)
			file << Nutrients[i].ID << "\t" << Nutrients[i].name << "\t" << Nutrients[i].recAmnt << "\t" << Nutrients[i].units << "\n";
		//Begin sending the food information to the file.
		for (int i = 0; i < Food.size(); i++) {
			file << Food[i].getName();
			for (int j = 0; j < Nutrients.size(); j++)
				file << "\t" << Nutrients[j].ID << "\t" << Food[i].getNutrient(Nutrients[j].ID);
			file << "\n";
		}
		file << "[eodb]\n";		//Indicator for the end of the general food database

		//Begin sending profile information to the database.
		for (int i = 0; i < profileList.size(); i++) {
			file << "{" << profileList[i].getName() << "}\n";		//Profile name
			for (int j = 0; j < profileList[i].meals.size(); j++) {
				file << profileList[i].meals[j].mealName <<  "\t";		//Each meal displays the meal name, tab, each food name used followed by a space and the number of servings, then a tab, and at the end, an endline.
				for (int k = 0; k < profileList[i].meals[j].mealFoods.size(); k++) {
					for (int l = 0; l < Food.size(); l++)
						if (Food[l].getName() == profileList[i].meals[j].mealFoods[k].foodName) {
							file << l << " ";
							break;
						}
					file << profileList[i].meals[j].mealFoods[k].numServings << "\t";
				}
				file << "\n";
			}
			file << "[eofb]\n";		//Once profile food database is finished, send this end of profile food database indicator

			//Begin sending the mealplans of the profile, with name, a tab, then all meals seperated by a space with a \n at the end of each mealplan.
			for (int k = 0; k < profileList[i].mealPlans.size(); k++) {
				file << profileList[i].mealPlans[i].planName;
				file << "\t";
				for (int j = 0; j < profileList[i].mealPlans[k].meals.size(); j++)
					file << profileList[i].mealPlans[k].meals[j] << " ";
				file << "\n";
			}
		}

		//Indicate the save was successful.
		printf("File Saved Successfully\n");
	}
	return;
}

void loadFile(vector<NutList> &NutrientList, vector<Foods> &Food, vector<Profile> &profileList, bool choose)
//Loads the file from the file to the proper places in the program memory. If choose is true the user can input the file they want to load from, otherwise defaults to db
{
	fstream file;
	string line, filename;
	int num, pos;
	if (choose) {		//If choose is true, have user input filename.
		printf("What file is the database stored in? ");
		getline(cin, filename);
	}
	else filename = "db";

	//Open file and check if found. If not, output an error message depending on if choose is true or not.
	file.open(filename + ".db", fstream::in);
	if (!file.good()) {
		if (choose) {
			printf("The file could not be found.");
			cin.ignore();
		}
		else printf("The Default Database was not found. Remember to save before quitting.\n\n\n");
	}
	else {
		//For each of the different vectors in the program, empty them.
		NutrientList.clear();
		Food.clear();
		profileList.clear();

		NutList temp;
		getline(file, line);
		num = stoi(line);		//Get the number right at the beginning of the file. If it is saved correclty, this indicates the  number of nutrients.

		//For that number, load in the nutrient information. Name, ID, reccomended Amount, and Units.
		for (int i = 0; i < num; i++) {
			getline(file, line);
			pos = line.find("\t");
			temp.ID = stoi(line.substr(0, pos));
			line = line.substr(pos + 1);
			pos = line.find("\t");
			temp.name = line.substr(0, pos);
			line = line.substr(pos + 1);
			pos = line.find("\t");
			temp.recAmnt = stof(line.substr(0, pos));
			temp.units = line.substr(pos + 1);

			NutrientList.push_back(temp);
		}
		Nutrient tempnut;
		getline(file, line);

		//Until the [eodb] identifier has been reached, begin loading in the foods into the database
		while (line != "[eodb]") {
			pos = line.find("\t");
			Foods tempfood(line.substr(0, pos));
			for (int i = 0; i < num; i++) {
				line = line.substr(pos + 1);
				pos = line.find("\t");
				tempnut.ID = stoll(line.substr(0, pos));
				line = line.substr(pos + 1);
				pos = line.find("\t");
				tempnut.amount = stof(line.substr(0, pos));

				tempfood.addnutrient(tempnut);
			}
			Food.push_back(tempfood);
			getline(file, line);
		}
		getline(file, line);
		Profile tempProf("temp");
		int counter;

		//After [eodb] begin loading the Profiles.
		while (!file.eof()) {
			tempProf.changeName(line.substr(1, line.size() - 2));
			getline(file, line);
			MealTrack tempMeal;
			FoodTrack tempFood;

			//Load in the meals to the profile
			while (line != "[eofb]") {
				pos = line.find('\t');
				tempMeal.mealName = line.substr(0, pos);
				line = line.substr(pos + 1);
				pos = line.find(' ');
				while (pos != -1) {
					tempFood.foodName = Food[stoi(line.substr(0, pos))].getName();
					line = line.substr(pos + 1);
					pos = line.find('\t');
					tempFood.numServings = stof(line.substr(0, pos));
					line = line.substr(pos + 1);
					pos = line.find(' ');
					tempMeal.mealFoods.push_back(tempFood);
				}
				tempProf.meals.push_back(tempMeal);

				tempMeal.mealFoods.clear();
				getline(file, line);
			}
			getline(file, line);
			MealPlan tempPlan;
			
			//Begin loading in the mealplans based on the formatting of the saves
			while (!file.eof()) {
				if (line[0] != '{' && line[line.size() - 1] != '}') {
					counter = 0;
					pos = line.find('\t');
					tempPlan.planName = line.substr(0, pos);
					line = line.substr(pos + 1);
					pos = line.find(' ');
					while (pos != -1) {
						tempPlan.meals.push_back(stoi(line.substr(0, pos)));
						line = line.substr(pos + 1);
						pos = line.find(' ');
						counter++;
					}
					tempProf.mealPlans.push_back(tempPlan);
					tempPlan.meals.clear();
					getline(file, line);
				}
				else break;
			}
			profileList.push_back(tempProf);
			tempProf.mealPlans.clear();
			tempProf.meals.clear();
		}
		if (!choose)
			printf("Default ");
		printf("Database Loaded Successfully\n\n\n");
	}
	file.close();
}

string confirmation()
//Get an input from the user, check if it is  y or n, capital or not, and if so, return that character, else continue having the user input until they give a proper input.
{
	string confirm;
	do {
		getline(cin, confirm);
		if (confirm != "y" && confirm != "Y" && confirm != "n" && confirm != "N") {
			confirm = "-1";
			printf("Please enter y or n. ");
		}
	} while (confirm == "-1");
	return confirm;
}

void displayFood(vector<Foods> food, vector<NutList> &Nutrients) 
//Take in the vecotr of foods and the nutrient list. From there, display every food with it's nutrients.
{
	int counter = food.size();
	int round = 0;
	while (counter > 13) {
		printf("\n%*s", 16, "-");
		for (int i = 0; i < 13; i++)
			printf(" %s%*s-", (food[13 * round + i].getName().size() > 15) ? food[13 * round + i].getName().substr(0, 15).c_str() : food[13 * round + i].getName().c_str(), (food[13 * round + i].getName().size() > 15) ? 0 : 16 - food[13 * round + i].getName().size(), "-");
		for (int i = 0; i < Nutrients.size(); i++) {
			printf("\n%s%*s-", (Nutrients[i].getName().size() > 15) ? Nutrients[i].name.substr(0,15).c_str() : Nutrients[i].name.c_str(), 16 - Nutrients[i].name.size(), "-");
			for (int j = 0; j < 13; j++)
				printf("%*.1f %s%*s-", 9, food[13 * round + j].getNutrient(Nutrients[i].ID), Nutrients[i].units.c_str(), 7 - Nutrients[i].units.size(), "-");
		}
		printf("\n");
		cin.ignore();
		counter -= 13;
		round++;
	}
	if (counter > 0) {
		printf("\n%*s", 16, "-");
		for (int i = 0; i < counter; i++)
			printf(" %s%*s", (food[13 * round + i].getName().size() > 15) ? food[13 * round + i].getName().substr(0, 15).c_str() : food[13 * round + i].getName().c_str(), (food[13 * round + i].getName().size() > 15) ? 0 : 16 - food[13 * round + i].getName().size(), "-");
		for (int i = 0; i < Nutrients.size(); i++) {
			printf("\n%s%*s", (Nutrients[i].getName().size() > 15) ? Nutrients[i].getName().substr(0, 15).c_str() : Nutrients[i].name.c_str(), 16 - Nutrients[i].getName().size(), "-");
			for (int j = 0; j < counter; j++)
				printf("%*.1f %s%*s", 9, food[13 * round + j].getNutrient(Nutrients[i].ID), Nutrients[i].units.c_str(), 7 - Nutrients[i].units.size(), "-");
		}
		printf("\n\n");
	}
}

/*
int getnum(int max, bool Qabil)
{
	int num = 0;
	string line;
	do {
		getline(cin, line);
		if (Qabil && (line == "q" || line == "Q")) {
			num = 0;
			break;
		}
		else if (line == "")
			line = -1;
		for (int i = 0; i < line.size(); i++)
			if (line[i] < '0' || line[i] > '9') {
				line = "-1";
				break;
			}
		num = stoi(line);
		if (num < 1 || num > max) {
			printf("That is an invalid number. Please enter a number between 1 and %d", max);
			if (Qabil)
				printf(" or press Q to quit. ");
			else
				printf(". ");
			num = -1;
		}
	} while (num == -1);

	return num;
}

template <class T>
void displayVec(vector<T> &stuff, int tabs)
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
int getItem(vector<T> &stuff, string line)
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
		if (number)
			pos = stoi(line) - 1;
		else pos = checkVec(stuff, line);
		if (pos > stuff.size() - 1 || pos < 0) {
			pos = -1;
			printf("\tImproper input. Please select which item needs to be changed. ");
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

string confirmation()
{
	string confirm;
	do {
		getline(cin, confirm);
		if (confirm != "y" && confirm != "Y" && confirm != "n" && confirm != "N") {
			confirm = "-1";
			printf("Please enter y or n. ");
		}
	} while (confirm == "-1");
	return confirm;
}

/* OLD AND POTENTIALLY USELESS NOW
int checkVec(vector<Foods> &Food, string line)
{
for (int i = 0; i < Food.size(); i++)
if (Food[i].getName() == line) {
return i;
}
return -1;
}

int checkVec(vector<NutList> &Nutrient, string line)
{
for (int i = 0; i < Nutrient.size(); i++)
if (Nutrient[i].name == line) {
return i;
}
return -1;
}


int getItem(vector<Foods> &Food, string line)
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
if (number)
pos = stoi(line) - 1;
else pos = checkVec(Food, line);
if (pos > Food.size() - 1 || pos < 0) {
pos = -1;
printf("\tImproper input. Please select which food needs to be changed. ");
getline(cin, line);
}
} while (pos == -1);
return pos;
}

int getItem(vector<NutList> &Nutrients, string line)
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
if (number)
pos = stoi(line) - 1;
else pos = checkVec(Nutrients, line);
if (pos > Nutrients.size() - 1 || pos < 0) {
pos = -1;
printf("\tImproper input. Please select which nutrient needs to be changed. ");
getline(cin, line);
}
} while (pos == -1);
return pos;
}
*/