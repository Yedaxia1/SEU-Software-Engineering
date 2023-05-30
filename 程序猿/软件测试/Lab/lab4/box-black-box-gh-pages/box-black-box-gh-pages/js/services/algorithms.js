(function() {
    angular.module("BoxBlackBox").factory("algorithmService", algorithmService);
    function algorithmService() {
        var service = {
            getAlgorithms : getAlgorithms
        };
        var algorithms = [];

        algorithms.push({"name": "a", "run" : a });
        algorithms.push({"name": "b", "run" : b });
        algorithms.push({"name": "c", "run" : c });
        algorithms.push({"name": "d", "run" : d });
        algorithms.push({"name": "e", "run" : e });
        algorithms.push({"name": "f", "run" : f });

        return service;

        ////////////////////////////////////////
        function getAlgorithms() {
            return algorithms;
        }

        function doBothWays(box1, box2, func){
            if(!func(box1, box2)) {
                return func(box2, box1);
            }else {
                return true;
            }
        }

        //fine for everything except the plus sign
        function a(box1, box2) {
            return doBothWays(box1, box2, function(box1, box2) {
                if(((box1.y >= box2.y && box1.x >= box2.x) &&
                    (box1.y < (box2.y + box2.height) && box1.x < (box2.x + box2.width) )) ||
                    ((box1.y >= box2.y && box1.x + box1.width <= box2.x + box2.width) &&
                    (box1.y < (box2.y + box2.height) && box1.x + box1.width > box2.x))) {

                    return true;
                }
                return false;
            });

        }

        //correct answer without reversing
        function b(box2, box1) {
            if(((box1.y >= box2.y && box1.x >= box2.x) &&
                (box1.y < (box2.y + box2.height) && box1.x < (box2.x + box2.width) )) ||
                ((box1.y >= box2.y && box1.x + box1.width <= box2.x + box1.width) &&
                (box1.y < (box2.y + box2.height) && box1.x + box1.width < box2.x)) ||
                ((box1.y < box2.y && box1.x > box2.x ) &&
                ((box1.y + box1.height) > (box2.y + box2.height) &&
                (box1.x + box1.width) < (box2.x + box2.width)))) {

                return true;
            }6
            return false;
        }

        //correct answer but also any touching [edge/vertex] is considered an overlap – incorrect according to spec
        function c(box1, box2) {
            if(box1.x <= (box2.x + box2.width) &&
                (box1.x + box1.width) >= box2.x  &&
                box1.y <= (box2.y + box2.height) &&
                (box1.y + box1.height) >= box2.y ){

                return true;
            }
            return false;
        }


        //any vertex inside the area of the opposite rectangle is an overlap, and nothing else is
        //only plus sign and identical rectangles fail
        function d(box1, box2) {
            return doBothWays(box1, box2, function(box1, box2) { 
                if((box1.x > box2.x && box1.x < (box2.x + box2.width)) ||
                    (box1.y > box2.y && box1.y < (box2.y + box2.height)) ||
                    ((box1.x + box1.width) > box2.x && (box1.x + box1.width) < (box2.x + box2.width)) ||
                    ((box1.y + box1.height) > box2.y && (box1.y + box1.height)< (box2.y + box2.height))) {
                    return true;
                }
                return false;

            });
        }

        //My Way
        function e(box1, box2) {
            if(box1.x < (box2.x + box2.width) &&
                (box1.x + box1.width) > box2.x  &&
                box1.y < (box2.y + box2.height) &&
                (box1.y + box1.height) > box2.y ){

                return true;
            }
            return false;
        }

        //The highway 
        function f(box1, box2) {
            return doBothWays(box1, box2, function(box1, box2) {
                if(((box1.y >= box2.y && box1.x >= box2.x) &&
                    (box1.y < (box2.y + box2.height) && box1.x < (box2.x + box2.width) )) ||
                    ((box1.y >= box2.y && box1.x + box1.width <= box2.x + box2.width) &&
                    (box1.y < (box2.y + box2.height) && box1.x + box1.width > box2.x)) ||
                    ((box1.y < box2.y && box1.x > box2.x ) &&
                    ((box1.y + box1.height) > (box2.y + box2.height) &&
                    (box1.x + box1.width) < (box2.x + box2.width)))) {

                    return true;
                }
                return false;
            })
        }

        }
})();
