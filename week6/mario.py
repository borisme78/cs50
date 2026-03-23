from cs50 import get_int, get_string
def mario(rows, columns):
    for r in range(rows):
        for j in range(rows - r - 1):
            print(" ", end="")
        for c in range(columns):
            print("#", end="")
            if r == c:
                break
        print()
while True:
    n = get_int("Height: ")
    if 1<= n <= 8:
        break
mario(n, n)