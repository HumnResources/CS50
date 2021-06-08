-- list the names of all people who starred in a movie in which Kevin Bacon also starred --

SELECT people.name FROM
(SELECT * FROM movies JOIN stars ON stars.movie_id = movies.id JOIN people ON stars.person_id = people.id WHERE people.name = 'Kevin Bacon' AND people.birth = 1958) t1
JOIN stars ON stars.movie_id = t1.id
JOIN people ON stars.person_id = people.id
WHERE people.name != 'Kevin Bacon';