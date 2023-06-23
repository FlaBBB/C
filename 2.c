#include <stdio.h>
#include <string.h>

int isValid(char * s){
    char temp[256] = "";
    char OPENER[] = "({[";
    char CLOSER[] = ")}]";
    for(int i = 0; i < strlen(s); i++){
        if(strchr(OPENER,s[i])){
            strncat(temp,&CLOSER[3-strlen(strchr(OPENER,s[i]))],1);
        }else if(strlen(temp)>0){
            if(temp[strlen(temp)-1] == s[i]){
                temp[strlen(temp)-1] = '\0';
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }
    if(strlen(temp)!=0){
        return 0;
    }
    return 1;
}

int main(){
    char s[] = "()";
    printf("%d",isValid(s));
}