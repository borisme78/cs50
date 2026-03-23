from cs50 import get_string
from sys import argv
import sys

def main():

        if len(sys.argv) != 2:
            print("Usage: python script.py dictionary.txt")
            sys.exit(1)
    # створюєм словник щоб зберегти слова
        dictionary = set()
    # беремо argv тобто banned.txt
        file_path = sys.argv[1]
    # якщо файл то відкриваємо
        try:
            file = open(file_path, "r")

            for line in file:
                word = line.strip().lower()
                if word:
                    dictionary.add(word)
            file.close()
    # якщо не файл то помилка закриваєм програму
        except FileNotFoundError:
            print(f"Error: File '{file_path}' not found")
            sys.exit(1)
    # беремо текст від користувача 
        user_text = get_string("Text: ")
    # перетворяєм текст на слова 
        word_list = user_text.split()
    # проходимся по кожному слову і перевіряєм чи є сллово у словнику dictionary
        for every_word in word_list:
        # переводим всі слова у нижній регістр і ігноруєм знаки 
            word = every_word.strip(",.?!").lower()
        # перевіряєм чи є слово у словнику 
            if word in dictionary:
            #якщо є вимірюєм розмір і друкуєм замість нього *
                    lent = len(word)
                    for count in range (lent):
                        print("*", end="")
                    print(end=" ")
        # якщо слова немає просто друкуєм його
            else:
                    print(every_word, end=" ")
        print()




if __name__ == "__main__":
    main()