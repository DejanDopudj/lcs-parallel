#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mmax(int a, int b) {
    return (a > b) ? a : b;
}

int lcs(char *text1, char *text2, int i, int j) {
    if (text1[i] == '\0' || text2[j] == '\0')
        return 0;

    if (text1[i] == text2[j])
        return 1 + lcs(text1, text2, i + 1, j + 1);
    else
        return mmax(
            lcs(text1, text2, i + 1, j),
            lcs(text1, text2, i, j + 1)
        );
}

int main() {
    

    clock_t start = clock();
    FILE *in = fopen("t1.txt", "r");
    int m = 10;
    int n = 10;
    // int num_threads = atoi(argv[4]);
    char *text1 = (char *)malloc(m * sizeof(char));
    char *text2 = (char *)malloc(n * sizeof(char));
    fscanf(in, "%s %s", text1, text2);
    fclose(in);

    int result = lcs(text1, text2, 0, 0);
    printf("Length of Longest Common Subsequence: %d\n", result);
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);
    return 0;
}
