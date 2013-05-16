#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 

int fib(int number1, int number2) {
	return number1 + number2;
}

int main(int argc, char** args) { 
	int limit = atoi(args[1]);
	int list[100] = { 1, 1 };
	
	int i;
	for (i = 2; i < limit; i++){
		list[i] = fib(list[i-2], list[i-1]);
	}
	
	for (i = 0; i < limit; i++){
		printf("%d, ", list[i]);
	}
    exit(0); 
}