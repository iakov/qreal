/* Copyright 2007-2015 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#pragma once

#include "qrutils/utilsDeclSpec.h"

namespace utils {

/// On-screen control api keyboard
class QRUTILS_EXPORT VirtualKeyboard
{
public:
	/// Shows on-screen keyboard. Implementation is different for each platform.
	/// @warning Currently works only in windows 8
	static void show();

private:
	static void showWindows8Keyboard();
};

}
