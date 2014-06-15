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

if (fs.existsSync("Autogen") == false) {
    fs.mkdirSync("Autogen");
}

var execString = protoc +
    " --cpp_out=\"" + __dirname + "\\Autogen\"" +
    " -I" + __dirname;
for (var i in protoFiles) {
    execString += " " + __dirname + "\\" + protoFiles[i];
}

console.log(execString);

exec(execString);

// Copy .proto files to nodejs source folder
if (fs.existsSync("../../nodejs_source/public/proto/") == false) {
    fs.mkdirSync("../../nodejs_source/public/proto/");
}

for (var i in protoFiles) {
    var fullPath = __dirname + "\\" + protoFiles[i];
    fs.createReadStream(fullPath).pipe(fs.createWriteStream("../../nodejs_source/public/proto/" + protoFiles[i]));
}

console.log("Packet project prebuild success!");