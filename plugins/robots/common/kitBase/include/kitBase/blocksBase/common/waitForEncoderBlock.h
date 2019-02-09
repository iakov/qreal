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

#include <kitBase/blocksBase/common/waitForSensorBlock.h>

namespace kitBase {
namespace robotModel {
namespace robotParts {
class EncoderSensor;
}
}

namespace blocksBase {
namespace common {

/// An interpreter`s implementation for "wait for the encoder" block.
class ROBOTS_KIT_BASE_EXPORT WaitForEncoderBlock : public WaitForSensorBlock
{
	Q_OBJECT

public:
	/// Constructor, takes current robot model as parameter.
	explicit WaitForEncoderBlock(robotModel::RobotModelInterface &robotModel);

private slots:
	/// Called when new data from encoder ready, checks it against "TachoLimit" property.
	void responseSlot(int reading);

private:
	robotModel::DeviceInfo device() const override;
};

}
}
}
