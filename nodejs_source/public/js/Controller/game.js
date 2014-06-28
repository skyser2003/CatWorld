var Game = function () {
    var self = this;
    var pm = new PacketManager();

    this.player = new FieldObject();

    this.init() = function () {
    this.init = function () {
        pm.setReceiveFunc(onReceivePacket);
        initControl();
    };

    var initControl = function () {
        jQuery(document).keydown(function (e) {
            switch (e.keyCode) {
                case 65: // a
                    {
                        player.pos.x -= 0.1;;
                    }
                    break;
                case 83: // s
                    {
                        player.pos.y -= 0.1;;
                    }
                    break;
                case 68: // d
                    {
                        player.pos.x += 0.1;;
                    }
                    break;
                case 87: // w
                    {
                        player.pos.y += 0.1;;
                    }
                    break;
            }
        });
    };

    var onReceivePacket = function (pksName, pks) {
        var handlerFunc = eval("onPacket_" + pksName);
        if (handlerFunc !== undefined) {
            handlerFunc(pks);
        }
    };
};