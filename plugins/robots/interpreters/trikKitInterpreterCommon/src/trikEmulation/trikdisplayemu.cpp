/* Copyright 2016-2017 CyberTech Labs Ltd.
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

#include <trikKitInterpreterCommon/trikEmulation/trikdisplayemu.h>

#include <kitBase/robotModel/robotModelUtils.h>
///todo:
#include <trikKitInterpreterCommon/robotModel/twoD/parts/twoDDisplay.h>

using namespace trik;

TrikDisplayEmu::TrikDisplayEmu(const QSharedPointer<robotModel::twoD::TrikTwoDRobotModel> &model)
	: mTwoDRobotModel(model), mDisplay(nullptr)
{
}

trikControl::DisplayWidgetInterface &TrikDisplayEmu::graphicsWidget()
{
	return mDisplayWidgetInterface;
}

void TrikDisplayEmu::init()
{
	mDisplay = kitBase::robotModel::RobotModelUtils::findDevice<robotModel::twoD::parts::Display>(*mTwoDRobotModel
			, "DisplayPort");
}

void TrikDisplayEmu::showImage(const QString &fileName)
{
	const bool smile = fileName.endsWith(QLatin1String("sad.png"));
	QMetaObject::invokeMethod(mDisplay,
			"drawSmile",
			 Q_ARG(bool, smile));
}

void TrikDisplayEmu::addLabel(const QString &text, int x, int y)
{
	QMetaObject::invokeMethod(mDisplay,
			"printText",
			Q_ARG(int, x),
			Q_ARG(int, y),
			Q_ARG(const QString &, text));
}

void TrikDisplayEmu::setPainterColor(const QString &color)
{
	QMetaObject::invokeMethod(mDisplay,
			"setPainterColor",
			Q_ARG(const QColor &, QColor(color)));
}

void TrikDisplayEmu::setPainterWidth(int penWidth)
{
	QMetaObject::invokeMethod(mDisplay,
			"setPainterWidth",
			Q_ARG(int, penWidth));
}

void TrikDisplayEmu::drawLine(int x1, int y1, int x2, int y2)
{
	QMetaObject::invokeMethod(mDisplay,
			"drawArc",
			Q_ARG(int, x1),
			Q_ARG(int, y1),
			Q_ARG(int, x2),
			Q_ARG(int, y2));
}

void TrikDisplayEmu::drawPoint(int x, int y)
{
	QMetaObject::invokeMethod(mDisplay,
			"drawPixel",
			Q_ARG(int, x),
			Q_ARG(int, y));
}

void TrikDisplayEmu::drawRect(int x, int y, int width, int height, bool filled)
{
	QMetaObject::invokeMethod(mDisplay,
			"drawRect",
			Q_ARG(int, x),
			Q_ARG(int, y),
			Q_ARG(int, width),
			Q_ARG(int, height),
			Q_ARG(bool, filled));
}

void TrikDisplayEmu::drawEllipse(int x, int y, int width, int height, bool filled)
{
	QMetaObject::invokeMethod(mDisplay,
			"drawEllipse",
			Q_ARG(int, x),
			Q_ARG(int, y),
			Q_ARG(int, width),
			Q_ARG(int, height),
			Q_ARG(bool, filled));
}

void TrikDisplayEmu::drawArc(int x, int y, int width, int height, int startAngle, int spanAngle)
{
	QMetaObject::invokeMethod(mDisplay,
			"drawArc",
			Q_ARG(int, x),
			Q_ARG(int, y),
			Q_ARG(int, width),
			Q_ARG(int, height),
			Q_ARG(int, startAngle),
			Q_ARG(int, spanAngle));
}

void TrikDisplayEmu::setBackground(const QString &color)
{
	QMetaObject::invokeMethod(mDisplay,
			"setBackground",
			Q_ARG(const QColor &, QColor(color)));
}

void TrikDisplayEmu::clear()
{
	QMetaObject::invokeMethod(mDisplay, "clearScreen");
}

void TrikDisplayEmu::reset()
{
	if (mDisplay) {
		QMetaObject::invokeMethod(mDisplay, "reset");
	}
}

void TrikDisplayEmu::redraw()
{
	QMetaObject::invokeMethod(mDisplay, "redraw");
}
