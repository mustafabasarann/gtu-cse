#include <iostream>
using namespace std;

int main() {

    for(int i = 3; i <= 100; i++){
    	bool isPrime = true; 
    	for(int x = 2; x < i/2; x++){
    		if ( i%x == 0 ){
    			isPrime = false;
    			break;
    			}
    			}
    			  if(isPrime){
    				cout << i << " ";
    				}
    		}
       	
return 0;
}

