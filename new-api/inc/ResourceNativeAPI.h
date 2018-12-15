/* Copyright (c) 2017-2018 SKKU ESLAB, and contributors. All rights reserved.
 *
 * Contributor: Gyeonghwan Hong<redcarrottt@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __RESOURCE_API_H__
#define __RESOURCE_API_H__

#include <map>

#include <node.h>
#include <node_object_wrap.h>
#include <uv.h>

#include "BaseMessage.h"
#include "NativeResourceAPI.h"

using namespace v8;

class ResourceResponseCallbackAsync {
public:
  ResourceResponseCallbackAsync(uv_async_cb nativeFunction,
                           Local<Function> jsFunction) {
    this->mNativeFunction = nativeFunction;
    Isolate *isolate = Isolate::GetCurrent();
    this->mJSFunction.Reset(isolate, jsFunction);

    uv_loop_t *loop = uv_default_loop();
    uv_async_init(loop, &this->mUVAsync, this->mNativeFunction);
  }

  void callAsync() { uv_async_send(&this->mUVAsync); }

  void destroy() { this->mJSFunction.Reset(); }

  Local<Function> getJSFunction(Isolate *isolate) {
    Local<Function> localJsFunction =
        Local<Function>::New(isolate, this->mJSFunction);
    return localJsFunction;
  }

private:
  uv_async_t mUVAsync;
  uv_async_cb mNativeFunction;
  Persistent<Function> mJSFunction;
};

class ResourceCallbackManager {
public:
  static ResourceCallbackManager *singleton() {
    if (sSingleton == NULL) {
      sSingleton = new ResourceCallbackManager();
    }
    return sSingleton;
  }
  void addJSCallback(int requestId, Local<Function> responseJSCallback);
  void removeJSCallback(int requestId);
  ResourceResponseCallbackAsync* getCallback(int requestId);

  static void onResourceResponseDbusThread(BaseMessage *responseMessage);
  static void onResourceResponseMainThread(uv_async_t *handle);

  void addSubscription(std::string targetUri, int requestMessageId);
  int removeSubscription(std::string targetUri);

private:
  static ResourceCallbackManager *sSingleton;
  ResourceCallbackManager() {}
  ~ResourceCallbackManager() {}
  std::map<int, ResourceResponseCallbackAsync *> mResponseCallbacks;
  std::map<std::string, int> mSubscriptionList;
  std::vector<BaseMessage *> mIncomingResponseList;
};

// How to create this object: antAPI.resource();
class ResourceNativeAPI : public node::ObjectWrap {
public:
  // Prototype Intializer
  static void InitPrototype(Isolate *isolate);

  // Constructor 1
  static void NewInstance(const FunctionCallbackInfo<Value> &args);

protected:
  ResourceNativeAPI() {}
  ~ResourceNativeAPI() {}

  // Static Constructor
  static Persistent<Function> sConstructor;

  // Constructor 2
  static void New(const FunctionCallbackInfo<Value> &args);

  // Member functions
  static void registerResource(const FunctionCallbackInfo<Value> &args);
  static void findLocalResource(const FunctionCallbackInfo<Value> &args);

  static void sendPost(const FunctionCallbackInfo<Value> &args);
  static void sendGet(const FunctionCallbackInfo<Value> &args);
  static void sendPut(const FunctionCallbackInfo<Value> &args);
  static void sendDelete(const FunctionCallbackInfo<Value> &args);

  static void sendDiscover(const FunctionCallbackInfo<Value> &args);
  static void sendSubscribe(const FunctionCallbackInfo<Value> &args);
  static void sendUnsubscribe(const FunctionCallbackInfo<Value> &args);

  static void sendRequest(ResourceOperationType::Value opType,
                          const FunctionCallbackInfo<Value> &args);
};

#endif // !defined(__RESOURCE_API_H__)