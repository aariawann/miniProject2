#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

static int numOfUsers;
static FILE* inFile;
static char line[1000];

/**
 * user_t structure
*/
typedef struct
{

    //declare position variables
    double lat;
    double lng;
    double alt;

    //declare time variables
    double time;

    //declare name variable of max length 49
    char name[50];

} User;

/**
 * distance structure
*/
typedef struct
{

    //declare distance from our user
    double dist;

    char name[50];

} UserDistance;




User scan_user(User userStruc){

    //char line[1000];
    
    //fill user structure
    for (int j = 0; j < 5; j++)
        {
            fgets(line, sizeof(line), inFile);

            switch(j){

                case 0:
                    line[strlen(line) - 1] = '\0';
                    strcpy(userStruc.name,line);
                    break;
                case 1:
                    userStruc.time = atof(line);
                    break;
                case 2:
                    userStruc.lat = atof(line);
                    break;
                case 3:
                    userStruc.lng = atof(line);
                    break;
                case 4:
                    userStruc.alt = atof(line);
                    break;
                
            }

            if(feof(inFile))
                break;
        }

    return userStruc;
}

UserDistance distanceCalc(User userStruc, User ourUser){

    UserDistance distStruc;

    //put name into distance Structure
    strcpy(distStruc.name, userStruc.name);
    
    //fill structure with distance value
    distStruc.dist = sqrt(
        pow((ourUser.lat-userStruc.lat), 2)+
        pow((ourUser.lng-userStruc.lng), 2)+
        pow((ourUser.alt-userStruc.alt), 2)
    );

    return distStruc;

}

void swapIndex(UserDistance *x, UserDistance *y, User *x2, User *y2){

    UserDistance temp = *x;
    *x = *y;
    *y = temp;

    User temp2 = *x2;
    *x2 = *y2;
    *y2 = temp2;

}

void sortArray(UserDistance distanceArray[], User other_users[], int n){

    
    if(n == 1)
        return;
    
    int count = 0;

    for (int i = 0; i < n-1; i++)
    {
        if (distanceArray[i].dist > distanceArray[i+1].dist)
        {
            swapIndex(&distanceArray[i], &distanceArray[i+1], &other_users[i], &other_users[i+1]);
            count++;
        }
    }

    if(count==0)
            return;
    
    sortArray(distanceArray, other_users, n-1);


}


int main(){

    char fileName[1000];

    printf("Type path of text file to scan: ");
    scanf("%s", fileName);
    
    inFile = fopen(fileName, "r");
    User our_user;
    int numOfUsers;
    //char line[1000];

    if(inFile==NULL){
        perror("Unable to open file");
        exit(1);
    }
    
    //scan first line (number of other users)
    fgets(line, sizeof(line), inFile);
    
    //convert string into int and store number of users amount in variable
    numOfUsers = atoi(line);

    //create array of other users with size scanned
    User other_users[numOfUsers];
    UserDistance distanceArray[numOfUsers];

    our_user = scan_user(our_user);

    //fill other users array
    for (int i = 0; i < numOfUsers; i++)
    {
        other_users[i] = scan_user(other_users[i]);
    }

    //fill distance structure array
    for (int i = 0; i < numOfUsers; i++)
    {
        distanceArray[i] = distanceCalc(other_users[i], our_user);
    }





    // for (int i = 0; i < numOfUsers; i++)
    // {
    //     printf("%s %f\n", distanceArray[i].name, distanceArray[i].dist);
    // }
    
    printf("-----------------------------\n");

    sortArray(distanceArray, other_users, numOfUsers);


    for (int i = 0; i < numOfUsers; i++)
    {
        printf("%s %f\n", distanceArray[i].name, distanceArray[i].dist);
    }

    printf("-----------------------------\n");

    printf("Closest user is %s\nLatitude: %.3f\nLongitude: %.3f\nAltitude: %.3f\n", 
    other_users[0].name,
    other_users[0].lat,
    other_users[0].lng,
    other_users[0].alt);



    // printf("OUR USER\n");
    // printf("%s\n%f\n%f\n%f\n%f\n", 
    //     our_user.name,
    //     our_user.time,
    //     our_user.lat,
    //     our_user.lng,
    //     our_user.alt);
    
    // printf("OTHER USERS\n");
    // for (int i = 0; i < numOfUsers; i++)
    // {
    //     printf("%s\n%f\n%f\n%f\n%f\n", 
    //     other_users[i].name,
    //     other_users[i].time,
    //     other_users[i].lat,
    //     other_users[i].lng,
    //     other_users[i].alt);

    // }
    


    

    return 0;
}