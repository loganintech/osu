-- Write the query to create the 4 tables below.
CREATE TABLE IF NOT EXISTS `client` (
  `id` int(11) AUTO_INCREMENT PRIMARY KEY,
  `first_name` VARCHAR(255) NOT NULL,
  `last_name` VARCHAR(255) NOT NULL,
  `dob` DATE NOT NULL,
  CONSTRAINT `full_name` UNIQUE (`first_name`, `last_name`)
);
CREATE TABLE IF NOT EXISTS `employee` (
  `id` int(11) AUTO_INCREMENT PRIMARY KEY,
  `first_name` VARCHAR(255) NOT NULL,
  `last_name` VARCHAR(255) NOT NULL,
  `dob` DATE NOT NULL,
  `date_joined` DATE NOT NULL,
  CONSTRAINT `full_name` UNIQUE (`first_name`, `last_name`)
);
CREATE TABLE IF NOT EXISTS `project` (
  `id` int(11) AUTO_INCREMENT PRIMARY KEY,
  `cid` int(11),
  CONSTRAINT `project_ibfk_1` FOREIGN KEY (`cid`) REFERENCES client (`id`),
  `name` VARCHAR(255) UNIQUE NOT NULL,
  `notes` TEXT
);
CREATE TABLE IF NOT EXISTS `works_on` (
  `eid` int(11),
  `pid` int(11),
  CONSTRAINT `works_on_ibfk_1` FOREIGN KEY (`eid`) REFERENCES employee (`id`),
  CONSTRAINT `works_on_ibfk_2` FOREIGN KEY (`pid`) REFERENCES project (`id`),
  `start_date` DATE NOT NULL,
  PRIMARY KEY(`eid`, `pid`)
);
-- Leave the queries below untouched. These are to test your submission correctly.
-- Test that the tables were created
DESCRIBE client;
DESCRIBE employee;
DESCRIBE project;
DESCRIBE works_on;
-- Test that the correct foreign keys were created
SELECT
  TABLE_NAME,
  COLUMN_NAME,
  CONSTRAINT_NAME,
  REFERENCED_TABLE_NAME,
  REFERENCED_COLUMN_NAME
FROM
  INFORMATION_SCHEMA.KEY_COLUMN_USAGE
WHERE
  REFERENCED_TABLE_SCHEMA = 'grade';
