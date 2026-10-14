#include <iostream> 
#include <iomanip> 
#include <vector> 
using namespace std; 
 
const int INF = 999; 
 
void displayTables(int n, const vector<vector<int>>& dist, 
                   const vector<vector<int>>& nextHop, 
                   string title) 
{ 
    cout << "\n========== " << title 
         << " ==========\n"; 
 
    for (int i = 0; i < n; i++) 
    { 
        cout << "\nRouter " << i + 1 << ":\n"; 
        cout << left << setw(15) << "Destination" 
             << setw(12) << "Cost" 
             << "Next Hop\n"; 
 
        for (int j = 0; j < n; j++) 
        { 
            cout << left << setw(15) << j + 1; 
 
            if (dist[i][j] == INF) 
                cout << setw(12) << "INF"; 
            else 
                cout << setw(12) << dist[i][j]; 
 
            if (nextHop[i][j] == -1) 
                cout << "-\n"; 
            else 
                cout << nextHop[i][j] + 1 << "\n"; 
        } 
    } 
} 
 
int main() 
{ 
    int n; 
 
    cout << "Enter number of nodes (1-20): "; 
    cin >> n; 
 
    if (!cin || n < 1 || n > 20) 
    { 
        cout << "Invalid number of nodes.\n"; 
        return 1; 
    } 
 
    vector<vector<int>> cost(n, vector<int>(n)); 
    vector<vector<int>> dist(n, vector<int>(n)); 
    vector<vector<int>> nextHop(n, vector<int>(n, -1)); 
 
    cout << "\nEnter the cost matrix:\n"; 
    cout << "Use 999 for infinity (no direct connection).\n"; 
 
    for (int i = 0; i < n; i++) 
    { 
        cout << "Row " << i + 1 << ": "; 
 
        for (int j = 0; j < n; j++) 
        { 
            cin >> cost[i][j]; 
 
            if (!cin || cost[i][j] < 0 || 
                (cost[i][j] >= INF && cost[i][j] != INF)) 
            { 
                cout << "Invalid cost. Use 0 to 998 or 999.\n"; 
                return 1; 
            } 
 
            if (i == j && cost[i][j] != 0) 
            { 
                cout << "Diagonal costs must be zero.\n"; 
                return 1; 
            } 
 
            dist[i][j] = cost[i][j]; 
 
            if (i != j && cost[i][j] != INF) 
                nextHop[i][j] = j; 
        } 
    } 
 
    displayTables(n, dist, nextHop, 
                  "INITIAL ROUTING TABLES"); 
 
    // Distance Vector Routing: synchronous updates 
    bool changed; 
 
    do 
    { 
        changed = false; 
 
        // Use the previous round's routing information 
        vector<vector<int>> oldDist = dist; 
        vector<vector<int>> oldNextHop = nextHop; 
 
        for (int i = 0; i < n; i++) 
        { 
            for (int j = 0; j < n; j++) 
            { 
                for (int k = 0; k < n; k++) 
                { 
                    if (cost[i][k] == INF || 
                        oldDist[k][j] == INF) 
                        continue; 
 
                    int newCost = cost[i][k] + oldDist[k][j]; 
 
                    if (newCost < dist[i][j]) 
                    { 
                        dist[i][j] = newCost; 
 
                        if (i == k) 
                            nextHop[i][j] = oldNextHop[k][j]; 
                        else 
                            nextHop[i][j] = k; 
 
                        changed = true; 
                    } 
                } 
            } 
        } 
 
    } while (changed); 
 
    displayTables(n, dist, nextHop, 
                  "FINAL ROUTING TABLES"); 
 
    int source, destination; 
 
    cout << "\nEnter source node (1-" << n << "): "; 
    cin >> source; 
 
    cout << "Enter destination node (1-" << n << "): "; 
    cin >> destination; 
 
    if (!cin || source < 1 || source > n || 
        destination < 1 || destination > n) 
    { 
        cout << "Invalid source or destination.\n"; 
        return 1; 
    } 
 
    source--; 
    destination--; 
 
    cout << "\n========== SHORTEST PATH ==========\n"; 
 
    if (dist[source][destination] == INF) 
    { 
        cout << "No path exists between the selected nodes.\n"; 
    } 
    else 
    { 
        cout << "Path: "; 
 
        int current = source; 
        cout << current + 1; 
 
        int steps = 0; 
 
        while (current != destination && steps < n) 
        { 
            current = nextHop[current][destination]; 
 
            if (current == -1) 
            { 
                cout << "\nPath reconstruction failed.\n"; 
                return 1; 
            } 
 
            cout << " -> " << current + 1; 
            steps++; 
        } 
 
        if (current != destination) 
        { 
            cout << "\nPath reconstruction failed.\n"; 
            return 1; 
        } 
 
        cout << "\nMinimum Cost: " 
             << dist[source][destination] << "\n"; 
    } 
 
    return 0; 
}
