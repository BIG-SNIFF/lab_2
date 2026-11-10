#include <stdio.h>

#define MAX 100

struct song {
    char band[100];
    char name[100];
    float price;
    int year;
};

struct song songs[MAX];

int songCount = 0;


void enterData(void)   //
{
    int number;     //stores how many songs the user wants
    int i;          //used as counter in loop

    printf("\nHow many songs would you like to enter? ");    
    scanf("%d", &number);     //answer to question is sotred in number

    if (number > MAX - songCount)    //checks if user si trying to enter more songs than array can hold 
    {
        number = MAX - songCount;
        printf("You can only enter %d more songs.\n", number);
    }

    for (i = 0; i < number; i++)    //repeats the code inside it for however many song the user wants to enter
    {
        printf("\nEnter band or singer name: ");   //reads up to 99 characters of the user input, selects current position in our song array
        scanf(" %99[^\n]", songs[songCount].band);

        printf("Enter song name: ");
        scanf(" %99[^\n]", songs[songCount].name);

        printf("Enter song price: ");
        scanf("%f", &songs[songCount].price);

        printf("Enter release year: ");
        scanf("%d", &songs[songCount].year);

        songCount++;   //increases the number of songs stored by one after each song is entered

        printf("\nSong added successfully!\n");
    }
}

void saveData(void)
{
    FILE *file;    //creates a file point caled file
    int i;   

    file = fopen("songs.txt", "w");  //opens a file called songs and opens it in write mode.

    if (file == NULL)     //wont try to write to an open file
    {
        printf("Error opening file!\n");   //
        return;   //ends function if file cant be opened
    }

    for (i = 0; i < songCount; i++)   //for loop that goes through every song sotred in array 
    {
        fprintf(file, "%s|%s|%.2f|%d\n",   //how it will be displayed in the file, 1st: string, 2nd: string, 3rd: 2 deimal place number, 4th: an integer
                songs[i].band,
                songs[i].name,
                songs[i].price,
                songs[i].year);
    }

    fclose(file);   //closes file after being used so it saves properly

    printf("\nSongs successfully saved to file!\n");   //
}

void readData(void)
{
    FILE *file;  //creates a file pointer

    file = fopen("songs.txt", "r");   //open the file songs.txt in read mode 

    if (file == NULL)   //checks to see if file has been opened and if not displays a message
    {
        printf("Error opening file!\n");
        return;
    }

    songCount = 0;  //resets song counter as we want to replace info with the info from the file

    while (songCount < MAX &&    
           fscanf(file, " %99[^|]|%99[^|]|%f|%d",    //reads info from file, reads text until it encounters a |, reads a floating point numbr, reads a integer
                  songs[songCount].band,  
                  songs[songCount].name,   //already proides an address 
                  &songs[songCount].price,    //uses & becasue we need the memory address where the numbers should be stored
                  &songs[songCount].year) == 4)
    {
        songCount++;   //increases song count
    }

    fclose(file);   //closes file after ebing read

    printf("\n%d songs successfully read from file!\n", songCount);
}


void sortSongs(void)    //sorting algorithm (bubble sort)
{
    int i, j;     //creates an outer and inner loop 
    struct song temp;   //creates a temp storage space used while swapping songs

    for (i = 0; i < songCount - 1; i++)    //controls how many passes the sorting agoithms make through the array 
    {
        for (j = 0; j < songCount - 1 - i; j++)   //compares songs next to each other and doesnt comapre songs in their right palce
        {
            if (songs[j].year < songs[j + 1].year)   //inner loop checks if current song ha ealier release year than the next song
            {    //statement aboive is true this code runs
                temp = songs[j];    //saves a song in temp storage 
                songs[j] = songs[j + 1];  //will move the other song into the other poisiton  
                songs[j + 1] = temp;   //moves the song into temp storage
            }
        }
    }
}

void printCatalogue(void)
{
    int i;

    if (songCount == 0)   //if songs count is zero it wont carry on because there is nothing to print
    {
        printf("\nNo songs available. Please enter or read songs first.\n");
        return;
    }

    sortSongs();    //calls the function we made earlier so the songs will be in the order of newest to oldest

    printf("\n===== SONG CATALOGUE =====\n");    //displays a header

    for (i = 0; i < songCount; i++)    //repeats the printing code for every song in the array
    {
        printf("\nSong %d\n", i + 1);    //starts at zero but we need to start at 1
        printf("Band/Singer: %s\n", songs[i].band);   //displays each bit of information that has been stored in each song structure 
        printf("Song Name: %s\n", songs[i].name);
        printf("Price: £%.2f\n", songs[i].price);
        printf("Year of Release: %d\n", songs[i].year);
    }
}

int main(void)
{
    int choice;

    do
    {
        printf("\n===== SONG CATALOGUE =====\n");
        printf("1. Enter data\n");
        printf("2. Save data to file\n");
        printf("3. Read data from file\n");
        printf("4. Print out the catalogue to screen\n");
        printf("5. Exit Program\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        // Decide which function to execute
        switch (choice)
        {
            case 1:
                enterData();    //if '1' is typed in it will call the enterdata function 
                break;    //stops the switch statement from going to the case

            case 2:
                saveData();
                break;

            case 3:
                readData();
                break;

            case 4:
                printCatalogue();
                break;

            case 5:
                printf("\nYou selected Exit Program. Goodbye!\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 5);   //repeats the program until '5' is typed so the program can shut down

    return 0;
}