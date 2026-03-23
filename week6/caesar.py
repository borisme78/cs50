from cs50 import get_int, get_string
import sys

def encode (k, text):
    result = ""
    for char in text:
        if char.isalpha():
            start = ord('A') if char.isupper() else ord('a')
            new_a = chr((ord(char) - start + k) % 26 + start)
            result += new_a
        else:
            result += char
    return result

if len(sys.argv) != 2:
    print("Usage: python caesar.py k")
    sys.exit(1)


k = int(sys.argv[1])
text = get_string("plaintext: ")

a = encode(k,text)
print("ciphertext: ", a)





