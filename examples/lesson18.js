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
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, image.width, image.height, 0, gl.RGBA, gl.UNSIGNED_BYTE, image);
        glu.build2DMipmaps(gl.TEXTURE_2D, 3, image.width, image.height, gl.RGB, gl.UNSIGNED_BYTE, image);
    }
    image.src = "Data/lesson18/crate.bmp";
    return texture;
}
drawCube = function() {
    gl.begin(gl.QUADS); // begin drawing a cube
    // Front Face (note that the texture's corners have to match the quad's corners)
    gl.normal3f(0.0, 0.0, 1.0); // front face points out of the screen on z.
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(-1.0, -1.0, 1.0); // Bottom Left Of The Texture and Quad
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(1.0, -1.0, 1.0); // Bottom Right Of The Texture and Quad
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(1.0, 1.0, 1.0); // Top Right Of The Texture and Quad
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(-1.0, 1.0, 1.0); // Top Left Of The Texture and Quad
    // Back Face
    gl.normal3f(0.0, 0.0, -1.0); // back face points into the screen on z.
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(-1.0, -1.0, -1.0); // Bottom Right Of The Texture and Quad
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(-1.0, 1.0, -1.0); // Top Right Of The Texture and Quad
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(1.0, 1.0, -1.0); // Top Left Of The Texture and Quad
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(1.0, -1.0, -1.0); // Bottom Left Of The Texture and Quad
    // Top Face
    gl.normal3f(0.0, 1.0, 0.0); // top face points up on y.
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(-1.0, 1.0, -1.0); // Top Left Of The Texture and Quad
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(-1.0, 1.0, 1.0); // Bottom Left Of The Texture and Quad
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(1.0, 1.0, 1.0); // Bottom Right Of The Texture and Quad
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(1.0, 1.0, -1.0); // Top Right Of The Texture and Quad
    // Bottom Face       
    gl.normal3f(0.0, -1.0, 0.0); // bottom face points down on y. 
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(-1.0, -1.0, -1.0); // Top Right Of The Texture and Quad
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(1.0, -1.0, -1.0); // Top Left Of The Texture and Quad
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(1.0, -1.0, 1.0); // Bottom Left Of The Texture and Quad
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(-1.0, -1.0, 1.0); // Bottom Right Of The Texture and Quad
    // Right face
    gl.normal3f(1.0, 0.0, 0.0); // right face points right on x.
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(1.0, -1.0, -1.0); // Bottom Right Of The Texture and Quad
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(1.0, 1.0, -1.0); // Top Right Of The Texture and Quad
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(1.0, 1.0, 1.0); // Top Left Of The Texture and Quad
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(1.0, -1.0, 1.0); // Bottom Left Of The Texture and Quad
    // Left Face
    gl.normal3f(-1.0, 0.0, 0.0); // left face points left on x.
    gl.texCoord2f(0.0, 0.0);
    gl.vertex3f(-1.0, -1.0, -1.0); // Bottom Left Of The Texture and Quad
    gl.texCoord2f(1.0, 0.0);
    gl.vertex3f(-1.0, -1.0, 1.0); // Bottom Right Of The Texture and Quad
    gl.texCoord2f(1.0, 1.0);
    gl.vertex3f(-1.0, 1.0, 1.0); // Top Right Of The Texture and Quad
    gl.texCoord2f(0.0, 1.0);
    gl.vertex3f(-1.0, 1.0, -1.0); // Top Left Of The Texture and Quad
    gl.end(); // done with the polygon.
}
var lightAmbient = [0.5, 0.5, 0.5, 1.0];
/* super bright, full intensity diffuse light. */
var lightDiffuse = [1.0, 1.0, 1.0, 1.0];
/* position of light (x, y, z, (position of light)) */
var lightPosition = [0.0, 0.0, 2.0, 1.0];
skel.onInitScene = function() {
    // init.    
    loadTextures();
    gl.enable(gl.TEXTURE_2D);
    gl.clearColor(0, 0, 0, 0);
    gl.clearDepth(1.0);
    gl.depthFunc(gl.LESS);
    gl.enable(gl.DEPTH_TEST);
    gl.shadeModel(gl.SMOOTH);
    gl.matrixMode(gl.PROJECTION);
    gl.lightfv(gl.LIGHT1, gl.AMBIENT, lightAmbient);
    gl.lightfv(gl.LIGHT1, gl.DIFFUSE, lightDiffuse);
    gl.lightfv(gl.LIGHT1, gl.POSITION, lightPosition);
    gl.enable(gl.LIGHT1);
    gl.blendFunc(gl.SRC_ALPHA, gl.ONE);
    gl.color4f(1, 1, 1, 0.5);
    quadratic = glu.createQuadric();
    console.log(quadratic);
    glu.quadricNormals(quadratic, glu.SMOOTH);
    glu.quadricTexture(quadratic, gl.TRUE);
}
var light = true,
    filter = 0,
    blend = true,
    object = 0,
    z = -5.0,
    xrot = 0,
    yrot = 0,
    xspeed = 0,
    yspeed = 0,
    part1 = 0,
    part2 = 0,
    p1 = 0,
    p2 = 1;
skel.onDrawScene = function() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer    
    gl.loadIdentity(); // Reset The View
    gl.translatef(0.0, 0.0, z); // move 5 units into the screen.
    gl.rotatef(xrot, 1.0, 0.0, 0.0); // Rotate On The X Axis
    gl.rotatef(yrot, 0.0, 1.0, 0.0); // Rotate On The Y Axis
    gl.bindTexture(gl.TEXTURE_2D, texture[filter]); // choose the texture to use.
    switch (object) // Check object To Find Out What To Draw
    {
        case 0: // Drawing object
            drawCube(); // Draw the cube
            break; // Done
        case 1: // Drawing object 2
            gl.translatef(0.0, 0.0, -1.5); // Center the cylinder
            glu.cylinder(quadratic, 1.0, 1.0, 3.0, 32, 32); // Draw Our Cylinder
            break; // Done
        case 2: // Drawing Object 3
            glu.disk(quadratic, 0.5, 1.5, 32, 32); // Draw A Disc (CD Shape)
            break; // Done
        case 3: // Drawing Object 4
            glu.sphere(quadratic, 1.3, 32, 32); // Draw A Sphere
            break; // Done
        case 4: // Drawing Object 5
            gl.translatef(0.0, 0.0, -1.5); // Center The Cone
            glu.cylinder(quadratic, 1.0, 0.2, 3.0, 32, 32); // A Cone With A Bottom Radius Of .5 And A Height Of 2
            break; // Done
        case 5: // Drawing Object 6
            part1 += p1; // Increase Start Angle
            part2 += p2; // Increase Sweep Angle
            if (part1 > 359) { // 360 Degrees
                p1 = 0; // Stop Increasing Start Angle
                part1 = 0; // Set Start Angle To Zero
                p2 = 1; // Start Increasing Sweep Angle
                part2 = 0; // Start Sweep Angle At Zero
            }
            if (part2 > 359) { // 360 Degrees
                p1 = 1; // Start Increasing Start Angle
                p2 = 0; // Stop Increasing Sweep Angle
            }
            glu.partialDisk(quadratic, 0.5, 1.5, 32, 32, part1, part2 - part1); // A Disk Like The One Before
            break; // Done
    };
    xrot += xspeed; // X Axis Rotation  
    yrot += yspeed; // Y Axis Rotation
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
        case "B".charCodeAt(0):
            blend = blend ? 0 : 1; // switch the current value of blend, between 0 and 1.
            console.log("Blend is now: " + blend + "\n");
            if (!blend) {
                gl.disable(gl.BLEND); // Turn Blending Off
                gl.enable(gl.DEPTH_TEST); // Turn Depth Testing On
            } else {
                gl.enable(gl - BLEND); // Turn Blending On
                gl.disable(gl.DEPTH_TEST); // Turn Depth Testing Off
            }
            break;
        case "G".charCodeAt(0):
            fogfilter += 1;
            if (fogfilter > 2) {
                fogfilter = 0;
            }
            gl.fogi(gl.FOG_MODE, fogMode[fogfilter]);
            console.log("fogfilter:" + fogfilter);
            break;
        case glfw.KEY_SPACE:
            object++; // Cycle Through The Objects
            if (object > 5) // Is object Greater Than 5?
                object = 0; // If So, Set To Zero
            break;
        case glfw.KEY_PAGE_UP: // move the cube into the distance.
            z -= 0.02;
            break;
        case glfw.KEY_PAGE_DOWN: // move the cube closer.
            z += 0.02;
            break;
        case glfw.KEY_UP: // decrease x rotation speed;
            xspeed -= 0.01;
            break;
        case glfw.KEY_DOWN: // increase x rotation speed;
            xspeed += 0.01;
            break;
        case glfw.KEY_LEFT: // decrease y rotation speed;
            yspeed -= 0.01;
            break;
        case glfw.KEY_RIGHT: // increase y rotation speed;
            yspeed += 0.01;
            break;
        default:
            console.log(evt);
            break;
    }
    //console.log('[zoom:' + zoom + ', twinkle:'+twinkle+']');
});
skel.main();