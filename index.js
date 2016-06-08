var StepNC = require('./build/Release/StepNC');

var finder = new StepNC.Finder();
finder.OpenProject("model.stpnc");
var a = 94989;

console.log(finder.IsSelective(a));
console.log(finder.IsWorkingStep(a));
console.log(finder.IsWorkplan(a));

process.exit();
