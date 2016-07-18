CREATE TABLE room (
    room_id SERIAL PRIMARY KEY,
    label CHARACTER VARYING NOT NULL
);

CREATE TABLE temperature (
    created TIMESTAMP WITHOUT TIME ZONE DEFAULT now(),
    room_id INTEGER REFERENCES room(room_id),
    temperature NUMERIC NOT NULL,
    PRIMARY KEY (created, room_id)
);

CREATE TABLE humidity (
    created TIMESTAMP WITHOUT TIME ZONE DEFAULT now(),
    room_id INTEGER REFERENCES room(room_id),
    humidity NUMERIC NOT NULL,
    PRIMARY KEY (created, room_id)
);
