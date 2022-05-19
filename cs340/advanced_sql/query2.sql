-- write your queries to insert data here
INSERT INTO
  `client` (`first_name`, `last_name`, `dob`)
VALUES
  ("Sara", "Smith", "1970-01-02"),
  ("Miguel", "Cabrera", "1988-02-02"),
  ("Bo", "Chang", "1985-03-02");
INSERT INTO
  `employee` (`first_name`, `last_name`, `dob`, `date_joined`)
VALUES
  ("Ananya", "Jaiswal", "1975-01-02", "2009-01-01"),
  ("Michael", "Fern", "1980-10-18", "2013-06-05"),
  ("Abdul", "Rehman", "1984-03-21", "2013-11-10");
INSERT INTO
  `project` (`cid`, `name`, `notes`)
VALUES
  (1, "Diamond", "Should be done by Jan 2019"),
  (3, "Chan'g", "Ongoing maintenance"),
  (2, "The Robinson Project", NULL);
INSERT INTO
  `works_on` (`eid`, `pid`, `start_date`)
VALUES
  (1, 2, "2012-01-01"),
  (2, 3, "2013-08-08"),
  (3, 1, "2014-09-11");
-- Leave the queries below untouched. These are to test your submission correctly.
select
  *
from
  project;
select
  *
from
  client;
select
  *
from
  employee;
select
  *
from
  works_on;
