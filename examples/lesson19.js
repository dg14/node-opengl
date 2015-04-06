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
    glu.perspective(45, gl.viewportWidth / gl.viewportHeight, 0.1, 200.0);
    gl.matrixMode(gl.MODELVIEW);
    gl.loadIdentity();
}
Math.rand = function(min, max) {
    var diff = max - min;
    return Math.round(min + Math.random() * (max - min));
}
var texture = [];
loadTextures = function() {
    image = new Image();
    image.onload = function() {
        texture[0] = gl.createTexture();
        // create nearest filtered texture
        gl.bindTexture(gl.TEXTURE_2D, texture[0]);
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        //gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, image.width, image.height, 0, gl.RGB, gl.UNSIGNED_BYTE, image);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, image.width, image.height, 0, gl.RGBA, gl.UNSIGNED_BYTE, image);
        console.log("width:" + image.width + ",height:" + image.height);
    }
    image.src = "Data/lesson19/Particle.pnm";
    return texture;
}
var colors = // Rainbow Of Colors
[
    [1.0, 0.5, 0.5],
    [1.0, 0.75, 0.5],
    [1.0, 1.0, 0.5],
    [0.75, 1.0, 0.5],
    [0.5, 1.0, 0.5],
    [0.5, 1.0, 0.75],
    [0.5, 1.0, 1.0],
    [0.5, 0.75, 1.0],
    [0.5, 0.5, 1.0],
    [0.75, 0.5, 1.0],
    [1.0, 0.5, 1.0],
    [1.0, 0.5, 0.75]
];
var MAX_PARTICLES = 1000;
var particle = [];
skel.onInitScene = function() {
    // init.    
    loadTextures();
    gl.shadeModel(gl.SMOOTH);
    gl.clearColor(0, 0, 0, 0);
    gl.clearDepth(1.0);
    gl.disable(gl.DEPTH_TEST);
    gl.enable(gl.BLEND);
    gl.blendFunc(gl.SRC_ALPHA, gl.ONE);
    gl.hint(gl.PERSPECTIVE_CORRECTION_HINT, gl.NICEST);
    gl.hint(gl.POINT_SMOOTH_HINT, gl.NICEST);
    gl.enable(gl.TEXTURE_2D);
    gl.bindTexture(gl.TEXTURE_2D, texture[0]);
    for (loop = 0; loop < MAX_PARTICLES; loop++) {
        particle[loop] = new Object();
        particle[loop].active = true;
        particle[loop].life = 1.0; // Give All The Particles Full Life
        particle[loop].fade = Math.round(Math.random() * 100) / 1000.0 + 0.003; // Random Fade Speed
        index = Math.floor((loop) / (MAX_PARTICLES / 12));
        particle[loop].r = colors[index][0]; // Select Red Rainbow Color
        particle[loop].g = colors[index][1]; // Select Green Rainbow Color
        particle[loop].b = colors[index][2]; // Select Blue Rainbow Color
        particle[loop].xi = (Math.rand(0, 50) - 26.0) * 10.0; // Random Speed On X Axis
        particle[loop].yi = (Math.rand(0, 50) - 25.0) * 10.0; // Random Speed On Y Axis
        particle[loop].zi = (Math.rand(0, 50) - 25.0) * 10.0; // Random Speed On Z Axis
        particle[loop].xg = 0.0; // Set Horizontal Pull To Zero
        particle[loop].yg = -0.8; // Set Vertical Pull Downward
        particle[loop].zg = 0.0; // Set Pull On Z Axis To Zero
    }
}
var keys = [];
var active = true; // Window Active Flag Set To TRUE By Default
var rainbow = true; // Rainbow Mode?
var sp = false; // Spacebar Pressed?
var rp = false; // Enter Key Pressed?
var slowdown = 2.0; // Slow Down Particles
var xspeed=0; // Base X Speed (To Allow Keyboard Direction Of Tail)
var yspeed=0; // Base Y Speed (To Allow Keyboard Direction Of Tail)
var zoom = -40.0; // Used To Zoom Out
var loop; // Misc Loop Variable
var col = 0; // Current Color Selection
var delay; // Rainbow Effect Delay
skel.onDrawScene = function() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer    
    gl.loadIdentity(); // Reset The ModelView Matrix
    for (var loop = 0; loop < MAX_PARTICLES; loop++) { // Loop Through All The Particles        
        if (particle[loop].active) { // If The Particle Is Active                         
            var x = particle[loop].x; // Grab Our Particle X Position
            var y = particle[loop].y; // Grab Our Particle Y Position
            var z = particle[loop].z + zoom; // Particle Z Pos + Zoom
            // Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
            gl.color4f(particle[loop].r, particle[loop].g, particle[loop].b, particle[loop].life);
            gl.begin(gl.TRIANGLE_STRIP); // Build Quad From A Triangle Strip
            gl.texCoord2f(1, 1);
            gl.vertex3f(x + 0.5, y + 0.5, z); // Top Right
            gl.texCoord2f(0, 1);
            gl.vertex3f(x - 0.5, y + 0.5, z); // Top Left
            gl.texCoord2f(1, 0);
            gl.vertex3f(x + 0.5, y - 0.5, z); // Bottom Right
            gl.texCoord2f(0, 0);
            gl.vertex3f(x - 0.5, y - 0.5, z); // Bottom Left
            gl.end(); // Done Building Triangle Strip
            particle[loop].x += particle[loop].xi / (slowdown * 1000); // Move On The X Axis By X Speed
            particle[loop].y += particle[loop].yi / (slowdown * 1000); // Move On The Y Axis By Y Speed
            particle[loop].z += particle[loop].zi / (slowdown * 1000); // Move On The Z Axis By Z Speed
            particle[loop].xi += particle[loop].xg; // Take Pull On X Axis Into Account
            particle[loop].yi += particle[loop].yg; // Take Pull On Y Axis Into Account
            particle[loop].zi += particle[loop].zg; // Take Pull On Z Axis Into Account
            particle[loop].life -= particle[loop].fade; // Reduce Particles Life By 'Fade'
            if (particle[loop].life < 0.0) // If Particle Is Burned Out
            {
                particle[loop].life = 1.0; // Give It New Life
                particle[loop].fade = Math.round(Math.random() * 100) / 1000.0 + 0.003; // Random Fade Value
                particle[loop].x = 0.0; // Center On X Axis
                particle[loop].y = 0.0; // Center On Y Axis
                particle[loop].z = 0.0; // Center On Z Axis
                particle[loop].xi = xspeed + Math.rand(0, 60) - 32.0; // X Axis Speed And Direction
                particle[loop].yi = yspeed + Math.rand(0, 60) - 30.0; // Y Axis Speed And Direction
                particle[loop].zi = Math.rand(0, 60) - 30.0; // Z Axis Speed And Direction
                particle[loop].r = colors[col][0]; // Select Red From Color Table
                particle[loop].g = colors[col][1]; // Select Green From Color Table
                particle[loop].b = colors[col][2]; // Select Blue From Color Table
            }
            // If Number Pad 8 And Y Gravity Is Less Than 1.5 Increase Pull Upwards
            if (keys[glfw.KEY_UP] && (particle[loop].yg < 1.5)) particle[loop].yg += 0.01;
            // If Number Pad 2 And Y Gravity Is Greater Than -1.5 Increase Pull Downwards
            if (keys[glfw.KEY_DOWN] && (particle[loop].yg > -1.5)) particle[loop].yg -= 0.01;
            // If Number Pad 6 And X Gravity Is Less Than 1.5 Increase Pull Right
            if (keys[glfw.KEY_RIGHT] && (particle[loop].xg < 1.5)) particle[loop].xg += 0.01;
            // If Number Pad 4 And X Gravity Is Greater Than -1.5 Increase Pull Left
            if (keys[glfw.KEY_LEFT] && (particle[loop].xg > -1.5)) particle[loop].xg -= 0.01;
            if (keys[glfw.KEY_TAB]) // Tab Key Causes A Burst
            {
                particle[loop].x = 0.0; // Center On X Axis
                particle[loop].y = 0.0; // Center On Y Axis
                particle[loop].z = 0.0; // Center On Z Axis
                particle[loop].xi = (Math.rand(0, 50) - 26.0) * 10.0; // Random Speed On X Axis
                particle[loop].yi = (Math.rand(0, 50) - 25.0) * 10.0; // Random Speed On Y Axis
                particle[loop].zi = (Math.rand(0, 50) - 25.0) * 10.0; // Random Speed On Z Axis
            }
        }
        if (keys[glfw.KEY_TAB]) // Tab Key Causes A Burst
        {
            particle[loop].x = 0.0; // Center On X Axis
            particle[loop].y = 0.0; // Center On Y Axis
            particle[loop].z = 0.0; // Center On Z Axis
            particle[loop].xi = (Math.rand(0, 50) - 26.0) * 10.0; // Random Speed On X Axis
            particle[loop].yi = (Math.rand(0, 50) - 25.0) * 10.0; // Random Speed On Y Axis
            particle[loop].zi = (Math.rand(0, 50) - 25.0) * 10.0; // Random Speed On Z Axis
        }
    }
    check_keys();
    requestAnimationFrame(skel.onDrawScene);
}
check_keys = function() {
    if (keys[glfw.KEY_KP_ADD] && (slowdown > 0.0)) { slowdown -= 0.01; }
    if (keys[glfw.KEY_KP_SUBTRACT] && (slowdown < 4.0)) slowdown += 0.01; // Slow Down Particles
    if (keys[glfw.KEY_PAGEUP]) zoom += 0.1; // Zoom In
    if (keys[glfw.KEY_PAGEDOWN]) zoom -= 0.1; // Zoom Out
    if (keys[glfw.KEY_ENTER] && !rp) // Return Key Pressed
    {
        rp = true; // Set Flag Telling Us It's Pressed
        rainbow = !rainbow; // Toggle Rainbow Mode On / Off        
    }
    if (!keys[glfw.KEY_RETURN]) rp = false; // If Return Is Released Clear Flag
    if ((keys[glfw.KEY_SPACE] && !sp) || (rainbow && (delay > 25))) // Space Or Rainbow Mode
    {
        if (keys[glfw.KEY_SPACE]) rainbow = false; // If Spacebar Is Pressed Disable Rainbow Mode
        sp = true; // Set Flag Telling Us Space Is Pressed
        delay = 0; // Reset The Rainbow Color Cycling Delay
        col++; // Change The Particle Color
        if (col > 11) col = 0; // If Color Is To High Reset It        
    }
    if (!keys[glfw.KEY_SPACE]) sp = false; // If Spacebar Is Released Clear Flag
    // If Up Arrow And Y Speed Is Less Than 200 Increase Upward Speed
    if (keys[glfw.KEY_UP] && (yspeed < 200)) yspeed += 1.0;
    // If Down Arrow And Y Speed Is Greater Than -200 Increase Downward Speed
    if (keys[glfw.KEY_DOWN] && (yspeed > -200)) yspeed -= 1.0;
    // If Right Arrow And X Speed Is Less Than 200 Increase Speed To The Right
    if (keys[glfw.KEY_RIGHT] && (xspeed < 200)) xspeed += 1.0;
    // If Left Arrow And X Speed Is Greater Than -200 Increase Speed To The Left
    if (keys[glfw.KEY_LEFT] && (xspeed > -200)) xspeed -= 1.0;
    delay++; // Increase Rainbow Mode Color Cycling Delay Counter
}
// testing events
glfw.events.on('keyup', function(evt) {
    keys[evt.which] = false;    
});
glfw.events.on('keydown', function(evt) {    
    keys[evt.which] = true;
});
skel.main();