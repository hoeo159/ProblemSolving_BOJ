#include <stdio.h>
#include <algorithm>
using namespace std;

int a[10001];

bool self_number(void)
{
    int j, k;
    for(j=1; j<=10000; j++){
        k=j+j/1000+(j%1000)/100+(j%100)/10+j%10;
        a[k]=1;
    }
}

int main()
{
    int i;

    self_number();

    for(i=1; i<=10000; i++){
        if(!a[i]) printf("%d \n", i);
    }
}
