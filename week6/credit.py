from cs50 import get_int

card_number = get_int("Number:")
lent = len(str(card_number))
s = str(card_number)

every_other_digit = s[-2::-2]

sum_products = 0

for digit in every_other_digit:
    product = int(digit) * 2
    sum_products += (product // 10) +(product % 10)

total_sum = sum_products

ramaining_digit = s[-1::-2]

for digit in ramaining_digit:
    total_sum += int(digit)

if total_sum % 10 != 0:
    print("INVALID")
else:
    if lent == 15 and (s.startswith("34") or s.startswith("37")):
        print("AMEX")
    elif lent == 16 and (s.startswith(("51", "52", "53", "54", "55"))):
        print("MASTERCARD")
    elif lent == 13 or lent == 16 and (s.startswith("4")):
        print("VISA")
    else:
        print("INVALID")
