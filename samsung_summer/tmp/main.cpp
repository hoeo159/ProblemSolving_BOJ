#include <iostream>
#include <cstring>

int main()
{
    char str[31];
    std::cin >> str;
    int len = strlen(str);
    printf("%d\n", len);
    return 0;
}