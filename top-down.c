#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int** dp;


int lcs_top_down(char text1[], char text2[], int i, int j) {
    if (text1[i] == '\0' || text2[j] == '\0')
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    if (text1[i] == text2[j]) {
        dp[i][j] = 1 + lcs_top_down(text1, text2, i + 1, j + 1);
        return dp[i][j];
    } else {
        dp[i][j] = max(
            lcs_top_down(text1, text2, i + 1, j),
            lcs_top_down(text1, text2, i, j + 1)
        );
        return dp[i][j];
    }
}

int main() {
    char text1[] = "TFGEHST";
    char text2[] = "TESJHT";
    int len1 = sizeof(text1) - 1; 
    int len2 = sizeof(text2) - 1; 
    
    dp = (int**)malloc((len1 + 1) * sizeof(int*));
    for (int i = 0; i <= len1; i++) {
        dp[i] = (int*)malloc((len2 + 1) * sizeof(int));
        for (int j = 0; j <= len2; j++) {
            dp[i][j] = -1;
        }
    }
    int result = lcs_top_down(text1, text2, 0, 0);
    printf("Length of Longest Common Subsequence: %d\n", result);
    return 0;
}
