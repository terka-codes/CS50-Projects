#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Prompts user for their name
    string name = get_string("What is your name?\n");

    // Prints sting with user's name
    printf("hello, %s\n", name);
}