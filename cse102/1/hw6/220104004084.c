#include <stdio.h>

int find_size_of_array();
int mostRepeated();
int countElement();
float average();
int median();


int main(){
	int A,B,i,j;
	printf("Enter A and B values: ");
	scanf("%d %d",&A,&B);
	printf("\n");
	int flag = 1;
	while(flag){         /* checking for error situations*/
		if(A<50 || B>200){
			printf("A must be at least 50 and B must not exceed 200.\n"),
			printf("Enter A and B values: ");
			scanf("%d %d",&A,&B);
			}else if(A > B) {
				printf("A must be less than B.\n");
				scanf("%d %d",&A,&B);
			}else{
				flag = 0;
			}
	}
	int SIZE = B-A+1;
	int arr[SIZE+1];
	for(i = 0; i<(SIZE); i++){
		arr[i] = A+i;
	}
	arr[i+1] = -1;
	
	
	int size_number_array = 22;
	int number_array[200]={1,2,51,52,52,51,51,51,51,51,83,65,76,43,55,55,55,66,34,66,78,55};
	int newArray[200];
	int k=0;
	for(i = 0; i < size_number_array; i++){ /* assigning useful number_array numbers to newArray */
		for(j = 0; j<SIZE; j++){
			if(number_array[i] == arr[j]){
				newArray[k] = number_array[i];
				k++;
			}
		}
	}
	k++;
	int x;
	x = mostRepeated(newArray,k);
	
	int index;
	while(x > 0){ /* printing initial histogram */
		for(index = 0; index<SIZE; index++){
			if(countElement(arr,newArray,k,index) >= x){
				printf("*");
			}else{
				printf(" ");
		}
		}
		printf("\n");
		x--;
		
	}
	
	int choice,y;
	printf("Would you like to add new numbers? Press 1 for yes, Press 0 for no.\n");
	scanf("%d",&choice);
	
	k--;
	
	if(choice == 1){ /* checking for adding numbers and assigning them to the number_array and newArray*/
		scanf(" %d",&y);
		while(y != -1){
			scanf(" %d",&y);
			number_array[size_number_array] = y;
			size_number_array++;
		}
	k = 0;
	for(i = 0; i < size_number_array; i++){
		for(j = 0; j<SIZE; j++){
			if(number_array[i] == arr[j]){
				newArray[k] = number_array[i];
				k++;
			}
		}
	}
	x = mostRepeated(newArray,k);
	while(x > 0){
		for(index = 0; index<SIZE; index++){
			if(countElement(arr,newArray,k,index) >= x){
				printf("*");
			}else{
				printf(" ");
		}
		}
		printf("\n");
		x--;		
		}
	}
	
	
	printf("Average: %f\n",average(newArray,k));
	printf("Mode: %d\n",mostRepeated(newArray,k));
	printf("Median: %d\n",median(newArray,k));
}

int find_size_of_array(int A[]){ /* finding size of the array */
	
	int i=0;
	int counter = 0;
	while(A[i] != -1){
		i++;
	}
	return (i-1);
}

int mostRepeated(int B[],int n){ /* finding most repeated element in the array and it can be used for finding mode*/
	int i,j,maxcount=0;
	
	for(i=0; i<n; i++){
		int count = 0;
		for(j = 0; j<n; j++){
			if(B[i] == B[j]){
			count++;
			}
		}
		if(count > maxcount){
		maxcount = count;
		}
	}
	return maxcount;
}  

int countElement(int A[],int B[],int m,int i){ /* counting each element in the array with their indexes */ 
	int j,count=0;
		for(j = 0; j < m; j++){
			if(A[i] == B[j]){
				count++;
			}	
		}
	return count;
}


float average(int A[],int n){ /* finding average of the numbers in the array */
int sum = 0,i;

	for(i=0; i<n; i++){
		sum = sum+A[i];
	}
	return (sum/n);
}

int median(int a[],int n){ /* finding median  */
	int i,t,j;
	for (i = 1 ; i <= n-1 ; i++){
   		for (j = 1 ; j <= n-i ; j++){
      			if (a[j] <= a[j+1]){
         			t = a[j];
         			a[j] = a[j+1];
         			a[j+1] = t;
      			} else
      				continue ;
		   }
		}


}



