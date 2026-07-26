-- SQL: Create table t_skill_watch used by GameServer\SkillUseLog.cpp
-- Compatible with MySQL/MariaDB

CREATE TABLE `t_skill_watch` (
  `char_index` INT NOT NULL,
  `note` VARCHAR(255) DEFAULT NULL,
  PRIMARY KEY (`char_index`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- Example rows: add the character indexes you want to watch
INSERT INTO `t_skill_watch` (`char_index`, `note`) VALUES
(1001, 'Example watched character'),
(1002, 'Another example');
