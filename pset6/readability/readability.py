from cs50 import get_string

# Coleman-Lieu Index
# Formula: index = 0.0588 * L - 0.296 * S - 15.8
# Where L is the avg # of letters per 100 words,
# and S is the avg # of sentences per 100 words.
# *Given a provided text.

text = get_string("Text: ")
length = len(text)
nWords = 0
nSentences = 0
nLetters = 0

for idx, char in enumerate(text):
    # Collect text data
    if char.isalpha():
        nLetters += 1
    elif char.isspace() and idx != 0 and text[idx - 1].isspace() == False:
        nWords += 1
    elif char in ['.', '!', '?']:
        nSentences += 1

    # Checks to see if we are at end of file and adds the last
    if idx == length - 1:
        nWords += 1

# Calculate Coleman-Lieu Index
L = nLetters / nWords * 100
S = nSentences / nWords * 100
index = 0.0588 * L - 0.296 * S - 15.8

# Display results
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")
