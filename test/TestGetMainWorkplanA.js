var StepNC = require('../build/Release/StepNC');
var globals = require('./testglobals');
var find = globals.find;
var expect = require("chai").expect;
find.OpenProject('C:/Users/Nick/Documents/GitHub/STEPNode/test/model.stpnc');

describe("Test A GetMainWorkplan", function(){
	describe("Correct Return Value", function(){
		it("returns main workplan id", function() {
			var id = find.GetMainWorkplan();

			expect(id).to.equal(94989);
		});
	});
});