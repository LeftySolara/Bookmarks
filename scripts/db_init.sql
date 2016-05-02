--
-- File generated with SQLiteStudio v3.0.7 on Mon May 2 09:02:37 2016
--
-- Text encoding used: UTF-8
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: show
DROP TABLE IF EXISTS show;

CREATE TABLE show (
    title      TEXT    PRIMARY KEY ON CONFLICT ROLLBACK
                       NOT NULL,
    ep_watched INT     DEFAULT (0),
    ep_total   INT     NOT NULL,
    art_path   TEXT,
    ongoing    BOOLEAN NOT NULL
                       DEFAULT (0) 
);


-- Table: manga
DROP TABLE IF EXISTS manga;

CREATE TABLE manga (
    title          TEXT    PRIMARY KEY
                           NOT NULL,
    chapters_read  INT     DEFAULT (0),
    chapters_total INT     NOT NULL,
    art_path       TEXT,
    ongoing        BOOLEAN NOT NULL
                           DEFAULT (0) 
);


-- Table: sources
DROP TABLE IF EXISTS sources;

CREATE TABLE sources (
    name TEXT PRIMARY KEY
              UNIQUE
              NOT NULL,
    link TEXT
);


COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
