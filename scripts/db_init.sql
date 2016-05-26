--
-- File generated with SQLiteStudio v3.0.7 on Thu May 26 09:40:01 2016
--
-- Text encoding used: UTF-8
--
-- NOTE: This script is only for creating a new (empty) database.
--       To alter an existing database, use another script.

PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: meta
DROP TABLE IF EXISTS meta;
CREATE TABLE meta (
    version_major INT CONSTRAINT version NOT NULL ON CONFLICT ROLLBACK
                      DEFAULT (0),
    version_minor INT CONSTRAINT version NOT NULL ON CONFLICT ROLLBACK
                      DEFAULT (0) 
);

-- Table: show
DROP TABLE IF EXISTS show;
CREATE TABLE show (
    id               INT     PRIMARY KEY
                             CONSTRAINT valid_id NOT NULL ON CONFLICT ROLLBACK
                             UNIQUE
                             CONSTRAINT valid_id CHECK (id >= 0),
    title            TEXT    CONSTRAINT has_title NOT NULL ON CONFLICT ROLLBACK
                             CONSTRAINT title_length CHECK (length(title) > 0),
    episodes_watched INT     NOT NULL ON CONFLICT ROLLBACK
                             DEFAULT (0) 
                             CHECK (episodes_watched >= 0),
    episodes_total   INT     NOT NULL
                             CHECK (episodes_total >= 0),
    ongoing          BOOLEAN NOT NULL
                             DEFAULT (0) 
);

-- Table: manga
DROP TABLE IF EXISTS manga;
CREATE TABLE manga (
    id               INT     PRIMARY KEY
                             CONSTRAINT valid_id NOT NULL ON CONFLICT ROLLBACK
                             UNIQUE
                             CONSTRAINT valid_id CHECK (id >= 0),
    title            TEXT    CONSTRAINT has_title NOT NULL ON CONFLICT ROLLBACK
                             CONSTRAINT title_length CHECK (length(title) > 0),
    chapters_read    INT     NOT NULL ON CONFLICT ROLLBACK
                             DEFAULT (0) 
                             CHECK (chapters_read >= 0),
    chapters_total   INT     NOT NULL
                             CHECK (chapters_total >= 0),
    ongoing          BOOLEAN NOT NULL
                             DEFAULT (0) 
);

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
