var StepNC = require('./build/Release/StepNC');

var ms = new StepNC.machineState("model.stpnc");
var keystr = ms.GetKeystateJSON();

var finder = new StepNC.Finder();
finder.Open238("model.stpnc");
console.log(finder.GetMainWorkplan());
//console.log(keystr);
//var key = JSON.parse(keystr);
//console.log(key.geom[0].shell);
//var geom = ms.GetGeometryJSON(key.geom[0].id,"MESH");
//console.log(geom);
//length
//undefined from first to last
//type from first to last

process.exit();
