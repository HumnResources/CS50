from sys import argv

for arg in argv:
    print(arg)

if len(argv) == 2:
    print(f"Hello, {argv[1]}")
else:
    print("Hello, world!")
