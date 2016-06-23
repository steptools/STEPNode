var StepNC = require('./build/Release/StepNC');

var finder = new StepNC.Finder();
finder.OpenProject("model.stpnc");
var tools = finder.GetToolAll();
console.log(tools);
for(var i = 0; i < tools.length; i++){
	console.log(tools[i]);
	console.log(finder.GetToolIdentifier(tools[i]));
}

process.exit();