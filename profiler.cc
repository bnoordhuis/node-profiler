#include <v8.h>
#include <node.h>

using namespace v8;
using namespace node;

namespace {

Handle<Value> GC(const Arguments& args) {
  while (!V8::IdleNotification());
  return Undefined();
}

Handle<Value> Resume(const Arguments& args) {
  V8::ResumeProfiler();
  return Undefined();
}

Handle<Value> Pause(const Arguments& args) {
  V8::PauseProfiler();
  return Undefined();
}

extern "C" void init(Handle<Object> target) {
  HandleScope scope;
  target->Set(String::New("gc"), FunctionTemplate::New(GC)->GetFunction());
  target->Set(String::New("pause"), FunctionTemplate::New(Pause)->GetFunction());
  target->Set(String::New("resume"), FunctionTemplate::New(Resume)->GetFunction());
}

}
