var fs = require('fs');
var exec = require('child_process').exec;

// Generate proto files
var protoc = __dirname + "\\..\\External\\protoc.exe";
var protoRegex = new RegExp(/^.*\.proto$/);
var files = fs.readdirSync(__dirname);

var protoFiles = [];

for (var i in files) {
    var file = files[i];
    if (protoRegex.test(file) === true) {
        protoFiles.push(file);
    }
}

var execString = protoc +
    " --cpp_out=\"" + __dirname + "\\Autogen\"" +
    " -I" + __dirname;
for (var i in protoFiles) {
    execString += " " + __dirname + "\\" + protoFiles[i];
}

console.log(execString);

exec(execString);