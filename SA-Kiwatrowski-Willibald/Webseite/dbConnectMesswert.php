<?php
/**
 * Created by PhpStorm.
 * User: Kinomi
 * Date: 29.03.2017
 * Time: 12:47
 */
$mysqli = new mysqli("193.196.175.151", "root", "4r7ZUK14", "messwerte");
if ($mysqli->connect_error) {
	echo "Failed to connect t  o MySQL: " . mysqli_connect_error();
}
?>