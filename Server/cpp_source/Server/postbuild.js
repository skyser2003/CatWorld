var fs = require('fs');
var exec = require('child_process').exec;

// Generate binding.gyp
var cppRegex = new RegExp(/^.*\.cpp$/);
var files = fs.readdirSync(__dirname);
var targetName = "server";

var binding = {};
binding.targets = [];
binding.targets[0] = {};
binding.targets[0].target_name = targetName;
binding.targets[0].sources = [];

for (var i in files)
{
    var file = files[i];
    if(cppRegex.test(file) === true)
    {
        binding.targets[0].sources.push(file);
    }
}

fs.writeFile("binding.gyp", JSON.stringify(binding));

// Activate node-gyp
exec("node-gyp configure build");

// Copy generated file to express server's node_modules
fs.createReadStream("build/Release/" + targetName + ".node").pipe(fs.createWriteStream("../../nodejs_source/node_modules/" + targetName + ".node"));

console.log("Postbuild success");