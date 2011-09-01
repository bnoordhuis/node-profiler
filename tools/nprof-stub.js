#!/usr/bin/env node

LOG_FNAME = 'v8.log';

function print(s) {
  console.log('%s', s);
}

function read(fileName) {
  return require('fs').readFileSync(fileName, 'utf8');
}

var readline = (function() {
  var i = 0, lines = read(LOG_FNAME).split("\n");
  return function() {
    return lines[i++];
  };
})();

var arguments = process.argv.slice(2);
