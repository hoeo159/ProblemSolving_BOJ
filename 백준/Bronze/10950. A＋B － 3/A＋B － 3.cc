#include <stdio.h>

int main(){
	int a, b, c, answer[100000]={0,};
	scanf("%d", &a);
	for(int i=0; i<a; i++){
		scanf("%d %d", &b, &c);
		answer[i]=b+c;
	}
	for(int i=0; i<a; i++)	printf("%d \n", answer[i]);
	return 0;
}