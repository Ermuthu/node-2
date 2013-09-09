// Copyright (c) 2012 Intel Corp
// Copyright (c) 2012 The Chromium Authors
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell co
// pies of the Software, and to permit persons to whom the Software is furnished
//  to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in al
// l copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IM
// PLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNES
// S FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
//  OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WH
// ETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "node.h"
#include "object_life_monitor.h"

namespace nw {

static v8::Handle<v8::Value> GetHiddenValue(const v8::Arguments& args) {
  return args[0]->ToObject()->GetHiddenValue(args[1]->ToString());
}

static v8::Handle<v8::Value> SetHiddenValue(const v8::Arguments& args) {
  args[0]->ToObject()->SetHiddenValue(args[1]->ToString(), args[2]);
  return v8::Undefined();
}

static v8::Handle<v8::Value> GetConstructorName(const v8::Arguments& args) {
  return args[0]->ToObject()->GetConstructorName();
}

static v8::Handle<v8::Value> SetDestructor(const v8::Arguments& args) {
  nw::ObjectLifeMonitor::BindTo(args[0]->ToObject(), args[1]);
  return v8::Undefined();
}

static v8::Handle<v8::Value> GetCreationContext(const v8::Arguments& args) {
  v8::HandleScope handle_scope;
  v8::Local<v8::Context> creation_context = args[0]->ToObject()->
      CreationContext();

  return handle_scope.Close(creation_context->Global());
}

static v8::Handle<v8::Value> GetObjectHash(const v8::Arguments& args) {
  v8::HandleScope handle_scope;
  return handle_scope.Close(v8::Integer::New(
      args[0]->ToObject()->GetIdentityHash()));
}

void InitializeV8Util(v8::Handle<v8::Object> target) {
  NODE_SET_METHOD(target, "getHiddenValue", GetHiddenValue);
  NODE_SET_METHOD(target, "setHiddenValue", SetHiddenValue);
  NODE_SET_METHOD(target, "getConstructorName", GetConstructorName);
  NODE_SET_METHOD(target, "setDestructor", SetDestructor);
  NODE_SET_METHOD(target, "getCreationContext", GetCreationContext);
  NODE_SET_METHOD(target, "getObjectHash", GetObjectHash);
}

}  // namespace nw

NODE_MODULE(node_v8_util, nw::InitializeV8Util)
