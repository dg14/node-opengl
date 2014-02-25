var nodejs = true,
    opengl = require('node-opengl'),
    glfw = require('node-glfw'),
    Image = opengl.Image,
    app=opengl.createApp();

function initGL(canvas) {
    try {
        gl = canvas.getContext("experimental-webgl");
        gl.viewportWidth = canvas.width;
        gl.viewportHeight = canvas.height;        
    } catch (e) {}
    if (!gl) {
        alert("Could not initialise WebGL, sorry :-(");
    }
}
requestAnimationFrame = app.requestAnimationFrame;

exports.main = function() {
    var canvas = app.createElement("lesson02-canvas");
    initGL(canvas);
    if (this.onInitScene) this.onInitScene();
    if (this.onResize) this.onResize();
    var state=[];
    if (this.onDrawScene) this.onDrawScene();
}

