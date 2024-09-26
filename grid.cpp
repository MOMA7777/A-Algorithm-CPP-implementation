#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

int r = 5, c = 4;

//up - down - left - right.
int row[] = {-1, 1,  0, 0};
int col[] = { 0, 0, -1, 1};


struct Point {
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
};

//to trace the path.
vector<vector<Point>> parent(r, vector<Point>(c, Point(-1,-1))); //acssesing no valid indexes.




struct Node {
    Point pt;

    int g, h, f;
    Node (Point npt, int g, int h) : pt(npt), g(g), h(h) {
        f = h + g;
    } 

    const bool operator<(const Node & other) const {
        return (f > other.f);   
    }
};

bool isWalkable(vector<vector<int>> & grid, Point nxt, int &r, int &c) {
    if( (nxt.x>=0 && nxt.x<r) && (nxt.y>=0 && nxt.y<c) && grid[nxt.x][nxt.y]==0 ) return true;
    return false;
}

int heuristic (Point current, Point goal) {
    return abs( goal.x - current.x ) + abs( goal.y - current.y );
}

void construct_path( vector<vector<Point>> & parent, Point end) {
    for(; end.x != -1; end = parent[end.x][end.y]) {
        cout << "("<<end.x<<","<<end.y<<")" << " ";
    }
    cout << endl;
}

void aStar(vector<vector<int>> & grid, Point start, Point &goal) {
    priority_queue<Node> openSet;
    set<pair<int,int>> closeSet;

    openSet.push( {start, 0, heuristic(start, goal)} ); //push the hole node.
    closeSet.insert( {start.x, start.y} ); //mark it visited.

    while ( !openSet.empty() ) {
        
        Node current = openSet.top(); 
        openSet.pop(); 
        Point pt = current.pt;        
        
        //mark it visited if we just pop it.
        closeSet.insert( {pt.x, pt.y} );

        //early exit.
        if ( pt.x == goal.x && pt.y == goal.y ) {
            cout << "\nfound\n";
            construct_path(parent, current.pt);
            return;
        }

        for(int i = 0; i < 4; i++) {
            Point nxt( pt.x+row[i], pt.y+col[i] );

            if ( isWalkable(grid, nxt, r, c) && closeSet.find( {nxt.x, nxt.y} )==closeSet.end() ) {
                int newG = current.g + 1;
                int newH = heuristic(nxt, goal);
                
                openSet.push( {nxt, newG, newH} );
                parent[nxt.x][nxt.y] = {pt.x, pt.y};
            }
        }
    }
    cout << "path cant be reached\n";
}

int main() {
    r = 5, c = 4;

    vector<vector<int>> grid = {
        { 0, 0, 1, 1 },
        { 0, 1, 0, 0 },
        { 0, 0, 0, 1 },
        { 1, 0, 0, 0 },
        { 0, 1, 1, 0 }
    };
    
    Point St({0,0}), Goal({4,3});

    aStar(grid,St,Goal);

    return 0;
}

