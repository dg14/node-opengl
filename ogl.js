// ogl
exports.rectangleT = function(x, y, w, h, filled) {
    gl.begin(filled ? gl.QUADS : gl.LINE_STRIP);
    gl.vertex2f(x + w, y + h);
    gl.vertex2f(x + w, y);
    gl.vertex2f(x, y);
    gl.vertex2f(x, y + h);
    gl.vertex2f(x + w, y + h);
    gl.end();
}
exports.rectangle = function(w, h, filled) {
    gl.begin(filled ? gl.QUADS : gl.LINE_STRIP);
    gl.vertex2f(w / 2, h / 2);
    gl.vertex2f(w / 2, -h / 2);
    gl.vertex2f(-w / 2, -h / 2);
    gl.vertex2f(-w / 2, h / 2);
    gl.vertex2f(w / 2, h / 2);
    gl.end();
}
exports.polygon = function(l, s, filled) {
    incr = (Math.PI * 2) / l;
    alpha = Math.PI / 2;
    if (!filled) {
        gl.begin(gl.LINE_STRIP);
        for (i = 0; i <= l; i++) {
            x1 = s * Math.cos(alpha);
            y1 = s * Math.sin(alpha);
            alpha += incr;
            gl.vertex2f(x1, y1);
        }
        gl.end();
    } else {
        gl.begin(gl.TRIANGLES);
        for (i = 0; i <= l; i++) {
            x1 = s * Math.cos(alpha);
            y1 = s * Math.sin(alpha);
            alpha += incr;
            x2 = s * Math.cos(alpha);
            y2 = s * Math.sin(alpha);
            gl.vertex2f(0, 0);
            gl.vertex2f(x1, y1);
            gl.vertex2f(x2, y2);
        }
        gl.end();
    }
}
exports.gridT = function(x, y, lw, sw, lh, sh) {
    w = lw * sw;
    h = lh * sh;
    //sx = -w / 2;
    //sy = -h / 2;
    sx = x;
    sy = y;
    gl.begin(gl.LINES);
    for (var i = 0; i < lw; i++) {
        for (var j = 0; j < lh; j++) {
            x1 = sx + i * sw;
            y1 = sy + j * sh;
            x2 = sx + (i + 1) * sw;
            y2 = sy + (j + 1) * sh;
            gl.vertex2f(x1, y1);
            gl.vertex2f(x2, y1);
            gl.vertex2f(x2, y1);
            gl.vertex2f(x2, y2);
            gl.vertex2f(x2, y2);
            gl.vertex2f(x1, y2);
            gl.vertex2f(x1, y2);
            gl.vertex2f(x1, y1);
        }
    }
    gl.end();
}
exports.grid = function(lw, sw, lh, sh) {
    w = lw * sw;
    h = lh * sh;
    sx = -w / 2;
    sy = -h / 2;
    gl.begin(gl.LINES);
    for (var i = 0; i < lw; i++) {
        for (var j = 0; j < lh; j++) {
            x1 = sx + i * sw;
            y1 = sy + j * sh;
            x2 = sx + (i + 1) * sw;
            y2 = sy + (j + 1) * sh;
            gl.vertex2f(x1, y1);
            gl.vertex2f(x2, y1);
            gl.vertex2f(x2, y1);
            gl.vertex2f(x2, y2);
            gl.vertex2f(x2, y2);
            gl.vertex2f(x1, y2);
            gl.vertex2f(x1, y2);
            gl.vertex2f(x1, y1);
        }
    }
    gl.end();
}