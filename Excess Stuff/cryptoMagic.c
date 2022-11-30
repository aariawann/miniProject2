/*
crypoMagic.c
***********************
November 19 2022

This is an encryption and decryption utility, compatable with .crp and .txt files.
*/


#include<stdio.h>
#include<string.h>
#include<ctype.h>

/*
This function converts ascii chars into hexadecimal integers
*/
int asciiToHex(char c)
{
        int num = (int) c;

        //ascii values 0-9
        if(num < 58 && num > 47)
        {
                return num - 48; 
        }
        //ascii values a-f
        if(num < 103 && num > 96)
        {
                return num - 87;
        }
        return num;

}//end of asciiToHex

/**
 * This function encrypts a .txt file
*/
int encryption(char *fileName){

    //declare pointer for file
    FILE *inFile;
    FILE *outFile;
    int c;
    int outChar;

    //add crp extension to fileName to decrypt
    char crpFileName[100];
    strcpy(crpFileName, fileName);
    strcat(crpFileName, ".crp");

    //create or append txt file
    char txtFileName[100];
    strcpy(txtFileName, fileName);
    strcat(txtFileName, ".txt");

    //opens file for reading
    inFile = fopen(txtFileName, "r");
    
    //cant find file 
    if(inFile == NULL){
        printf("file does not exist\n");
        return(-1);
    }

    //opens file for writing
    outFile = fopen(crpFileName, "w");


    while(1){

        //reads file character by character
        c = fgetc(inFile);

        if(feof(inFile))
            break;

        //turn into encrypted ascii
        //recognizes tab
        if(c==9){
            fprintf(outFile, "TT");
        }
        //recognizes carriage return
        else if(c==10){
            fprintf(outFile, "\n");
        }
        else{
            outChar = c-16;

            if(outChar<32)
                outChar = (outChar-32) + 144;
            
            //print hexadecimal value
            fprintf(outFile, "%X", outChar);

        }  
    }
    fclose(inFile);

    return 0;
}//end of encryption

/**
 * This function decrypts a crp file
*/
int decryption(char *fileName){

    //declare pointer for file
    FILE *inFile;
    FILE *outFile;
    int b;
    int a;
    int outChar;

    //add crp extension to fileName to decrypt
    char crpFileName[100];
    strcpy(crpFileName, fileName);
    strcat(crpFileName, ".crp");

    //make txt file to create
    char txtFileName[100];
    strcpy(txtFileName, fileName);
    strcat(txtFileName, ".txt");


    //opens file for reading
    inFile = fopen(crpFileName, "r");

    //cant find file 
    if(inFile == NULL){
        printf("file does not exist.\n");
        return(-1);
    }

    //opens file for writing
    outFile = fopen(txtFileName, "w");

    while(1){

        //read first character
        a = tolower(fgetc(inFile));

        //if carriage return, do not bother reading second char just enter
        if(a==10){
            fprintf(outFile, "\n");
        }
        //if not carriage return, read second char
        else{
            b = tolower(fgetc(inFile));

            //combine two chars
            char pair[] = {a,b,'\0'};

            //if end of file, break out of loop
            if(feof(inFile))
                break;

            //if pair of characters is tt then tab
            if(strcmp(pair, "tt") == 0){
                fprintf(outFile, "\t");
            }
            else{

                //convert char a and b from ascii to hexadecimal
                a = asciiToHex(a);
                b = asciiToHex(b);

                //decryption
                outChar = a*16;
                outChar+=b;
                outChar+=16;

                if(outChar>127){
                    outChar = (outChar-144) + 32;
                }

                //print to character to outFile
                fprintf(outFile, "%c", outChar);
            }
        }
    }
    //close inFile
    fclose(inFile);

    return 0;

}//end of decryption

/**
 * This function removes the extension from the file name
*/
char * removeExtension(char*fileName){

    //find position of where extension starts in filename
    int removeEx = strchr(fileName, '.') - fileName;

    //null termanator in place of where extension would be
    fileName[removeEx] = '\0';

    return fileName;
}//end of removeExtension

int main(int argCount, char *args[]){

    //initialize fileName
    char *fileName;

    //switch case for number of arguments entered
    switch (argCount)
    {
    case 3:
         //user types -d then decrypt
        if(strcmp(args[1], "-d") == 0){

            fileName = args[2];

            //if user entered extension, strip extension and decrypt
            if(strchr(fileName, '.') > 0){
                decryption(removeExtension(fileName));
            }

            //user doesn't enter extension, call decryption function
            decryption(fileName);
        
        }
        //use types in -e then encrypt
        else if(strcmp(args[1], "-e") == 0){

            fileName = args[2];

            //if user entered extension, strip extension and decrypt
            if(strchr(fileName, '.') > 0){
                encryption(removeExtension(fileName));
            }

            //user doesn't enter extension, call encryption function
            encryption(fileName);

        }
        //error trap
        else{
            printf("Invalid command-line.\n");
        }
        break;
    case 2:

            fileName = args[1];

            //if user entered extension, strip extension and decrypt
            if(strchr(fileName, '.') > 0){
                encryption(removeExtension(fileName));
            }

            //user doesn't enter extension, call encryption function
            encryption(fileName);
        break;
    default:
        //error trap
        printf("Invalid Entry\n");
        break;
    }
    
    return 0;
}