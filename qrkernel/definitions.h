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

#include "ids.h"
#include "roles.h"

namespace qReal {

/// Separator used in situations where there is need to form path consisting of multiple Ids.
const char ID_PATH_DIVIDER = '#';

/// MIME type for drag-and-drop operations inside QReal
const QString DEFAULT_MIME_TYPE = "application/x-real-uml-data";

#ifndef qUtf8Printable
# define qUtf8Printable(string) QString(string).toUtf8().constData()
#endif

}
