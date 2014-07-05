var FieldObjectFSM = {
    STATE_IDLE: 0,
    STATE_MOVE: 1
};

var FieldObjectFSM_IDLE = function (owner) {
    this.onBegin = function () {
    };

    this.onUpdate = function (dt) {

    };

    this.onEnd = function () {

    };
};

var FieldObjectFSM_MOVE = function (owner) {
    var self = this;

    this.onBegin = function () {
    };

    this.onUpdate = function (dt) {
        owner.pos.x += owner.velocity.x * dt / 1000;
        owner.pos.y += owner.velocity.y * dt / 1000;
        owner.pos.z += owner.velocity.z * dt / 1000;
    };

    this.onEnd = function () {

    };
};