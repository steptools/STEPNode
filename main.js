'use strict';
let Platform = process.platform;
let StepNode;

switch(Platform) {
	case 'win32':
		StepNode = require('./Win/STEPNode');
		break;
	case 'linux':
		StepNode = require('./Linux/STEPNode');
		break;
	case 'darwin':
		StepNode = require('./Mac/STEPNode');
		break;
}
module.exports = StepNode;
