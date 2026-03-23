from cs50 import get_int, get_string


def positive_int(prompt):
    while True:
        n = get_int(prompt)
        if 1 <= n <= 8:
            return n

n = positive_int("Height: ")

# Малюємо піраміду
for i in range(1, n + 1):
    # Обчислюємо компоненти рядка:
    spaces = " " * (n - i)
    bricks = "#" * i
    
    # Виводимо все разом: пробіли + ліва частина + два пробіли + права частина
    print(f"{spaces}{bricks}  {bricks}")


