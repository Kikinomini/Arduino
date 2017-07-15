<?php
/**
 * Created by PhpStorm.
 * User: Kinomi
 * Date: 04.04.2017
 * Time: 16:58
 */
include 'dbConnectMesswert.php';

$messwert = $_POST["w"];
$sensor = $_POST["s"];
$pflanze = $_POST["p"];


//var_dump($_REQUEST);

$sql = "INSERT INTO messwerte (wert, sensor, id_pflanze) VALUES ('$messwert', '$sensor', '$pflanze')";

$mysqli->query($sql);

require_once 'DumpHTTPRequestToFile.php';
(new DumpHTTPRequestToFile())->execute('request.log');

$mysqli->close();
?>