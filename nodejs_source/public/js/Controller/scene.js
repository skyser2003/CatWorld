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
        jQuery(document).keydown(function (e) {
            switch (e.keyCode) {
                case 65: // a
                    {
                        var dest = game.player.pos.clone();
                        dest.x -= moveDist;
                        game.player.moveTo(dest);
                    }
                    break;
                case 83: // s
                    {
                        var dest = game.player.pos.clone();
                        dest.y -= moveDist;
                        game.player.moveTo(dest);
                    }
                    break;
                case 68: // d
                    {
                        var dest = game.player.pos.clone();
                        dest.x += moveDist;
                        game.player.moveTo(dest);
                    }
                    break;
                case 87: // w
                    {
                        var dest = game.player.pos.clone();
                        dest.y += moveDist;
                        game.player.moveTo(dest);
                    }
                    break;
            }
        });
    };
};