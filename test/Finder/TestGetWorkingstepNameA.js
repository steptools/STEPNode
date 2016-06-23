var StepNC = require('./build/Release/StepNC');

var finder = new StepNC.Finder();
finder.OpenProject("model.stpnc");
var a = 89308;

console.log(finder.GetWorkingstepName(a));

process.exit();

//Don't do GetCount/GetNext Functions, only do GetAll
//If get all isn't implemented yet mark red so that Sam can do
