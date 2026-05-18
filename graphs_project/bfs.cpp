#include "bfs.h"

bool BFS::connected(Node* begin, Node* end) {
    if (begin == end) return true;

    std::queue<Node*> nodes; 
    std::set<Node*> visited; 

    nodes.push(begin); 
    visited.insert(begin); 

    while (!nodes.empty()) {
        Node* next = nodes.front(); 
        nodes.pop(); 

        if (next == end) return true; 

        for (node_iterator it = next->nb_begin(); it != next->nb_end(); it++) { 
            if (visited.find(*it) == visited.end()) { 
                visited.insert(*it); 
                nodes.push(*it); 
            }
        }
    }
    return false; 
}

// BFS-обход для сбора всех вершин одной компоненты связности
std::set<Node*> BFS::getComponent(Node* start, std::set<Node*>& globalVisited) {
    std::set<Node*> component;
    std::queue<Node*> nodes;

    nodes.push(start);
    globalVisited.insert(start);
    component.insert(start);

    while (!nodes.empty()) {
        Node* next = nodes.front();
        nodes.pop();

        for (node_iterator it = next->nb_begin(); it != next->nb_end(); it++) {
            if (globalVisited.find(*it) == globalVisited.end()) {
                globalVisited.insert(*it);
                component.insert(*it);
                nodes.push(*it);
            }
        }
    }
    return component;
}