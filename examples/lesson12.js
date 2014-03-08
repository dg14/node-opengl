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
        //gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_NEAREST);
        //gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, image.width, image.height, 0, gl.RGBA, gl.UNSIGNED_BYTE, image);        
        glu.build2DMipmaps(gl.TEXTURE_2D, 3, image.width, image.height, gl.RGBA, gl.UNSIGNED_BYTE, image);        
    }
    image.src = "Data/lesson12/cube.bmp";
    return texture;
}
var cube;
var top;
buildList = function() {
    cube = gl.createList();
    gl.newList(cube, gl.COMPILE);
    gl.begin(gl.QUADS);
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(-1.0, -1.0, -1.0); // Top Right Of The Texture and Quad
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(1.0, -1.0, -1.0); // Top Left Of The Texture and Quad
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(1.0, -1.0, 1.0); // Bottom Left Of The Texture and Quad
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(-1.0, -1.0, 1.0); // Bottom Right Of The Texture and Quad
    // Front Face
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(-1.0, -1.0, 1.0); // Bottom Left Of The Texture and Quad
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(1.0, -1.0, 1.0); // Bottom Right Of The Texture and Quad
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(1.0, 1.0, 1.0); // Top Right Of The Texture and Quad
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(-1.0, 1.0, 1.0); // Top Left Of The Texture and Quad
    // Back Face
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(-1.0, -1.0, -1.0); // Bottom Right Of The Texture and Quad
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(-1.0, 1.0, -1.0); // Top Right Of The Texture and Quad
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(1.0, 1.0, -1.0); // Top Left Of The Texture and Quad
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(1.0, -1.0, -1.0); // Bottom Left Of The Texture and Quad
    // Right face
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(1.0, -1.0, -1.0); // Bottom Right Of The Texture and Quad
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(1.0, 1.0, -1.0); // Top Right Of The Texture and Quad
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(1.0, 1.0, 1.0); // Top Left Of The Texture and Quad
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(1.0, -1.0, 1.0); // Bottom Left Of The Texture and Quad
    // Left Face
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(-1.0, -1.0, -1.0); // Bottom Left Of The Texture and Quad
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(-1.0, -1.0, 1.0); // Bottom Right Of The Texture and Quad
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(-1.0, 1.0, 1.0); // Top Right Of The Texture and Quad
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(-1.0, 1.0, -1.0); // Top Left Of The Texture and Quad
    gl.end();
    gl.endList();
    top = gl.createList(); // since we generated 2 lists, this is where the second is...1 GLuint up from cube.
    gl.newList(top, gl.COMPILE); // generate 2nd list (top of box).
    gl.begin(gl.QUADS);
    // Top Face
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(-1.0, 1.0, -1.0); // Top Left Of The Texture and Quad
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(-1.0, 1.0, 1.0); // Bottom Left Of The Texture and Quad
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(1.0, 1.0, 1.0); // Bottom Right Of The Texture and Quad
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(1.0, 1.0, -1.0); // Top Right Of The Texture and Quad
    gl.end();
    gl.endList();
}
var points = [];
skel.onInitScene = function() {
    // init.    
    loadTextures();
    buildList();
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
    gl.enable(gl.LIGHT0);
    gl.enable(gl.LIGHTING);
    //gl.enable(gl.COLOR_MATERIAL);
}
var boxcol = [
    [1.0, 0.0, 0.0],
    [1.0, 0.5, 0.0],
    [1.0, 1.0, 0.0],
    [0.0, 1.0, 0.0],
    [0.0, 1.0, 1.0]
];
var topcol = [
    [0.5, 0.0, 0.0],
    [0.5, 0.25, 0.0],
    [0.5, 0.5, 0.0],
    [0.0, 0.5, 0.0],
    [0.0, 0.5, 0.5]
];
var xloop = 0,
    yloop = 0;
var xrot = 0,
    yrot = 0;
skel.onDrawScene = function() {
    var x, y;
    var float_x, float_y, float_xb, float_yb;
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer    
    gl.bindTexture(gl.TEXTURE_2D, texture[0]);
    for (yloop = 1; yloop < 6; yloop++) { // 5 rows of cubes.
        for (xloop = 0; xloop < yloop; xloop++) {
            gl.loadIdentity();
            gl.translatef(1.4 + (xloop * 2.8) - (yloop * 1.4), ((6.0 - yloop) * 2.4) - 7.0, -20.0);
            gl.rotatef(45.0 - (2.0 * yloop) + xrot, 1.0, 0.0, 0.0);
            gl.rotatef(45.0 + yrot, 0.0, 1.0, 0.0);
            var c1=boxcol[yloop-1];
            var c2=topcol[yloop-1];
            gl.color3f(c1[0], c1[1], c1[2]);
            gl.callList(cube);
            //gl.color3fv(topcol[yloop - 1]);
            gl.color3f(c2[0],c2[1],c2[2]);
            gl.callList(top);
        }
    }
    requestAnimationFrame(skel.onDrawScene);
}
// testing events
glfw.events.on('keydown', function(evt) {
    switch (evt.which) {
        case glfw.KEY_UP: // up.
            xrot -= 0.2;
            break;
        case glfw.KEY_DOWN: // down 
            xrot += 0.2;
            break;
        case glfw.KEY_LEFT: // left
            yrot += 0.2;
            break;
        case glfw.KEY_RIGHT: // right
            yrot -= 0.2;
            break;
        default:
            console.log(evt);
            break;
    }    
    //console.log('[zoom:' + zoom + ', twinkle:'+twinkle+']');
});
skel.main();