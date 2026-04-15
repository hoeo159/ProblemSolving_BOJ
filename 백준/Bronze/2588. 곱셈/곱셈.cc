#include <stdio.h>

int main(){
	int a, b, c, d, e ,f;
	scanf("%d %d", &a, &b);

	c=(b%10)*a;
	printf("%d \n", c);
	d=((b/10)%10)*a;
	printf("%d \n", d);
	e=((b/100)%10)*a;
	printf("%d \n", e);
	f=c+d*10+e*100;
	printf("%d \n", f);
} 