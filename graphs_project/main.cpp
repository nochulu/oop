#include <iostream>
#include <fstream>
#include <set>
#include "graph.h"
#include "bfs.h"

using namespace std;

// Сохранение ребер компоненты связности в файл структуры аналогичной исходной
void saveComponentToFile(const std::set<Node*>& component, const std::string& outputFilename) {
    ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        cerr << "Failed to open output file: " << outputFilename << std::endl;
        return;
    }

    outFile << "Source\tTarget\n";
    
    // Множество для исключения дублирования ребер (ведь граф неориентированный, 0-1 и 1-0 это одно ребро)
    set<pair<string, string>> writtenEdges;

    for (Node* node : component) {
        for (node_iterator it = node->nb_begin(); it != node->nb_end(); it++) {
            Node* neighbour = *it;
            
            string u = node->getName();
            string v = neighbour->getName();
            if (u > v) swap(u, v); // Нормализуем порядок имен в паре

            if (writtenEdges.find({u, v}) == writtenEdges.end()) {
                outFile << u << "\t" << v << "\n";
                writtenEdges.insert({u, v});
            }
        }
    }
    outFile.close();
    cout << "Saved component with " << component.size() << " nodes to -> " << outputFilename << endl;
}

// Общая функция обработки любого файла графа
void processGraphFile(const string& inputFilename, const string& prefix) {
    cout << "\n--- Processing: " << inputFilename << " ---" << endl;
    
    // Создаем граф из файла 
    Graph graph(inputFilename);
    BFS bfs(graph);

    set<Node*> globalVisited;
    int componentCount = 0;

    // Итерируемся по всем вершинам графа для поиска непересекающихся подграфов
    for (node_iterator it = graph.begin(); it != graph.end(); it++) {
        Node* currentNode = *it;

        // Если вершина еще не была посещена ни в одной из предыдущих компонент
        if (globalVisited.find(currentNode) == globalVisited.end()) {
            componentCount++;
            
            // Выделяем подграф при помощи BFS 
            set<Node*> component = bfs.getComponent(currentNode, globalVisited);
            
            // Формируем имя файла 
            string outName = prefix + "_comp_" + to_string(componentCount) + ".txt";
            saveComponentToFile(component, outName);
        }
    }
   cout << "Success! Total components found: " << componentCount << endl;
}

int main() {
    //  Тестовый файл графа
    processGraphFile("testgraph.txt", "TestGraph");

    // Основной файл графа 
    processGraphFile("1000.csv", "1000");

    cout << "\nAll tasks completed successfully!" << endl;
    system("pause");
    return 0;
}