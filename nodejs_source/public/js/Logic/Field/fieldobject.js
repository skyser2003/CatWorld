var FieldObject = function () {
    this.pos = new Vector3(0, 0, 0);
    this.dest = new Vector3(0, 0, 0);

    this.fsmEnum = FieldObjectFSM.STATE_IDLE;
    this.fsm = new FieldObjectFSM_IDLE(this);
};