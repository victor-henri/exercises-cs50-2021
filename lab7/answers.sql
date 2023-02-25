-- 1
SELECT name FROM songs;

-- 2
SELECT name FROM songs ORDER BY tempo;

-- 3
SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5;

-- 4
SELECT name FROM songs WHERE danceability > 0.75 AND energy > 0.75 AND valence > 0.75;

-- 5
SELECT AVG(energy) FROM songs;

-- 6
SELECT s.name
FROM songs AS s
JOIN artists AS a ON a.id = s.artist_id
WHERE a.name = "Post Malone";

-- 7
SELECT AVG(s.energy)
FROM songs AS s
JOIN artists AS a ON a.id = s.artist_id
WHERE a.name = "Drake";

-- 8
SELECT name FROM songs WHERE name LIKE "%feat.%";
