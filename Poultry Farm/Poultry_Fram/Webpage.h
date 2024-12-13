const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style>
.card{
    max-width: 400px;
     min-height: 250px;
     background: #02b875;
     padding: 30px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}
</style>
<body>

<div class="card">
  <h2>Poultry Farm</h2><br>
  <h1>Ammonia :<span id=>0</span> %</h1><br>
  <h1>Methane  :<span id=>0</span> %</h1><br>
  <h1>CO2      :<span id="ADCValue3">0</span> %</h1><br>
  <h1>Hydrogen Sulphide:<span id=>0</span> %</h1><br>
 

  <br><a href="https://www.armadai.net/">Armada Industrial Automation</a>
</div>
<script>
var sensorElements = [ "ADCValue3"]; // IDs of sensor value elements

setInterval(function() {
  // Call a function repetitively with a 2-second interval
  getData();
}, 2000); // 2000 milliseconds update rate

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var values = this.responseText.split(',').map(Number);
      // Update sensor value elements in the webpage
      for (var i = 0; i < values.length; i++) {
        var sensorValue = values[i];
        document.getElementById(sensorElements[i]).innerHTML = sensorValue ;
        // Change font color based on sensor value
        if (sensorValue > 50 && sensorElements[i] !== "ADCValue3") 
        {
          document.getElementById(sensorElements[i]).style.color = "red";
        } 
        else if (sensorElements[i] === "ADCValue3" && sensorValue >= 50) 
        {
          document.getElementById(sensorElements[i]).style.color = "red";
        }
        else 
         {
          document.getElementById(sensorElements[i]).style.color = "black";
        }

      }
    }
  };
  xhttp.open("GET", "readAllSensors", true);
  xhttp.send();
}
</script>

</body>
</html>
)=====";
