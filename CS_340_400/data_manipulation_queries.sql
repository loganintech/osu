-- Select

SELECT customer_id, fname, lname, birthday FROM customers WHERE customer_id = :id;
SELECT movie_id, name, rating, genre, length FROM movies WHERE movie_id = :id;
SELECT room_id, capacity, theater_id FROM rooms WHERE room_id = :id;
SELECT showing_id, time, movie_id, room_id FROM showings WHERE showing_id = :id;
SELECT theater_id, name, address, address_two, city, state, zip FROM theaters WHERE theater_id = :id;
SELECT ticket_id, price, showing_id, customer_id FROM tickets WHERE ticket_id = :id;

-- Insert

INSERT INTO customers (`fname`, `lname`, `birthday`) VALUES (:fname, :lname, :birthday);
INSERT INTO movies (`name`, `rating`, `genre`, `length`) VALUES (:name, :rating, :genre, :length);
INSERT INTO rooms (`capacity`, `theater_id`) VALUES (:capacity, :theater_id);
INSERT INTO showings (`time`, `movie_id`, `room_id`) VALUES (:time, :movie_id, :room);
INSERT INTO theaters (`name`, `address`, `address_two`, `city`, `state`, `zip`) VALUES (:name, :address, :address_two, :city, :state, :zip);
INSERT INTO tickets (`price`, `showing_id`, `customer_id`) VALUES (:price, :showing_id, :customer_id);


-- Update

UPDATE customers SET `fname` = :fname, `lname` = :lname, `birthday` = :birthday WHERE `customer_id` = :customer_id;
UPDATE movies SET `name` = :name, `rating` = :rating, `genre` = :genre, `length` = :length WHERE `movie_id` = :movie_id;
UPDATE rooms SET `capacity` = :capacity, `theater_id` = :theater_id WHERE `room_id` = :room;
UPDATE showings SET `time` = :time, `movie_id` = :movie_id, `room_id` = :room WHERE `showing_id` = :showing_id;
UPDATE theaters SET `name` = :name, `address` = :address, `address_two` = :address_two,`city` = :city,`state` = :state,`zip` = :zip WHERE `theater_id` = :theater_id;
UPDATE tickets SET `price` = :price, `showing_id` = :showing_id, `customer_id` = :customer_id WHERE `ticket_id` = :ticket_id;

-- Delete

DELETE FROM customers WHERE `customer_id` = :customer_id;
DELETE FROM movies WHERE `movie_id` = :movie_id;
DELETE FROM rooms WHERE `room_id` = :room;
DELETE FROM showings WHERE `showing_id` = :showing_id;
DELETE FROM theaters WHERE `theater_id` = :theater_id;
DELETE FROM tickets WHERE `ticket_id` = :ticket_id;
