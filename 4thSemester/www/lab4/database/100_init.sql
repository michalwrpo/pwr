-- 100 - Create database and users

-- Superuser and wwwlab is managed by compose.yaml

CREATE ROLE appuser WITH LOGIN PASSWORD 'appuser';

-- must connect to the database first in order to grant role privileges in the specific db.
\c wwwlab

-- grant privileges to appuser
GRANT USAGE ON SCHEMA public TO appuser;
GRANT SELECT, INSERT, UPDATE, DELETE ON ALL TABLES IN SCHEMA public TO appuser;
GRANT USAGE, SELECT ON ALL SEQUENCES IN SCHEMA public TO appuser;