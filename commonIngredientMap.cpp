#include "commonIngredientMap.hpp"

using namespace std;

void CommonIngredientMap::addNode(string nodeName) {
    nodes.push_back(nodeName);
    adj.resize(nodes.size());
}

void CommonIngredientMap::addEdge(string u, string v, int w) {
    int uIndex = getIndex(u);
    int vIndex = getIndex(v);
    adj[uIndex].push_back(make_pair(vIndex, w));
    adj[vIndex].push_back(make_pair(uIndex, w));
}

int CommonIngredientMap::getIndex(string nodeName) {
    for (int i = 0; i < nodes.size(); ++i) {
        if (nodes[i] == nodeName) {
            return i;
        }
    }
    return -1;
}

void CommonIngredientMap::initializeEdges() {
    for (int i = 0; i < nodes.size(); i++) {
        for (int j = i + 1; j < nodes.size(); j++) {
            int commonIngredients = recipes.getCommonIngredients(nodes[i], nodes[j]);
            if (commonIngredients > 0) {
                addEdge(nodes[i], nodes[j], commonIngredients);
            }
        }
    }
}

priority_queue<Edge> CommonIngredientMap::nextMeals(string currentMeal) {
    priority_queue<Edge> nextMeals;
    int currentIndex = getIndex(currentMeal);
    for (const auto& edge : adj[currentIndex]) {
        nextMeals.push(Edge(nodes[edge.first], edge.second));
    }
    return nextMeals;
}

void CommonIngredientMap::print() {
    for (int i = 0; i < nodes.size(); ++i) {
        cout << endl;
        cout << "Adjacency list of node " << nodes[i] << ": ";
        for (const auto& edge : adj[i]) {
            cout << "(" << nodes[edge.first] << ", " << edge.second << ") ";
        }
        cout << endl;
    }
}