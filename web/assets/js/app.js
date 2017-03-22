$( document ).ready(function() {
  $(document).foundation();

});

var update = function(value){
  window.Chart.addData(value);
  $('#currentNumber').text(value);
  calcValues(value);
}

$(function(){

    var myCounter = new flipCounter('myCounter', {value: 1000, inc: 123, pace: 1000, auto: true});

    // $('#style-switcher a').on('click', function(e){
    //   e.preventDefault();
    //   $("#myCounter").removeClass().addClass('flip-counter '+$(this).data('style'));
    //   $('#style-switcher a').removeClass('active');
    //   $(this).addClass('active');
    // });

    // $('#inc_slider').slider({
    //   range: 'max',
    //   value: 123,
    //   min: 0,
    //   max: 1000,
    //   slide: function(event, ui){
    //     $('#inc_value').text(ui.value);
    //     myCounter.setIncrement(ui.value);
    //
    //     if (ui.value == 0) myCounter.setAuto(false);
    //     else myCounter.setAuto(true);
    //   }
    // });

    // // Pace
    // $('#pace_slider').slider({
    //   range: 'max',
    //   value: 1000,
    //   min: 400,
    //   max: 2000,
    //   step: 100,
    //   slide: function(event, ui){
    //     myCounter.setPace(ui.value);
    //     $("#pace_value").text(ui.value);
    //   }
    // });

  });
