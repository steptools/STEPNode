var StepNC = require('../build/Release/StepNC');
module.exports.find = new StepNC.Finder();
module.exports.apt = new StepNC.AptStepMaker();