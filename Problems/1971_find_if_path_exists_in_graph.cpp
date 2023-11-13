#include<iostream>
#include<vector>
#include<deque>

using namespace std;

// accepted
class Solution {
public:
    bool validPath(int n, vector<vector<int>> &edges, int start, int end) {
        int n_nodes;
        for (vector<int> e : edges) {
            n_nodes = max(n_nodes, max(e[0], e[1]));
        }
        n_nodes++;
        vector<vector<int>> neighbors(n_nodes, vector<int>());
        for (vector<int> e : edges) {
            int v = e[0], u = e[1];
            neighbors[v].push_back(u);
            neighbors[u].push_back(v);
        }
        vector<bool> visited (n_nodes, 0);
        deque<int> bfs_queue;
        bfs_queue.push_back(start);
        visited[start] = true;
        while (!bfs_queue.empty()) {
            int node = bfs_queue.front();
            bfs_queue.pop_front();
            if (node == end)
                return true;
            for (int neigh : neighbors[node])
                if (!visited[neigh]) {
                    bfs_queue.push_back(neigh);
                    visited[neigh] = true;
                }
        }
        return false;
    }
};

vector<vector<int>> read_graph() {
    int n;
    cin >> n;
    vector<vector<int>> edges(n, vector<int>(2, 0));
    for (int i = 0; i < n; i++) {
        cin >> edges[i][0] >> edges[i][1];
    }
    return edges;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> edges(n, vector<int>(2, 0));
    for (int i = 0; i < n; i++) {
        cin >> edges[i][0] >> edges[i][1];
    }
    int start, end;
    cin >> start >> end;
    cout << Solution().validPath(n, edges, start, end) << endl;
    return 0;
}