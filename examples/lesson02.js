var skel = require('./skel.js');
var i = 0;
var glu = require('node-glu');
skel.onResize = function() {
    // resize.
    gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
    gl.matrixMode(gl.PROJECTION);
    gl.loadIdentity();
    glu.perspective(60, gl.viewportWidth / gl.viewportHeight, 0.1, 1000.0);
    gl.matrixMode(gl.MODELVIEW);
    gl.loadIdentity();
}
skel.onInitScene = function() {
    // init.
    gl.shadeModel(gl.SMOOTH);
    gl.clearColor(0.0, 0.0, 0.0, 0.5);
    gl.clearDepth(1.0);
    gl.enable(gl.DEPTH_TEST);
    gl.depthFunc(gl.LEQUAL);
    gl.hint(gl.PERSPECTIVE_CORRECTION_HINT, gl.NICEST);
}
skel.onDrawScene = function() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    gl.loadIdentity();
    gl.translatef(-1.5, 0.0, -6.0);
    gl.begin(gl.TRIANGLES);
    gl.vertex3f(0.0, 1.0, 0.0);
    gl.vertex3f(1.0, -1.0, 0.0);
    gl.vertex3f(-1.0, -1.0, 0.0);
    gl.end();
    gl.translatef(3.0, 0.0, 0.0);
    gl.begin(gl.QUADS);
    gl.vertex3f(-1.0, 1.0, 0.0);
    gl.vertex3f(1.0, 1.0, 0.0);
    gl.vertex3f(1.0, -1.0, 0.0);
    gl.vertex3f(-1.0, -1.0, 0.0);
    gl.end();
    requestAnimationFrame(skel.onDrawScene);
}
skel.main();