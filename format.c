#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
//#include "format.h"

//Purpose: find the exponent of a 1EEE float
//Parameters: char array of bit string
//Output: the exponent for IEEE float
int getExp(char * input){
    int sum = 0;
	int index = 1;
	int base = 7;
	int bin;
	while(base > -1){
		bin = input[index] - '0';
		if(bin == 1){
			sum = sum + pow(2,base);
		}
		base--;
		index++;
	}
	int exp = sum - 127;
	return exp;
}

//Purpose: find the magnitude of a 1EEE float
//Parameters: char array of bit string
//Output: the magnitude for IEEE float
double getSig(char* input){
	int index = 9;
	double sum = 1;
	double sig = .5;
	int bin;
	while(index != 32){
		bin = input[index] - '0';
		if(bin == 1){
			sum = sum + sig; 
		}
		sig = sig / 2;
		index++;
	}
	return sum;
}

//Purpose: Switch all '1' to '0' and vice versa
//Parameters: char array of bit string
//Output: flipped char array of but string
char * flipBit(char * input){
	int l = strlen(input);
	int i;
	for(i = 0; i < l; i++){
		if(input[i] == '1'){
			input[i] = '0';
		}
		else{
			input[i] = '1';
		}
	}
	return input;
}

//Purpose: add one to flipped binary string
//Parameters: flipped binary string
//Output: flipped binary string + 1
char* addOne(char * input){
	int l = strlen(input) -1 ;
	int n = 0;
	int carry = 0;
	if(input[l] == '0'){
		input[l] = '1';
		return input;
	}
	else{
		input[l] = '0';
		carry = 1;
	}
	l--;
	while(n < 1){
	
		if(input[l] == '0'){
			input[l] = '1';
			break;
		}
		else if(input[l] == '1'){
			input[l] = '0';
		}
			l--;
	}
	return input;
}

//Purpose: turn a char array of binary into a int 
//Parameters: char array of bit string
//Output: int in decimal form
int binToInt(char * input){
	int l = strlen(input) - 1;
    int base = 0;
	int sum = 0;
	while(l > -1){
		
		if(input[l] == '1'){
			sum += (int) pow(2,base);
		}
		base++;
		l--;
	}
	return sum;
}
int main(int argc, char **argv){

	if(argc != 3){
		fprintf(stderr,"ERROR, Incorrect number of arguements \n\n");
		return -1;
	}
	double answer;
	int sum = 0;
	char *input = argv[1];
	char *type = argv[2];
	if(strlen(input) != 32){
		fprintf(stderr,"ERROR, Incorrect input size \n\n");
		return -1;
	}
	int q = 0;
	for(q = 0; q < strlen(input); q++){
		if(input[q] != '1' && input[q] != '0'){
			fprintf(stderr,"ERROR, Incorrect input \n\n");
			return -1;
		}
	}
	char pos = input[0];
	int sign = 1;
	char * end;
	if(pos == '1'){
		sign = -1 * sign;
	}
	
	//checks if int
	if(type[0] == 'i' && type[1] == 'n' && type[2] == 't' && strlen(type) == 3){
		input = flipBit(input);
		end = addOne(input);
		sum = binToInt(end);
		sum = abs(sum);

		if(pos == '1'){
			sum = sum * -1;
			printf("%d\n\n" , sum );
		}
		else{
			printf("%d\n\n" , sum );
		}
		
		
	}
	// check if float
	else if (type[0] == 'f' && type[1] == 'l' && type[2] == 'o' && type[3] == 'a' && type[4] == 't' && strlen(type) == 5){
		
		if (strcasecmp(argv[1], "10000000000000000000000000000000") == 0){
			printf("-0.0e0\n");
		}
		else if(strcasecmp(argv[1], "00000000000000000000000000000000") == 0){
			printf("0.0e0\n");
		}
		else{
		// get sign, magniatude, and exp for IEEE float
		int eVal = getExp(input);
		double mag = getSig(input);
		double power = (pow(2, eVal));
		answer = power * mag;
		answer = fabs(answer);
		int n = 0;
		int exp = 0;
		
		//checks if it input is inf, -inf, +nan, -nan, or neither
		if(eVal == 128 && mag == 1 && pos == '1'){
			printf("ninf\n");
		}
		else if(eVal == 128 && mag == 1 && pos == '0'){
			printf("pinf\n");
		}
		else if(eVal == 128 && mag != 1 && pos == '0'){
			printf("+NaN\n");
		}
		else if(eVal == 128 && mag != 1 && pos == '1'){
			printf("-NaN\n");
		}
		else{
			
			// converts into a float
			while(n < 1){
			
				if((answer >= 1.0) && (answer < 10.0)){
					if(pos == '1'){
						answer = answer * -1;
					}
					printf("%f", answer);
					printf("e%d\n",exp);
					
					break;
				}
				else if(answer >= 10.0){
					answer = answer / 10.0;
					exp++;
				}
				else if (answer < 1){
					answer = answer * 10.0;
					exp--;
				}
			}		
		}
	}
	}
			else{
			fprintf(stderr,"ERROR, Incorrect type\n\n");
			return -1;
	}
	
	return 0;
}
	