#include <stdio.h>
int main(){
	int num, count = 0, result[42]={0,};
	for(int i=0; i<10; i++){
		scanf("%d", &num);
		result[num%42] = 1;
		}
	for(int i=0; i<42; i++){
		if(result[i]==1)	count++;
	}
	printf("%d", count);
	return 0;
}