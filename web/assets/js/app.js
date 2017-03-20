$( document ).ready(function() {
  $(document).foundation();

});

var update = function(value){
  window.Chart.addData(value);
  $('#currentNumber').text(value);
  calcValues(value);
}
