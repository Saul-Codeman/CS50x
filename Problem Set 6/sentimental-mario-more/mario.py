from cs50 import get_int
loop = True
while loop:
    height = get_int("Height: ")
    if height < 9 and height > 0:
        loop = False
blocks = 0
spaces = 0
for i in range(height):
    # Blocks
    blocks = i + 1
    # Spaces
    spaces = height - blocks
    print(" " * spaces + "#" * blocks + " " * 2 + "#" * blocks)

