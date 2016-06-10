var StepNC = require('../../build/Release/StepNC');

var find = new StepNC.Finder();
find.OpenProject("Toleranced_Boxy_Part_5-Axis_Machining_2_Setups_Apr1.stpnc");
var a = 68815;

console.log(find.GetCompoundFeatureCount(a));


process.exit();
