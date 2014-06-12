var fs = require('fs');
var exec = require('child_process').exec;

// Generate binding.gyp
var cppRegex = new RegExp(/^.*\.cpp$/);
var files = fs.readdirSync(__dirname);

var binding = {};
binding.targets = [];
binding.targets[0] = {};
binding.targets[0].target_name = "server";
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

console.log("Postbuild success");