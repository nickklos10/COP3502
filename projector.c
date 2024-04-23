#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double angle;
    int count;
} Point;

int compare(const void* a, const void* b) {
    double diff = ((Point*)a)->angle - ((Point*)b)->angle;
    if (diff > 0) return 1;
    if (diff < 0) return -1;
    return 0;
}

int main() {
    int N, A;
    scanf("%d %d", &N, &A);
    
    Point points[2*N];
    for (int i = 0; i < N; i++) {
        int x, y, s;
        scanf("%d %d %d", &x, &y, &s);

        double angle = atan2(y, x);
        if (angle < 0) angle += 2 * M_PI;

        points[i] = (Point){angle, s};
        points[i + N] = (Point){angle + 2 * M_PI, s};
    }

    qsort(points, 2*N, sizeof(Point), compare);

    // Minimize people in projection
    int start = 0, end = 0, total = 0, min_people = 1e9;
    while (start < N) {
        while (end < 2 * N && points[end].angle - points[start].angle < A * M_PI / 180.0) {
            total += points[end].count;
            end++;
        }
        if (total < min_people) min_people = total;
        total -= points[start].count;
        start++;
    }

    // Maximize the angle without any projection
    double max_gap = 0.0;
    for (int i = 1; i < 2*N; i++) {
        double gap = points[i].angle - points[i-1].angle;
        if (gap > max_gap) max_gap = gap;
    }
    double max_angle = max_gap * 180.0 / M_PI;

    printf("%d\n", min_people);
    printf("%.4lf\n", max_angle);

    return 0;
}









