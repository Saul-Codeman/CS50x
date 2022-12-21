from cs50 import get_int
loop = True
while loop:
    height = get_int("Height: ")
    if height < 9 and height > 0:
        loop = False
for i in range(height):
    for _ in range(0, height - i - 1):
        print(" ",end="")
    for _ in range(i + 1, 0, -1):
        print("#",end="")
    print(end="\n")