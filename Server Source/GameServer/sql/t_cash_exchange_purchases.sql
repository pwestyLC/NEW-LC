-- Cash Exchange Purchase Log Table
-- Tracks all purchases made by buyers for history/audit purposes

CREATE TABLE IF NOT EXISTS `t_cash_exchange_purchases` (
	`purchase_id` BIGINT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	`buyer_char_index` INT NOT NULL,
	`buyer_name` VARCHAR(32) NOT NULL,
	`seller_char_index` INT NOT NULL,
	`seller_name` VARCHAR(32) NOT NULL,
	`cash_amount` BIGINT UNSIGNED NOT NULL,
	`price_per_unit` BIGINT UNSIGNED NOT NULL,
	`total_nas_price` BIGINT UNSIGNED NOT NULL,
	`listing_id` BIGINT UNSIGNED NOT NULL,
	`purchased_at` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

	-- Indexes
	INDEX `idx_buyer_char_index` (`buyer_char_index`),
	INDEX `idx_seller_char_index` (`seller_char_index`),
	INDEX `idx_listing_id` (`listing_id`),
	INDEX `idx_purchased_at` (`purchased_at`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Add comments
ALTER TABLE `t_cash_exchange_purchases` MODIFY COLUMN `purchase_id` BIGINT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'Unique purchase transaction ID';
ALTER TABLE `t_cash_exchange_purchases` MODIFY COLUMN `buyer_char_index` INT NOT NULL COMMENT 'Character index of the buyer';
ALTER TABLE `t_cash_exchange_purchases` MODIFY COLUMN `buyer_name` VARCHAR(32) NOT NULL COMMENT 'Character name of buyer for display';
ALTER TABLE `t_cash_exchange_purchases` MODIFY COLUMN `seller_char_index` INT NOT NULL COMMENT 'Character index of the seller';
ALTER TABLE `t_cash_exchange_purchases` MODIFY COLUMN `seller_name` VARCHAR(32) NOT NULL COMMENT 'Character name of seller for display';
ALTER TABLE `t_cash_exchange_purchases` MODIFY COLUMN `cash_amount` BIGINT UNSIGNED NOT NULL COMMENT 'Amount of cash purchased';
ALTER TABLE `t_cash_exchange_purchases` MODIFY COLUMN `price_per_unit` BIGINT UNSIGNED NOT NULL COMMENT 'Price per unit paid in NAS';
ALTER TABLE `t_cash_exchange_purchases` MODIFY COLUMN `total_nas_price` BIGINT UNSIGNED NOT NULL COMMENT 'Total NAS paid for this purchase';
ALTER TABLE `t_cash_exchange_purchases` MODIFY COLUMN `listing_id` BIGINT UNSIGNED NOT NULL COMMENT 'Reference to the listing from t_cash_exchange_listings';
ALTER TABLE `t_cash_exchange_purchases` MODIFY COLUMN `purchased_at` TIMESTAMP DEFAULT CURRENT_TIMESTAMP COMMENT 'Timestamp when purchase was completed';
