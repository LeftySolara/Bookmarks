--
-- File generated with SQLiteStudio v3.0.7 on Fri Apr 29 19:14:16 2016
--
-- Text encoding used: UTF-8
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: Show
DROP TABLE IF EXISTS Show;

CREATE TABLE Show (
    name       TEXT PRIMARY KEY ON CONFLICT ROLLBACK
                    NOT NULL,
    ep_watched INT  DEFAULT (0),
    ep_total   INT  NOT NULL,
    art_path   TEXT
);


COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
