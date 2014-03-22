#!/usr/bin/nodejs

var fs = require('fs');
fs.readFile('file.txt', function(err, data) {
    if (err) throw err;
    offset = 0;
    console.log("P3");
    console.log("#");
    console.log("#");
    console.log("32 32");
    console.log("255");
    for (i = 0; i < 32; i++) {
        line = "";
        for (j = 0; j < 32; j++) {
            for (k = 0; k < 3; k++) {                
                line += data[offset] + " ";
                offset++;
            }
        }
        console.log(line);
        //console.log(" ");
    }
});