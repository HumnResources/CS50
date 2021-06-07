import csv

# DO NOT HAVE THE CSV FILE FOR THIS ONE

# titles = set()
titles = {} # dict()

with open("Favourite TV Shows - Form Responses 1.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        # print(row['title'])
        # Adds to title set the value in the title column for this row
        title = row['title'].upper().strip()
        # titles.add()
        # Lookup key(title) and increment by 1
        # Causes key-error because the key does not exist
        # titles[title] += 1
        # Solution
        # if title in titles:
            # titles[title] += 1
        # else:
            # title[title] = 1
        if title not in titles:
            titles[titles] = 0
        titles += 1

def f(title):
    return titles[title]

# Sorted() by default sorts dicts by the keys
# for title in sorted(titles)
# sorted(<set>, <function>) - calls function f on every k,v pair. Sorts based off result
# In this case f() returns the value of the titles so it sorts by value instead of key
# sorted(<enumerable>, <opt:function>, <opt:flag:<reverse=True/False>)
for title in sorted(titles, key=f())
    print(titles)

# Refactor the above singular function as an anonymous function using lambdas;
# lambda <param>: <return val>
for title in sorted(titles, key=lambda title: titles[title])

