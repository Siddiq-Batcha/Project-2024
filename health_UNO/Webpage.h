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
  <h2>Health Monitor</h2><br>
  <h1>TempC :<span id="ADCValue1">0</span> </h1><br>
  <h1>Beat  :<span id="ADCValue2">0</span> </h1><br>
  

  <br><a href="https://www.armadai.net/">Armada Industrial Automation</a>
</div>
<script>

setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
  getData1();
}, 2000); //2000mSeconds update rate

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue1").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readG1", true);
  xhttp.send();
}

function getData1() {
  var xhttp1 = new XMLHttpRequest();
  xhttp1.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue2").innerHTML =
      this.responseText;
    }
  };
  xhttp1.open("GET", "readG2", true);
  xhttp1.send();
}

</script>
</body>
</html>
)=====";
