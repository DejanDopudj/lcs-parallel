#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

int my_min(int a, int b) {
    return (a < b) ? a : b;
}

int longestCommonSubsequence(char *text1, char *text2) {
    int m = strlen(text1);
    int n = strlen(text2);

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; ++i) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    for (int i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }

    int help = 1, i = 1, j = 1;
    while(help < m + n ){
        #pragma omp parallel for firstprivate(i,j) num_threads(4)
        for (int helpInner = 0; helpInner < my_min(i,(n-j+1)); helpInner++) {
            int helpI = i-helpInner;
            int helpJ = j+helpInner;
            if (text1[helpI - 1] == text2[helpJ - 1]) {
                dp[helpI][helpJ] = dp[helpI - 1][helpJ - 1] + 1;
            } else {
                dp[helpI][helpJ] = 
                (dp[helpI - 1][helpJ] > dp[helpI][helpJ - 1]) ? dp[helpI - 1][helpJ] : dp[helpI][helpJ - 1];
            }
        }
        if (help < m){
            help++;i++;
        }
        else{
            help++;j++;
        }
    }


    int result = dp[m][n];

    for (int i = 0; i <= m; ++i) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    clock_t start = clock();
    
    FILE *in = fopen("t6.txt", "r");
    int m = 50000;
    int n = 50000;
    char *text1 = (char *)malloc(m * sizeof(char));
    char *text2 = (char *)malloc(n * sizeof(char));
    fscanf(in, "%s %s", text1, text2);
    fclose(in);
    int len1 = sizeof(text1) - 1; 
    int len2 = sizeof(text2) - 1; 
    printf("Length of Longest Common Subsequence: %d\n", longestCommonSubsequence(text1, text2));
    
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time taken: %f seconds\n", cpu_time_used);


    return 0;
}
