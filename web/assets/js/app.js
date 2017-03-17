
var config = {
    type: 'line',
    data: {
      labels: [],
      datasets: [
        {
          label: "Temperature",
          type: 'line',
          data: [],
          fill: false,
          backgroundColor: "rgba(255, 99, 132, 0.8)",
          borderColor: "rgba(255, 99, 132, 0.8)",
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
            scaleType: "linear"
          }
        ]
      }
    }
  }

$( document ).ready(function() {
  $(document).foundation();


  var ctx = document.getElementById("totalChart").getContext("2d");
  var chart = new Chart(ctx, config);

  chart.addData = function(count) {
    chart.config.data.labels.push(Number(moment()));
    chart.config.data.datasets[0].data.push(count);
    return chart.update();
  };

  window.Chart = chart;
});
