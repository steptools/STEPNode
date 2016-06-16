var StepNC = require('./build/Release/StepNC');

var ms = new StepNC.machineState("model.stpnc");
//ms.LoadMachine("model.stpnc");
var a = 89387;

var fs = require('fs');
console.log(ms.GetKeystateJSON());
ms.GoToWS(a);
console.log(ms.GetKeystateJSON());

process.exit();