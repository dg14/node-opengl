function Timer(fun, interval) {
    this.fun = fun;
    this.interval = !interval ? 1000 : interval;
}
Timer.prototype = {
    fun: false,
    stopped: true,
    interval: 1000, // one second.
    internaltimer: false,
    setFunction: function(fun) {
        this.fun = fun;
    },
    setInterval: function(a) {
        this.interval = a;
    },
    start: function() {
        if (this.stopped && this.fun) {
            this.stopped = false;
            this.internaltimer = setInterval(this.fun, this.interval, this);
        }
    },
    end: function() {
        if (!this.stopped) {
            this.stopped = true;
            clearInterval(this.internaltimer);
        }
    }
};
module.exports = Timer;
/*
main = function() {
    var steps = 0;
    var b = new Timer(function(timer) {
        console.log("Ding:" + steps);
        steps++;
        if (steps > 25*10) {
            timer.end();
        }
    },1000/25);
    console.log("**");
    b.start();
}

*/
