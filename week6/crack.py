import sys
from passlib.hash import des_crypt
from itertools import product

def crack():
    if len(sys.argv) != 2:
        return "Usage: python crack.py hash"

    hash_to_crack = sys.argv[1]
    salt = hash_to_crack[:2]
    alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

    # Один універсальний цикл для довжини від 1 до 5
    for length in range(1, 6):
        print(f"Checking passwords of length {length}...") # Додав для візуалізації прогресу
        for guess_tuple in product(alphabet, repeat=length):
            guess = "".join(guess_tuple)
            if des_crypt.hash(guess, salt=salt) == hash_to_crack:
                return guess

    return "Password not found"

print(crack())
