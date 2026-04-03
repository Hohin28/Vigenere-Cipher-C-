#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
char* vigenereEncrypt(const char* plaintext,const char* key) {
    int textLen=strlen(plaintext);
    int keyLen=strlen(key);
    char* ciphertext=(char*)malloc((textLen + 1)*sizeof(char));
    if(ciphertext==NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    for (int i=0,j=0;i<textLen;i++){
        if (isalpha(plaintext[i])){
            char base=isupper(plaintext[i]) ? 'A' : 'a';
            char keyChar=tolower(key[j%keyLen]);
            if(!isalpha(keyChar)){
                printf("Key must contain only alphabetic characters.\n");
                free(ciphertext);
                exit(1);
            }
            ciphertext[i]=(plaintext[i]-base+keyChar-'a')%26+base;
            j++;
        }else{
            ciphertext[i]=plaintext[i];
        }
    }
    ciphertext[textLen]='\0';
    return ciphertext;
}

char* getInput(const char* prompt){
    char buffer[1024];
    printf("%s",prompt);
    if (fgets(buffer,sizeof(buffer), stdin)==NULL){
        printf("Error reading input.\n");
        exit(1);
    }
    buffer[strcspn(buffer,"\n")]=0;
    return strdup(buffer);
}
void saveToFile(const char* plaintext,const char* key,const char* ciphertext){
    FILE* file=fopen("vigenere_log.txt","a");
    if(file==NULL){
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file,"Plaintext: %s\n",plaintext);
    fprintf(file,"Key: %s\n",key);
    fprintf(file,"Ciphertext: %s\n\n",ciphertext);
    fclose(file);
    printf("Data saved to vigenere_log.txt\n");
}
int main(){
    char* plaintext=NULL;
    char* key=NULL;

    plaintext=getInput("Enter the plaintext: ");
    if (strlen(plaintext)==0){
        printf("Plaintext cannot be empty.\n");
        free(plaintext);
        return 1;
    }

    key=getInput("Enter the key: ");
    if (strlen(key)==0){
        printf("Key cannot be empty.\n");
        free(plaintext);
        free(key);
        return 1;
    }

    char* ciphertext=vigenereEncrypt(plaintext,key);
    printf("Ciphertext: %s\n",ciphertext);
    saveToFile(plaintext, key,ciphertext);
    free(plaintext);
    free(key);
    free(ciphertext);

    return 0;
}
