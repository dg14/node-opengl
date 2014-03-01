var skel = require('./skel.js');
var i = 0;
var glu = require('node-glu');
var gl = require('node-opengl');
var glfw = require('node-glfw');
var util = require('util');
var Image = new require('node-opengl').Image;

skel.onResize = function() {
    // resize.
    gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
    gl.matrixMode(gl.PROJECTION);
    gl.loadIdentity();
    glu.perspective(45, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0);
    gl.matrixMode(gl.MODELVIEW);
    gl.loadIdentity();
}
var texture = [];
loadTextures = function() {
    image = new Image();
    image.onload = function() {
        console.log("Loaded");
        texture[0] = gl.createTexture();
        // create nearest filtered texture
        gl.bindTexture(gl.TEXTURE_2D, texture[0]);
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, image.width, image.height, 0, gl.RGBA, gl.UNSIGNED_BYTE, image);
    }
    image.src = "Data/lesson9/Star.bmp";
    return texture;
}

var ESCAPE=27, PAGE_UP=73, PAGE_DOWN=81, UP_ARROW=72, DOWN_ARROW=80, LEFT_ARROW=75, RIGHT_ARROW=77;
var star=[];
var STAR_NUM=50;

var zoom = -15.0;   // viewing distance from stars.
var tilt = 90.0;    // tilt the view
var spin=0.0;            // spin twinkling stars

skel.onInitScene = function() {
    // init.
    loadTextures();
    gl.enable(gl.TEXTURE_2D);    
    gl.clearColor(0.0, 0.0, 0.0, 0.5);
    gl.clearDepth(1.0);
    gl.shadeModel(gl.SMOOTH);
    gl.matrixMode(gl.PROJECTION);
    gl.loadIdentity();
    glu.perspective(45, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0);
    gl.matrixMode(gl.MODELVIEW);
    gl.blendFunc(gl.SRC_ALPHA,gl.ONE);
    gl.enable(gl.BLEND);
    for (loop=0;loop<50;loop++) {
        star[loop]= {
            angle: 0.0,
            dist: loop*1.0/STAR_NUM*5.0,
            r: Math.round(Math.random()*256),
            g: Math.round(Math.random()*256),            
            b: Math.round(Math.random()*256)
        };
    }

}
var z = -5.5;
var xrot=0, yrot=0, xspeed=0.5, yspeed=0.5;
var filter = 0;
var twinkle = 0;
skel.onDrawScene = function() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
    gl.bindTexture(gl.TEXTURE_2D, texture[0]);
    for (var loop=0;loop<STAR_NUM;loop++) {
        gl.loadIdentity();
        gl.translatef(0.0, 0.0,zoom);
        gl.rotatef(tilt, 1.0, 0.0, 0.0);
        gl.rotatef(star[loop].angle,0.0, 1.0,0.0);
        gl.translatef(star[loop].dist, 0.0, 0.0);
        gl.rotatef(-star[loop].dist,0.0,1.0,0.0);
        gl.rotatef(-tilt, 1.0,0.0,0.0);

        if (twinkle) {
            console.log(STAR_NUM-loop);
            console.log(loop);
            console.log(STAR_NUM);
            gl.color4ub(star[STAR_NUM-loop-1].r, star[STAR_NUM-loop-1].g, star[STAR_NUM-loop-1].b, 255);
            gl.begin(gl.QUADS);
            gl.texCoords2f(0.0,0.0); gl.vertex3f(-1.0, -1.0,0.0);
            gl.texCoords2f(1.0,0.0); gl.vertex3f( 1.0, -1.0,0.0);
            gl.texCoords2f(1.0,1.0); gl.vertex3f( 1.0,  1.0,0.0);
            gl.texCoords2f(0.0,1.0); gl.vertex3f(-1.0,  1.0,0.0);
            gl.end();

        }
        gl.rotatef(spin, 0.0, 0.0, 1.0);
        gl.color4ub(star[loop].r, star[loop].g, star[loop].b,255);
        gl.begin(gl.QUADS);          // Begin Drawing The Textured Quad
        gl.texCoord2f(0.0, 0.0); gl.vertex3f(-1.0,-1.0, 0.0);
        gl.texCoord2f(1.0, 0.0); gl.vertex3f( 1.0,-1.0, 0.0);
        gl.texCoord2f(1.0, 1.0); gl.vertex3f( 1.0, 1.0, 0.0);
        gl.texCoord2f(0.0, 1.0); gl.vertex3f(-1.0, 1.0, 0.0);
        gl.end();                // Done Drawing The Textured Quad

        spin +=0.01;                           // used to spin the stars.
        star[loop].angle += loop * 1.0 / STAR_NUM * 1.0;    // change star angle.
        star[loop].dist  -= 0.01;              // bring back to center.

        if (star[loop].dist<0.0) {             // star hit the center
            star[loop].dist += 5.0;            // move 5 units from the center.
            star[loop].r = Math.round(Math.random() *256);        // new red color.
            star[loop].g = Math.round(Math.random() * 256);        // new green color.
            star[loop].b = Math.round(Math.random() * 256);        // new blue color.
        }

    }
    requestAnimationFrame(skel.onDrawScene);
}
// testing events
glfw.events.on('keydown', function(evt) {
    switch (evt.which) {
        case "A".charCodeAt(0): //a            
            zoom += 1.0;            
            break;
        case "Z".charCodeAt(0): //z            
            zoom -= 1.0;
            break;
        case "T".charCodeAt(0): // t
            //if (twinkle==0) twinkle=1; else twinkle=0;
            // deactivated. bug in code???
            break;
        case "F".charCodeAt(0): // c
            filter++; if (filter==3) filter=0;
            break;
    }
    console.log('[zoom:' + zoom + ', twinkle:'+twinkle+']');
});

skel.main();