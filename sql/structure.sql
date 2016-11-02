CREATE TABLE IF NOT EXISTS room (
    room_id SERIAL PRIMARY KEY,
    label CHARACTER VARYING NOT NULL
);

CREATE TABLE IF NOT EXISTS temperature (
    created TIMESTAMP WITH TIME ZONE DEFAULT now(),
    room_id INTEGER REFERENCES room(room_id),
    temperature NUMERIC NOT NULL,
    PRIMARY KEY (created, room_id)
);

CREATE INDEX IF NOT EXISTS temperature_created_index ON temperature (created DESC);

CREATE TABLE IF NOT EXISTS humidity (
    created TIMESTAMP WITH TIME ZONE DEFAULT now(),
    room_id INTEGER REFERENCES room(room_id),
    humidity NUMERIC NOT NULL,
    PRIMARY KEY (created, room_id)
);

CREATE INDEX IF NOT EXISTS humidity_created_index ON humidity (created DESC);
