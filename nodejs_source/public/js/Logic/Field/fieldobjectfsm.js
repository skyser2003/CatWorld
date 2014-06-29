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

    this.onUpdate = function (dt) {
        if (fieldObject.pos.equal(fieldObject.dest)) {
            fieldObject.changeFSM("IDLE");
            return;
        }

        var moveDist = fieldObject.dest.sub(fieldObject.pos);
        var magnitude = moveDist.magnitude();

        var signX = moveDist.x >= 0 ? 1 : -1;
        var signY = moveDist.y >= 0 ? 1 : -1;
        var signZ = moveDist.z >= 0 ? 1 : -1;

        var absX = Math.abs(moveDist.x);
        var absY = Math.abs(moveDist.y);
        var absZ = Math.abs(moveDist.z);

        var dx = Math.min(absX / magnitude * fieldObject.moveSpeed * dt / 1000, absX);
        var dy = Math.min(absY / magnitude * fieldObject.moveSpeed * dt / 1000, absY);
        var dz = Math.min(absZ / magnitude * fieldObject.moveSpeed * dt / 1000, absZ);

        fieldObject.pos.x += dx * signX;
        fieldObject.pos.y += dy * signY;
        fieldObject.pos.z += dz * signZ;
    };

    this.onEnd = function () {

    };
};