#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 10

int n, p;
char names[MAXN][20];
int popcorn[MAXN];
bool dislikes[MAXN][MAXN];

bool used[MAXN];
int arrangement[MAXN];

bool found_solution = false;

bool is_valid_arrangement() {
    for (int i = 0; i < n; i++) {
        // Check for popcorn
        if (!popcorn[arrangement[i]]) {
            if (i == 0 && !popcorn[arrangement[i+1]]) return false;
            else if (i == n-1 && !popcorn[arrangement[i-1]]) return false;
            else if (i > 0 && i < n-1 && !popcorn[arrangement[i-1]] && !popcorn[arrangement[i+1]]) return false;
        }
        
        // Check for dislikes
        if (i > 0 && dislikes[arrangement[i]][arrangement[i-1]]) return false;
        if (i < n-1 && dislikes[arrangement[i]][arrangement[i+1]]) return false;
    }
    return true;
}

void generate_permutations(int pos) {
    if (found_solution) return; // Early return if solution is found

    if (pos == n) {
        if (is_valid_arrangement()) {
            for (int i = 0; i < n; i++) {
                printf("%s\n", names[arrangement[i]]);
            }
            found_solution = true; // Mark solution as found
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            used[i] = true;
            arrangement[pos] = i;
            generate_permutations(pos + 1);
            used[i] = false;
        }
    }
}

int main() {
    scanf("%d %d", &n, &p);

    for (int i = 0; i < n; i++) {
        scanf("%s %d", names[i], &popcorn[i]);
    }

    memset(dislikes, 0, sizeof(dislikes));
    for (int i = 0; i < p; i++) {
        char a[20], b[20];
        scanf("%s %s", a, b);
        int index_a, index_b;
        for (int j = 0; j < n; j++) {
            if (strcmp(names[j], a) == 0) index_a = j;
            if (strcmp(names[j], b) == 0) index_b = j;
        }
        dislikes[index_a][index_b] = true;
        dislikes[index_b][index_a] = true;
    }

    memset(used, 0, sizeof(used));
    generate_permutations(0);

    return 0;
}
