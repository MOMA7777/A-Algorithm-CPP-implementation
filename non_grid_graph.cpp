#include <bits/stdc++.h>
#define maxn 10000
using namespace std;

int V, E;

vector<int> node;

vector<int> gScore   (100, maxn);
vector<int> fScore   (100, maxn);
vector<int> camefrom (100, 0);
    
unordered_map<int, pair<int,int>> coordinate;

int heuristic(const pair<int,int> &coordinate1, const pair<int,int> &coordinate2) {
    return (abs(coordinate2.first-coordinate1.first) + abs(coordinate2.second-coordinate2.second));
}

void construct_path (int current, const int &goal = 5) {
    for(;current != -1; current = camefrom[current]) {
        cout << current << " ";
    }
    cout << endl;
}

void aStar(unordered_map<int, vector<pair<int,int>>> & graph, int start, int goal) {
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> openSet;
    openSet.push( {0, start} );
    gScore[start] = 0;
    camefrom[start] = -1;


    while (!openSet.empty()) {
        auto [fs, u] = openSet.top();
        
        if ( u == goal ) {
            cout << "found\n";
            construct_path(u, goal);
            return;
        }

        openSet.pop();
        
        for ( const auto & [neibour, weight] : graph[u]) {
            int tentitveScore = gScore[u] + weight;

            if ( tentitveScore < gScore[neibour] ) gScore[neibour] = tentitveScore;
            
            int tentitve_fScore = gScore[neibour] + heuristic(coordinate[neibour], coordinate[goal]);

            if ( tentitve_fScore < fScore[neibour] ) { 
                fScore[neibour] = tentitve_fScore;
                openSet.push( {tentitve_fScore, neibour} );
                camefrom[neibour] = u;
            }
        }  
    }
    
    cout << "not Found\n";
}


void printGraph(unordered_map<int, vector<pair<int,int>>> & graph) {

    for (const auto & u : node) {
        for (const auto & [v, w] : graph[u]) {
            cout << u << " -> " << v << " (" << w << ")" << endl;
        }
    }

}


int main() {
    
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    cin >> V >> E;

    unordered_map<int, vector<pair<int,int>>> graph;

    cout << "for every edge :\nsrc<space>dest<space>edge-weight :\n";
    while ( E-- ) {
        int u, v, weight;
        cin >> u >> v >> weight;

        graph[u].push_back( {v, weight} );
        coordinate[v] = {u,v};
    }
    
    int start, goal;
    cout << "Enter the Start and Your Goal : ";
    cin >> start >> goal;
    
    aStar(graph, start, goal); 

    return 0;
}
