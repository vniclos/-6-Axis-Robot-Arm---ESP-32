//javascripts

#ifndef _WEB_CSS_H
#define _WEB_CSS_H
const char g_HTML_Web_CSS[] PROGMEM = R"=====(
body {background-color: #555; background-image: linear-gradient(#333, #555); padding: 2px;}
#divbody { min-height:100vh; padding:5px; max-width: 800px; margin: auto; background-color: #fff; border-radius: 15px;  border: 1px solid #73AD21;}
#scnMsg{float-none;}
.round{border-radius: 50%;   min-width:60px;  min-height: 60px;margin:5px; cursor:pointer;}
.square {
   width:60px;  height: 50px; margin:2px;
  display:inline-flex;
  justify-content: left;
  align-items: center;
 }
 .big{font-size:1.6rem;font-weight:bold;}
  .med{font-size:1.2rem;font-weight:bold;}
.blue{background-color:blue;color:#ffffff;}
.yellow{background-color:yellow;color:#000000;}
.red{background-color:red;color:#ffffff;}
.green{background-color:green;color:#ffffff;}
.black{background-color:black;color:#ffffff;}
legend{font-weight: bold; background-color:green;color:#fff;padding:5px;}
fieldset {
  margin: 5px;
  margin-top:50px;
  padding: 0 10px 10px;
  border: 1px solid #666;
  border-radius: 8px;
  box-shadow: 0 0 10px #666;
  //padding-top: 30px;
}
legend {
  padding: 2px 4px;
  background: #fff;
  font-weight: bold; background-color:#222222;color:#fff;padding:5px;
   border: 1px solid #666;
  border-radius: 8px;
  box-shadow: 0 0 10px #666;
  /* For better legibility against the box-shadow */
}
fieldset > legend {
  float: left;
  margin-top: -20px;
}
fieldset > legend + * {
  clear: both;
}
.wrap {
  clear: both;
 padding: 2px;
 margin: 2px;
 height:auto;
 background: #fff;
}
.column {
  float: left;
  width: auto;
  padding: 5px;
  
}

/* Clear floats after the columns */
.row:after {
  content: "";
  display: table;
  clear: both;
}

/* Responsive layout - makes the two columns stack on top of each other instead of next to each other */
@media screen and (max-width:300px) {
  .column {
    width: 100%;
  }
}
.titlesub{font-size:0.8rem;}
.title{font-size:1.5rem;font-weight:bold;]
)=====";
#endif