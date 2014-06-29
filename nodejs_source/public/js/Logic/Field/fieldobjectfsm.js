var FieldObjectFSM = {
    STATE_IDLE: 0,
    STATE_MOVE: 1
};

var FieldObjectFSM_IDLE = function (fieldObject) {
    this.onBegin = function () {
    };

    this.onUpdate = function (dt) {

    };

    this.onEnd = function () {

    };
};

var FieldObjectFSM_MOVE = function (fieldObject) {
    var self = this;

    self.moveDist = null;

    this.onBegin = function () {
        self.moveDist = fieldObject.dest.sub(fieldObject.pos);
    };

    this.onUpate = function (dt) {
        var moveDist = fieldObject.dest.sub(fieldObject.pos);
        var magnitude = moveDist.magnitude();

        var dx = Math.min(moveDist.x / magnitude * fieldObject.moveSpeed * dt / 1000, movDist.x);
        var dy = Math.min(moveDist.y / magnitude * fieldObject.moveSpeed * dt / 1000, moveDist.y);
        var dz = Math.min(moveDist.z / magnitude * fieldObject.moveSpeed * dt / 1000, moveDist.z);

        fieldObject.pos.x += dx;
        fieldObject.pos.y += dy;
        fieldObject.pos.z += dz;

        if (fieldObject.pos.equal(fieldObject.dest)) {
            fieldObject.changeFSM("IDLE");
        }
    };

    this.onEnd = function () {

    };
};