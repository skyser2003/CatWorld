var fs = require('fs');
var exec = require('child_process').exec;

function addInclude(binding, path) {
    binding.targets[0].include_dirs.push(path);
}

function addLib(arr, path) {
    binding.targets[0].libraries.push(path);
}

// Config
var mode = "Debug";

// Generate binding.gyp
var sourceRegex = new RegExp(/^.*\.(cpp|pb\.cc|c)$/);
var targetName = "gameServer";

var binding = {};
binding.targets = [];
binding.targets[0] = {};
binding.targets[0].target_name = targetName;
binding.targets[0].sources = [];

binding.targets[0].include_dirs = [];
binding.targets[0].libraries = [];

addInclude(binding, __dirname + "\\..\\External\\protobuf-2.5.0\\src");
addInclude(binding, __dirname + "\\..\\External\\protobuf-2.5.0\\gtest\\include");
addInclude(binding, __dirname + "\\..\\ServerLib");
addInclude(binding, __dirname + "\\..\\Packet");
addInclude(binding, __dirname + "\\..\\SQLite");
addInclude(binding, __dirname + "\\..\\GLM");

var libprotobufLibName =  __dirname + "\\..\\External\\libprotobuf_";
if (mode == "Debug") {
    libprotobufLibName += "Debug.lib";
}
else if (mode == "Release") {
    libprotobufLibName += "Release.lib";
}

addLib(binding, libprotobufLibName);

var directories = [];
var dirLevels = [];
var curLevel = 0;
dirLevels[curLevel] = [__dirname + "\\.."];

while (true) {
    for (var i in dirLevels[curLevel]) {
        var files = fs.readdirSync(dirLevels[curLevel][i]);
        for (var j in files) {
            if (files[j] == "protobuf-2.5.0") {
                console.log("boo");
                continue;
            }
            var file = dirLevels[curLevel][i] + "\\" + files[j];
            var isDir = fs.lstatSync(file).isDirectory();

            if (isDir == true) {
                if (dirLevels[curLevel + 1] === undefined) {
                    dirLevels[curLevel + 1] = [];
                }

                dirLevels[curLevel + 1].push(file);
                directories.push(file);
            }
        }
    }

    if (dirLevels[curLevel + 1] === undefined) {
        break;
    }
    else {
        ++curLevel;
    }
}

for (var i in directories) {
    var files = fs.readdirSync(directories[i]);

    for (var j in files) {
        var file = files[j];
        if (sourceRegex.test(file) === true) {
            console.log(file);
            binding.targets[0].sources.push(directories[i] + "\\" + file);
        }
    }
}

fs.writeFile("binding.gyp", JSON.stringify(binding));

// Activate node-gyp
var gypString = "node-gyp configure build --arch=x64 --msvs_version=2013";
if (mode == "Debug") {
    gypString += " --debug";
}

exec(gypString, function (err, stdout, stderr) {
    console.log(err);
    // Copy generated file to express server's node_modules
    fs.createReadStream("build/" + mode + "/" + targetName + ".node").pipe(fs.createWriteStream("../../nodejs_source/node_modules/" + targetName + ".node"));
    fs.createReadStream("build/" + mode + "/" + targetName + ".pdb").pipe(fs.createWriteStream("../../nodejs_source/node_modules/" + targetName + ".pdb"));

    console.log("Postbuild success");
});