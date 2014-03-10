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
var texture = [];
loadTextures = function() {
    image = new Image();
    image.onload = function() {
        console.log("Loaded");
        texture[0] = gl.createTexture();
        // create nearest filtered texture
        gl.bindTexture(gl.TEXTURE_2D, texture[0]);
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, image.width, image.height, 0, gl.RGBA, gl.UNSIGNED_BYTE, image);
        // linear filtered
        texture[1] = gl.createTexture();
        gl.bindTexture(gl.TEXTURE_2D, texture[1]);
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, image.width, image.height, 0, gl.RGBA, gl.UNSIGNED_BYTE, image);
        // mipmap.
        texture[2] = gl.createTexture();
        gl.bindTexture(gl.TEXTURE_2D, texture[2]);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_NEAREST);
        glu.build2DMipmaps(gl.TEXTURE_2D, 3, image.width, image.height, gl.RGB, gl.UNSIGNED_BYTE, image);
    }
    image.src = "Data/lesson16/crate.bmp";
    return texture;
}
var fXRotation = 0;
var fYRotation = 0;
var fXSpeed = 0;
var fYSpeed = 0;
var z = -5.0;
var lightAmbient = [0.5, 0.5, 0.5, 1.0];
var lightDiffuse = [1.0, 1.0, 1.0, 1.0];
var lightPosition = [0.0, 0.0, 2.0, 1.0];
var filter = 0; // Which Filter To Use
var light = true; // Light switch
var fogMode = [gl.EXP, gl.EXP2, gl.LINEAR]; // Storage For Three Types Of Fog
var fogfilter = 0; // Which Fog Mode To Use
var fogColor = [0.5, 0.5, 0.5, 1.0]; // Fog Color
skel.onInitScene = function() {
    // init.    
    loadTextures();
    gl.enable(gl.TEXTURE_2D);
    gl.shadeModel(gl.SMOOTH);
    gl.clearColor(0.5, 0.5, 0.5, 1.0);
    gl.clearDepth(1.0);
    gl.enable(gl.DEPTH_TEST);
    gl.depthFunc(gl.LEQUAL);
    gl.hint(gl.PERSPECTIVE_CORRECTION_HINT, gl.NICEST);
    gl.lightfv(gl.LIGHT1, gl.AMBIENT, lightAmbient);
    gl.lightfv(gl.LIGHT1, gl.DIFFUSE, lightDiffuse);
    gl.lightfv(gl.LIGHT1, gl.POSITION, lightPosition);
    gl.enable(gl.LIGHT1);
    //gl.fogi(gl.FOG_MODE, fogMode[fogfilter]);
    gl.fogfv(gl.FOG_COLOR, fogColor);
    //gl.fogfv(10,[0.1,1.2]);
    //gl.fogiv(10,[1,2]);
    gl.fogf(gl.FOG_DENSITY, 0.35);
    gl.fogf(gl.FOG_START, 1.0);
    gl.fogf(gl.FOG_END, 5.0);
    gl.enable(gl.FOG);
    //gl.enable(gl.COLOR_MATERIAL);
}
skel.onDrawScene = function() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer    
    gl.loadIdentity();
    gl.translatef(0.0, 0.0, z);
    gl.rotatef(fXRotation, 1.0, 0.0, 0.0);
    gl.rotatef(fYRotation, 0.0, 1.0, 0.0);
    gl.bindTexture(gl.TEXTURE_2D, texture[filter]);
    gl.begin(gl.QUADS);
    // Front Face
    gl.normal3f(0.0, 0.0, 1.0);
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(-1.0, -1.0, 1.0);
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(1.0, -1.0, 1.0);
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(1.0, 1.0, 1.0);
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(-1.0, 1.0, 1.0);
    // Back Face
    gl.normal3f(0.0, 0.0, -1.0);
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(-1.0, -1.0, -1.0);
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(-1.0, 1.0, -1.0);
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(1.0, 1.0, -1.0);
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(1.0, -1.0, -1.0);
    // Top Face
    gl.normal3f(0.0, 1.0, 0.0);
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(-1.0, 1.0, -1.0);
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(-1.0, 1.0, 1.0);
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(1.0, 1.0, 1.0);
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(1.0, 1.0, -1.0);
    // Bottom Face
    gl.normal3f(0.0, -1.0, 0.0);
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(-1.0, -1.0, -1.0);
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(1.0, -1.0, -1.0);
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(1.0, -1.0, 1.0);
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(-1.0, -1.0, 1.0);
    // Right face
    gl.normal3f(1.0, 0.0, 0.0);
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(1.0, -1.0, -1.0);
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(1.0, 1.0, -1.0);
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(1.0, 1.0, 1.0);
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(1.0, -1.0, 1.0);
    // Left Face
    gl.normal3f(-1.0, 0.0, 0.0);
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(-1.0, -1.0, -1.0);
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(-1.0, -1.0, 1.0);
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(-1.0, 1.0, 1.0);
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(-1.0, 1.0, -1.0);
    gl.end();
    fXRotation += fXSpeed;
    fYRotation += fYSpeed;
    requestAnimationFrame(skel.onDrawScene);
}
// testing events
glfw.events.on('keydown', function(evt) {
    switch (evt.which) {
        case "L".charCodeAt(0):
            light = !light;
            if (light) {
                gl.disable(gl.LIGHTING);
                console.log("lighting disabled");
            } else {
                gl.enable(gl.LIGHTING);
                console.log("lighting enabled");
            }
            break;
        case "F".charCodeAt(0):
            filter++; // switch the current value of filter, between 0/1/2;
            if (filter > 2) {
                filter = 0;
            }
            break;
        case "G".charCodeAt(0):
            fogfilter += 1;
            if (fogfilter > 2) {
                fogfilter = 0;
            }
            gl.fogi(gl.FOG_MODE, fogMode[fogfilter]);
            console.log("fogfilter:"+fogfilter);
            break;
        case glfw.KEY_PAGEUP:
            z -= 0.02;
            break;
        case glfw.KEY_PAGEDOWN:
            z += 0.02;
            break;
        case glfw.KEY_UP:
            fXSpeed -= 0.01;
            break;
        case glfw.KEY_DOWN:
            fXSpeed += 0.01;
            break;
        case glfw.KEY_LEFT:
            fYSpeed -= 0.01;
            break;
        case glfw.KEY_RIGHT:
            fYSpeed += 0.01;
            break;
        default:
            console.log(evt);
            break;
    }
    //console.log('[zoom:' + zoom + ', twinkle:'+twinkle+']');
});
skel.main();