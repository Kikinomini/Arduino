<?php
/**
 * Created by PhpStorm.
 * User: nkiwa
 * Date: 06.06.2017
 * Time: 20:06
 */
require_once 'GetData.php';

//verarbeite Sensor 1
$getData = new GetData();
$arrErg_s1 = $getData->get_data_last_ten_hours(1);
//var_dump($arrErg);

$arr_data_s1 = [];
$arr_time = [];

//Teilt Ergebnis Array in Werte und Time auf
foreach($arrErg_s1 AS $key => $value)
{
    $arr_data_s1 = $value[0];
    $arr_time = $value[1];
}

//verarbeite Sensor 3
$arrErg_s3 = $getData->get_data_last_ten_hours(3);
foreach($arrErg_s3 AS $key => $value)
{
    $arr_data_s3 = $value[0];
}

$arr_data = $getData->create_array_for_json($arr_time, $arr_data_s1, $arr_data_s3);

echo json_encode($arr_data);
?>