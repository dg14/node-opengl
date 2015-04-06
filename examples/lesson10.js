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
    glu.perspective(45, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0);
    gl.matrixMode(gl.MODELVIEW);
    gl.loadIdentity();
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
        gl.generateMipmap(gl.TEXTURE_2D);
        // mipmap.
        texture[2] = gl.createTexture();
        gl.bindTexture(gl.TEXTURE_2D, texture[2]);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_NEAREST);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, image.width, image.height, 0, gl.RGBA, gl.UNSIGNED_BYTE, image);
        gl.generateMipmap(gl.TEXTURE_2D);
    }
    image.src = "Data/lesson10/mud.bmp";
    return texture;
}
var ESCAPE = 27,
    PAGE_UP = 73,
    PAGE_DOWN = 81,
    UP_ARROW = 72,
    DOWN_ARROW = 80,
    LEFT_ARROW = 75,
    RIGHT_ARROW = 77;
var lightAmbient = [0.5, 0.5, 0.5, 1];
var lightDiffuse = [1, 1, 1, 1];
var lightPosition = [0, 0, 2, 1];
var light = 0,
    blend = 0;
var xrot = 0,
    yrot = 0,
    xspeed = 0.5,
    yspeed = 0.5;
var xpos = 0,
    ypos = 0,
    zpos = 0;
var walkbias = 0,
    walkbiasangle = 0;
var lookupdown = 0.0;
var piover180 = Math.PI / 180;
var heading, xpos, ypos, zpos;
var camx = 0,
    camy = 0,
    camz = 0;
var therotate;
var z = 0.0;
var filter = 0;
var sector1;
readstr = function(lines, cur) {
    while (cur < lines.length) {
        line = lines[cur].trim();
        if (line != '' && line[0] != '/' && line[0] != '\n' && line[0] != '\l') {
            return {
                cur: cur + 1,
                str: line
            };
        }
        cur++;
    }
    return false;
}
setupWorld = function() {
    var fs = require('fs');
    lines = fs.readFileSync('Data/lesson10/world.txt');
    lines = String(lines).split('\n');
    cur = 0;
    ret = readstr(lines, cur);
    if (!ret) {
        return false;
    }
    cur = ret.cur;
    ptn1 = new RegExp('NUMPOLLIES ([0-9]+)');
    ptn2 = new RegExp('([0-9\.\-]+) ([0-9\.\-]+) ([0-9\.\-]+) ([0-9\.\-]+) ([0-9\.\-]+)');
    line = ret.str;
    line = line.replace("\t", " ");
    line = line.replace("\s+", "\s");
    arr = line.match(ptn1);
    sector1 = [];
    sector1.numtriangles = parseInt(arr[1]);
    sector1.triangle = [];
    for (loop = 0; loop < sector1.numtriangles; loop++) {
        sector1.triangle[loop] = [];
        sector1.triangle[loop].vertex = [];
        for (vert = 0; vert < 3; vert++) {
            sector1.triangle[loop].vertex[vert] = [];
            ret = readstr(lines, cur);
            line = ret.str;
            line = line.replace(/\s+/g, " ");
            if (arr = line.match(ptn2)) {
                sector1.triangle[loop].vertex[vert].x = parseFloat(arr[1]);
                sector1.triangle[loop].vertex[vert].y = parseFloat(arr[2]);
                sector1.triangle[loop].vertex[vert].z = parseFloat(arr[3]);
                sector1.triangle[loop].vertex[vert].u = parseFloat(arr[4]);
                sector1.triangle[loop].vertex[vert].v = parseFloat(arr[5]);
            }
            cur = ret.cur;
        }
    }
}
skel.onInitScene = function() {
    // init.
    setupWorld();
    loadTextures();
    gl.enable(gl.TEXTURE_2D);
    gl.blendFunc(gl.SRC_ALPHA, gl.ONE);
    gl.clearColor(0.0, 0.0, 0.0, 0.5);
    gl.clearDepth(1.0);
    gl.depthFunc(gl.LESS);
    gl.enable(gl.DEPTH_TEST);
    gl.shadeModel(gl.SMOOTH);
    gl.matrixMode(gl.PROJECTION);
    gl.loadIdentity();
    glu.perspective(45, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0);
    gl.matrixMode(gl.MODELVIEW);
    gl.lightfv(gl.LIGHT1, gl.AMBIENT, lightAmbient);
    gl.lightfv(gl.LIGHT1, gl.DIFFUSE, lightDiffuse);
    gl.lightfv(gl.LIGHT1, gl.POSITION, lightPosition);
    gl.enable(gl.LIGHT1);
}
skel.onDrawScene = function() {
    var x_m, y_m, z_m, u_m, v_m;
    var xtrans, ytrans, ztrans;
    var sceneroty;
    var numTriangles;
    xtrans = -xpos;
    ztrans = -zpos;
    ytrans = -walkbias - 0.25;
    sceneroty = 360 - yrot;
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
    gl.loadIdentity();
    gl.rotatef(lookupdown, 1.0, 0, 0);
    gl.rotatef(sceneroty, 0, 1.0, 0);
    gl.translatef(xtrans, ytrans, ztrans);
    //console.log([xtrans, ytrans, ztrans]);
    gl.bindTexture(gl.TEXTURE_2D, texture[filter]);
    numtriangles = sector1.numtriangles;
    gl.color3f(1.0, 1.0, 0.0);
    for (loop = 0; loop < numtriangles; loop++) { // loop through all the triangles        
        gl.begin(gl.TRIANGLES);
        gl.normal3f(0.0, 0.0, 1.0);
        x_m = sector1.triangle[loop].vertex[0].x;
        y_m = sector1.triangle[loop].vertex[0].y;
        z_m = sector1.triangle[loop].vertex[0].z;
        u_m = sector1.triangle[loop].vertex[0].u;
        v_m = sector1.triangle[loop].vertex[0].v;
        gl.texCoord2f(u_m, v_m);
        gl.vertex3f(x_m, y_m, z_m);
        x_m = sector1.triangle[loop].vertex[1].x;
        y_m = sector1.triangle[loop].vertex[1].y;
        z_m = sector1.triangle[loop].vertex[1].z;
        u_m = sector1.triangle[loop].vertex[1].u;
        v_m = sector1.triangle[loop].vertex[1].v;
        gl.texCoord2f(u_m, v_m);
        gl.vertex3f(x_m, y_m, z_m);
        x_m = sector1.triangle[loop].vertex[2].x;
        y_m = sector1.triangle[loop].vertex[2].y;
        z_m = sector1.triangle[loop].vertex[2].z;
        u_m = sector1.triangle[loop].vertex[2].u;
        v_m = sector1.triangle[loop].vertex[2].v;
        gl.texCoord2f(u_m, v_m);
        gl.vertex3f(x_m, y_m, z_m);
        gl.end();
    }
    requestAnimationFrame(skel.onDrawScene);
}
// testing events
glfw.events.on('keydown', function(evt) {
    switch (evt.which) {
        case "B".charCodeAt(0): //a            
            blend = blend ? 0 : 1; // switch the current value of blend, between 0 and 1.
            if (blend) {
                gl.enable(gl.BLEND);
                gl.disable(gl.DEPTH_TEST);
            } else {
                gl.disable(gl.BLEND);
                gl.enable(gl.DEPTH_TEST);
            }
            break;
        case "F".charCodeAt(0): // f
            filter++; // switch the current value of filter, between 0/1/2;
            if (filter > 2) {
                filter = 0;
            }
            break;
        case "L".charCodeAt(0): //z            
            light = light ? 0 : 1; // switch the current value of light, between 0 and 1.
            if (light) {
                gl.enable(gl.LIGHTING);
            } else {
                gl.disable(gl.LIGHTING);
            }
            break;
        case "T".charCodeAt(0): // t
            //if (twinkle==0) twinkle=1; else twinkle=0;
            // deactivated. bug in code???
            break;
        case "F".charCodeAt(0): // c
            filter++;
            if (filter == 3) filter = 0;
            break;
        case glfw.KEY_UP: // up.
            xpos -= Math.sin(yrot * piover180) * 0.05;
            zpos -= Math.cos(yrot * piover180) * 0.05;
            if (walkbiasangle >= 359.0) walkbiasangle = 0.0;
            else walkbiasangle += 10;
            walkbias = Math.sin(walkbiasangle * piover180) / 20.0;
            break;
        case glfw.KEY_DOWN: // down 
            xpos += Math.sin(yrot * piover180) * 0.05;
            zpos += Math.cos(yrot * piover180) * 0.05;
            if (walkbiasangle <= 1.0) walkbiasangle = 359.0;
            else walkbiasangle -= 10;
            walkbias = Math.sin(walkbiasangle * piover180) / 20.0;
            break;
        case glfw.KEY_LEFT: // left
            yrot += 1.5;
            break;
        case glfw.KEY_RIGHT: // right
            yrot -= 1.5;
            break;
        case glfw.KEY_PAGEUP: // pageup
            z -= 0.2;
            lookupdown -= 0.2;
            break;
        case glfw.KEY_PAGEDOWN: // pageup
            z += 0.2;
            lookupdown += 1.0;
            break;
        case glfw.KEY_SPACE:
            console.log({
                z: z,
                yrot: yrot,
                xpos: xpos,
                ypos: ypos,
                lookupdown: lookupdown,
                filter: filter,
                light: light,
                blend: blend
            })
            break;
        default:
            console.log(evt);
            break;
    }
    //console.log('[zoom:' + zoom + ', twinkle:'+twinkle+']');
});
skel.main();