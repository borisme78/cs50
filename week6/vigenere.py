import sys

# 1. Перевірка аргументів командного рядка
if len(sys.argv) != 2:
    print("Usage: python vigenere.py key")
    sys.exit(1)

key = sys.argv[1]

# 2. Перевірка, чи ключ складається тільки з літер
if not key.isalpha():
    print("Key must be alphabetical.")
    sys.exit(1)

# 3. Отримання тексту від користувача
plaintext = input("plaintext: ")

# 4. Підготовка зміщень (shifts)
shifts = []
for char in key:
    base = ord('a') if char.islower() else ord('A')
    shifts.append(ord(char) - base)

key_len = len(shifts)
j = 0  # Індекс для просування по ключу

# 5. Шифрування та вивід
print("ciphertext: ", end="")

for char in plaintext:
    if char.isalpha():
        # Визначаємо базу (A або a) для збереження регістру
        base = ord('a') if char.islower() else ord('A')
        
        # Беремо поточне зміщення
        shift = shifts[j % key_len]
        
        # Обчислюємо новий символ: (позиція + зміщення) % 26
        cipher_char = chr((ord(char) - base + shift) % 26 + base)
        
        print(cipher_char, end="")
        j += 1  # Збільшуємо лічильник ключа ТІЛЬКИ для літер
    else:
        # Пробіли та знаки друкуємо без змін
        print(char, end="")

# Фінальний перенос рядка
print()
