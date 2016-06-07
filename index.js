var StepNC = require('./build/Release/StepNC');

var finder = new StepNC.Finder();
finder.OpenProject("model.stpnc");
var a = 45070;

console.log(finder.GetFeatureOutsideProfileClosedCircular(a));


process.exit();
