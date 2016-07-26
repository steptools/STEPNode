var StepNode = require('../build/Release/StepNode');
module.exports.find = new StepNode.Finder();
module.exports.apt = new StepNode.AptStepMaker();