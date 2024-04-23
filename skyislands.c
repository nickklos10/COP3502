#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 1005 // Some arbitrary large value

int n, m;
bool adj[MAXN][MAXN];
bool visited[MAXN];

void dfs(int node) {
    visited[node] = true;

    for (int i = 1; i <= n; i++) {
        if (adj[node][i] && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    memset(adj, false, sizeof(adj));
    memset(visited, false, sizeof(visited));

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = true;
    }

    dfs(1); // Start DFS traversal from the first island

    bool isConnected = true;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            isConnected = false;
            break;
        }
    }

    printf(isConnected ? "YES\n" : "NO\n");

    return 0;
}

