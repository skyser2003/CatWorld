var Vector3 = function () {
    var self = this;
    this.x = 0;
    this.y = 0;
    this.z = 0;

    switch(arguments.length)
    {
        case 1:
            {
                this.x = arguments[0];
            }
            break;
        case 2:
            {
                this.x = arguments[0];
                this.y = arguments[1];
            }
            break;
        case 3:
            {
                this.x = arguments[0];
                this.y = arguments[1];
                this.z = arguments[2];
            }
            break;
    }

    this.sub = function (target) {
        var ret = new Vector3();
        ret.x = self.x - target.x;
        ret.y = self.y - target.y;
        ret.z = self.z - target.z;

        return ret;
    };

    this.equal = function (target) {
        return self.x == target.x && self.y == target.y && self.z == target.z;
    };

    this.magnitude = function () {
        return Math.sqrt(Math.pow(self.x, 2) + Math.pow(self.y, 2) + Math.pow(self.z, 2));
    };

    this.clone = function () {
        var clone = new Vector3();
        clone.x = self.x;
        clone.y = self.y;
        clone.z = self.z;

        return clone;
    };
};