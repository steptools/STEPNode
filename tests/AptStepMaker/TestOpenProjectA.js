var StepNC = require('../../build/Release/StepNC');

var apt = new StepNC.AptStepMaker();
apt.OpenProject("../../model.stpnc");

process.exit();
