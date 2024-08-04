#include <iostream>
#include <climits> // Use INT_MAX for clarity

// Node structure representing each node in the graph
struct Node {
    int distanceValue; // Distance value for shortest path calculations
    int status; // Status of the node (visited or not)
    char data; // Data held by the node (e.g., vertex identifier)
    int weight; // Weight of the edge
    Node *next; // Pointer to the next node in the list
    Node *adjacent; // Pointer to the adjacent nodes (edges)
};

// Graph class to manage graph operations
class Graph {
private:
    Node *startNode; // Pointer to the starting node of the graph
public:
    Graph() {
        startNode = nullptr; // Initialize start node to null
        createGraph();
    }

    ~Graph() {
        // Destructor to clean up dynamically allocated memory
        Node *currentNode = startNode, *tempNode;
        while (currentNode != nullptr) {
            tempNode = currentNode;
            currentNode = currentNode->next;
            delete tempNode;
        }
    }

    // Function prototypes
    void createGraph();
    int findShortestPath(char targetVertex);
    char getStartNodeData();

    // Temporary pointers for graph operations
    Node *currentNode, *previousNode, *tempNode, *linkNode;
};

// Function to get the data of the start node
char Graph::getStartNodeData() {
    if (startNode != nullptr)
        return startNode->data;
    return '\0'; // Return null character if start node is not set
}

// Function to create the graph by inputting nodes and their connections
void Graph::createGraph() {
    int isFirstNode = 1, edgeWeight;
    char nodeData;
    std::cout << "\nEnter the nodes in the graph (press x to exit): ";

    // Input nodes until 'x' is entered
    while (true) {
        std::cin >> nodeData;
        if (nodeData == 'x') {
            break;
        }

        // Create new node
        currentNode = new Node;
        currentNode->data = nodeData;
        currentNode->status = 0;
        currentNode->next = nullptr;
        currentNode->adjacent = nullptr;

        // Set start node if it's the first node
        if (isFirstNode) {
            startNode = currentNode;
            previousNode = currentNode;
            isFirstNode = 0;
        } else {
            previousNode->next = currentNode;
            previousNode = currentNode;
        }
    }

    // Input edges for each node
    currentNode = startNode;
    while (currentNode != nullptr) {
        std::cout << "\nEnter the links to " << currentNode->data << " (x to exit): ";
        isFirstNode = 1;

        while (true) {
            std::cin >> nodeData;
            if (nodeData == 'x') {
                break;
            }

            // Create new edge node
            tempNode = new Node;
            tempNode->adjacent = nullptr;
            tempNode->data = nodeData;

            if (isFirstNode) {
                currentNode->adjacent = tempNode;
                linkNode = tempNode;
                isFirstNode = 0;
            } else {
                linkNode->adjacent = tempNode;
                linkNode = tempNode;
            }

            // Link the edge node to the corresponding graph node
            previousNode = startNode;
            while (previousNode != nullptr) {
                if (previousNode->data == nodeData) {
                    tempNode->next = previousNode;
                    break;
                }
                previousNode = previousNode->next;
            }
        }
        currentNode = currentNode->next;
    }

    // Input edge weights
    currentNode = startNode;
    while (currentNode != nullptr) {
        linkNode = currentNode->adjacent;
        while (linkNode != nullptr) {
            std::cout << "\nEnter the weight for edge " << currentNode->data << " --- " << linkNode->data << ": ";
            std::cin >> linkNode->weight;
            linkNode = linkNode->adjacent;
        }
        currentNode = currentNode->next;
    }
}

// Function to find the shortest path using Dijkstra's algorithm
int Graph::findShortestPath(char targetVertex) {
    Node *minNode = nullptr;
    int minDistance;

    // Initialize all nodes
    currentNode = startNode;
    while (currentNode != nullptr) {
        if (currentNode->data != startNode->data) {
            currentNode->distanceValue = INT_MAX; // Set initial distance to infinity
        } else {
            currentNode->distanceValue = 0; // Distance to start node is zero
        }
        currentNode->status = 0; // Mark all nodes as unvisited
        currentNode = currentNode->next;
    }

    // Main loop of Dijkstra's algorithm
    while (true) {
        currentNode = startNode;
        minDistance = INT_MAX;

        // Find the unvisited node with the smallest distance value
        while (currentNode != nullptr) {
            if (currentNode->distanceValue <= minDistance && currentNode->status != 1) {
                minDistance = currentNode->distanceValue;
                previousNode = currentNode;
            }
            currentNode = currentNode->next;
        }

        if (previousNode->data == targetVertex) {
            break; // Exit loop if target vertex is reached
        }

        // Update the distance values of adjacent nodes
        linkNode = previousNode->adjacent;
        previousNode->status = 1; // Mark node as visited
        while (linkNode != nullptr) {
            minNode = linkNode->next;
            if (minNode && (previousNode->distanceValue + linkNode->weight < minNode->distanceValue)) {
                minNode->distanceValue = previousNode->distanceValue + linkNode->weight;
            }
            linkNode = linkNode->adjacent;
        }
    }
    return previousNode->distanceValue;
}

// Main function
int main() {
    char startVertex, targetVertex;
    int shortestDistance = 0;
    Graph graph;

    startVertex = graph.getStartNodeData(); // Get the start vertex
    std::cout << "Enter the terminal vertex: ";
    std::cin >> targetVertex;
    shortestDistance = graph.findShortestPath(targetVertex); // Find the shortest path
    std::cout << "\nThe shortest distance between " << startVertex << " and " << targetVertex << " is " << shortestDistance << std::endl;

    getchar(); // Wait for user input before closing
}
