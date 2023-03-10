import cs50

while True:
    # Get user input for height
    height = cs50.get_int("Height: ")

    try:
        # Try to convert input to integer
        height = int(height)
    except ValueError:
        # If input cannot be converted to integer, prompt user to enter a number
        print("Error: Please enter a number between 1 and 8.")
        continue

    # Check if the input is between 1 and 8
    if height < 1 or height > 8:
        # If input is outside the range of 1-8, prompt user to enter a valid number
        print("Please enter a number between 1 and 8.")
        continue

    # If the input is valid, break out of the loop
    break


for i in range(height):
    print(" " * (height - 1 - i) + "#" * (i + 1))
