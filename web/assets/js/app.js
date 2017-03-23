$( document ).ready(function() {
  $(document).foundation();
  window.myCounter = new flipCounter('counter');
});

var update = function(value){
  console.log("Update value: " + value);
  window.Chart.addData(value);
  window.myCounter.setValue(value);
}
