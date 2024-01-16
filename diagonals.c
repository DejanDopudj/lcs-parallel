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
        #pragma omp parallel for firstprivate(i,j)
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

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }

    int result = dp[m][n];

    for (int i = 0; i <= m; ++i) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    char text1[] = "CDEEA";
    char text2[] = "BCDEFA";

    printf("Length of Longest Common Subsequence: %d\n", longestCommonSubsequence(text1, text2));

    return 0;
}
