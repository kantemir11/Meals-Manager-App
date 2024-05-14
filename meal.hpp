#ifndef MEAL_H
#define MEAL_H

#include <iostream>
#include <vector>

using namespace std;

struct Ingredient {
    string name;
    int priority = -1;
};

class Meal {
    private:
    public:
        string name;
        int numIngredients;
        Ingredient* ingredients;

        Meal(string name, int numIngredients, Ingredient* inputIngredients);

        int searchIngredient(string IngredientName);

        vector<Ingredient> getIngredientList();

        void updatePriority(string ingredientName, int priority);

        void prioritize(string ingredientName);

        int getIngredientPriority(string ingredientName);

        int getTotalPriority();

        int numberCommonIngredients(Meal* other);

        vector<string> getCommonIngredients(Meal* other);
};

#endif