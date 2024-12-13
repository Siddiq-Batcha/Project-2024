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
  <h2>AI Solar Panel</h2><br>
  <h1>Solar panel 1 :<span id="ADCValue">0</span></h1><br>
  <h1>Solar panel 2 :<span id="ADCValue2">0</span></h1><br>
  <h1>Solar panel 3 :<span id="ADCValue3">0</span></h1><br>
  <h1>Short Circuit :<span id="ADCValue4">0</span></h1><br>
  
  <br><a href="https://www.armadai.net/">Armada Industrial Automation</a>
</div>
<script>

setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
  getData2();
  getData3();
  getData4();
  

}, 2000); //2000mSeconds update rate

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readADC1_2", true);
  xhttp.send();
}

function getData2() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue2").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readADC3_4", true);
  xhttp.send();
}


function getData3() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue3").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readADC5_6", true);
  xhttp.send();
}

function getData4() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue4").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readshot", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";
