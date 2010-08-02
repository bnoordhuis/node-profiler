# node-profiler

Access the V8 profiler from node.js - http://nodejs.org/

## A word of advice

This module is for people who need run-time control over V8's profiler. If all you want
is wholesale profiling, you don't need it. Simply start `node` with profiling enabled:

	node --prof application.js

Read on, however, if you want to wield the arcane powers this module grants.

## Compiling

When the stars are right - i.e. when `node-waf` is not broken:

	node-waf

On every other day of the aeon:

	export NODE_PATH=/path/to/nodejs
	g++ -I$NODE_PATH/include/node -O2 -fPIC -shared -Wall -ansi -o profiler.node profiler.cc

Yes, it sucks. But not as much as an Elder God trying to extract your brains through your nose.

## Usage

In most cases you will want to start your application with the profiler in suspended animation.

	node --prof --prof_lazy application.js

And inside your application:

	var profiler = require('./profiler');
	//
	// <here be code you don't want to profile>
	//
	profiler.resume();
	//
	// <performance critical code here>
	//
	profiler.pause();

This results in a v8.log being written to the current directory that you can process with the V8 profiling tools.

See http://code.google.com/p/v8/wiki/V8Profiler for more information.

## Advanced usage

By default, everything that can be profiled, is: heap and CPU usage, and JS object construction.
This can be customized by passing a bitwise OR of the following flags to resume() and pause():

	profiler.CPU
	profiler.HEAP_STATS
	profiler.HEAP_SNAPSHOT
	profiler.JS_CONSTRUCTORS

Example:

	profiler.resume(profiler.CPU | profiler.JS_CONSTRUCTORS);
	//
	// <performance critical code here>
	//
	profiler.pause(profiler.CPU | profiler.JS_CONSTRUCTORS);

You can optionally pass a tag to uniquely mark a section in the v8.log:

	profiler.resume(profiler.CPU, 42);
	//
	// <performance critical code here>
	//
	profiler.pause(profiler.CPU, 42);

Last but not least, the `profiler` object exposes the properties `heapSize` and `heapUsed` that
reflect the total size of V8's heap and the part of the heap that is actually in use, respectively.

	var profiler = require('./profiler'), puts = require('sys').puts;
	puts('Heap size: ' + profiler.heapSize);
	puts('Heap used: ' + profiler.heapUsed);

