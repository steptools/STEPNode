var StepNC = require('./build/Release/StepNC');

var finder = new StepNC.Finder();
finder.OpenProject("model.stpnc");
var a = 94989;

console.log(finder.GetExecutableDistance(a));

console.log(finder.GetExecutableDistanceUnit(a));

//console.log(finder.GetExecutableDistanceUnit(2983748298732873295));

process.exit();
