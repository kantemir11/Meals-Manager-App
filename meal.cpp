#include "meal.hpp"

using namespace std;

Meal::Meal(string name, int numIngredients, Ingredient* inputIngredients) {
    this->name = name;
    this->numIngredients = numIngredients;
    this->ingredients = inputIngredients;
}

int Meal::searchIngredient(string IngredientName) {
    for (int i = 0; i < numIngredients; i++) {
        if (ingredients[i].name == IngredientName) {
            return i;
        }
    }
    return -1;
}

vector<Ingredient> Meal::getIngredientList() {
    vector<Ingredient> ingredientList;
    for (int i = 0; i < numIngredients; i++) {
        ingredientList.push_back(ingredients[i]);
    }
    return ingredientList;
}

void Meal::updatePriority(string ingredientName, int priority) {
    int index = searchIngredient(ingredientName);
    if (index == -1) {
        return;
    } else {
        ingredients[index].priority = priority;
    }
}

void Meal::prioritize(string ingredientName) {
    int index = searchIngredient(ingredientName);
    if (index == -1) {
        return;
    } else {
        ingredients[index].priority--;
    }
}

int Meal::getIngredientPriority(string ingredientName) {
    int index = searchIngredient(ingredientName);
    if (index != -1) {
        return ingredients[index].priority;
    }
    return -1;
}

int Meal::getTotalPriority() {
    int total = 0;
    for (int i = 0; i < numIngredients; i++) {
        total += ingredients[i].priority;
    }
    return total;
}

int Meal::numberCommonIngredients(Meal* other) {
    int commonIngredients = 0;
    for (int i = 0; i < numIngredients; i++) {
        for (int j = 0; j < other->numIngredients; j++) {
            if (ingredients[i].name == other->ingredients[j].name) {
                commonIngredients++;
                break;
            }
        }
    }
    return commonIngredients;
}

vector<string> Meal::getCommonIngredients(Meal* other) {
    vector<string> commonIngredients;
    for (int i = 0; i < numIngredients; i++) {
        for (int j = 0; j < other->numIngredients; j++) {
            if (ingredients[i].name == other->ingredients[j].name) {
                commonIngredients.push_back(ingredients[i].name);
                break;
            }
        }
    }
    return commonIngredients;
}