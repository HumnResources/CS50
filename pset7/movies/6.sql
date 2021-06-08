-- Get the average rating of all the movies in the year 2012 --

SELECT AVG(rating) FROM ratings
JOIN movies ON movies.id = ratings.movie_id
WHERE movies.year = 2012;