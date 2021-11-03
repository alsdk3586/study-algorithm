#include <iostream>
#include <vector>

std::vector<std::vector<int>> lcs;

int main(int argc, const char* argv[]) {
    
    std::string str1, str2;
    std::cin >> str1 >> str2;
    
    int len1 = str1.length();
    int len2 = str2.length();
    
    std::vector<int> elem(len2 + 1, 0);
    lcs.resize(len1 + 1, elem);
    
    for (int i = 1; i <= len1; ++i)
        for (int j = 1; j <= len2; ++j)
            if (str1[i - 1] == str2[j - 1])
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            else
                lcs[i][j] = std::max(lcs[i - 1][j], lcs[i][j - 1]);
    
    std::cout << lcs[len1][len2];
    
    return 0;
}
