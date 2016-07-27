# **Mocha Testing Documentation**

#### Documentation for Mocha can be found here:  

[Mocha Documentation](https://mochajs.org/)

#### How to Start with Mocha Testing
 * Place your test file in the test/ folder
 * Run npm test
 * See the output

*Note that the file must be called test because that is what Mocha looks for

#### Example for GetMainWorkplan:

``` 
 
var globals = require('./testglobals');
var find = globals.find;
var expect = require("chai").expect;
find.OpenProject('model.stpnc');
describe("Test A GetMainWorkplan", function(){
	describe("Correct Return Value", function(){
		it("returns main workplan id", function() {
			var id = find.GetMainWorkplan();

			expect(id).to.equal(94989);
		});
	});
});
```

**testglobals module** is required in the first line due to the inability to open multiple finder objects from the StepNode Library so all: Finder, AptStepMaker, Tolerance, and any other objects that will be used across multiple tests should go here.

> var expect = require("chai").expect;

This line is needed at the top of the file in order to use chai style expect statements, but Mocha can use any assertion library out there (e.g. chai, must, should).

> describe(string message, func cb)

This function is used to describe your tests with the message field specified above.

> it(string message, func cb)

This function is used to describe what the test does using the message field specified above.

The semantics within the *it* block will be ran for the test and any exceptions or assertion fails that are thrown
within that block will cause the test case to fail.