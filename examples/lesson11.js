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
    image.src = "Data/lesson11/tim.bmp";
    return texture;
}
var points = [];
skel.onInitScene = function() {
    // init.    
    loadTextures();
    gl.enable(gl.TEXTURE_2D);
    gl.clearColor(0.0, 0.0, 1.0, 0);
    gl.clearDepth(1.0);
    gl.depthFunc(gl.LESS);
    gl.enable(gl.DEPTH_TEST);
    gl.shadeModel(gl.SMOOTH);
    gl.matrixMode(gl.PROJECTION);
    gl.loadIdentity();
    glu.perspective(45, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0);
    gl.matrixMode(gl.MODELVIEW);
    for (float_x = 0.0; float_x < 9.0; float_x += 0.2) {
        var x_rounded=Math.round(float_x * 5);
        points[x_rounded]=[];
        for (float_y = 0.0; float_y < 9.0; float_y += 0.2) {
            var y_rounded=Math.round(float_y * 5);
            points[x_rounded][y_rounded]=[];
            points[x_rounded][y_rounded][0] = float_x - 4.4;
            points[x_rounded][y_rounded][1] = float_y - 4.4;
            points[x_rounded][y_rounded][2] = Math.sin(((float_x * 5 * 8) / 360) * 3.14159 * 2);
        }
    }
}
var xrot=0,yrot=0,zrot=0, wiggle_count=0;
skel.onDrawScene = function() {
    var x, y;
    var float_x, float_y, float_xb, float_yb;
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer    
    gl.loadIdentity();
    gl.translatef(0.0, 0.0, -12.0);
    gl.bindTexture(gl.TEXTURE_2D, texture[0]);
    gl.polygonMode(gl.BACK, gl.FILL);
    gl.polygonMode(gl.FRONT, gl.LINE);
    gl.begin(gl.QUADS);
    for (x = 0; x < 44; x++) {
        for (y = 0; y < 44; y++) {
            float_x = x / 44;
            float_y = y / 44;
            float_xb = (x + 1) / 44;
            float_yb = (y + 1) / 44;
            gl.texCoord2f(float_x, float_y);
            gl.vertex3f(points[x][y][0], points[x][y][1], points[x][y][2]);
            gl.texCoord2f(float_x, float_yb);
            gl.vertex3f(points[x][y + 1][0], points[x][y + 1][1], points[x][y + 1][2]);
            gl.texCoord2f(float_xb, float_yb);
            gl.vertex3f(points[x + 1][y + 1][0], points[x + 1][y + 1][1], points[x + 1][y + 1][2]);
            gl.texCoord2f(float_xb, float_y);
            gl.vertex3f(points[x + 1][y][0], points[x + 1][y][1], points[x + 1][y][2]);
        }
    }
    gl.end();
    if (wiggle_count == 2) { // cycle the sine values
        for (y = 0; y < 45; y++) {
            points[44][y][2] = points[0][y][2];
        }
        for (x = 0; x < 44; x++) {
            for (y = 0; y < 45; y++) {
                points[x][y][2] = points[x + 1][y][2];
            }
        }
        wiggle_count = 0;
    }
    wiggle_count++;
    xrot += 0.3;
    yrot += 0.2;
    zrot += 0.4;
    requestAnimationFrame(skel.onDrawScene);
}
// testing events
glfw.events.on('keydown', function(evt) {
    switch (evt.which) {
        case "B".charCodeAt(0): //a            
            blend = blend ? 0 : 1; // switch the current value of blend, between 0 and 1.
            if (blend) {
                gl.enable(gl.BLEND);
                gl.disable(gl.DEPTH_TEST);
            } else {
                gl.disable(gl.BLEND);
                gl.enable(gl.DEPTH_TEST);
            }
            break;
        case "F".charCodeAt(0): // f
            filter++; // switch the current value of filter, between 0/1/2;
            if (filter > 2) {
                filter = 0;
            }
            break;
        case "L".charCodeAt(0): //z            
            light = light ? 0 : 1; // switch the current value of light, between 0 and 1.
            if (light) {
                gl.enable(gl.LIGHTING);
            } else {
                gl.disable(gl.LIGHTING);
            }
            break;
        case "T".charCodeAt(0): // t
            //if (twinkle==0) twinkle=1; else twinkle=0;
            // deactivated. bug in code???
            break;
        case "F".charCodeAt(0): // c
            filter++;
            if (filter == 3) filter = 0;
            break;
        case glfw.KEY_UP: // up.
            xpos -= Math.sin(yrot * piover180) * 0.05;
            zpos -= Math.cos(yrot * piover180) * 0.05;
            if (walkbiasangle >= 359.0) walkbiasangle = 0.0;
            else walkbiasangle += 10;
            walkbias = Math.sin(walkbiasangle * piover180) / 20.0;
            break;
        case glfw.KEY_DOWN: // down 
            xpos += Math.sin(yrot * piover180) * 0.05;
            zpos += Math.cos(yrot * piover180) * 0.05;
            if (walkbiasangle <= 1.0) walkbiasangle = 359.0;
            else walkbiasangle -= 10;
            walkbias = Math.sin(walkbiasangle * piover180) / 20.0;
            break;
        case glfw.KEY_LEFT: // left
            yrot += 1.5;
            break;
        case glfw.KEY_RIGHT: // right
            yrot -= 1.5;
            break;
        case glfw.KEY_PAGEUP: // pageup
            z -= 0.2;
            lookupdown -= 0.2;
            break;
        case glfw.KEY_PAGEDOWN: // pageup
            z += 0.2;
            lookupdown += 1.0;
            break;
        case glfw.KEY_SPACE:
            console.log({
                z: z,
                yrot: yrot,
                xpos: xpos,
                ypos: ypos,
                lookupdown: lookupdown,
                filter: filter,
                light: light,
                blend: blend
            })
            break;
        default:
            console.log(evt);
            break;
    }
    //console.log('[zoom:' + zoom + ', twinkle:'+twinkle+']');
});
skel.main();