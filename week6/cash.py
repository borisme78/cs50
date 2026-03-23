from cs50 import get_float
change = get_float("Change owed: ")
while change < 0:
    change = get_float("Change owed: ")
cents = round(change * 100)
coins = 0
while cents >= 25:
    cents -= 25
    coins += 1
while cents >= 10:
    cents -= 10
    coins += 1
while cents >= 5:
    cents -= 5
    coins += 1
while cents >= 1:
    cents -= 1
    coins += 1
print(coins)