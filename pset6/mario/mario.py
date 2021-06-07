from cs50 import get_int

MAX_VAL = 9


def main():
    height = get_positive_int("Height: ")

    # Start at offset of 1 to show floor one first. O includes blank empty row above top level
    print_pyramid(height, 1)


# Recursively print pyrmaid wall pices
def print_pyramid(height, offset):

    # Base case
    if offset > height:
        return

    # Create wall
    wall = '#' * offset
    space = ' ' * (height - offset)

    # Display current depth
    print(space + wall + '  ' + wall)
    print_pyramid(height, offset + 1)

    return


# Simply gets a positive integer from user
def get_positive_int(prompt):
    while True:
        n = get_int(prompt)
        if n < MAX_VAL and n > 0:
            break
    return n


# Run program
main()