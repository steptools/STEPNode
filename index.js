var StepNC = require('./build/Release/StepNC');

var finder = new StepNC.Finder();
finder.OpenProject("model.stpnc");
console.log(finder.GetMainWorkplan());
console.log(finder.GetFeatureID(89325));
finder.SaveAsP21("model2.stpnc");
//console.log(keystr);
//var key = JSON.parse(keystr);
//console.log(key.geom[0].shell);
//var geom = ms.GetGeometryJSON(key.geom[0].id,"MESH");
//console.log(geom);
//length
//undefined from first to last
//type from first to last

process.exit();
