var StepNC = require('../../build/Release/StepNC');

var finder = new StepNC.Finder();
finder.OpenProject("../../tests/model.stpnc");
console.log(finder.GetFeatureName(89325));

process.exit();
