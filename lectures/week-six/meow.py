#defining main at the start and ordering this way ensures all funtions are loaded into memory first
def main():
    meow(3)

def meow(n):
    for i in range(n):
        print("Meow")

#Start the program
main()
