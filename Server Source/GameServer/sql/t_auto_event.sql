-- SQL: Create table t_auto_event used by GameServer\AutoEventScheduler.cpp
-- Compatible with MySQL/MariaDB

CREATE TABLE `t_auto_event` (
  `a_index` INT NOT NULL AUTO_INCREMENT,
  `a_event_type` VARCHAR(64) NOT NULL,
  `a_day_of_week` TINYINT NOT NULL DEFAULT -1 COMMENT '-1 = every day, 0=Sun..6=Sat',
  `a_hour` TINYINT NOT NULL DEFAULT -1 COMMENT '-1 = ignore hour for interval events',
  `a_minute` TINYINT NOT NULL DEFAULT 0,
  `a_interval_min` INT NOT NULL DEFAULT 0 COMMENT 'interval in minutes; 0 = one-shot at hour:minute',
  `a_enabled` TINYINT(1) NOT NULL DEFAULT 1,
  PRIMARY KEY (`a_index`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- Example rows
INSERT INTO `t_auto_event` (`a_event_type`, `a_day_of_week`, `a_hour`, `a_minute`, `a_interval_min`, `a_enabled`) VALUES
('RLGL', -1, 3, 0, 0, 1),  -- one-shot every day at 03:00
('RLGL', -1, 0, 0, 180, 1);   -- interval mode: every 180 minutes (3 hours) starting immediately
