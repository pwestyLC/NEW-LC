-- Cash Exchange Listings Table
-- Stores active cash listings from players

CREATE TABLE IF NOT EXISTS `t_cash_exchange_listings` (
	`listing_id` BIGINT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	`seller_user_code` INT NOT NULL,
	`seller_char_name` VARCHAR(32) NOT NULL,
	`cash_amount` BIGINT UNSIGNED NOT NULL,
	`price_per_unit` BIGINT UNSIGNED NOT NULL,
	`total_price` BIGINT UNSIGNED NOT NULL,
	`created_at` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
	`expires_at` TIMESTAMP NULL,
	`is_active` TINYINT(1) DEFAULT 1,

	-- Indexes
	INDEX `idx_seller_user_code` (`seller_user_code`),
	INDEX `idx_is_active` (`is_active`),
	INDEX `idx_created_at` (`created_at`),
	INDEX `idx_price_per_unit` (`price_per_unit`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Add comments
ALTER TABLE `t_cash_exchange_listings` MODIFY COLUMN `listing_id` BIGINT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'Unique listing identifier';
ALTER TABLE `t_cash_exchange_listings` MODIFY COLUMN `seller_user_code` INT NOT NULL COMMENT 'User code of seller from bg_user table';
ALTER TABLE `t_cash_exchange_listings` MODIFY COLUMN `seller_char_name` VARCHAR(32) NOT NULL COMMENT 'Character name of seller for display';
ALTER TABLE `t_cash_exchange_listings` MODIFY COLUMN `cash_amount` BIGINT UNSIGNED NOT NULL COMMENT 'Amount of cash being sold';
ALTER TABLE `t_cash_exchange_listings` MODIFY COLUMN `price_per_unit` BIGINT UNSIGNED NOT NULL COMMENT 'Price in NAS per cash unit';
ALTER TABLE `t_cash_exchange_listings` MODIFY COLUMN `total_price` BIGINT UNSIGNED NOT NULL COMMENT 'Total price = cash_amount * price_per_unit';
ALTER TABLE `t_cash_exchange_listings` MODIFY COLUMN `is_active` TINYINT(1) DEFAULT 1 COMMENT '1 = active, 0 = sold or cancelled';
