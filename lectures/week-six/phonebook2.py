import csv
from cs50 import get_string

#file = open("phonebook.csv", "a")
#name = get_string("name: ")
#num = get_string("number: ")
#writer = csv.writer(file)
#writer.writerow([name, num])

# More pythonic way seemingly safer, too
with open("phonebook.csv", "a") as file:
    name = get_string("name: ")
    num = get_string("number: ")

    writer = csv.writer(file)

    writer.writerow([name, num])

#file.close()
