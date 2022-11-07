 #ifndef _WEB_ROOT_H
#define _WEB_ROOT_H

const char g_HTML_Web_root[] PROGMEM = R"=====(
    <!DOCTYPE html><html><head> 
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
	<meta name=viewport content="width=device-width, initial-scale=1">
<link rel="stylesheet" type="text/css" href="css.css"><script src="/js.js"></script> <title>Enlace de Susana y Javier </title> 
</head>
<body>
<div id="divbody">
<div class="row">
	<div class="column">
		<img  style=" width:120px; "src='/svg.svg' alt="Robot Susa & Javi">
	</div>
	<div class="column" >
			<spam class="title">Susana & Javier
			<br/><spam class="titlesub"> Gracias por vuestra compañia</spam></spam>
	</div>
  <div class="clear"></div>
</div>
 <fieldset>
   <legend>Mover:</legend>
  <br/>
  <span class="square">1</span>
  <input type="button" class="round green big" onClick="jsMove(0,'der','idMsg_0')" value ="&#8630;"/>
  <input type="button" class="round green big" onClick="jsMove(0,'izq','idMsg_0')" value ="&#8631;"/>
  
  <br/>
  <span class="square"> 2</span>
  <input type="button" class="round blue big" onClick="jsMove(1,'der','idMsg_0')" value ="&#11014;"/>
  <input type="button" class="round blue big" onClick="jsMove(1,'izq','idMsg_0')" value ="&#11015;"/>

  <br/>
  <span class="square">3</span>
  <input type="button" class="round red big" onClick="jsMove(2,'izq','idMsg_0')" value ="&#11014;"/>
  <input type="button" class="round red big" onClick="jsMove(2,'der','idMsg_0')" value ="&#11015;"/>
  <p id="idMsg_0">Para mover, pulsa en los botones<p>
 </fieldset>

 <fieldset>
 <legend>Manejar pinza:</legend>
   <br/><span class="square">Mover</span>
  <input type="button" class="round blue big" onClick="jsMove(3,'izq','idMsg_1')" value ="&#11014;"/>
  <input type="button" class="round blue big" onClick="jsMove(3,'der','idMsg_1')" value ="&#11015;"/>

  <br/><span class="square">Girar</span>
  <input type="button" class="round green big" onClick="jsMove(4,'der','idMsg_1')" value ="&#8630;"/>
  <input type="button" class="round green big" onClick="jsMove(4,'izq','idMsg_1')" value ="&#8631;"/>
 <br/>
 <span class="square">Pinzar</span>
  <input type="button" class="round yellow med" onClick="jsMove(5,'der','idMsg_1')" value ="C"/>
  <input type="button" class="round yellow med" onClick="jsMove(5,'izq','idMsg_1')" value ="A"/>
   <p id="idMsg_1">Para mover, pulsa en los botones<p>
 </fieldset>
  <fieldset>
  <legend>Funciones especiales:</legend>
  <br/><input type="button" class="round black big" onClick="jsMove(-1,'fnc01','idMsg_2')" value ="Inicio"/>
  <br><input type="button" class="round black big" onClick="jsMove(-1,'fnc02','idMsg_2')" value ="Auto"/>
      <p id="idMsg_2"> Elige una opcion<p>
  </fieldset>
<script>
function jsMove(idMotor,cmd,idMsg)
{
	document.getElementById('idMsg_0').innerHTML = 'Para mover, pulsa en los botones';
	document.getElementById('idMsg_1').innerHTML = 'Para mover, pulsa en los botones';
	document.getElementById('idMsg_2').innerHTML = 'Elige una opcion';
	let url="/cmd?idMotor="+idMotor+"&cmd="+cmd;
document.getElementById(idMsg).innerHTML =url;
   fncGetHtml(idMsg, url) ;
	}
</script>
<br/>
<div id="scnMsg">.</div>
<div id="scnBody">.</div>
<div id="scnDebug"></div>

</div>
</body>
</html>
)=====";
//<input type="button"   class="btn" value="All Stop" onclick="fncGetHtml('scnMsg','fncStopAll');return false;"></button>
#endif