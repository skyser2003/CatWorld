var fs = require('fs');
var exec = require('child_process').exec;

function addInclude(binding, path) {
    binding.targets[0].include_dirs.push(path);
}

function addLib(arr, path) {
    binding.targets[0].libraries.push(path);
}

// Generate binding.gyp
var cppRegex = new RegExp(/^.*\.(cpp|pb\.cc)$/);
var targetName = "server";

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

addLib(binding, __dirname + "\\..\\External\\libprotobuf_Release.lib");

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
        if (cppRegex.test(file) === true) {
            console.log(file);
            binding.targets[0].sources.push(directories[i] + "\\" + file);
        }
    }
}

fs.writeFile("binding.gyp", JSON.stringify(binding));

// Activate node-gyp
exec("node-gyp configure build --arch=x64 --msvs_version=2013");

// Copy generated file to express server's node_modules
fs.createReadStream("build/Release/" + targetName + ".node").pipe(fs.createWriteStream("../../nodejs_source/node_modules/" + targetName + ".node"));

console.log("Postbuild success");