#include<stdio.h>


void alterArray(int randomArray[]){

    randomArray[4] = 543;


}

int main(){

    int arr[] = {1,2,3,4,5};

    alterArray(arr);

        for (int i = 0; i < 5; i++)
        {
            printf("%d\n", arr[i]);
        }
        

}