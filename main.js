'use strict';
let Platform = process.platform;
let StepNode;

switch(Platform) {
	case 'win32':
		StepNode = require('./Win/StepNode');
		break;
	case 'linux':
		StepNode = require('./Linux/StepNode');
		break;
	case 'darwin':
		StepNode = require('./Mac/StepNode');
		break;
}
module.exports = StepNode;