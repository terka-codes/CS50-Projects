#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Get the key from the "./caesar (number)"
    string key = argv[1];

    // Checks if the input is a positive number
    int key2 = 0;

    if (argc != 2) // Checksif user inputed only one value
    {
        printf("wrong key");
        return 1;
    }

    // Checks if the key is a number
    for (int i = 0; i < strlen(key); i++)
    {
        if (isalnum(key[i]) != 0 && isalpha(key[i]) == 0)
        {
            key2 = 0;
        }
        else
        {
            key2 = 1;
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // If the input is a positive number key2 stayed 0, so the program can proceed with decoding by the key
    if (key2 == 0)
    {
        // Makes a number from the sring key
        int keynum = atoi(key);

        // Asks the user for a text to encrypt
        string text = get_string("plaintext:  ");

        // A string of the full ABC in lowercase to help encrypting
        string abc = "abcdefghijklmnopqrstuvwxyz";

        // Seting up a new string, which will be the output
        string output = text;

        // plus makes a value which will be later used to count it, it's the key as a number and it's reminder after dividing by 26 (the alphabeth)
        int plus = keynum % 26;

        // Checks if each character is a letter to encrypt or different character to leave as it is
        for (int i = 0; i < strlen(text); i++)
        {
            // Checks if it's a letter
            if (isalpha(text[i]))
            {
                // Checks if it's lower or upeer case
                if (isupper(text[i]) != 0) // Uppercase
                {
                    // Takes the number of each character from imputed text and subtracts 65 (because it's uppercase) and then adds the remainder of the key value
                    int num = ((text[i] - 65) + plus);
                    if (num > 25) // If the number is bigger than 25, it has to wrap around to start at the beginning of the alphabet
                    {
                        num = num - 26;
                    }
                    int value = abc[num];
                    output[i] = toupper(value); // Assigns the value to the output[i] and translated to uppercase

                }
                else // Lowercase
                {
                    // Takes the number of each character from imputed text and subtracts 97 (because it's lowercase) and then adds the remainder of the key value
                    int num = ((text[i] - 97) + plus);
                    if (num > 25) //If the number is bigger than 25, it has to wrap around to start at the beginning of the alphabet
                    {
                        num = num - 26;
                    }
                    int value = abc[num];
                    output[i] = value; //Assigns the value to the output[i]
                }

            }
            // If it isn't a letter the character remainds as it was
            else
            {
                output[i] = text[i];
            }
        }

        // Prints the output message and returns 0
        printf("ciphertext: %s\n", output);
        return 0;
    }
}