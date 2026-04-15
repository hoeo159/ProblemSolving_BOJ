#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    int n, i, k, t, a[3], han;
    scanf("%d", &n);
    for(i=1; i<=n; i++){
        if(i<100) han=i;
        else if (i==1000) break;
        else{
            k=0; t=i;
            while(t>0){
                a[k]=t%10;
                t/=10; k++;
            }
            if (a[0]-a[1]==a[1]-a[2]) han++;
        }
    }
    printf("%d", han);
}
