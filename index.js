var StepNC = require('./build/Release/StepNC');

var finder = new StepNC.Finder();
finder.OpenProject("model.stpnc");
var a = 94989;

console.log(finder.GetExecutableType(a));

process.exit();
