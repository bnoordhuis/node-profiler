# node-profiler

Access the V8 profiler from node.js - http://nodejs.org/

## A word of advice

This module is for people who need fine-grained run-time control over the V8
profiler. You don't need it if all you want is wholesale profiling, simply
start `node` with profiling enabled:

    node --prof application.js

Read on, however, if you want to wield the arcane powers this module grants.

## Compiling

Easy as pie. To build from source:

    node-gyp configure build install

Or, if you have `npm` installed:

    npm install profiler

## Usage

In most cases you will want to start your application with the profiler in
suspended animation.

    node --prof --prof_lazy --log application.js

And inside your application:

    var profiler = require('profiler');
    //
    // <here be code you don't want to profile>
    //
    profiler.resume();
    //
    // <performance critical code here>
    //
    profiler.pause();

This results in a v8.log being written to the current directory that you can
process with the bundled `nprof` tool. Run `sh tools/build-nprof` to build it.

## Advanced usage

You will sometimes want to run the garbage collector before profiling
a performance critical section of code. Here is how you do it:

    $ cat application.js
    if (typeof gc === 'function') gc();
    profiler.resume();
    // ...
    $ node --prof --prof_lazy --log --expose-gc application.js
