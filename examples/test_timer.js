// test_timer.js
var Timer = require('node-opengl').Timer;
var start = 0;
var t = new Timer(function(timer) {    
    start++;
    if (start > 5) timer.end();
    console.log("counter:"+start);
});

t.start();