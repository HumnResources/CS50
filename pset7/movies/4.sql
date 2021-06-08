-- Get the number of movies with 10.0 rating --

SELECT COUNT(title) FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE rating LIKE 10.0;