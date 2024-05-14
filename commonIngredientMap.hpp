#ifndef COMMONINGREDIENTMAP_H
#define COMMONINGREDIENTMAP_H

#include <iostream>
#include <vector>
#include <queue>
#include "recipeBook.hpp"

using namespace std;

struct Edge {
    string otherNode;
    int weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }

    Edge(string nodeName, int edgeWeight) : otherNode(nodeName), weight(edgeWeight) {}
};

class CommonIngredientMap {
    private:
        vector<string> nodes;
        vector<vector<pair<int, int>>> adj;
        RecipeBook& recipes;

    public:
        CommonIngredientMap(RecipeBook& input_recipes) : recipes(input_recipes) {
            this->nodes = input_recipes.getMealList();
            adj.resize(nodes.size());
            initializeEdges();
        }

        void addNode(string nodeName);

        void addEdge(string u, string v, int w);

        int getIndex(string nodeName);

        void initializeEdges();
        
        priority_queue<Edge> nextMeals(string currentMeal);

        void print();
};

#endif