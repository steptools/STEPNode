var StepNC = require('./build/Release/StepNC');

var ms = new StepNC.machineState("model.stpnc");
var keystr = ms.GetKeystateJSON();
//console.log(keystr);
//var key = JSON.parse(keystr);
//console.log(key.geom[0].shell);
//var geom = ms.GetGeometryJSON(key.geom[0].id,"MESH");
//console.log(geom);

process.exit();
