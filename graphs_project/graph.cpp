#include "graph.h"
#include <fstream>
#include <sstream>

void Node::addNeighbour(Node* neighbour) {
    neighbours.insert(neighbour);
}

void Node::removeNeighbour(Node* neighbour) {
    neighbours.erase(neighbour);
}

void Graph::addNode(Node* node) {
    nodes.insert(node);
    nameToNode[node->getName()] = node;
}

void Graph::removeNode(Node* node) {
    nodes.erase(node); 
    nameToNode.erase(node->getName());
    for (std::set<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
        (*it)->removeNeighbour(node); 
    }
}

void Graph::addEdge(Node* begin, Node* end) {
    if (nodes.find(begin) == nodes.end()) return; 
    if (nodes.find(end) == nodes.end()) return; 
    
    begin->addNeighbour(end); 
    end->addNeighbour(begin); 
}

void Graph::removeEdge(Node* begin, Node* end) {
    if (nodes.find(begin) == nodes.end() || nodes.find(end) == nodes.end()) return;
    begin->removeNeighbour(end);
    end->removeNeighbour(begin);
}

Node* Graph::findNode(const std::string& name) const {
    auto it = nameToNode.find(name);
    if (it != nameToNode.end()) {
        return it->second;
    }
    return nullptr;
}

Graph::Graph(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    // Проверяем первую строку на наличие заголовков (типа Source,Target)
    std::getline(file, line);
    if (line.find("Source") == std::string::npos && line.find("source") == std::string::npos) {
        // Если заголовка нет, возвращаем указатель чтения в начало файла
        file.clear();
        file.seekg(0, std::ios::beg);
    }

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        for (char& c : line) {
            if (c == ',') c = ' ';
        }

        std::stringstream ss(line);
        std::string sourceName, targetName;
        if (ss >> sourceName >> targetName) {
            Node* sourceNode = findNode(sourceName);
            if (!sourceNode) {
                sourceNode = new Node(sourceName);
                addNode(sourceNode);
            }
            Node* targetNode = findNode(targetName);
            if (!targetNode) {
                targetNode = new Node(targetName);
                addNode(targetNode);
            }
            addEdge(sourceNode, targetNode);
        }
    }
    file.close();
}

Graph::~Graph() {
    for (Node* node : nodes) {
        delete node;
    }
}