const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Toku Automations</title>
<style>
.card1{
    max-width: 350px;
     min-height: 150px;
     background: #02b875;
     margin: auto;
     padding: 30px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
     text-align: center;
     position: relative;
     margin-left: auto;
    margin-right: auto;
    text-shadow: 2px 2px grey;
}
.card2{
    max-width: 350px;
     min-height: 150px;
     background: rgb(255, 165, 0);
     padding: 50px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
     text-align: center;
     margin-left: auto;
     margin-right: auto;
}
.card3{
    max-width: 400px;
     min-height: 250px;
     background: rgb(25, 100, 255);
     padding: 50px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
     text-align: center;
     margin-left: auto;
     margin-right: auto;i8
     font-size: 50px;
}
.button {
  background-color: #008CBA; /* Green */
  border: none;
  color: white;
  padding: 20px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
  border-radius: 8px;
  width: 80px;
  text-align: center;
  box-shadow: 0 8px 16px 0 rgba(0,0,0,0.2), 0 6px 20px 0 rgba(0,0,0,0.19)
}
.button:hover {
  background-color: #4CAF50;
  color: white;
}
.button:active {
  background-color: #3e8e41;
  box-shadow: 0 3px #666;
  transform: translateY(2px);
}
.button1 {
  background-color: #008CBA; /* Green */
  border: none;
  color: white;
  padding: 20px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
  border-radius: 8px;
  width: 150px;
  text-align: center;
  box-shadow: 0 8px 16px 0 rgba(0,0,0,0.2), 0 6px 20px 0 rgba(0,0,0,0.19)
}
.button1:hover {
  background-color: #4CAF50;
  color: white;
}
.button1:active {
  background-color: #3e8e41;
  box-shadow: 0 3px #666;
  transform: translateY(2px);
}
</style>
</head>
<body>  
<p style="text-align:center; font-size: 30px; ">Toku Technologies</p>

<div class="card1">
  Water-pump Machine <br><br>
  <button class="button" type="button" onclick="sendData(1)">ON</button>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <button class="button" type="button" onclick="sendData(0)">OFF</button>
  <br>
  <br>Machine State is : <span id="LEDState">NA</span>
</div>

<div class="card2">
  <h3>Tank-Water Level : <span id="ADCValue">0</span></h3>
  <h3>Time to fill : <span id="ADCValue1">0</span> minutes</h3>
  <button class="button1" type="button" onclick="sendData(1)">Fill & Off</button>

</div>

<script>
function sendData(led) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("LEDState").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "setLED?LEDstate="+led, true);
  xhttp.send();
}

setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
  getData1();
}, 2000); //2000mSeconds update rate

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readADC", true);
  xhttp.send();
}

function getData1() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue1").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readADC1", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";
