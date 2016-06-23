var StepNC = require('./build/Release/StepNC');

var finder = new StepNC.Finder();
finder.OpenProject("model.stpnc");
console.log(finder.GetWorkplanToolAll(finder.GetMainWorkplan()));

process.exit();
