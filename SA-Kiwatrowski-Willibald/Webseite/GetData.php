<?php
/**
 * Created by PhpStorm.
 * User: nkiwa
 * Date: 23.06.2017
 * Time: 08:10
 */
class GetData{

    function __construct()
    {
    }

    function get_data_last_ten_hours($sensor)
    {
        $mysqli = new mysqli("193.196.175.151", "root", "4r7ZUK14", "messwerte");
        if ($mysqli->connect_error) {
            echo "Failed to connect t  o MySQL: " . mysqli_connect_error();
        }
        //verarbeite Sensor
        $sql = "Select wert, TIME(messzeitpunkt) as zeitpunkt from messwerte where sensor = '$sensor' Order by messzeitpunkt desc LIMIT 10";

        $result = $mysqli->query($sql);
        $arr_data = [];
        $arr_label = [];

        //schreibe Result in Array
        if($result) {
            foreach ($result AS $key => $value) {
                $arr_data[] = (int)$value['wert'];
                $arr_label[] = $value['zeitpunkt'];
            }
            $arr_data = array_reverse($arr_data);
            $arr_label = array_reverse($arr_label);
        }

        $arr_erg[] = [$arr_data, $arr_label];
        $mysqli->close();
        return $arr_erg;
    }

    //erzeugt Array Struktur für Json
    function create_array_for_json($arr_labels, $arr_data_s1, $arr_data_s3)
    {
        $arr_data = [
            "labels" => $arr_labels,
            "datasets" => [[
                "label" => "Sensor 1",
                "data" => $arr_data_s1,
                "borderColor" => [
                    'rgba(255,0,0,0.6)'
                ],
                "backgroundColor" => [
                    'rgba(255,0,0,0.6)'
                ],
                "fill" => false,
                "borderWidth" => 1
            ],
                [
                    "label" => "Sensor 3",
                    "data" => $arr_data_s3,
                    "borderColor" => [
                        'rgba(0,0,255,0.6)'
                    ],
                    "backgroundColor" => [
                        'rgba(0,0,255,0.6)'
                    ],
                    "fill" => false,
                    "borderWidth" => 1
                ]
            ]
        ];
        return $arr_data;
    }

    function get_avg_date_week($sensor, $i)
    {
        $mysqli = new mysqli("193.196.175.151", "root", "4r7ZUK14", "messwerte");
        if ($mysqli->connect_error) {
            echo "Failed to connect t  o MySQL: " . mysqli_connect_error();
        }
        $i = $i*7;
        $arr_data = [];
        //erzeuge date für aktueller Tag - i Tage
        $timestamp = time() - $i*24*60*60;
        $date = date("Y-m-d", $timestamp);

        //erzeuge date minus 1 Tag
        $timestamp_plus_1_day = $timestamp + 24*60*60;
        $date_plus_1_day = date("Y-m-d", $timestamp_plus_1_day);

        for ($i = 0; $i < 7; $i++)
        {
            $sql = "Select AVG(wert) as Wert FROM messwerte 
                where messzeitpunkt > '$date' 
                AND messzeitpunkt <= '$date_plus_1_day' 
                AND sensor = '$sensor'";
            $result = $mysqli->query($sql);

            if($result) {
                foreach ($result AS $key => $value) {
                    $arr_data[] = $value['Wert'];
                }
            }
            $timestamp = $timestamp - 24*60*60;
            $date = date("Y-m-d", $timestamp);
            $timestamp_plus_1_day = $timestamp_plus_1_day- 24*60*60;
            $date_plus_1_day = date("Y-m-d", $timestamp_plus_1_day);
        }

        $arr_data = array_reverse($arr_data);
        $mysqli->close();
        return $arr_data;
    }

    function get_timestamp_for_week($i)
    {
        $i = $i*7;
        $arr_data = [];
        //erzeuge date für aktueller Tag - i Tage
        $timestamp = time() - $i*24*60*60;
        $date = date("d.m.Y", $timestamp);

        for ($i = 0; $i < 7; $i++)
        {
            $arr_data[] = $date;
            $timestamp = $timestamp - 24*60*60;
            $date = date("d.m.Y", $timestamp);
        }
        $arr_data = array_reverse($arr_data);
        return $arr_data;
    }

    function get_current_data()
    {
        $mysqli = new mysqli("193.196.175.151", "root", "4r7ZUK14", "messwerte");
        if ($mysqli->connect_error) {
            echo "Failed to connect t  o MySQL: " . mysqli_connect_error();
        }
        $arr_data = [];

        $sql = "Select wert FROM messwerte 
                where sensor = 1 ORDER BY id DESC LIMIT 1";
        $result = $mysqli->query($sql);

        if($result) {
            foreach ($result AS $key => $value) {
                $arr_data[] = $value['wert'];
            }
        }

        $sql = "Select wert FROM messwerte 
                where sensor = 3 ORDER BY id DESC LIMIT 1";
        $result = $mysqli->query($sql);

        if($result) {
            foreach ($result AS $key => $value) {
                $arr_data[] = $value['wert'];
            }
        }
        $mysqli->close();
        return $arr_data;
    }
}
