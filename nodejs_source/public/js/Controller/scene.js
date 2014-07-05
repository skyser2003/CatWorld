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
        // Key state
        var keyDown = {};
        
        // Initialize
        keyDown[key.left] = false;
        keyDown[key.up] = false;
        keyDown[key.right] = false;
        keyDown[key.down] = false;

        var isMoveKeyAllDown = function () {
            return keyDown[65] && keyDown[83] && keyDown[68] && keyDown[87];
        };
        var isMoveKeyAllUp = function () {
            return !(keyDown[65] || keyDown[83] || keyDown[68] || keyDown[87]);
        };

        jQuery(document).keydown(function (e) {
            if (keyDown[e.keyCode] == true) {
                return;
            }
            keyDown[e.keyCode] = true;

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