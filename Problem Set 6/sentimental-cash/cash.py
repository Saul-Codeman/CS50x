from cs50 import get_float
import math
loop = True
while loop:
    change = get_float("Change owed: ")
    if change > 0:
        loop = False
change = change * 100
change = int(change)
coins = 0
if change % 25 >= 0:
    coins += math.floor(change / 25)
    change = change % 25
if change % 10 >= 0:
    coins += math.floor(change / 10)
    change = change % 10
if change % 5 >= 0:
    coins += math.floor(change / 5)
    change = change % 5
if change % 1 >= 0:
    coins += math.floor(change / 1)
    change = change % 1
print(coins)
