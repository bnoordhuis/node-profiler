#!/usr/bin/env node

function quit(status) {
  process.exit(status || 0);
}

function print(s) {
  console.log('%s', s);
}

function read(fileName) {
  return require('fs').readFileSync(fileName, 'utf8');
}

var readline = (function() {
  // find first non-option, use as log file to read, default to v8.log
  var args = process.argv.slice(2).concat(['v8.log']).filter(function(arg) {
    return !~arg.indexOf('--');
  });
  var i = 0, lines = read(args[0]).split("\n");
  return function() {
    return lines[i++];
  };
})();

var arguments = process.argv.slice(2);
