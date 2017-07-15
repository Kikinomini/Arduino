/**
 * Created by nkiwa on 28.06.2017.
 */
$( document ).ready(function () {
    var refreshInterval = 600000;
    window.setInterval("createHourChartWithoutAnimation('myHourChart','get_data_last_ten_hours.php' )", refreshInterval);
    window.setInterval("createChartWithoutAnimation('myWeekChart','get_avg_data_last_week.php' )", refreshInterval);
    window.setInterval("createChartWithoutAnimation('mySecondWeekChart','get_avg_data_last_second_week.php' )", refreshInterval);
    window.setInterval("getWaterDrop()", refreshInterval);
    createHourChart('myHourChart','get_data_last_ten_hours.php');
    createChart('myWeekChart','get_avg_data_last_week.php');
    createChart('mySecondWeekChart','get_avg_data_last_second_week.php');
});

function createChart(elementName, DataName) {
    var ctx = document.getElementById(elementName);
    var oReq = new XMLHttpRequest();
    var test;
    oReq.onload = function () {
        test = JSON.parse(this.responseText);
        var myChart = new Chart(ctx, {
            type: 'line',
            data: test,
            options: {
                scales: {
                    yAxes: [{
                        ticks: {
                            beginAtZero: false
                        }
                    }]
                }
            }
        });
    };
    console.log(this.responseText);
    oReq.open("get", DataName, true);
    oReq.send();
}

function createHourChart(elementName, DataName) {
    var ctx = document.getElementById(elementName);
    var oReq = new XMLHttpRequest();
    var test;
    oReq.onload = function () {
        test = JSON.parse(this.responseText);
        var myChart = new Chart(ctx, {
            type: 'line',
            data: test,
            options: {
                scales: {
                    yAxes: [{
                        ticks: {
                            beginAtZero: false,
                            suggestedMin: 175,
                            suggestedMax: 225
                        }
                    }]
                }
            }
        });
    };
    console.log(this.responseText);
    oReq.open("get", DataName, true);
    oReq.send();
}

function createChartWithoutAnimation(elementName, DataName) {
    var ctx = document.getElementById(elementName);
    var oReq = new XMLHttpRequest();
    var test;
    oReq.onload = function () {
        test = JSON.parse(this.responseText);
        var myChart = new Chart(ctx, {
            type: 'line',
            data: test,
            options: {
                scales: {
                    yAxes: [{
                        ticks: {
                            beginAtZero: false
                        }
                    }]
                },
                animation: {
                    duration: 0 // general animation time
                },
                hover: {
                    animationDuration: 0 // duration of animations when hovering an item
                },
                responsiveAnimationDuration: 0 // animation duration after a resize
            }
        });
    };
    console.log(this.responseText);
    oReq.open("get", DataName, true);
    oReq.send();
}

function createHourChartWithoutAnimation(elementName, DataName) {
    var ctx = document.getElementById(elementName);
    var oReq = new XMLHttpRequest();
    var test;
    oReq.onload = function () {
        test = JSON.parse(this.responseText);
        var myChart = new Chart(ctx, {
            type: 'line',
            data: test,
            options: {
                scales: {
                    yAxes: [{
                        ticks: {
                            beginAtZero: false,
                            suggestedMin: 175,
                            suggestedMax: 225
                        }
                    }]
                },
                animation: {
                    duration: 0 // general animation time
                },
                hover: {
                    animationDuration: 0 // duration of animations when hovering an item
                },
                responsiveAnimationDuration: 0 // animation duration after a resize
            }
        });
    };
    console.log(this.responseText);
    oReq.open("get", DataName, true);
    oReq.send();
}

function getWaterDrop() {
    var ctx = document.getElementById('waterdrop');
    var oReq = new XMLHttpRequest();
    oReq.open("get", 'get_plant.php', true);
    oReq.send();
}