#include "v8.h"
#include "node.h"

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

void Init(Handle<Object> target) {
  HandleScope scope;

  target->Set(String::New("gc"),
              FunctionTemplate::New(GC)->GetFunction());

  target->Set(String::New("pause"),
              FunctionTemplate::New(Pause)->GetFunction());

  target->Set(String::New("resume"),
              FunctionTemplate::New(Resume)->GetFunction());

  // mimic browser API
  Local<Object> global = Context::GetCurrent()->Global();
  Local<Value> console_v = global->Get(String::New("console"));
  if (console_v.IsEmpty() || !console_v->IsObject()) return;
  Local<Object> console = console_v->ToObject();

  console->Set(String::New("profile"),
               FunctionTemplate::New(Resume)->GetFunction());

  console->Set(String::New("profileEnd"),
               FunctionTemplate::New(Pause)->GetFunction());
}

NODE_MODULE(profiler, Init)

}
