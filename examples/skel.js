var nodejs = true,
    opengl = require('node-opengl'),
    Image = new require('node-opengl').Image,
    glfw = require('node-glfw');
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
    glfw.Enable(glfw.KEY_REPEAT);    
    if (this.onInitScene) this.onInitScene();
    if (this.onResize) this.onResize();
    var state=[];
    if (this.onDrawScene) this.onDrawScene();
}

var textures=[];
var images=[];

exports.loadTexture = function (key, file) {    
    var util=require('util');
        texture = gl.createTexture();

    image=new Image();
    image.onload=function() {        

        gl.bindTexture(gl.TEXTURE_2D, texture);
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
        //gl.texImage2D(gl.TEXTURE_2D, 0,  gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, image.width, image.height, 0, gl.RGBA, gl.UNSIGNED_BYTE, image);    
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        //gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
        //gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_NEAREST);        
        gl.generateMipmap(gl.TEXTURE_2D);
        gl.bindTexture(gl.TEXTURE_2D, null);
        textures[key]=texture;
        images[key]=image;
    }
    image.src=file;
    return texture;    
}

