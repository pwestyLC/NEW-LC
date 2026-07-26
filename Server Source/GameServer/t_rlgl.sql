-- t_rlgl table for RLGL event prizes
-- Place this in your data database

CREATE TABLE IF NOT EXISTS `t_rlgl` (
  `a_index`      INT NOT NULL AUTO_INCREMENT,
  `a_pos`        INT NOT NULL DEFAULT 0          COMMENT '0=loser/consolation, 1=1st place, 2=2nd place, 3=3rd place',
  `a_item_idx`   INT NOT NULL DEFAULT 0          COMMENT 'Item index from t_item',
  `a_item_count` INT NOT NULL DEFAULT 1          COMMENT 'Number of items to give',
  `a_item_plus`  INT NOT NULL DEFAULT 0          COMMENT 'Item plus/upgrade level',
  `a_item_flag`  INT NOT NULL DEFAULT 0          COMMENT 'Item flags',
  `a_message`    VARCHAR(255) NOT NULL DEFAULT '' COMMENT 'Description of this prize entry',
  PRIMARY KEY (`a_index`),
  KEY `idx_pos` (`a_pos`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ============================================================
-- If the table already exists without a_index primary key,
-- use this ALTER TABLE instead:
-- ============================================================

-- ALTER TABLE `t_rlgl`
--   ADD COLUMN `a_index` INT NOT NULL AUTO_INCREMENT FIRST,
--   ADD PRIMARY KEY (`a_index`),
--   ADD KEY `idx_pos` (`a_pos`);

-- ============================================================
-- PRIZE POSITIONS:
-- ============================================================
--   a_pos = 0  : Loser / consolation prize (given to eliminated players and players still in zone at event end)
--   a_pos = 1  : 1st place prize (given to the first player to cross the finish line)
--   a_pos = 2  : 2nd place prize
--   a_pos = 3  : 3rd place prize
--
-- Multiple rows with the same a_pos are supported (player receives all items for their position).
--
-- ============================================================
-- EXAMPLE DATA:
-- ============================================================

-- Loser consolation prize: 10x item #85
-- INSERT INTO t_rlgl (a_pos, a_item_idx, a_item_count, a_item_plus, a_item_flag, a_message) VALUES (0, 85, 10, 0, 0, 'Consolation prize');

-- 1st place: 1x item #85 + 5x item #5001 at +7
-- INSERT INTO t_rlgl (a_pos, a_item_idx, a_item_count, a_item_plus, a_item_flag, a_message) VALUES (1, 85, 1, 0, 0, 'First place reward');
-- INSERT INTO t_rlgl (a_pos, a_item_idx, a_item_count, a_item_plus, a_item_flag, a_message) VALUES (1, 5001, 5, 7, 0, 'Bonus item for first');

-- 2nd place: 1x item #2
-- INSERT INTO t_rlgl (a_pos, a_item_idx, a_item_count, a_item_plus, a_item_flag, a_message) VALUES (2, 2, 1, 0, 0, 'Second place reward');

-- 3rd place: 1x item #2
-- INSERT INTO t_rlgl (a_pos, a_item_idx, a_item_count, a_item_plus, a_item_flag, a_message) VALUES (3, 2, 1, 0, 0, 'Third place reward');
