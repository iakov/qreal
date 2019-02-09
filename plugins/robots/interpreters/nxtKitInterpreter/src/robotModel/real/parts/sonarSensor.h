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

#include <kitBase/robotModel/robotParts/rangeSensor.h>
#include <nxtKit/communication/i2cCommunicator.h>

#include "nxtInputDevice.h"

namespace nxt {
namespace robotModel {
namespace real {
namespace parts {

class SonarSensor : public kitBase::robotModel::robotParts::RangeSensor
{
	Q_OBJECT
	Q_CLASSINFO("friendlyName", tr("Sonar sensor"))

public:
	SonarSensor(const kitBase::robotModel::DeviceInfo &info
			, const kitBase::robotModel::PortInfo &port
			, utils::robotCommunication::RobotCommunicator &robotCommunicator);

	void read() override;
	void doConfiguration() override;

private slots:
	void sensorSpecificProcessResponse(const QByteArray &reading);

private:
	void setMode(enums::sonarMode::SonarModeEnum mode);
	void writeRegister(enums::sonarRegisters::SonarRegistersEnum reg, int value);
	void sendCommand(const QByteArray &command, int responseSize);

	NxtInputDevice mImplementation;
	communication::I2CCommunicator mI2C;
};

}
}
}
}
