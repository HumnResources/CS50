-- Get all movies from year 2018 and up --

SELECT title FROM movies
WHERE year >= 2018
ORDER BY title