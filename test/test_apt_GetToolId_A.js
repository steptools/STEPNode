var StepNC = require('./build/Release/StepNC');

var apt = StepNC.AptStepMaker();
apt.OpenProject("model.stpnc");

console.log(apt.GetToolNumber(89308)); // 1
console.log(apt.GetToolNumber(90358)); // 2
console.log(apt.GetToolNumber());	   // undefined
console.log(apt.GetToolNumber(""));    // undefined
console.log(apt.GetToolNumber(-1));    // undefined

process.exit();
