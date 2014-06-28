jQuery(document).ready(function () {
    var game = new Game();
    game.init();

    // Init scene
    var scene = new THREE.Scene();
    var camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
    camera.position.x = 5;
    camera.position.y = -5;
    camera.position.z = 5;
    camera.up = new THREE.Vector3(-1, 1, 1);
    camera.lookAt(new THREE.Vector3(-1, 1, -1));

    var renderer = new THREE.WebGLRenderer();
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.domElement.id = "canvas";
    document.body.appendChild(renderer.domElement);

    // Init keyboard
    jQuery(document).keydown(function (e) {
        switch (e.keyCode) {
            case 65: // a
                {
                    --cube.position.x;
                    for (var i in edgeCubes) {
                        --edgeCubes[i].position.x;
                    }
                }
                break;
            case 83: // s
                {
                    --cube.position.y;
                    for (var i in edgeCubes) {
                        --edgeCubes[i].position.y;
                    }
                }
                break;
            case 68: // d
                {
                    ++cube.position.x;
                    for (var i in edgeCubes) {
                        ++edgeCubes[i].position.x;
                    }
                }
                break;
            case 87: // w
                {
                    ++cube.position.y;
                    for (var i in edgeCubes) {
                        ++edgeCubes[i].position.y;
                    }
                }
                break;
        }
    });

    // Init test object
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

        //cube.rotation.x += 0.1;
        //cube.rotation.y += 0.1;

        for (var i in edgeCubes) {
            //edgeCubes[i].rotation.x += 0.1;
            //edgeCubes[i].rotation.y += 0.1;
        }

        renderer.render(scene, camera);
    };

    render();
});