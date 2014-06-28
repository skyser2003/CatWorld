var PacketManager = function()
{
    var self = this;

    var socket = io();

    var ProtoBuf = dcodeIO.ProtoBuf;
    var msgBuilder = ProtoBuf.loadProtoFile("proto/Message.proto");
    var structBuilder = ProtoBuf.loadProtoFile("proto/Struct.proto");

    var Packet = msgBuilder.build("Packet");

    // Init message - struct dictionary
    var strTable = [];
    var msgTable = {};
    for (var msgName in Packet.Message) {
        var value = Packet.Message[msgName];
        strTable[value] = structBuilder.build(msgName);
        msgTable[msgName] = value;
    }

    // Send
    this.send = function (pks) {
        var pksName = pks.toString().substr(1, pks.toString().length - 1);
        var msg = msgtable[pksName];

        var packet = { msg: "", data: "" };
        packet.msg = msg;
        packet.data = pks.toHex();

        socket.emit("packet", packet);
    };

    // Receive
    this.setReceiveFunc = function (callback) {
        this.receiveCallback = callback;
    };

    socket.on("packet", function (data) {
        var msg = data.msg;
        var hex = data.data;

        var struct = strTable[msg];
        var decoded = struct.decodeHex(hex);

        self.receiveCallback(decoded);
    });

    // Generate pks
    this.getInstance = function (pksName) {
        var msg = msgTable[pksName];
        if (msg === undefined) {
            return null;
        }

        var struct = strTable[msg];
        return new struct();
    };
}