#include <stdio.h>

int main (){
	int num, a, b, result, cyc=1, c ;
	scanf("%d", &num);
	result = num ;
	while(1){
		a = result/10;
		b = result%10;
		c = a + b;
		result = b*10 + c%10;
		if(result == num)	break;
		else cyc++;
	}
	printf("%d", cyc);
	return 0;
}