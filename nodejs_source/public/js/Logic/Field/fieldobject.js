var FieldObject = function () {
    var self = this;

    this.pos = new Vector3(0, 0, 0);
    this.direction = new Vector3(0, 0, 0);
    this.speed = 0.0;

    this.fsmEnum = FieldObjectFSM.STATE_IDLE;
    this.fsm = new FieldObjectFSM_IDLE(this);

    this.moveTo = function (direction) {
        if (self.fsmEnum !== FieldObjectFSM.STATE_MOVE) {
            changeFSM("MOVE");
        }

        direction.normalize();

        self.direction.x = direction.x;
        self.direction.y = direction.y;
        self.direction.z = direction.z;
    }
    this.stop = function () {
        self.direction.x = 0;
        self.direction.y = 0;
        self.direction.z = 0;
    }

    this.update = function (dt) {
        self.fsm.onUpdate(dt);
    };

    var changeFSM = function (nextFSM) {
        self.fsm.onEnd();

        self.fsmEnum = FieldObjectFSM["STATE_" + nextFSM];
        self.fsm = eval("new FieldObjectFSM_" + nextFSM + "(self)");
        self.fsm.onBegin();
    };
};