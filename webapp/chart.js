//Gauge

var chart = AmCharts.makeChart("chartdiv", {
  "theme": "light",
  "type": "gauge",
  "axes": [{
    "topTextFontSize": 20,
    "topTextYOffset": 70,
    "axisColor": "#000000",
    "axisThickness": 1,
    "endValue": 100,
    "gridInside": true,
    "inside": true,
    "radius": "50%",
    "valueInterval": 10,
    "tickColor": "#000000",
    "startAngle": -90,
    "endAngle": 90,
    "unit": "%",
    "bandOutlineAlpha": 0,
    "bands": [{
      "color": "#ea4631",
      "endValue": 100,
      "innerRadius": "105%",
      "radius": "170%",
      "gradientRatio": [0.5, 0, -0.5],
      "startValue": 0
    }, {
      "color": "#0a9b1b",
      "endValue": 0,
      "innerRadius": "105%",
      "radius": "170%",
      "gradientRatio": [0.5, 0, -0.5],
      "startValue": 0
    }]
  }],
  "arrows": [{
    "alpha": 1,
    "innerRadius": "35%",
    "nailRadius": 0,
    "radius": "170%"
  }]
});

//setInterval(triggerChart, 6000);

// get value from global variable result.
function triggerChart() {

  var value = result;
  chart.arrows[0].setValue(value);
  chart.axes[0].setTopText(value + " %");
  // adjust darker band to new value
  chart.axes[0].bands[1].setEndValue(value);
}
