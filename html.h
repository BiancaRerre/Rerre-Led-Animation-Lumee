
const char gerador[] PROGMEM = R"===(
  
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Gerador de animação RGB</title>
  </head>
  
  <style>
    @import url('https://fonts.googleapis.com/css2?family=Courgette&display=swap');
    @import url('https://fonts.googleapis.com/css2?family=Lobster&display=swap');
    @import url('https://fonts.googleapis.com/css2?family=Mynerve&display=swap');
    @import url('https://fonts.googleapis.com/css2?family=Sacramento&display=swap');
    
body {
  color: #000;
  background:  #e0e0e0;
  line-height: 150%;
  display: flex;
  justify-content: center;
  align-items: center;
  height: 100vh;
  padding: 24px;
  font-family: arial;
}
.titulo{
  font-size: 72px;
  color: #5d5d5d;
  line-height: 20px;
  text-shadow: 2px 2px 5px #34343434;
}
.quadrado{
  width: 100%;
  max-width: 500px;
  box-shadow:  4px 4px 15px #acacac55,
             -4px -4px 15px #eee2;
  margin: 0 auto;
  display: flex;
  justify-content: center;
  align-items: center;
  flex-direction: column;
  padding: 24px;
  gap: 6px;
  border-radius: 32px;
  background-color: white;
 
}
p{
  font-size: 24px;
}

.sliders{
  border-radius: 10px;
  padding: 10px;
  background:#0001;
  font-family: Lobster;
}

h2 {
  margin-bottom: 3px; /* remove o espaçamento inferior */
  font-family: Arial;

}

h1 {
  font-family: Courgette;

}

input[type="range"] {
  width: 300px;
  height: 10px;
  border-radius: 0px;
  background-color: red;
  
}
  </style>
  
  <body>
    <div class="quadrado"> 
    <h1>Gerador de animação RGB</h1>
     <div class="sliders">      
    <h2>Cores RGB <span id='rgbValue' style="color:#999;"></span></h2>  
   <div class="sliders">
     
<table>
  <tr>
    <td><label for="red">Red:</label></td>
    <td><input type="range" id="red" name="red" min="0" max="255" value="0"></td>
  </tr>
  <tr>
    <td><label for="green">Green:</label></td>
    <td><input type="range" id="green" name="green" min="0" max="255" value="0"></td>
  </tr>
  <tr>
    <td><label for="blue">Blue:</label></td>
    <td><input type="range" id="blue" name="blue" min="0" max="255" value="0"></td>
  </tr>
</table>
     
</div>

    <h2>Espera e transição</h2>
    <div class="sliders">
    <label for="wait">Wait:</label>
    <input type="number" id="wait" name="wait" min="0" max="5000" value="0">
    <br>

    <label for="fade">Fade:</label>
    <input type="number" id="fade" name="fade" min="0" max="5000" value="2000">
    <br></div>

    <h2>Código de animação RGB</h2>
    <div class="sliders">
    <textarea id="result" rows="5" cols="50"></textarea>
    <br>
    <div>
    <button id="insert-btn">Inserir</button>
    <button id="insert-loop-btn">Inserir loop</button>
    <button id="salvar">Salvar</button>
    <button id="parar">Parar ⏹</button>
    <button id="play">Play ⏵</button>
    <button id="restart">Restart</button>
    </div>
      

    <script id="principal">
      const insertBtn = document.querySelector("#insert-btn");
      const insertLoopBtn = document.querySelector("#insert-loop-btn");
      const salvarBtn = document.querySelector("#salvar");
      const stopBtn = document.querySelector("#parar");
      const playBtn = document.querySelector("#play");
      const restartBtn = document.querySelector("#restart");
      const resultInput = document.querySelector("#result");
      const redInput = document.querySelector("#red");
      const greenInput = document.querySelector("#green");
      const blueInput = document.querySelector("#blue");
      const waitInput = document.querySelector("#wait");
      const fadeInput = document.querySelector("#fade");

      let hasLoop = false;
      

      insertBtn.addEventListener("click", () => {
  const red = redInput.value;
  const green = greenInput.value;
  const blue = blueInput.value;
  
  const wait = waitInput.value;
  const waitCode = wait > 0 ? `W${wait}` : "";
  
  const fade = fadeInput.value;
  const fadeCode = fade > 0 ? `F${fade}` : "";

  const code = `${hasLoop ? "L" : ""}R${red}G${green}B${blue}${fadeCode}${waitCode}`;

  resultInput.value += `${resultInput.value ? "," : ""}${code}`;
});
      
salvarBtn.addEventListener("click", () => {
    fazRequisicao(`/animation?animation=${resultInput.value}`);
  console.log(resultInput);
      });
      
stopBtn.addEventListener("click", () => {
    fazRequisicao(`/stop`);
  console.log(resultInput);
      });
restartBtn.addEventListener("click", () => {
    fazRequisicao(`/restart`);
  console.log(resultInput);
      });      
playBtn.addEventListener("click", () => {
    fazRequisicao(`/play`);
  console.log(resultInput);
      });
      insertLoopBtn.addEventListener("click", () => {
        hasLoop = true;
        resultInput.value += hasLoop ? "L" : "";
         hasLoop = false;
      });
       const fazRequisicao = function(url){
    console.log(url);
    let request = new XMLHttpRequest();
    request.open("GET", url, true);
  request.send();
}
    </script>
      
      <script id="trocar-cor-do-fundo">
      const body = document.body 
const rbgValue = document.getElementById('rgbValue');
const red = document.getElementById('red')
const green = document.getElementById('green')
const blue = document.getElementById('blue')

const changeColor = ( ) =>{
  let r = red.value;
  let g = green.value;
  let b = blue.value;
  let bkgdClr = `rgb(${r},${g},${b})`
  body.style.background = bkgdClr;
  rbgValue.innerHTML = bkgdClr;
 }

red.addEventListener('input', changeColor);
green.addEventListener('input', changeColor);
blue.addEventListener('input', changeColor)

changeColor();

      </script>
  </body>
</html>

)===";

const char postForms[] PROGMEM = R"===(

<html>
  <head>
    <script src="https://cdn.jsdelivr.net/npm/@jaames/iro@5"></script>
    <link rel="stylesheet" href="style.css"> 
    <meta name="viewport" content="initial-scale=1">
    <title>LUMEE</title>
  </head>
  <body>
    <div id="values"></div>
    <div id="hexInput"></div>
    <div class="quadrado"> 
      <h1 class="titulo">Lumee</h1>
      <div class="wrap">
        <div class="colorPicker"></div>
      </div>
      <P class="frase"> tech is beauty</P>
    </div>
    <script type="text/javascript" src="/js"></script>
  </body>
</html>

)===";

const char configLumee[] PROGMEM = R"===(
<html>
  <head>
  <script src="https://cdn.jsdelivr.net/npm/@jaames/iro@5"></script>
  <link rel="stylesheet" href="style.css"> 
   <title>
     LUMEE
    </title>
  </head>
  <body>
    <div id= "values"></div>
    <div id= "hexInput"></div>
    <center><div class="quadrado"> 
    <center><h1 class = "titulo">Config Lumee</centerr>  

    </center>
  </div>
  </body>
</html>
)===";