var skel = require('node-opengl').skel;
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
        gl.generateMipmap(gl.TEXTURE_2D);
        // mipmap.
        texture[2] = gl.createTexture();
        gl.bindTexture(gl.TEXTURE_2D, texture[2]);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR_MIPMAP_NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_NEAREST);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, image.width, image.height, 0, gl.RGBA, gl.UNSIGNED_BYTE, image);
        gl.generateMipmap(gl.TEXTURE_2D);
    }
    image.src = "Data/lesson8/glass.bmp";
    return texture;
}
var lightAmbient = [0.5, 0.5, 0.5, 1.0];
var lightDiffuse = [1.0, 1.0, 1.0, 1.0];
var lightPosition = [0.0, 0.0, 2.0, 1.0];
skel.onInitScene = function() {
    // init.
    loadTextures();
    gl.enable(gl.TEXTURE_2D);
    gl.shadeModel(gl.SMOOTH);
    gl.clearColor(0.0, 0.0, 0.0, 0.5);
    gl.clearDepth(1.0);
    gl.enable(gl.DEPTH_TEST);    
    gl.depthFunc(gl.LESS);
    gl.shadeModel(gl.SMOOTH);
    gl.hint(gl.PERSPECTIVE_CORRECTION_HINT, gl.NICEST);
    gl.lightfv(gl.LIGHT1, gl.AMBIENT, lightAmbient);
    gl.lightfv(gl.LIGHT2, gl.DIFFUSE, lightDiffuse);
    gl.lightfv(gl.LIGHT3, gl.POSITION, lightPosition);
    gl.blendFunc(gl.SRC_ALPHA,gl.ONE);
    gl.color4f(1.0, 1.0, 1.0, 0.5);
}
var z = -5.5;
var xrot=0, yrot=0, xspeed=0.5, yspeed=0.5;
var filter = 0;
skel.onDrawScene = function() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
    gl.loadIdentity(); // Reset The View
    gl.translatef(0.0, 0.0, z);
    gl.rotatef(xrot, 1.0, 0.0, 0.0);
    gl.rotatef(yrot, 0.0, 1.0, 0.0);
    gl.bindTexture(gl.TEXTURE_2D, texture[filter]);
    gl.begin(gl.QUADS);
    // Front Face
    gl.normal3f(0.0, 0.0, 1.0);
    gl.texCoord2f(0.0, 0.0); gl.vertex3f(-1.0, -1.0, 1.0);
    gl.texCoord2f(1.0, 0.0); gl.vertex3f(1.0, -1.0, 1.0);
    gl.texCoord2f(1.0, 1.0); gl.vertex3f(1.0, 1.0, 1.0);
    gl.texCoord2f(0.0, 1.0); gl.vertex3f(-1.0, 1.0, 1.0);
    // Back Face
    gl.normal3f(0.0, 0.0, -1.0);
    gl.texCoord2f(1.0, 0.0); gl.vertex3f(-1.0, -1.0, -1.0);
    gl.texCoord2f(1.0, 1.0); gl.vertex3f(-1.0, 1.0, -1.0);
    gl.texCoord2f(0.0, 1.0); gl.vertex3f(1.0, 1.0, -1.0);
    gl.texCoord2f(0.0, 0.0); gl.vertex3f(1.0, -1.0, -1.0);
    // Top Face
    gl.normal3f(0.0, 1.0, 0.0);
    gl.texCoord2f(0.0, 1.0); gl.vertex3f(-1.0, 1.0, -1.0);
    gl.texCoord2f(0.0, 0.0); gl.vertex3f(-1.0, 1.0, 1.0);
    gl.texCoord2f(1.0, 0.0); gl.vertex3f(1.0, 1.0, 1.0);
    gl.texCoord2f(1.0, 1.0); gl.vertex3f(1.0, 1.0, -1.0);
    // Bottom Face
    gl.normal3f(0.0, -1.0, 0.0);
    gl.texCoord2f(1.0, 1.0); gl.vertex3f(-1.0, -1.0, -1.0);
    gl.texCoord2f(0.0, 1.0); gl.vertex3f(1.0, -1.0, -1.0);
    gl.texCoord2f(0.0, 0.0); gl.vertex3f(1.0, -1.0, 1.0);
    gl.texCoord2f(1.0, 0.0); gl.vertex3f(-1.0, -1.0, 1.0);
    // Right face
    gl.normal3f(1.0, 0.0, 0.0);
    gl.texCoord2f(1.0, 0.0); gl.vertex3f(1.0, -1.0, -1.0);
    gl.texCoord2f(1.0, 1.0); gl.vertex3f(1.0, 1.0, -1.0);
    gl.texCoord2f(0.0, 1.0); gl.vertex3f(1.0, 1.0, 1.0);
    gl.texCoord2f(0.0, 0.0); gl.vertex3f(1.0, -1.0, 1.0);
    // Left Face
    gl.normal3f(-1.0, 0.0, 0.0);
    gl.texCoord2f(0.0, 0.0); gl.vertex3f(-1.0, -1.0, -1.0);
    gl.texCoord2f(1.0, 0.0); gl.vertex3f(-1.0, -1.0, 1.0);
    gl.texCoord2f(1.0, 1.0); gl.vertex3f(-1.0, 1.0, 1.0);
    gl.texCoord2f(0.0, 1.0); gl.vertex3f(-1.0, 1.0, -1.0);
    gl.end();
    xrot+=xspeed;
    yrot+=yspeed;
    requestAnimationFrame(skel.onDrawScene);
}
// testing events
var light=true;
var blending=true;
glfw.events.on('keydown', function(evt) {
    switch (evt.which) {
        case "A".charCodeAt(0): //a            
            z += 1.0;            
            break;
        case "Z".charCodeAt(0): //z            
            z -= 1.0;
            break;
        case "S".charCodeAt(0): //s 
            xspeed += 0.01;
            break;
        case "X".charCodeAt(0): //x
            xspeed -= 0.01;
            break;
        case "D".charCodeAt(0): // d
            yspeed += 0.01;
            break;
        case "C".charCodeAt(0): // c
            yspeed -= 0.01;
            break;
        case "F".charCodeAt(0): // c
            filter++; if (filter==3) filter=0;
            break;
        case "B".charCodeAt(0): // c
            if (blending) {
                gl.disable(gl.BLEND);
                gl.enable(gl.DEPTH_TEST);
                blending=false;
            } else {
                gl.enable(gl.BLEND);
                gl.disable(gl.DEPTH_TEST);
                blending=true;

            }
            break;
        case " ".charCodeAt(0): // 
            if (light) {
                light=false;
                gl.disable(gl.LIGHTING);
            } else {
                light=true;
                gl.enable(gl.LIGHTING);
            }            
            break;
    }
    console.log('[z:' + z + ', xspeed:' + xspeed + ', yspeed:' + yspeed + ', filter:'+filter+']');
});

skel.main();