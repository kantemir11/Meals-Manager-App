#include "recipeBook.hpp"

using namespace std;

Ingredient* generateIngredientList(string* ingredientNames, int* priorities, int numIngredients) {
    Ingredient* ingredients = new Ingredient[numIngredients];
    for (int i = 0; i < numIngredients; i++) {
        ingredients[i].name = ingredientNames[i];
        ingredients[i].priority = priorities[i];
    }
    return ingredients;
}


RecipeBook::RecipeBook(string menu_path) {
    this->numMeals = 0;
    initializeFromTxt(menu_path);
}

void RecipeBook::initializeFromTxt(string menu_path) {
    ifstream inputFile(menu_path);
    if (!inputFile.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }

    string mealName;
    vector<string> ingredients;
    vector<int> priorities;

    string line;
    int count = 0;
    while (getline(inputFile, line)) {
        if (line.empty()) continue;
        else if (line[0] == '-') {
            size_t pos = line.find_last_of('(');
            size_t prio = stoi(line.substr(pos + 1, 1));
            ingredients.push_back(line.substr(2, pos - 3));
            priorities.push_back(prio);
        } else {
            if (!mealName.empty()) {
                addMeal(mealName, ingredients, priorities);
                mealName.clear();
                ingredients.clear();
                priorities.clear();
            }
            mealName = line;
        }
    }
    if (!mealName.empty()) addMeal(mealName, ingredients, priorities);

    inputFile.close();
}

void RecipeBook::addMeal(string mealName, vector<string> ingredients, vector<int> priorities) {
    Ingredient* ingredientsList = generateIngredientList(ingredients.data(), priorities.data(), ingredients.size());
    Meal* meal = new Meal(mealName, ingredients.size(), ingredientsList);
    mealsPointers.push_back(meal);
    numMeals++;
}

Meal* RecipeBook::getMeal(string name) {
    for (list<Meal*>::iterator it = mealsPointers.begin(); it != mealsPointers.end(); it++) {
        if ((*it)->name == name) {
            return *it;
        }
    }
    return NULL;
}

unordered_set<string> RecipeBook::getIngredientList() {
    unordered_set<string> ingredientList;
    for (list<Meal*>::iterator it = mealsPointers.begin(); it != mealsPointers.end(); it++) {
        for (int i = 0; i < (*it)->numIngredients; i++) {
            ingredientList.insert((*it)->ingredients[i].name);
        }
    }
    return ingredientList;
}

vector<string> RecipeBook::getMealList() {
    vector<string> mealList;
    for (list<Meal*>::iterator it = mealsPointers.begin(); it != mealsPointers.end(); it++) {
        mealList.push_back((*it)->name);
    }
    return mealList;
}

int RecipeBook::getCommonIngredients(string meal1, string meal2) {
    Meal* meal1Pointer = getMeal(meal1);
    Meal* meal2Pointer = getMeal(meal2);
    return meal1Pointer->numberCommonIngredients(meal2Pointer);
}

vector<string> RecipeBook::getCommonIngredientsList(string meal1, string meal2) {
    Meal* meal1Pointer = getMeal(meal1);
    Meal* meal2Pointer = getMeal(meal2);
    return meal1Pointer->getCommonIngredients(meal2Pointer);
}

MealPriority* RecipeBook::getMealPriorities() {
    MealPriority* priorities = new MealPriority[numMeals];
    int i = 0;
    for (list<Meal*>::iterator it = mealsPointers.begin(); it != mealsPointers.end(); it++) {
        priorities[i].name = (*it)->name;
        priorities[i].priority = (*it)->getTotalPriority();
        i++;
    }
    return priorities;
}

void RecipeBook::prioritizeMeals(vector<string> ingredientList) {
    for (list<Meal*>::iterator it = mealsPointers.begin(); it != mealsPointers.end(); it++) {
        Meal meal = **it;
        for (int i = 0; i < ingredientList.size(); i++) {
            meal.prioritize(ingredientList[i]);
        }
    }
}

priority_queue<MealPriority> RecipeBook::generateSuggestionQueue() {
    priority_queue<MealPriority> suggestionQueue;
    MealPriority* priorities = getMealPriorities();
    for (int i = 0; i < numMeals; i++) {
        suggestionQueue.push(priorities[i]);
    }
    return suggestionQueue;
}

void RecipeBook::print() {
    for (list<Meal*>::iterator it = mealsPointers.begin(); it != mealsPointers.end(); it++) {
        cout << (*it)->name << ":" << endl;
        for (int i = 0; i < (*it)->numIngredients; i++) {
            cout << "- " << (*it)->ingredients[i].name << " " << (*it)->ingredients[i].priority << endl;
        }
    }
}