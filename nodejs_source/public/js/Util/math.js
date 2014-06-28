var Vector3 = function () {
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
};