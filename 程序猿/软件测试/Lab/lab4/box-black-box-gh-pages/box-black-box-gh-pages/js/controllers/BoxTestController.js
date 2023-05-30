(function () {
    angular.module("BoxBlackBox").controller("BoxTestController",["algorithmService", "focus", "$timeout", BoxTestController]);

    function TestCase(number, box1, box2) {
        this.number =number;
        this.box1 = box1;
        this.box2 = box2;
        this.results = [];
        this.expected = true;
        this.resultsInvalid = false;
        var self = this;

        this.isValid = function() {
            return box1.isValid() && box2.isValid();
        }

        this.backup = function() {
            box1.backup();
            box2.backup();
        }

        this.revert = function() {
            box1.revert();
            box2.revert();
            this.resultsInvalid = false;
        }

        this.clone = function(number) {
            var testCase = new TestCase(number, self.box1.clone(), self.box2.clone());
            testCase.notes = self.notes;
            testCase.expected = self.expected;
            console.log(testCase);
            return testCase;
        }
    }

    function Box(x, y, width, height) {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
        var self = this;
        
        this.isValid = function() {
            return isInt(self.x) && 
                isInt(self.y) &&
                isInt(self.width) &&
                isInt(self.height);
        }

        function isInt(i) {
            return i === parseInt(i, 10);
        }

        this.clone = function() {
            return new Box(self.x, self.y, self.width, self.height);
        }

        this.backup = function() {
            self.back = self.clone();
        }

        this.revert = function() {
            if(this.back !== undefined){
                self.x = self.back.x;
                self.y = self.back.y;
                self.width = self.back.width;
                self.history = self.back.history;
            }
        }
    }

    function BoxTestController(algorithmService, focus, $timeout) {
        var vm = this;
        vm.testCases = [];
        vm.algorithms = algorithmService.getAlgorithms();
        vm.scrolling = isOverflowed();
        vm.number = 0;
        vm.sorting = true;

        vm.runTests = function() {
            vm.testCases.forEach(runTestSuit);
        }

        vm.delete = function(test) {
            console.log("before", vm.testCases);
            vm.testCases.splice(vm.testCases.indexOf(test), 1);
            console.log("after", vm.testCases);
            console.log("vm ", vm);
            
            vm.scrolling = isOverflowed();
        }

        vm.clone = function(test) {
            vm.testCases.splice(vm.testCases.indexOf(test) + 1, 0, test.clone(vm.number));
            focus("xcoord" +(vm.number));
            vm.number ++;
        }

        vm.testChanged = function(test){
            if(test.results.length > 0 && !test.resultsInvalid) {
                test.resultsInvalid = true;
            }
        }

        vm.swap = function(test) {
            var tBox = test.box1;
            test.box1 = test.box2;
            test.box2 = tBox;
            test.resultsInvalid = true;
        }

        vm.revert = function(test) {
            test.revert();
        }

        vm.plusTest = newTest;
        vm.runTest = runTestSuit;

        vm.sortableOptions = {
            handle: '> .myHandle',
            placeholder: "app"
        };

        function runTestSuit(testCase) {
            testCase.results = [];
            testCase.errors = "";
            testCase.backup();

            if(testCase.isValid()){
                testCase.resultsInvalid = false;
                vm.algorithms.forEach(function(algorithm) {
                    var out = algorithm.run(testCase.box1, testCase.box2);
                    testCase.results.push({
                        "algorithm" : algorithm.name,
                        "algOutCome" : out,
                        "result" : out === testCase.expected

                    });
                })
            } else {
                testCase.errors = "Test case contains invalid values";
            }
        }

        function newTest() {
            var box1 = new Box(0, 0, 2, 2);
            var box2 = new Box(0, 0, 1, 1);
            var test = new TestCase(vm.number, box1, box2);
            test.notes = "square with smaller square in top right hand corner"
            vm.number++;
            vm.testCases.push(test);

            $timeout(function() {
                vm.scrolling = isOverflowed();    
            });
            
            focus("xcoord" +(vm.number - 1));
        }

        function secondTest() {
            var box1 = new Box(0, 0, 2, 2);
            var box2 = new Box(6, 6, 2, 2);
            var test = new TestCase(vm.number, box1, box2);
            test.notes = "square with equal square to far bottom left not overlapping"
            test.expected = false;
            vm.number++;
            vm.testCases.push(test);
        }

        function isOverflowed(){
            var element = document.getElementById("this-can-scroll");
            return element.scrollHeight > element.clientHeight || element.scrollWidth > element.clientWidth;
        }
        newTest();
        secondTest();
        /*var box1 = new Box(0,0,4,4)
        var box2 = new Box(1,1,4,4)
        vm.testCases.push(new TestCase(vm.number,box1,box2))
        vm.number++;

        box2 = new Box(0,0,4,4)
        box1 = new Box(1,1,4,4)
        vm.testCases.push(new TestCase(vm.number,box1,box2))
        vm.number++;

        box1 = new Box(2,0,2,4)
        box2 = new Box(1,1,4,2)
        vm.testCases.push(new TestCase(vm.number,box1,box2))
        vm.number++;

        box2 = new Box(2,0,2,4)
        box1 = new Box(1,1,4,2)
        vm.testCases.push(new TestCase(vm.number,box1,box2))
        vm.number++;

        box1 = new Box(0,0,2,2)
        box2 = new Box(1,3,2,2)
        var testCase = new TestCase(vm.number, box1,box2);
        vm.number++;
        testCase.expected = false;
        vm.testCases.push(testCase);

        box2 = new Box(0,0,2,2)
        box1 = new Box(3,1,2,2)
        testCase = new TestCase(vm.number, box1,box2);
        vm.number++;
        testCase.expected = false;
        vm.testCases.push(testCase);

        box1 = new Box(0,0,2,2)
        box2 = new Box(2,2,2,2)
        testCase = new TestCase(vm.number, box1,box2);
        vm.number++;
        testCase.expected = false;
        vm.testCases.push(testCase);

        box1 = new Box(2,2,2,2)
        box2 = new Box(2,2,2,2)
        testCase = new TestCase(vm.number, box1,box2);
        vm.number++;
        vm.testCases.push(testCase);

        box1 = new Box(2,2,2,2)
        box2 = new Box(1,1,3,3)
        testCase = new TestCase(vm.number, box1,box2);
        vm.number++;
        vm.testCases.push(testCase);

        box1 = new Box(0,0,2,2)
        box2 = new Box(0,2,2,2)
        testCase = new TestCase(vm.number, box1,box2);
        vm.number++;
        testCase.expected = false;
        vm.testCases.push(testCase);

        box1 = new Box(2,0,3,1)
        box2 = new Box(0,0,1,2)
        testCase = new TestCase(vm.number, box1,box2);
        vm.number++;
        testCase.expected = false;
        vm.testCases.push(testCase);*/
    }

})();
