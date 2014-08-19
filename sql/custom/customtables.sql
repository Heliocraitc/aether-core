CREATE TABLE `aevum_companion_names` (
	`entry` INT NOT NULL AUTO_INCREMENT COMMENT 'The ID of the name.',
	`name` VARCHAR(50) NOT NULL COMMENT 'The actual name goes here.',
	`race` INT NOT NULL COMMENT 'The race which will use this name will go here.',
	`gender` TINYINT NOT NULL COMMENT 'The gender of a name. 0 for neuter, 1 for male, 2 for female.',
	PRIMARY KEY (`entry`),
	UNIQUE INDEX `name` (`name`)
)
COMMENT='This table holds all of the randomly generated names for Aevum.'
COLLATE='latin1_swedish_ci'
ENGINE=InnoDB;

CREATE TABLE `aevum_companion_surnames` (
	`entry` INT NOT NULL AUTO_INCREMENT COMMENT 'The ID of the name.',
	`name` VARCHAR(50) NOT NULL COMMENT 'The actual name goes here.',
	`race` INT NOT NULL COMMENT 'The race which will use this name will go here.',
	`gender` TINYINT NOT NULL COMMENT 'The gender of a name. 0 for neuter, 1 for male, 2 for female.',
	PRIMARY KEY (`entry`),
	UNIQUE INDEX `name` (`name`)
)
COMMENT='This table holds all of the randomly generated names for Aevum.'
COLLATE='latin1_swedish_ci'
ENGINE=InnoDB;