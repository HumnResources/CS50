from cs50 import get_int

def main():
    i = get_positive_int()
    print(i)
# A substitution for a do-while. Pythonic way to get input
def get_positive_int():
    while True:
        n = get_int("Positive Integer: ")
        if n > 0:
            break
    return n


main()
