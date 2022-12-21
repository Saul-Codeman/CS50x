SELECT title FROM movies
WHERE id IN (SELECT movies.id FROM movies
JOIN stars ON stars.movie_id = movies.id JOIN people ON stars.person_id = people.id
WHERE people.name = "Johnny Depp")
AND id IN (SELECT movies.id FROM movies
JOIN stars ON stars.movie_id = movies.id JOIN people ON stars.person_id = people.id
WHERE people.name = "Helena Bonham Carter");