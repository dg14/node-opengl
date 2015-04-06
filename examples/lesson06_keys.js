var skel = require('node-opengl').skel;
var i = 0;
var glu = require('node-glu');
var gl = require('node-opengl');
var glfw = require('node-glfw');
var util = require('util');
skel.onResize = function() {
    // resize.
    gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
    gl.matrixMode(gl.PROJECTION);
    gl.loadIdentity();
    glu.perspective(60, gl.viewportWidth / gl.viewportHeight, 0.1, 1000.0);
    gl.matrixMode(gl.MODELVIEW);
    gl.loadIdentity();
}
var texture;
skel.onInitScene = function() {
    // init.
    texture = skel.loadTexture(1, 'Data/lesson6/nehe.gif');
    gl.enable(gl.TEXTURE_2D);
    gl.shadeModel(gl.SMOOTH);
    gl.clearColor(0.0, 0.0, 0.0, 0.5);
    gl.clearDepth(1.0);
    gl.enable(gl.DEPTH_TEST);
    gl.depthFunc(gl.LEQUAL);
    gl.hint(gl.PERSPECTIVE_CORRECTION_HINT, gl.NICEST);
}

var xrot = 0,
    yrot = 0,
    zrot = 0;

var x = 0,
    y = 0,
    z = -5;
var rotate = true;
skel.onDrawScene = function() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
    gl.loadIdentity(); // Reset The View
    gl.translatef(0.0, 0.0, -5.0);
    gl.translatef(x, y, z);
    gl.rotatef(xrot, 1.0, 0.0, 0.0);
    gl.rotatef(yrot, 0.0, 1.0, 0.0);
    gl.rotatef(zrot, 0.0, 0.0, 1.0);
    gl.bindTexture(gl.TEXTURE_2D, texture);
    gl.begin(gl.QUADS);
    // Front Face
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(-1.0, -1.0, 1.0);
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(1.0, -1.0, 1.0);
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(1.0, 1.0, 1.0);
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(-1.0, 1.0, 1.0);
    // Back Face
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(-1.0, -1.0, -1.0);
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(-1.0, 1.0, -1.0);
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(1.0, 1.0, -1.0);
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(1.0, -1.0, -1.0);
    // Top Face
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(-1.0, 1.0, -1.0);
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(-1.0, 1.0, 1.0);
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(1.0, 1.0, 1.0);
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(1.0, 1.0, -1.0);
    // Bottom Face
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(-1.0, -1.0, -1.0);
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(1.0, -1.0, -1.0);
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(1.0, -1.0, 1.0);
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(-1.0, -1.0, 1.0);
    // Right face
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(1.0, -1.0, -1.0);
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(1.0, 1.0, -1.0);
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(1.0, 1.0, 1.0);
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(1.0, -1.0, 1.0);
    // Left Face
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(-1.0, -1.0, -1.0);
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(-1.0, -1.0, 1.0);
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(-1.0, 1.0, 1.0);
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(-1.0, 1.0, -1.0);
    gl.end();
    if (rotate) {
        xrot += 0.3;
        yrot += 0.2;
        zrot += 0.4;
    }
    requestAnimationFrame(skel.onDrawScene);
}
// testing events
glfw.events.on('keydown', function(evt) {
    switch (evt.which) {
        case 65: //a
            console.log('[' + x + ',' + y + ',' + z + ']');
            x += 1.0;
            break;
        case 90: //z
            console.log('[' + x + ',' + y + ',' + z + ']');
            x -= 1.0;
            break;
        case 83: //s 
            y += 1.0;
            console.log('[' + x + ',' + y + ',' + z + ']');
            break;
        case 88: //x
            y -= 1.0;
            console.log('[' + x + ',' + y + ',' + z + ']');
            break;
        case 68: // d
            z += 1.0;
            console.log('[' + x + ',' + y + ',' + z + ']');
            break;
        case 67: // c
            z -= 1.0;
            console.log('[' + x + ',' + y + ',' + z + ']');
            break;
        case 32: // 
            rotate = !rotate;
            break;
        default:
            console.log("[keydown] " + util.inspect(evt));
            break;
    }
});
skel.main();