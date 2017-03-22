$( document ).ready(function() {
  $(document).foundation();

  window.myCounter = new flipCounter('myCounter');

});

var update = function(value){
  window.Chart.addData(value);
  window.myCounter.setValue(value);
}
