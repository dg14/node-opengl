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
Math.rand = function(min, max) {
    var diff = max - min;
    return Math.round(min + Math.random() * (max - min));
}
var texture = [];
var image = [];
loadTexture = function(idx, file) {
    image[idx] = new Image();
    image[idx].idx = idx;
    image[idx].onload = function() {
        texture[this.idx] = gl.createTexture();
        gl.bindTexture(gl.TEXTURE_2D, texture[this.idx]);
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, image[idx].width, image[idx].height, 0, gl.RGBA, gl.UNSIGNED_BYTE, image[idx]);
        gl.generateMipmap(gl.TEXTURE_2D);
    }
    image[idx].src = file;
}
loadTextures = function() {
    loadTexture(0, "Data/lesson20/logo.bmp");
    loadTexture(1, "Data/lesson20/image1.bmp")
    loadTexture(2, "Data/lesson20/mask1.bmp");
    loadTexture(3, "Data/lesson20/image2.bmp");
    loadTexture(4, "Data/lesson20/mask2.bmp");
}
skel.onInitScene = function() {
    // init.    
    loadTextures();
    gl.clearColor(0.0, 0.0, 0.0, 0.0); // Clear The Background Color To Black
    gl.clearDepth(1.0); // Enables Clearing Of The Depth Buffer
    gl.enable(gl.DEPTH_TEST); // Enable Depth Testing
    gl.shadeModel(gl.SMOOTH); // Enables Smooth Color Shading
    gl.enable(gl.TEXTURE_2D); // Enable 2D Texture Mapping
}
var masking = true; // Masking On/Off
var scene = true; // Which Scene To Draw
var loop = 0; // Generic Loop Variable
var roll = 0.0; // Rolling Texture
skel.onDrawScene = function() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer    
    gl.loadIdentity(); // Reset The Modelview Matrix
    gl.translatef(0.0, 0.0, -2.0); // Move Into The Screen 5 Units
    gl.bindTexture(gl.TEXTURE_2D, texture[0]); // Select Our Logo Texture
    gl.begin(gl.QUADS); // Start Drawing A Textured Quad
    gl.texCoord2f(0.0, -roll + 0.0);
    gl.vertex3f(-1.1, -1.1, 0.0); // Bottom Left
    gl.texCoord2f(3.0, -roll + 0.0);
    gl.vertex3f(1.1, -1.1, 0.0); // Bottom Right
    gl.texCoord2f(3.0, -roll + 3.0);
    gl.vertex3f(1.1, 1.1, 0.0); // Top Right
    gl.texCoord2f(0.0, -roll + 3.0);
    gl.vertex3f(-1.1, 1.1, 0.0); // Top Left
    gl.end(); // Done Drawing The Quad
    gl.enable(gl.BLEND); // Enable Blending
    gl.disable(gl.DEPTH_TEST); // Disable Depth Testing
    if (masking) // Is Masking Enabled?
    {
        gl.blendFunc(gl.DST_COLOR, gl.ZERO); // Blend Screen Color With Zero (Black)
    }
    if (scene) // Are We Drawing The Second Scene?
    {
        gl.translatef(0.0, 0.0, -1.0); // Translate Into The Screen One Unit
        gl.rotatef(roll * 360, 0.0, 0.0, 1.0); // Rotate On The Z Axis 360 Degrees.
        if (masking) // Is Masking On?
        {
            gl.bindTexture(gl.TEXTURE_2D, texture[3]); // Select The Second Mask Texture
            gl.begin(gl.QUADS); // Start Drawing A Textured Quad
            gl.texCoord2f(0.0, 0.0);
            gl.vertex3f(-1.1, -1.1, 0.0); // Bottom Left
            gl.texCoord2f(1.0, 0.0);
            gl.vertex3f(1.1, -1.1, 0.0); // Bottom Right
            gl.texCoord2f(1.0, 1.0);
            gl.vertex3f(1.1, 1.1, 0.0); // Top Right
            gl.texCoord2f(0.0, 1.0);
            gl.vertex3f(-1.1, 1.1, 0.0); // Top Left
            gl.end(); // Done Drawing The Quad
        }
        gl.blendFunc(gl.ONE, gl.ONE); // Copy Image 2 Color To The Screen
        gl.bindTexture(gl.TEXTURE_2D, texture[4]); // Select The Second Image Texture
        gl.begin(gl.QUADS); // Start Drawing A Textured Quad
        gl.texCoord2f(0.0, 0.0);
        gl.vertex3f(-1.1, -1.1, 0.0); // Bottom Left
        gl.texCoord2f(1.0, 0.0);
        gl.vertex3f(1.1, -1.1, 0.0); // Bottom Right
        gl.texCoord2f(1.0, 1.0);
        gl.vertex3f(1.1, 1.1, 0.0); // Top Right
        gl.texCoord2f(0.0, 1.0);
        gl.vertex3f(-1.1, 1.1, 0.0); // Top Left
        gl.end(); // Done Drawing The Quad
    } else // Otherwise
    {
        if (masking) // Is Masking On?
        {
            gl.bindTexture(gl.TEXTURE_2D, texture[1]); // Select The First Mask Texture
            gl.begin(gl.QUADS); // Start Drawing A Textured Quad
            gl.texCoord2f(roll + 0.0, 0.0);
            gl.vertex3f(-1.1, -1.1, 0.0); // Bottom Left
            gl.texCoord2f(roll + 4.0, 0.0);
            gl.vertex3f(1.1, -1.1, 0.0); // Bottom Right
            gl.texCoord2f(roll + 4.0, 4.0);
            gl.vertex3f(1.1, 1.1, 0.0); // Top Right
            gl.texCoord2f(roll + 0.0, 4.0);
            gl.vertex3f(-1.1, 1.1, 0.0); // Top Left
            gl.end(); // Done Drawing The Quad
        }
        gl.blendFunc(gl.ONE, gl.ONE); // Copy Image 1 Color To The Screen
        gl.bindTexture(gl.TEXTURE_2D, texture[2]); // Select The First Image Texture
        gl.begin(gl.QUADS); // Start Drawing A Textured Quad
        gl.texCoord2f(roll + 0.0, 0.0);
        gl.vertex3f(-1.1, -1.1, 0.0); // Bottom Left
        gl.texCoord2f(roll + 4.0, 0.0);
        gl.vertex3f(1.1, -1.1, 0.0); // Bottom Right
        gl.texCoord2f(roll + 4.0, 4.0);
        gl.vertex3f(1.1, 1.1, 0.0); // Top Right
        gl.texCoord2f(roll + 0.0, 4.0);
        gl.vertex3f(-1.1, 1.1, 0.0); // Top Left
        gl.end(); // Done Drawing The Quad
    }
    gl.enable(gl.DEPTH_TEST); // Enable Depth Testing
    gl.disable(gl.BLEND); // Disable Blending
    roll += 0.002; // Increase Our Texture Roll Variable
    if (roll > 1.0) // Is Roll Greater Than One
    {
        roll -= 1.0; // Subtract 1 From Roll
    }
    requestAnimationFrame(skel.onDrawScene);
}
// testing events
glfw.events.on('keydown', function(evt) {
    switch (evt.which) {
        case glfw.KEY_SPACE:
            scene = !scene;
            break;
        case "M".charCodeAt(0): // c
            masking = !masking;
            break;
    }
});
skel.main();