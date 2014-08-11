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
                        velocity.x = -moveDist;
                        game.moveTo(velocity);
                    }
                    break;
                case key.up:
                    {
                        velocity.y = moveDist;
                        game.moveTo(velocity);
                    }
                    break;
                case key.right:
                    {
                        velocity.x = moveDist;
                        game.moveTo(velocity);
                    }
                    break;
                case key.down:
                    {
                        velocity.y = -moveDist;
                        game.moveTo(velocity);
                    }
                    break;
            }

            console.log(velocity);
        });

        jQuery(document).keyup(function (e) {
            if (keyDown[e.keyCode] == false) {
                return;
            }
            keyDown[e.keyCode] = false;

            switch (e.keyCode) {
                case key.left: // a
                    {
                        velocity.x = 0;
                    }
                    break;
                case key.up: // s
                    {
                        velocity.y = 0;
                    }
                    break;
                case key.right: // d
                    {
                        velocity.x = 0;
                    }
                    break;
                case key.down: // w
                    {
                        velocity.y = 0;
                    }
                    break;
            }

            if (isMoveKeyAllUp() == true) {
                game.moveStop();
            }
            else {
                game.moveTo(velocity);
            }
        });
    };
};