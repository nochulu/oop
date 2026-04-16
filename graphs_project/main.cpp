#include <iostream>
#include "graph.h"
#include "bfs.h"
#include "dfs.h"

int main() {
    Graph myGraph;

    Node* n0 = new Node("0");
    Node* n1 = new Node("1");
    Node* n2 = new Node("2");
    Node* n3 = new Node("3");
    Node* n4 = new Node("4");
    Node* n5 = new Node("5");

    myGraph.addNode(n0);
    myGraph.addNode(n1);
    myGraph.addNode(n2);
    myGraph.addNode(n3);
    myGraph.addNode(n4);
    myGraph.addNode(n5);

    myGraph.addEdge(n0, n1);
    myGraph.addEdge(n1, n2);
    myGraph.addEdge(n0, n3);
    myGraph.addEdge(n3, n4);
    myGraph.addEdge(n4, n5);
    myGraph.addEdge(n0, n5); 

    BFS bfs(myGraph);
    std::cout << "BFS: Path 1 to 4 exists? " << (bfs.connected(n1, n4) ? "Yes" : "No") << std::endl;

    DFS dfs(myGraph);
    std::cout << "DFS: Path 2 to 3 exists? " << (dfs.connected(n2, n3) ? "Yes" : "No") << std::endl;

    myGraph.removeNode(n5);
    std::cout << "After removing node 5, DFS 0 to 5: " << (dfs.connected(n0, n5) ? "Yes" : "No") << std::endl;

    delete n0; delete n1; delete n2; delete n3; delete n4; delete n5;
    system("pause");
    return 0;
}