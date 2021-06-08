-- All movies released in 2010 and their ratings, in descending order, each rating group ordered alphabetically --

SELECT title, rating FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE movies.year = 2010
ORDER BY rating DESC, title;