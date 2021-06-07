import csv
from cs50 import SQL

# DO NOT HAVE CSV FILE

title = input("Title: ").strip().upper()

# Input of ALL comparisons needs top be canonicallized for formality

# Running time : O(n) - Slow
with open("favourites.csv") as file:
    reader - csv.DictReader(file)
    counter = 0
    for row in reader:
        if row['title'].strip().upper() == title:
            counter += 1


## REFACTOR ABOVE WITH SQL ##

# Attain this by using a second table for the genres (avoids storing csv in db)
# shows           genres
# primary_key ->  show_id
# title           genre

# If table one contains: 1 - The Office - "Comedy, Drama, ..."
# Table two contains two entries: 1 - comedy, 2 - drama, ...

# Every row in table containing show titles, each contains it's own respective table of genres

# Pythonic way to create a file
open("shows.db", "w").close()

# Opens previous file as a SQL database using cs50 lib
db = SQL("sqlite:///shows.db")

# Create table called shows with an incrementing key
db.execute("CREATE TABLE shows(id INTEGER, title TEXT, PRIMARY KEY(id)")

# Creates a table for genres, one row for each genre, where the show id references back the table 'shows' id column
# As the id is created in the 'shows' table, essentially uses show_id as a pointer
# The schema of this table is such that the id for the show will contain multiple, separate, entries for genres
db.execute)"CREATE TABLE genres(show_id INTEGER, genre TEXT, FOREIGN KEY(show_id) REFERENCES shows(id))"


with open("favourites.csv") as file:
    reader = csv.DictReader(file)
    for row in reader:
        title = row['title'].strip().upper()
        # ? - placeholder variable
        id = db.execute("INSERT INTO shows(title) VALUES(?)", title)

        for genre in row['genres'].split(', '):
            db.execute("INSERT INTO genres(show_id, genre) VALUES(?, ?)", id, genre)

# Nested query example
# Perenthesis are executed first
# SELECT title FROM shows Where id IN (SELECT show_id FROM genres WHERE genres = "Musical");


# BETTER REFACTOR - JOINED TABLE

# shows            shows_genres         genres
# primary_key  ->  show_id       |->    id
# title            genre_ID     -|      name

# Where shows_genres just contains foreign keys to link the shows and genres tables respectively