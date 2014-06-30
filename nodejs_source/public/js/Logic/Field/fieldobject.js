var FieldObject = function () {
    var self = this;

    this.pos = new Vector3(0, 0, 0);
    this.dest = new Vector3(0, 0, 0);
    this.moveSpeed = 0.5;

    this.fsmEnum = FieldObjectFSM.STATE_IDLE;
    this.fsm = new FieldObjectFSM_IDLE(this);

    this.moveTo = function (pos) {
        if (self.fsmEnum === FieldObjectFSM.STATE_MOVE) {
            return;
        }
        self.dest = pos;
        self.changeFSM("MOVE");
    }

    this.update = function (dt) {
        self.fsm.onUpdate(dt);
    };

    this.changeFSM = function (nextFSM) {
        self.fsm.onEnd();

        self.fsmEnum = FieldObjectFSM["STATE_" + nextFSM];
        self.fsm = eval("new FieldObjectFSM_" + nextFSM + "(self)");
        self.fsm.onBegin();
    };
};