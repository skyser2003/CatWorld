var Scene = function () {
};

var GameScene = function () {
    var self = this;

    this.prototype = new Scene();

    var game = new Game();

    this.init = function () {
        game.init();
        initControl();
    };

    this.run = function () {
        setInterval(game.update, 1000 / 60, 1000 / 60);
    };

    var velocity = new Vector3();

    var initControl = function () {
        // Key state
        var keyDown = {};
        
        // Initialize
        keyDown[key.left] = false;
        keyDown[key.up] = false;
        keyDown[key.right] = false;
        keyDown[key.down] = false;

        var isMoveKeyAllDown = function () {
            return keyDown[key.left]
                && keyDown[key.up]
                && keyDown[key.right]
                && keyDown[key.down];
        };
        var isMoveKeyAllUp = function () {
            return !(keyDown[key.left]
                || keyDown[key.up]
                || keyDown[key.right]
                || keyDown[key.down]);
        };

        jQuery(document).keydown(function (e) {
            if (keyDown[e.keyCode] == true) {
                return;
            }
            keyDown[e.keyCode] = true;

            var moveDist = 0.5;
            switch (e.keyCode) {
                case key.left:
                    {
                        game.moveTo(-moveDist, 0, 0);
                    }
                    break;
                case key.up:
                    {
                        game.moveTo(0, moveDist, 0);
                    }
                    break;
                case key.right:
                    {
                        game.moveTo(moveDist, 0, 0);
                    }
                    break;
                case key.down:
                    {
                        game.moveTo(0, -moveDist, 0);
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
                case key.left: // a
                case key.up: // s
                case key.right: // d
                case key.down: // w
                    {
                        if (isMoveKeyAllUp() == true) {
                            game.moveStop();
                        }
                        else {

                        }
                    }
                    break;
            }
        });
    };
};