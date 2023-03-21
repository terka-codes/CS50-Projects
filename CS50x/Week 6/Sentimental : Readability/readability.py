import cs50
import re

while True:
    # Get input text from user
    inputText = cs50.get_string("Text: ")

    # Define regular expressions to match letters and sentence ending punctuation
    regexLetters = re.compile(r"[a-zA-Z]")
    regexSentences = re.compile(r"[.!?]")

    # Count the number of letters, words, and sentences in the input text
    letters = len(regexLetters.findall(inputText))
    words = len(inputText.split())
    sentences = len(regexSentences.findall(inputText))

    # Compute the average number of letters and sentences per 100 words
    L = (letters / words) * 100
    S = (sentences / words) * 100

    # Compute the Coleman-Liau index for the input text
    index = 0.0588 * L - 0.296 * S - 15.8

    # Round the Coleman-Liau index to the nearest integer to determine the reading grade level
    grade = round(index)

    # Print the reading grade level
    if (grade < 1):
        print("Before Grade 1")
    elif (grade > 15):
        print("Grade 16+")
    else:
        print(f"Grade {grade}")

    # Exit the loop
    break