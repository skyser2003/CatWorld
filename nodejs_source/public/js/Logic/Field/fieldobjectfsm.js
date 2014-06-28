var FieldObjectFSM = {
    STATE_IDLE: 0,
    STATE_MOVE: 1
};

var FieldObjectFSM_IDLE = function (fieldObject) {
    this.fieldObject = fieldObject;

    this.onBegin = function () {
    };

    this.onUpdate = function () {

    };

    this.onEnd = function () {

    };
};

var FieldObjectFSM_MOVE = function (fieldObject) {
    this.fieldObject = fieldObject;

    this.onBegin = function () {

    };

    this.onUpate = function () {

    };

    this.onEnd = function () {

    };
};