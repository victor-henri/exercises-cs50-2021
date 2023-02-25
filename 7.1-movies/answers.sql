-- 1
SELECT title FROM movies WHERE year = 2008;

-- 2
SELECT birth FROM people WHERE name = "Emma Stone";

-- 3
SELECT title FROM movies WHERE year >= 2018 ORDER BY title;

-- 4
SELECT COUNT(movie_id) FROM ratings WHERE rating = 10.0;

-- 5
SELECT title, year FROM movies WHERE title LIKE "Harry Potter%" ORDER BY year;

-- 6
 SELECT AVG(rating) FROM ratings WHERE movie_id IN (SELECT id FROM movies WHERE year = 2012);

-- 7
SELECT m.title, r.rating
FROM movies AS m
JOIN ratings AS r
ON m.id = r.movie_id
WHERE m.year = 2010
ORDER BY r.rating DESC, m.title;

-- 8
SELECT name
FROM people
WHERE id IN (SELECT person_id
             FROM stars
             WHERE movie_id IN (SELECT id
                                FROM movies
                                WHERE title = "Toy Story"));

-- 9
SELECT p.name
FROM people AS p
JOIN stars AS s ON p.id = s.person_id
JOIN movies AS m ON s.movie_id = m.id
WHERE m.year = 2004
ORDER BY p.birth;

-- 10
SELECT p.name
FROM people AS p
JOIN directors AS d ON p.id = d.person_id
JOIN ratings AS r ON d.movie_id = r.movie_id
WHERE r.rating >= 9.0
GROUP BY p.id;

-- 11
SELECT m.title
FROM movies AS m
JOIN stars AS s ON s.movie_id = m.id
JOIN people AS p ON p.id = s.person_id
JOIN ratings AS r ON r.movie_id = s.movie_id
WHERE p.name = "Chadwick Boseman"
ORDER BY r.rating DESC
LIMIT 5;

-- 12
SELECT title
FROM movies
WHERE id IN (SELECT movie_id
             FROM stars
             WHERE person_id = (SELECT id
                                FROM people
                                WHERE name = "Johnny Depp")
             OR person_id = (SELECT id
                             FROM people
                             WHERE name = "Helena Bonham Carter")
             GROUP BY movie_id HAVING COUNT(*) > 1);

-- 13
SELECT p.name
FROM people AS p
JOIN stars AS s ON s.person_id = p.id
WHERE s.movie_id IN (SELECT movie_id FROM stars WHERE person_id  = (SELECT id FROM people WHERE name = "Kevin Bacon" and birth = 1958))
AND s.person_id NOT IN (SELECT id FROM people WHERE name = "Kevin Bacon" and birth = 1958)
GROUP BY p.name;