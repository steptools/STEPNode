var StepNC = require('../build/Release/StepNC');
find.OpenProject('model.stpnc');

describe("Test A GetMainWorkplan", function(){
	describe("Correct Return Value", function(){
		it("returns main workplan id", function() {
			var id = find.GetMainWorkplan();

			expect(id).to.equal(94989);
		});
	});
});