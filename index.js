var gl = require('./build/Release/gl.node');
module.exports = gl;
var shutdown_callback = false;
module.exports.setShutdownCallback = function(callback) {
    shutdown_callback = callback;
}
module.exports.createApp = function(quitfun) {
    var GLFW = require('node-glfw');
    var gl = require('./build/Release/gl.node');
    var onquit = function() {
        console.log('Shutting Down');
        if (shutdown_callback) shutdown_callback();
        process.exit(0);
    }
    if (process.platform !== 'win32') process.on('SIGINT', function() {
        onquit();
    });
    var events;
    var platform;
/*    
    Object.defineProperty(GLFW, 'events', {
        get: function() {
            if (events) return events;
            events = new(require('events').EventEmitter);
            var _emit = events.emit;
            events.emit = function() {
                var args = Array.prototype.slice.call(arguments);
                var evt = args[1]; // args[1] is the event, args[0] is the type of event
                if (evt) evt.preventDefault = function() {};
                if (evt) evt.stopPropagation = function() {};
                if (evt && evt.type === 'resize' && platform) {
                    platform.width = evt.width;
                    platform.height = evt.height;
                }
                _emit.apply(this, args);
            };
            return events;
        }
    });
*/    
    GLFW.Init();
    //  GLFW.events.on('event', console.dir);
    GLFW.events.on('quit', function() {
        onquit();
    });
    GLFW.events.on("keydown", function(evt) {
        if ((evt.keyCode === 'C'.charCodeAt(0) && evt.ctrlKey) || evt.keyCode === 27) onquit();
    });
    platform = {
        type: "nodeGLFW",
        setTitle: GLFW.SetWindowTitle,
        redrawFunction: false,
        flip: GLFW.SwapBuffers,
        createElement: function(name, width, height) {
            this.createWindow(width || 800, height || 800);
            this.canvas = this;
            gl.canvas = this;
            return this;
        },
        createWindow: function(width, height) {
            var attribs = GLFW.WINDOW;
            if (width == 0 || height == 0) {
                attribs = GLFW.FULLSCREEN;
                width = height = 0;
            }
            var resizeListeners = [],
                rl = GLFW.events.listeners('resize');
            for (var l = 0, ln = rl.length; l < ln; ++l) resizeListeners[l] = rl[l];
            GLFW.events.removeAllListeners('resize');
            GLFW.DefaultWindowHints();
            this.window = GLFW.CreateWindow(width, height, "Test");
            if (!this.window) {
                GLFW.Terminate();
                throw "Can't initialize GL surface";
            }
            GLFW.MakeContextCurrent(this.window);
            // make sure GLEW is initialized
            gl.Init();
            //GLFW.SwapBuffers();
            GLFW.SwapInterval(0); // Disable VSync (we want to get as high FPS as possible!)
            for (var l = 0, ln = resizeListeners.length; l < ln; ++l) GLFW.events.addListener('resize', resizeListeners[l]);
            //            var size = GLFW.GetWindowSize();
            var size = GLFW.GetFramebufferSize(this.window);
            this.width = this.drawingBufferWidth = size.width;
            this.height = this.drawingBufferHeight = size.height;
        },
        main: function() {
            while (!GLFW.WindowShouldClose(this.window) && !GLFW.GetKey(this.window, GLFW.KEY_ESCAPE)) {
                if (this.redrawFunction) {
                    this.redrawFunction();
                }
                // Get window size (may be different than the requested size)
                var wsize = GLFW.GetFramebufferSize(this.window);
                // 
                // Swap buffers
                GLFW.SwapBuffers(this.window);
                GLFW.PollEvents();
            }
        },
        main2: function() {
            var l=false;
            while (!GLFW.WindowShouldClose(this.window) && !GLFW.GetKey(this.window, GLFW.KEY_ESCAPE)) {
                // Get window size (may be different than the requested size)
                var wsize = GLFW.GetFramebufferSize(this.window);
                if (!l) {
                    this.redrawFunction();
                    l=true;
                }
                // 
                // Swap buffers
                GLFW.SwapBuffers(this.window);
                GLFW.PollEvents();
            }
        },
        setRedrawFunction: function(fun) {
            this.redrawFunction = fun;
        },
        getContext: function(name) {
            return gl;
        },
        on: function(name, callback) {
            GLFW.events.on(name, callback);
        },
        requestAnimationFrame: function(callback, delay) {
            //GLFW.SwapBuffers(this.window);
            //GLFW.PollEvents();
            var timer = setImmediate; //process.nextTick;
            var d = 16;
            if (delay == undefined || delay > 0) {
                timer = setTimeout;
                d = delay;
            }
            timer(function() {                
                callback(GLFW.GetTime() * 1000.0);
            }, d);
        }
    };
    Object.defineProperty(platform, 'AntTweakBar', {
        get: function(cb) {
            return new GLFW.AntTweakBar();
        }
    });
    Object.defineProperty(platform, 'onkeydown', {
        set: function(cb) {
            this.on('keydown', cb);
        }
    });
    Object.defineProperty(platform, 'onkeyup', {
        set: function(cb) {
            this.on('keyup', cb);
        }
    });
    return platform;
};
//var Image = module.exports.Image = require('./build/Release/gl.node').Image;
var Image = module.exports.Image = gl.Image;
var events = require('events');
Object.defineProperty(Image.prototype, 'onload', {
    set: function(callback) {
        this.on('load', callback);
    },
});
inherits(Image, events.EventEmitter);
// extend prototype
function inherits(target, source) {
    for (var k in source.prototype) target.prototype[k] = source.prototype[k];
}

module.exports.Timer=require('./timer.js');
module.exports.ogl=require('./ogl.js');
module.exports.skel=require('./skel.js');