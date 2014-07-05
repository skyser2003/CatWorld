var FieldObject = function () {
    var self = this;

    this.pos = new Vector3(0, 0, 0);
    this.velocity = new Vector3(0, 0, 0);

    this.fsmEnum = FieldObjectFSM.STATE_IDLE;
    this.fsm = new FieldObjectFSM_IDLE(this);

    this.moveTo = function (velocity) {
        if (self.fsmEnum !== FieldObjectFSM.STATE_MOVE) {
            changeFSM("MOVE");
        }
        self.velocity.x += velocity.x;
        self.velocity.y += velocity.y;
        self.velocity.z += velocity.z;
    }
    this.stop = function () {
        self.velocity.x = 0;
        self.velocity.y = 0;
        self.velocity.z = 0;
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