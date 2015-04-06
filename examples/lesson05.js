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
    gl.color3f(1.0, 0.0, 0.0); // Red
    gl.vertex3f(0.0, 1.0, 0.0); // Top Of Triangle (Front)
    gl.color3f(0.0, 1.0, 0.0); // Green
    gl.vertex3f(-1.0, -1.0, 1.0); // Left Of Triangle (Front)
    gl.color3f(0.0, 0.0, 1.0); // Blue
    gl.vertex3f(1.0, -1.0, 1.0); // Right Of Triangle (Front)
    gl.color3f(1.0, 0.0, 0.0); // Red
    gl.vertex3f(0.0, 1.0, 0.0); // Top Of Triangle (Right)
    gl.color3f(0.0, 0.0, 1.0); // Blue
    gl.vertex3f(1.0, -1.0, 1.0); // Left Of Triangle (Right)
    gl.color3f(0.0, 1.0, 0.0); // Green
    gl.vertex3f(1.0, -1.0, -1.0); // Right Of Triangle (Right)
    gl.color3f(1.0, 0.0, 0.0); // Red
    gl.vertex3f(0.0, 1.0, 0.0); // Top Of Triangle (Back)
    gl.color3f(0.0, 1.0, 0.0); // Green
    gl.vertex3f(1.0, -1.0, -1.0); // Left Of Triangle (Back)
    gl.color3f(0.0, 0.0, 1.0); // Blue
    gl.vertex3f(-1.0, -1.0, -1.0); // Right Of Triangle (Back)
    gl.color3f(1.0, 0.0, 0.0); // Red
    gl.vertex3f(0.0, 1.0, 0.0); // Top Of Triangle (Left)
    gl.color3f(0.0, 0.0, 1.0); // Blue
    gl.vertex3f(-1.0, -1.0, -1.0); // Left Of Triangle (Left)
    gl.color3f(0.0, 1.0, 0.0); // Green
    gl.vertex3f(-1.0, -1.0, 1.0); // Right Of Triangle (Left)
    gl.end(); // Done Drawing The Pyramid
    gl.loadIdentity(); // Reset The Current Modelview Matrix
    gl.translatef(1.5, 0.0, -7.0); // Move Right 1.5 Units And Into The Screen 7.0
    gl.rotatef(rquad, 1.0, 1.0, 1.0); // Rotate The Quad On The X axis ( NEW )
    gl.begin(gl.QUADS); // Draw A Quad
    gl.color3f(0.0, 1.0, 0.0); // Set The Color To Green
    gl.vertex3f(1.0, 1.0, -1.0); // Top Right Of The Quad (Top)
    gl.vertex3f(-1.0, 1.0, -1.0); // Top Left Of The Quad (Top)
    gl.vertex3f(-1.0, 1.0, 1.0); // Bottom Left Of The Quad (Top)
    gl.vertex3f(1.0, 1.0, 1.0); // Bottom Right Of The Quad (Top)
    gl.color3f(1.0, 0.5, 0.0); // Set The Color To Orange
    gl.vertex3f(1.0, -1.0, 1.0); // Top Right Of The Quad (Bottom)
    gl.vertex3f(-1.0, -1.0, 1.0); // Top Left Of The Quad (Bottom)
    gl.vertex3f(-1.0, -1.0, -1.0); // Bottom Left Of The Quad (Bottom)
    gl.vertex3f(1.0, -1.0, -1.0); // Bottom Right Of The Quad (Bottom)
    gl.color3f(1.0, 0.0, 0.0); // Set The Color To Red
    gl.vertex3f(1.0, 1.0, 1.0); // Top Right Of The Quad (Front)
    gl.vertex3f(-1.0, 1.0, 1.0); // Top Left Of The Quad (Front)
    gl.vertex3f(-1.0, -1.0, 1.0); // Bottom Left Of The Quad (Front)
    gl.vertex3f(1.0, -1.0, 1.0); // Bottom Right Of The Quad (Front)
    gl.color3f(1.0, 1.0, 0.0); // Set The Color To Yellow
    gl.vertex3f(1.0, -1.0, -1.0); // Top Right Of The Quad (Back)
    gl.vertex3f(-1.0, -1.0, -1.0); // Top Left Of The Quad (Back)
    gl.vertex3f(-1.0, 1.0, -1.0); // Bottom Left Of The Quad (Back)
    gl.vertex3f(1.0, 1.0, -1.0); // Bottom Right Of The Quad (Back)
    gl.color3f(0.0, 0.0, 1.0); // Set The Color To Blue
    gl.vertex3f(-1.0, 1.0, 1.0); // Top Right Of The Quad (Left)
    gl.vertex3f(-1.0, 1.0, -1.0); // Top Left Of The Quad (Left)
    gl.vertex3f(-1.0, -1.0, -1.0); // Bottom Left Of The Quad (Left)
    gl.vertex3f(-1.0, -1.0, 1.0); // Bottom Right Of The Quad (Left)
    gl.color3f(1.0, 0.0, 1.0); // Set The Color To Violet
    gl.vertex3f(1.0, 1.0, -1.0); // Top Right Of The Quad (Right)
    gl.vertex3f(1.0, 1.0, 1.0); // Top Left Of The Quad (Right)
    gl.vertex3f(1.0, -1.0, 1.0); // Bottom Left Of The Quad (Right)
    gl.vertex3f(1.0, -1.0, -1.0); // Bottom Right Of The Quad (Right)
    gl.end(); // Done Drawing The Quad
    rtri += 0.4; // Increase The Rotation Variable For The Triangle ( NEW )
    rquad -= 0.30; // Decrease The Rotation Variable For The Quad ( NEW )
    requestAnimationFrame(skel.onDrawScene);
}
skel.main();