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
        var pm = game.pm;

        var moveTo = function (x, y, z) {
            if (isMoveKeyDown) {
                return;
            }

            var dest = game.player.pos.clone();
            dest.x += x;
            dest.y += y;
            dest.z += z;
            game.player.moveTo(dest);

            var pks = pm.createInstance("MOVE");
            pks.x = x;
            pks.y = y;
            pks.z = z;
            pm.send(pks);

            isMoveKeyDown = true;
        };

        jQuery(document).keydown(function (e) {
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
            switch (e.keyCode) {
                case 65: // a
                case 83: // s
                case 68: // d
                case 87: // w
                    {
                        var pks = pm.createInstance("STOP");
                        pm.send(pks);

                        isMoveKeyDown = false;
                    }
                    break;
            }
        });
    };
};