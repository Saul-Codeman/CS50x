text = input("Text: ")
letters = 0
words = 1
sentences = 0
# Iterate through each character in the text
for char in text:
    # Check if character is in the alphabet
    if char.isalpha():
        letters += 1
    elif char == " ":
        words += 1
    elif char == "." or char == "!" or char == "?":
        sentences += 1
letters = round(letters / words * 100, 2)
sentences = round(sentences / words * 100, 2)
index = round(0.0588 * letters - 0.296 * sentences - 15.8)
if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")