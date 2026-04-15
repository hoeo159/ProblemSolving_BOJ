#include <stdio.h>
int main(){
	int num[9], max=0, index;
	for(int i=0; i<9; i++){
		scanf("%d", &num[i]);
		if(max<num[i]){
			max=num[i];
			index=i+1;
		}
	}
	printf("%d \n%d", max, index);
	return 0;
}