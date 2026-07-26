-- t_auto_event table for scheduling automated events
-- Place this in your data database

CREATE TABLE IF NOT EXISTS `t_auto_event` (
  `a_index`        INT NOT NULL AUTO_INCREMENT,
  `a_event_type`   VARCHAR(32) NOT NULL DEFAULT 'RLGL'  COMMENT 'Event type identifier (RLGL, etc.)',
  `a_day_of_week`  INT NOT NULL DEFAULT -1               COMMENT 'Day of week 0=Sun,1=Mon..6=Sat, -1=every day',
  `a_hour`         INT NOT NULL DEFAULT -1               COMMENT 'Hour 0-23, -1=ignore (used with interval)',
  `a_minute`       INT NOT NULL DEFAULT 0                COMMENT 'Minute 0-59',
  `a_interval_min` INT NOT NULL DEFAULT 0                COMMENT 'Repeat every X minutes (0=one-shot at a_hour:a_minute)',
  `a_enabled`      TINYINT NOT NULL DEFAULT 1            COMMENT '1=enabled, 0=disabled',
  PRIMARY KEY (`a_index`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ============================================================
-- USAGE MODES:
-- ============================================================
--
-- MODE 1: Fixed time (one-shot per day)
--   Set a_hour and a_minute to the desired time, a_interval_min = 0
--
-- MODE 2: Repeat every X minutes all day
--   Set a_hour = -1, a_minute = 0, a_interval_min = desired interval
--
-- MODE 3: Repeat every X minutes starting at a specific hour
--   Set a_hour = start hour, a_minute = start minute, a_interval_min = desired interval
--
-- ============================================================
-- EXAMPLES:
-- ============================================================

-- Run RLGL every day at exactly 18:00 (one-shot)
-- INSERT INTO t_auto_event (a_event_type, a_day_of_week, a_hour, a_minute, a_interval_min, a_enabled) VALUES ('RLGL', -1, 18, 0, 0, 1);

-- Run RLGL every 30 minutes all day every day
-- INSERT INTO t_auto_event (a_event_type, a_day_of_week, a_hour, a_minute, a_interval_min, a_enabled) VALUES ('RLGL', -1, -1, 0, 30, 1);

-- Run RLGL every 60 minutes all day, only on Saturday
-- INSERT INTO t_auto_event (a_event_type, a_day_of_week, a_hour, a_minute, a_interval_min, a_enabled) VALUES ('RLGL', 6, -1, 0, 60, 1);

-- Run RLGL every 45 minutes every day
-- INSERT INTO t_auto_event (a_event_type, a_day_of_week, a_hour, a_minute, a_interval_min, a_enabled) VALUES ('RLGL', -1, -1, 0, 45, 1);
