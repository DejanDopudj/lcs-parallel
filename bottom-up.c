#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
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
    char text1[] = "TFGEHST";
    char text2[] = "TESJHT";

    printf("Length of Longest Common Subsequence: %d\n", longestCommonSubsequence(text1, text2));

    return 0;
}
