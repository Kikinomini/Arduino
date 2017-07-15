<!DOCTYPE html>
<html class="no-js" lang="de">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.5.0/Chart.bundle.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
    <script src="js/get_datas.js"></script>
    <title>Feuchtigkeitssensor</title>
    <link rel="stylesheet" href="http://dhbhdrzi4tiry.cloudfront.net/cdn/sites/foundation.min.css">
    <link rel="stylesheet" href="css/style.css">
    <link rel="icon" type="image/png" href="image/favicon-32x32.png">
</head>
<body>


    <!-- Navigation -->
    <div class="title-bar" data-responsive-toggle="choosePlantMenu" data-hide-for="small">
        <div class="title-bar-title">Feuchtigkeitssensor</div>
    </div>
    <!-- /Navigation -->
    <br>
    <div class="row">
        <div class="row">
            <div class="medium-6 columns">
                <canvas id="myHourChart" width="400" height="200"></canvas>
            </div>
            <div class="medium-6 large-5 columns">
                <div>
                    <?php
                    $mysqli = new mysqli("193.196.175.151", "root", "4r7ZUK14", "messwerte");
                    if ($mysqli->connect_error) {
                        echo "Failed to connect t  o MySQL: " . mysqli_connect_error();
                    }

                    $sql = "Select name, standort, giessmenge, temperatur, hoehe FROM pflanze where id = 0";
                    $result = $mysqli->query($sql);
                    if($result) {
                        foreach ($result AS $key => $value) {
                            $name =  $value['name'];
                            $standort =  $value['standort'];
                            $hoehe =  $value['hoehe'];
                            $giessmenge =  $value['giessmenge'];
                            $temperatur =  $value['temperatur'];
                        }

                    }
                    $mysqli->close();
                    ?>
                    <h3> <?php echo $name; ?></h3>
                    <div class="flex">

                        <div class="div_left" id="waterdrop">
                            <img src="image/Drachenbaum3.jpg" class="kreis">
<?php
                                require_once 'get_plant.php';
                            ?>
                        </div>

                        <div class="div_right">

                            <p><b>Temperatur:</b>  <?php echo $temperatur; ?></p>
                            <p><b>Standort:</b>  <?php echo $standort; ?></p>
                            <p><b>Gießmenge:</b>  <?php echo $giessmenge; ?></p>
                            <p><b>Höhe:</b>  <?php echo $hoehe; ?></p>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>


    <div class="row column">
        <hr>
    </div>

    <div class="row column">
        <p class="lead">Wochenansicht</p>
    </div>

    <div class="row small-up-1 medium-up-2 large-up-2">
        <div class="column">
            <div class="callout">
                <p>Aktuelle Woche</p>
                <canvas id="myWeekChart" width="400" height="200"></canvas>
            </div>
        </div>
        <div class="column">
            <div class="callout">
                <p>Letzte Woche</p>
                <canvas id="mySecondWeekChart" width="400" height="200"></canvas>
            </div>
        </div>
    </div>


    <!--<div class="row column">-->
        <!--<a class="button hollow expanded">Load More</a>-->
    <!--</div>-->

    <footer>
        <div class="row">
            <div class="medium-6 columns">
                <ul class="menu">
                    <li><a href="Impressum.html">Impressum</a></li>
                </ul>
            </div>
            <div class="medium-6 columns">
                <ul class="menu float-right">

                    <li class="menu-text">© 2017 Duale Hochschule Baden-Württemberg Heidenheim</li>
		    <li class="menu-text"><div>Icons made by <a href="http://www.flaticon.com/authors/vectors-market" title="Vectors Market">Vectors Market</a> from <a href="http://www.flaticon.com" title="Flaticon">www.flaticon.com</a> is licensed by <a href="http://creativecommons.org/licenses/by/3.0/" title="Creative Commons BY 3.0" target="_blank">CC 3.0 BY</a></div></li>


                </ul>
            </div>
        </div>

    </footer>
</body>
</html>

