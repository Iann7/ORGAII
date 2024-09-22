#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct str_array {
   __uint8_t size;//----1 byte--0
   __uint8_t capacity; //---1 byte--1 + 6 de padding
   char** data;//---- 8byte-- 8
} str_array_t;//--16

void cesarEncoding(char* src,int x){
    for(int i=0;src[i]!='\0';i++){
        //A=65
        //Z=90
        //rango 25 
        //0<=x<=25
        //int i_int = (int) src[i];
        //int ord = i_int-65;
        //int total= (ord+x)%26;
        //src[i] = ((char) total)+65;
        printf("SIZE DE %ld",sizeof(str_array_t));
    }
    return;
}


int main(){
    char test[]="AVE";
    cesarEncoding(test,1);
    //printf("%ld",test);
    return 0;
}

