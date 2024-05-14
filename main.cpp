#include "iostream"
#include "recipeBook.hpp"
#include "commonIngredientMap.hpp"

using namespace std;

void printSeperator() {
    cout << "----------------------------------------";
    cout << "----------------------------------------" << endl;
}

int main() {
    string menu_path;
    cout << "Welcome to the Smart Meal Planner!" << endl << endl;
    cout << "Please enter the path to the menu file: ";
    getline(cin, menu_path);
    cout << endl << "Initializing..." << endl;
    RecipeBook recipes(menu_path);
    CommonIngredientMap ingredient_map(recipes);
    cout << "Initialization complete!" << endl << endl;

    vector<string> today_ingredients;
    string today_ingredient;
    cout << "Please enter the ingredients you want to use today (enter ! to finish):" << endl;
    for (int i=0; ;) {
        cout << "Ingredient " << ++i << ": ";
        getline(cin, today_ingredient);
        // cout << endl;
        if (today_ingredient == "!") {
            break;
        }
        today_ingredients.push_back(today_ingredient);
        today_ingredient.clear();
    }

    cout << "Computing suggestions..." << endl << endl << endl;

    recipes.prioritizeMeals(today_ingredients);
    priority_queue<MealPriority> suggestionQueue = recipes.generateSuggestionQueue();

    printSeperator();
    cout << "Suggested meals for today ('Y' to choose, 'N' for another option):" << endl;
    for (int i = 0; !suggestionQueue.empty(); i++) {
        printSeperator();
        MealPriority meal = suggestionQueue.top();
        suggestionQueue.pop();
        vector<Ingredient> ingredientList = recipes.getMeal(meal.name)->getIngredientList();
        cout << "Option " << i+1 << ": ";
        cout << meal.name << endl;

        cout << "Required ingredients: ";
        for (int j = 0; j < ingredientList.size(); j++) {
            int priority = ingredientList[j].priority;
            if (priority == 0 or priority == 1) {
                cout << ingredientList[j].name << ", ";
            }
        }

        cout << endl;

        cout << "Other ingredients: ";
        for (int j = 0; j < ingredientList.size(); j++) {
            if (ingredientList[j].priority > 1) {
                cout << ingredientList[j].name << ", ";
            }
        }

        string choice;
        cout << endl << "--> Would you like to choose this meal? (Y/N): ";
        getline(cin, choice);
        printSeperator();
        if (choice == "Y" or choice == "y") {
            cout << endl;
            printSeperator();
            cout << meal.name << " were chosen for today!" << endl;
            cout << "This is the full list of ingredients: " << endl;
            for (int j = 0; j < ingredientList.size(); j++) {
                cout << j+1 << ". " << ingredientList[j].name << endl;
            }
            cout << endl;
            
            string next_meal_choice;
            cout << "Food waste due to left-over ingredient is a major concern." << endl;
            cout << "Making dishes that share common ingredients can help using up the left-over ingredients from today's meal" << endl;
            printSeperator();
            cout << "Do you want to see suggestions for next meal that have similar ingredients? (Y/N): ";
            getline(cin, next_meal_choice);
            
            if (next_meal_choice == "Y" or next_meal_choice == "y") {
                printSeperator();
                string current_meal = meal.name;
                priority_queue<Edge> nextMeals = ingredient_map.nextMeals(current_meal);

                for (int j=0; !nextMeals.empty(); j++) {
                    Edge nextMeal = nextMeals.top();
                    nextMeals.pop();
                    string mealName = nextMeal.otherNode;
                    vector<string> commonIngredients = recipes.getCommonIngredientsList(current_meal, mealName);
                    cout << "Option " << j+1 << ": " << mealName << endl;
                    cout << "Reusing " << commonIngredients.size() << " ingredients: " << endl;
                    if (!commonIngredients.empty()) {
                        for (int k = 0; k < commonIngredients.size(); k++) {
                            cout << k+1 << ". " << commonIngredients[k] << endl;
                        }
                    }
                    
                    string next_meal_suggestion_choice;
                    cout << "--> Would you like a different suggestion? (Y/N): ";
                    getline(cin, next_meal_suggestion_choice);
                    if (next_meal_suggestion_choice == "N" or next_meal_suggestion_choice == "n") {
                        cout << "Thank you for using the Smart Meal Planner!" << endl;
                        break;
                    }
                    cout << endl;
                }
            }
            break;
        }
    }
    return 0;
}