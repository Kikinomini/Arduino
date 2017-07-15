<?php
/**
 * Created by PhpStorm.
 * User: nkiwa
 * Date: 29.06.2017
 * Time: 13:36
 */
require_once 'GetData.php';

$getData = new GetData();
$arr_data = [];
$arr_data = $getData->get_current_data();

//feucht
if($arr_data[0] <= 178 && $arr_data[1] <= 215 || $arr_data[0] <= 178 && $arr_data[1] <= 215)
{
    echo "<div class='hoehe'>";
    require 'image/svg/drop.svg';
    echo "</div>";
    echo "<div class='hoehe'>";
    require 'image/svg/drop.svg';
    echo "</div>";
    echo "<div class='hoehe'>";
    require 'image/svg/drop.svg';
    echo "</div>";
}
//trocken
else if($arr_data[0] > 194 && $arr_data[1] > 231 || $arr_data[0] > 194 && $arr_data[1] <= 231 && $arr_data[1] > 215 || $arr_data[1] > 231 && $arr_data[0] <= 194 && $arr_data[0] > 178)
{
    echo "<div class='hoehe'>";
    require 'image/svg/drop.svg';
    echo "</div>";
}
//mittel
else
{
    echo "<div class='hoehe'>";
    require 'image/svg/drop.svg';
    echo "</div>";
    echo "<div class='hoehe'>";
    require 'image/svg/drop.svg';
    echo "</div>";
}
?>