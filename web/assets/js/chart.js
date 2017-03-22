
var config = {
    type: 'line',
    legend: {
        display: false
    },
    data: {
      labels: [],
      datasets: [
        {
          label: "# of people",
          type: 'line',
          data: [],
          fill: true,
          backgroundColor: "#268bd2",
          borderColor: "#268bd2",
          yAxisID: "y-axis-total",
          lineTension: 0,
          pointRadius: 0,
          pointHitRadius: 10
        }
      ]
    },
    options: {
      animation: false,
      scales: {
        xAxes: [
          {
            type: 'time',
            time: {
              displayFormats: {
                'millisecond': 'HH:mm:ss',
                'second': 'HH:mm:ss',
                'minute': 'HH:mm:ss',
                'hour': 'HH:mm:ss',
                'day': 'HH:mm:ss',
                'week': 'HH:mm:ss',
                'month': 'HH:mm:ss',
                'quarter': 'HH:mm:ss',
                'year': 'HH:mm'
              }
            }
          }
        ],
        yAxes: [
          {
            position: "right",
            id: "y-axis-total",
            scaleType: "linear",
            ticks: {
              beginAtZero: true
            }
          }
        ]
      }
    }
  }

$( document ).ready(function() {

  var ctx = document.getElementById("totalChart").getContext("2d");
  var chart = new Chart(ctx, config);

  chart.addData = function(count) {
    chart.config.data.labels.push(Number(moment()));
    chart.config.data.datasets[0].data.push(count);
    return chart.update();
  };

  window.Chart = chart;

});
