-- Display all Harry Potter film names | year in cronological order --

SELECT title, year FROM movies
WHERE title LIKE 'Harry Potter%'
ORDER BY year ASC;