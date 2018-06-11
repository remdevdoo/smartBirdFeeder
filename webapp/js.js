  ////  Course:         Applications for IoT
  ////  Description:    Indicate seed volume of a bird feeder house.
  ////  Used sensor:    Ultrasonic
  ////  Used board:     Ardruino mkr 1300
  ////  Developed by:   Remon



  // Create global variable for storing ajax call data.
  var result = null;

  // Interval get function (10sec).
  setInterval(get, 10000);


  // GET data from /volume with an Ajax request.
  function get() {
      $.ajax({
          async: false,
          type: "GET",
          url: "http://localhost:2000/volume",
          datatype: "json",
          success: myCallback,
          error: errorHandler,
      });
  }


  // Function called on successful Ajax request.
  function myCallback(response) {
      response = JSON.parse(response);
      result = response.payload;
      console.log("Received value from AJAX call: " + result);
      display();
      triggerChart();
  }

  // Function to be called if Ajax request failed.
  function errorHandler() {

      alert("Ajax call failed");
  }


  // Function to display the correct volume div from index.html
  function display() {

      if (result == null) {

          $("#danger-value").fadeIn("slow");
          $("#danger-value").delay(5000).fadeOut("slow");

      } else if (result == 0) {

          $("#danger-empty").fadeIn("slow");
          $("#danger-empty").delay(5000).fadeOut("slow");

      } else if (result >= 1 && result < 30) {

          $("#danger").fadeIn("slow");
          $("#danger").delay(5000).fadeOut("slow");

      } else if (result >= 30 && result < 60) {

          $("#warning").fadeIn("slow");
          $("#warning").delay(5000).fadeOut("slow");

      } else if (result >= 60 && result <= 100) {

          $("#info").fadeIn("slow");
          $("#info").delay(5000).fadeOut("slow");

      } else {

          $("#danger-value").fadeIn("slow");
          $("#danger-value").delay(5000).fadeOut("slow");

      }

  }
