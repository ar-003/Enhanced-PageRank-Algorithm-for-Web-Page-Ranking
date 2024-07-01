#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    // Initialize vector to store links between pages
    vector<vector<int>> links;
    
    // Initialize vector to track existence of pages
    vector<bool> Existence_matrix(1000001, false);
    
    int from, to;
    // Read links from input until end of file
    while (cin >> from) {
        cin >> to;
        
        // Store link in the links vector
        links.push_back({from, to});
        
        // Mark the existence of both pages
        Existence_matrix[from] = true;
        Existence_matrix[to] = true;
    }
    
    // Set the damping factor
    double alpha = 0.85;

    // Create an unordered map to represent the adjacency matrix of the links.
    unordered_map<int, vector<int>> Graph;
    
    // Build the adjacency matrix from the links vector
    for (int i = 0; i < links.size(); i++) {
        if (Graph.find(links[i][1]) == Graph.end()) {
            vector<int> tempo;
            Graph[links[i][1]] = tempo;
        }
        Graph[links[i][0]].push_back(links[i][1]);
    }    

    // Get the number of nodes in the adjacency matrix
    int n = Graph.size();
    
    // Initialize the pagerank vector
    unordered_map<int, double> I;
    for (auto a : Graph) {
        I[a.first] = 0;
    }
    I.begin()->second = 1;

    // Set the maximum number of iterations
    int max_Iterations = 107;
    // Iterate over the PageRank algorithm
    while (max_Iterations--) {
        // Temporary pagerank vector
        unordered_map<int, double> I_temp;
        for (auto a : Graph) {
            I_temp[a.first] = 0;
        }
        // Calculate the next iteration of pagerank vector
        for (int i = 0; i < links.size(); i++) {
            I_temp[links[i][1]] += (1.0 / (double)Graph[links[i][0]].size()) * I[links[i][0]];
        }
        double temp = 0;
        // Calculate contribution due to dangling nodes
        for (auto a : Graph) {
            if (a.second.size() == 0) {
                temp += (1.0 / (double)n) * (I[a.first]);
            }
        }
        // Update the pagerank vector
        for (auto a : Graph) {
            I_temp[a.first] += temp;
        }
        // Update the pagerank vector with final modification
        for (auto a : Graph) {
            I[a.first] = (alpha * I_temp[a.first]);
            I[a.first] += (1 - alpha) * (1.0 / (double)n);
        }
    }
    
    // Calculate the sum of pagerank values
    double s = 0;
    // Print the pagerank of  existing pages
    for (int i = 0; i < Existence_matrix.size(); i++) {
        if (Existence_matrix[i]) {
            cout << i << " = " << I[i] << "\n";
            s += I[i];
        }
    }
    // Print the sum of pagerank values
    cout << "s = " << s << "\n";
    
    // exiting the main function
    return 0;
}

