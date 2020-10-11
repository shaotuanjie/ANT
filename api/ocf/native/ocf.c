#include "../../common/native/ant_common.h"
#include "ocf_adapter.h"
#include "ocf_resource.h"

#include "iotjs_def.h"
#include "iotjs_uv_request.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

JS_FUNCTION(ocf_init) {
  init_ant_async_list();
  ocf_adapter_init();
  ocf_resource_init();
}

JS_FUNCTION(ocf_deinit) { destroy_ant_async_list(); }

jerry_value_t InitOCFNative() {
  // Initialize sub-objects of OCF API
  jerry_value_t ocfNative = jerry_create_object();
  InitOCFAdapterNative(ocfNative);
  InitOCFResourceNative(ocfNative);
  return ocfNative;
}