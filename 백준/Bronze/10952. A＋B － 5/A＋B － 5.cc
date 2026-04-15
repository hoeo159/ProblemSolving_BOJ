#include <stdio.h>

int main()
{
    int a = 1, b = 1;

    while (1)
    {
        // 덧셈 수행하기
        scanf("%d%d", &a, &b);

        if (a == 0 && b == 0) // 0 0 이면 탈출!!
            break;

        printf("%d\n", a + b);
    }
    return 0;
}