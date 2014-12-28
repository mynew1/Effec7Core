/*
SQLyog Community v12.03 (64 bit)
MySQL - 5.5.41 : Database - char
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`char` /*!40100 DEFAULT CHARACTER SET latin1 */;

USE `char`;

/*Table structure for table `logy_gm` */

DROP TABLE IF EXISTS `logy_gm`;

CREATE TABLE `logy_gm` (
  `id` int(9) NOT NULL AUTO_INCREMENT,
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `player` varchar(12) NOT NULL,
  `account` int(9) NOT NULL,
  `command` varchar(255) NOT NULL,
  `position` varchar(96) NOT NULL,
  `selected` varchar(96) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `account` (`account`),
  KEY `player` (`player`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;

/*Table structure for table `logy_item_get` */

DROP TABLE IF EXISTS `logy_item_get`;

CREATE TABLE `logy_item_get` (
  `id` int(9) NOT NULL AUTO_INCREMENT,
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `guid` int(9) NOT NULL,
  `player` varchar(12) NOT NULL,
  `account` int(9) NOT NULL,
  `item` int(6) NOT NULL,
  `item_guid` int(6) NOT NULL,
  `state` tinyint(1) NOT NULL,
  `position` varchar(96) NOT NULL,
  `target` varchar(96) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `guid` (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
