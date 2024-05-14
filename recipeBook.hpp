#ifndef RECIPEBOOK_H
#define RECIPEBOOK_H

#include <iostream>
#include <list>
#include <fstream>
#include <queue>
#include <unordered_set>
#include "meal.hpp"

using namespace std;

struct MealPriority {
    string name;
    int priority = -1;
    bool operator<(const MealPriority& other) const {
        return priority >= other.priority; // use the default maxHeap as a minHeap
    }
};

Ingredient* generateIngredientList(string* ingredientNames, int* priorities, int numIngredients);

class RecipeBook {
    private:
        list<Meal*> mealsPointers;

    public:
        int numMeals;
        RecipeBook(string menu_path);

        void initializeFromTxt(string menu_path);

        void addMeal(string mealName, vector<string> ingredients, vector<int> priorities);

        Meal* getMeal(string name);

        unordered_set<string> getIngredientList();

        vector<string> getMealList();

        int getCommonIngredients(string meal1, string meal2);

        vector<string> getCommonIngredientsList(string meal1, string meal2);

        MealPriority* getMealPriorities();

        void prioritizeMeals(vector<string> ingredientList);

        priority_queue<MealPriority> generateSuggestionQueue();

        void print();
};

#endif