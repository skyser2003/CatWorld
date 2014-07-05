var Game = function () {
    var self = this;

    // Packet
    pm = new PacketManager();

    // Graphics
    this.canvasID = "canvas";
    var scene;
    var camera;
    var renderer;

    // Logic
    this.player = new FieldObject();

    this.init = function () {
        // Init packet
        pm.setReceiveFunc(onReceivePacket);

        var pks = pm.createInstance("LOGIN");
        pks.id = "skyser2003";
        pks.pw = "0000";
        pm.send(pks);

        // Init renderer
        initRenderer();
    };

    this.moveTo = function (x, y, z) {
        var velocity = new Vector3();
        velocity.x = x;
        velocity.y = y;
        velocity.z = z;
        self.player.moveTo(velocity);

        var pks = pm.createInstance("MOVE");
        pks.x = x;
        pks.y = y;
        pks.z = z;
        pm.send(pks);
    };

    this.moveStop = function () {
        self.player.stop();
        var pks = pm.createInstance("STOP");
        pm.send(pks);
    };

    this.update = function (dt) {
        self.player.update(dt);
    }

    var onReceivePacket = function (pksName, pks) {
        var handlerFunc = eval("onPacket_" + pksName);
        if (handlerFunc !== undefined) {
            handlerFunc(pks);
        }
    };

    // Packet receiver
    var onPacket_LOGIN_RESULT = function (pks) {
        console.log(pks.result);
    };

    var onPacket_POSITION = function (pks) {
        self.player.pos.x = pks.x;
        self.player.pos.y = pks.y;
        self.player.pos.z = pks.z;
    };

    var initRenderer = function () {
        // Remove existing canvas
        var canvasHTML = jQuery("#" + self.canvasID);
        if (canvasHTML !== undefined) {
            canvasHTML.remove();
        }

        // Scene
        scene = new THREE.Scene();

        // Camera
        camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
        camera.position.x = 5;
        camera.position.y = -5;
        camera.position.z = 5;
        camera.up = new THREE.Vector3(-1, 1, 1);
        camera.lookAt(new THREE.Vector3(-1, 1, -1));

        // Renderer
        renderer = new THREE.WebGLRenderer();
        renderer.setSize(window.innerWidth, window.innerHeight);
        renderer.domElement.id = "canvas";
        document.body.appendChild(renderer.domElement);

        // TEMP
        var geometry = new THREE.BoxGeometry(1, 1, 1);
        var material = new THREE.MeshBasicMaterial({ color: 0x00ff00 });
        var cube = new THREE.Mesh(geometry, material);
        scene.add(cube);

        var dist = 0.5;

        var edgePositions = [
            [
                [0, dist, dist],
                [0, dist, -dist],
                [0, -dist, -dist],
                [0, -dist, dist]
            ],
            [
                [dist, 0, dist],
                [dist, 0, -dist],
                [-dist, 0, -dist],
                [-dist, 0, dist]
            ],
            [
                [dist, dist, 0],
                [dist, -dist, 0],
                [-dist, -dist, 0],
                [-dist, dist, 0]
            ]
        ]
        var edges = [
            [1, 0.1, 0.1],
            [0.1, 1, 0.1],
            [0.1, 0.1, 1]
        ];
        var edgeCubes = [];

        for (var i in edges) {
            var edge = edges[i];
            var edgeGeometry = new THREE.BoxGeometry(edge[0], edge[1], edge[2]);
            var edgeMaterial = new THREE.MeshBasicMaterial({ color: 0xFFFFFF });

            for (var j in edgePositions[i]) {
                var edgeLine = new THREE.Mesh(edgeGeometry, edgeMaterial);

                edgeLine.position.x = edgePositions[i][j][0];
                edgeLine.position.y = edgePositions[i][j][1];
                edgeLine.position.z = edgePositions[i][j][2];

                scene.add(edgeLine);
                edgeCubes.push(edgeLine);
            }
        }

        var render = function () {
            requestAnimationFrame(render);
            cube.position.x = self.player.pos.x;
            cube.position.y = self.player.pos.y;
            cube.position.z = self.player.pos.z;

            renderer.render(scene, camera);
        };

        render();
    };
};