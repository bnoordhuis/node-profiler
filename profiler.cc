#include <v8.h>
#include <node.h>

using namespace v8;
using namespace node;

namespace {

struct ProfilerArguments {
  const int flags;
  const int tag;

  inline ProfilerArguments(const Arguments& args)
    : flags (args.Length() >= 1 ? args[0]->Uint32Value() : -1)
    , tag   (args.Length() >= 2 ? args[1]->Uint32Value() : 0)
  {
  }
};

static Handle<Value> GC(const Arguments& args) {
  HandleScope scope;
  while (!V8::IdleNotification());
  return Undefined();
}

static Handle<Value> Resume(const Arguments& args) {
  HandleScope scope;
  const ProfilerArguments pa(args);
  V8::ResumeProfilerEx(pa.flags, pa.tag);
  return Undefined();
}

static Handle<Value> Pause(const Arguments& args) {
  HandleScope scope;
  const ProfilerArguments pa(args);
  V8::PauseProfilerEx(pa.flags, pa.tag);
  return Undefined();
}

static Handle<Value> HeapSize(Local<String> property, const AccessorInfo& info) {
  return ThrowException(Exception::Error(String::New("profiler.heapSize is deprecated, use process.memoryUsage().heapTotal instead.")));
}

static Handle<Value> HeapUsed(Local<String> property, const AccessorInfo& info) {
  return ThrowException(Exception::Error(String::New("profiler.heapUsed is deprecated, use process.memoryUsage().heapUsed instead.")));
}

extern "C" void init(Handle<Object> target) {
  HandleScope scope;

  target->Set(String::New("gc"), FunctionTemplate::New(GC)->GetFunction());
  target->Set(String::New("pause"), FunctionTemplate::New(Pause)->GetFunction());
  target->Set(String::New("resume"), FunctionTemplate::New(Resume)->GetFunction());

  target->SetAccessor(String::New("heapSize"), HeapSize, 0, Undefined(), DEFAULT, DontEnum);
  target->SetAccessor(String::New("heapUsed"), HeapUsed, 0, Undefined(), DEFAULT, DontEnum);

  const PropertyAttribute attribs = (PropertyAttribute) (ReadOnly | DontDelete);
  target->Set(String::New("CPU"), Integer::New(PROFILER_MODULE_CPU), attribs);
  target->Set(String::New("HEAP_STATS"), Integer::New(PROFILER_MODULE_HEAP_STATS), attribs);
  target->Set(String::New("HEAP_SNAPSHOT"), Integer::New(PROFILER_MODULE_HEAP_SNAPSHOT), attribs);
  target->Set(String::New("JS_CONSTRUCTORS"), Integer::New(PROFILER_MODULE_JS_CONSTRUCTORS), attribs);
}

}
