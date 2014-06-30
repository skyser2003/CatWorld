var Scene = function () {
};

var GameScene = function () {
    this.prototype = new Scene();
    var self = this;

    var game = new Game();
    var isMoveKeyDown = false;

    this.init = function () {
        game.init();
        initControl();
    };

    this.run = function () {
        setInterval(game.update, 1000 / 60, 1000 / 60);
    };

    var moveDist = 0.5;

    var initControl = function () {
        jQuery(document).keydown(function (e) {
            switch (e.keyCode) {
                case 65: // a
                    {
                        if (isMoveKeyDown) {
                            return;
                        }

                        var dest = game.player.pos.clone();
                        dest.x -= moveDist;
                        game.player.moveTo(dest);

                        isMoveKeyDown = true;
                    }
                    break;
                case 83: // s
                    {
                        if (isMoveKeyDown) {
                            return;
                        }

                        var dest = game.player.pos.clone();
                        dest.y -= moveDist;
                        game.player.moveTo(dest);

                        isMoveKeyDown = true;
                    }
                    break;
                case 68: // d
                    {
                        if (isMoveKeyDown) {
                            return;
                        }

                        var dest = game.player.pos.clone();
                        dest.x += moveDist;
                        game.player.moveTo(dest);

                        isMoveKeyDown = true;
                    }
                    break;
                case 87: // w
                    {
                        if (isMoveKeyDown) {
                            return;
                        }

                        var dest = game.player.pos.clone();
                        dest.y += moveDist;
                        game.player.moveTo(dest);

                        isMoveKeyDown = true;
                    }
                    break;
            }
        });
        jQuery(document).keyup(function (e) {
            switch (e.keyCode) {
                case 65: // a
                case 83: // s
                case 68: // d
                case 87: // w
                    {
                        isMoveKeyDown = false;
                    }
                    break;
            }
        });
    };
};