<?php
/**
 * Created by PhpStorm.
 * User: nkiwa
 * Date: 20.06.2017
 * Time: 20:03
 */
require_once 'GetData.php';

$getData = new GetData();
$arrData_s1 = $getData->get_avg_date_week(1, 1);

//Sensor 3 Durchschnitt der letzten 7 Tage
$arrData_s3 = $getData->get_avg_date_week(3, 1);

//Lese Date aus
$arr_date = $getData->get_timestamp_for_week(1);

$arr_data = $getData->create_array_for_json($arr_date, $arrData_s1, $arrData_s3);

echo json_encode($arr_data);
?>