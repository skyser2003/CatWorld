var Scene = function () {
};

var GameScene = function () {
    this.prototype = new Scene();
    var self = this;

    var game = new Game();

    this.init = function () {
        game.init();
        initControl();
    };

    this.run = function () {
        setInterval(game.update, 1000 / 60, 1000 / 60);
    };

    var moveDist = 0.5;

    var initControl = function () {
        var pm = game.pm;

        // Key state
        var keyDown = {};
        
        // Initialize
        keyDown[65] = false; // a
        keyDown[83] = false; // s
        keyDown[68] = false; // d
        keyDown[87] = false; // w

        var isMoveKeyAllDown = function () {
            return keyDown[65] && keyDown[83] && keyDown[68] && keyDown[87];
        };
        var isMoveKeyAllUp = function () {
            return !(keyDown[65] || keyDown[83] || keyDown[68] || keyDown[87]);
        };

        var moveTo = function (x, y, z) {
            var velocity = new Vector3();
            velocity.x = x;
            velocity.y = y;
            velocity.z = z;
            game.player.moveTo(velocity);

            var pks = pm.createInstance("MOVE");
            pks.x = x;
            pks.y = y;
            pks.z = z;
            pm.send(pks);
        };

        var stop = function () {
            game.player.stop();
            var pks = pm.createInstance("STOP");
            pm.send(pks);
        };

        jQuery(document).keydown(function (e) {
            if (keyDown[e.keyCode] == true) {
                return;
            }
            keyDown[e.keyCode] = true;

            switch (e.keyCode) {
                case 65: // a
                    {
                        moveTo(-moveDist, 0, 0);
                    }
                    break;
                case 83: // s
                    {
                        moveTo(0, -moveDist, 0);
                    }
                    break;
                case 68: // d
                    {
                        moveTo(moveDist, 0, 0);
                    }
                    break;
                case 87: // w
                    {
                        moveTo(0, moveDist, 0);
                    }
                    break;
            }
        });

        jQuery(document).keyup(function (e) {
            if (keyDown[e.keyCode] == false) {
                return;
            }
            keyDown[e.keyCode] = false;

            switch (e.keyCode) {
                case 65: // a
                case 83: // s
                case 68: // d
                case 87: // w
                    {
                        if (isMoveKeyAllUp() == true) {
                            stop();
                        }
                        else {

                        }
                    }
                    break;
            }
        });
    };
};