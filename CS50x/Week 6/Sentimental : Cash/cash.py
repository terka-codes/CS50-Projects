import cs50  # get_float

while True:
    # Promptsstyle50 cash.py user to enter the amount of change owed
    change_owed = cs50.get_float("Change owed: ")

    try:
        # Trys to convert the user input to a float
        change_owed = float(change_owed)
    except ValueError:
        # If the user input cannot be converted to a float, prompts the user to enter a number
        print("Error: Please enter a number.")
        continue

    # Checks if the amount of change owed is less than 0.01
    if change_owed < 0.01:
        # If the amount of change owed is less than 0.01, prompts the user to enter a number greater than 0.01
        print("Please enter number heigher than O.O1.")
        continue

    # Converts the amount of change owed to cents for easier calculation
    change_owed = change_owed * 100

    # Breaks out of the loop if the input is valid
    break

# Initialize a variable to keep track of the number of coins
cash_count = 0

# Uses a while loop to count the number of quarters needed
while change_owed >= 25:
    change_owed -= 25
    cash_count += 1

# Uses a while loop to count the number of dimes needed
while change_owed >= 10:
    change_owed -= 10
    cash_count += 1

# Uses a while loop to count the number of nickels needed
while change_owed >= 5:
    change_owed -= 5
    cash_count += 1

# Uses a while loop to count the number of pennies needed
while change_owed >= 1:
    change_owed -= 1
    cash_count += 1

# Prints the total number of coins needed
print(cash_count)
