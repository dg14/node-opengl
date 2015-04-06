var skel = require('node-opengl').skel;
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
var rtri = 0;
var rquad = 0;
skel.onDrawScene = function() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
    gl.loadIdentity(); // Reset The Current Modelview Matrix
    gl.translatef(-1.5, 0.0, -6.0); // Move Left 1.5 Units And Into The Screen 6.0
    gl.rotatef(rtri, 0.0, 1.0, 0.0); // Rotate The Triangle On The Y axis ( NEW )
    gl.begin(gl.TRIANGLES); // Start Drawing A Triangle
    gl.color3f(1.0, 0.0, 0.0); // Set Top Point Of Triangle To Red
    gl.vertex3f(0.0, 1.0, 0.0); // First Point Of The Triangle
    gl.color3f(0.0, 1.0, 0.0); // Set Left Point Of Triangle To Green
    gl.vertex3f(-1.0, -1.0, 0.0); // Second Point Of The Triangle
    gl.color3f(0.0, 0.0, 1.0); // Set Right Point Of Triangle To Blue
    gl.vertex3f(1.0, -1.0, 0.0); // Third Point Of The Triangle
    gl.end(); // Done Drawing The Triangle
    gl.loadIdentity(); // Reset The Current Modelview Matrix
    gl.translatef(1.5, 0.0, -6.0); // Move Right 1.5 Units And Into The Screen 6.0
    gl.rotatef(rquad, 1.0, 0.0, 0.0); // Rotate The Quad On The X axis ( NEW )
    gl.color3f(0.5, 0.5, 1.0); // Set The Color To Blue One Time Only
    gl.begin(gl.QUADS); // Draw A Quad
    gl.vertex3f(-1.0, 1.0, 0.0); // Top Left
    gl.vertex3f(1.0, 1.0, 0.0); // Top Right
    gl.vertex3f(1.0, -1.0, 0.0); // Bottom Right
    gl.vertex3f(-1.0, -1.0, 0.0); // Bottom Left
    gl.end(); // Done Drawing The Quad
    rtri += 0.2; // Increase The Rotation Variable For The Triangle ( NEW )
    rquad -= 0.15; // Decrease The Rotation Variable For The Quad ( NEW )
    requestAnimationFrame(skel.onDrawScene);
}
skel.main();