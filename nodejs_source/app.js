var express = require('express');
var path = require('path');
var favicon = require('static-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');

var debug = require('debug')('nodejs_source');
var ProtoBuf = require('protobufjs');
var gameServer = require('gameServer');

var routes = require('./routes/index');
var users = require('./routes/users');

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

app.use(favicon());
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded());
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', routes);
app.use('/users', users);

/// catch 404 and forward to error handler
app.use(function(req, res, next) {
    var err = new Error('Not Found');
    err.status = 404;
    next(err);
});

/// error handlers

// development error handler
// will print stacktrace
if (app.get('env') === 'development') {
    app.use(function(err, req, res, next) {
        res.status(err.status || 500);
        res.render('error', {
            message: err.message,
            error: err
        });
    });
}

// production error handler
// no stacktraces leaked to user
app.use(function(err, req, res, next) {
    res.status(err.status || 500);
    res.render('error', {
        message: err.message,
        error: {}
    });
});


// Run
app.set('port', process.env.PORT || 3000);

var server = app.listen(app.get('port'), function () {
    debug('Express server listening on port ' + server.address().port);
});

var io = require('socket.io')(server);
var cppServer = new gameServer.Server();

cppServer.onSendMsg(function (msg, pks) {
    var struct = table[msg];
    var encoded = struct.encodeHex(pks);
    console.log(encoded);
    socket.emit({"packet" : encoded});
});

var msgBuilder = ProtoBuf.loadProtoFile(__dirname + "/public/proto/Message.proto");
var structBuilder = ProtoBuf.loadProtoFile(__dirname + "/public/proto/Struct.proto");

var Packet = msgBuilder.build("Packet");
var LOGIN = structBuilder.build("LOGIN");

var table = [];

// Init message - struct dictionary
for (var msgName in Packet.Message) {
    var value = Packet.Message[msgName];

    table[value] = structBuilder.build(msgName);
}

// Socket.io
io.on('connection', function (socket) {
    socket.on('packet', function (data) {
        var obj = JSON.parse(data);
        var msg = obj.msg;

        var struct = table[msg];
        var decoded = struct.decodeHex(obj.data);
        var newMsg = new struct(decoded.toRaw());

        cppServer.parse(msg, newMsg.toBuffer());
    });
});