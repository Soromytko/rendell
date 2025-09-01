#pragma once
#include "init_types.h"

namespace rendell {
bool init(const Initer &initer);
void release();

NativeViewId registerNativeView(NativeView nativeView);
void unregisterNativeView(NativeViewId nativeViewId);
} // namespace rendell