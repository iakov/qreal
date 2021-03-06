/* Copyright 2015-2016 QReal Research Group, Dmitry Mordvinov
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

#include "metaMetaModel/labelProperties.h"

using namespace qReal;

LabelProperties::LabelProperties()
	: mIndex(0)
	, mX(0)
	, mY(0)
	, mText()
	, mBinding()
	, mReadOnly(true)
	, mIsPlainText(false)
	, mRotation(0)
	, mBackground(Qt::transparent)
	, mScalingX(false)
	, mScalingY(false)
	, mIsHard(false)
	, mPrefix()
	, mSuffix()
{
}

LabelProperties::LabelProperties(int index, qreal x, qreal y, const QString &text, qreal rotation)
	: mIndex(index)
	, mX(x)
	, mY(y)
	, mText(text)
	, mBinding()
	, mReadOnly(true)
	, mIsPlainText(false)
	, mRotation(rotation)
	, mBackground(Qt::transparent)
	, mScalingX(false)
	, mScalingY(false)
	, mIsHard(false)
	, mPrefix()
	, mSuffix()
{
}
LabelProperties::LabelProperties(int index, qreal x, qreal y, const QString &binding, const QString &roleName
		, const QString &nameOfRoleProperty, bool readOnly, qreal rotation)
	: mIndex(index)
	, mX(x)
	, mY(y)
	, mText()
	, mBinding(binding)
	, mRoleName(roleName)
	, mNameOfPropertyRole(nameOfRoleProperty)
	, mReadOnly(readOnly)
	, mRotation(rotation)
	, mBackground(Qt::transparent)
	, mScalingX(false)
	, mScalingY(false)
	, mIsHard(false)
	, mPrefix()
	, mSuffix()
{
}

LabelProperties::LabelProperties(int index, qreal x, qreal y, const QString &binding, bool readOnly, qreal rotation)
	: mIndex(index)
	, mX(x)
	, mY(y)
	, mText()
	, mBinding(binding)
	, mReadOnly(readOnly)
	, mIsPlainText(false)
	, mRotation(rotation)
	, mBackground(Qt::transparent)
	, mScalingX(false)
	, mScalingY(false)
	, mIsHard(false)
	, mPrefix()
	, mSuffix()
{
}

LabelProperties::LabelProperties(const LabelProperties &other)
	: QObject(other.parent())
{
	copyFrom(other);
}

int LabelProperties::index() const
{
	return mIndex;
}

void LabelProperties::setIndex(int index)
{
	if (index != mIndex) {
		mIndex = index;
		emit indexChanged(index);
	}
}

qreal LabelProperties::x() const
{
	return mX;
}

void LabelProperties::setX(qreal x)
{
	if (mX != x) {
		mX = x;
		emit xChanged(x);
	}
}

qreal LabelProperties::y() const
{
	return mY;
}

void LabelProperties::setY(qreal y)
{
	if (mY != y) {
		mY = y;
		emit yChanged(y);
	}
}

bool LabelProperties::isStatic() const
{
	return mBinding.isEmpty();
}

QString LabelProperties::text() const
{
	return mText;
}

void LabelProperties::setText(const QString &text)
{
	if (mText != text) {
		mText = text;
		emit textChanged(text);
	}
}

QString LabelProperties::binding() const
{
	return mBinding;
}

QString LabelProperties::roleName() const
{
	return mRoleName;
}

QString LabelProperties::nameForRoleProperty() const
{
	if (!mRoleName.isEmpty() && !mNameOfPropertyRole.isEmpty()) {
		return mRoleName + "!" + mNameOfPropertyRole;
	}

	return "";
}

void LabelProperties::setBinding(const QString &binding)
{
	if (mBinding != binding) {
		mBinding = binding;
		emit bindingChanged(binding);
	}
}

bool LabelProperties::isReadOnly() const
{
	return mReadOnly;
}

void LabelProperties::setReadOnly(bool readOnly)
{
	if (mReadOnly != readOnly) {
		mReadOnly = readOnly;
		emit readOnlyChanged(readOnly);
	}
}

bool LabelProperties::isPlainTextMode() const
{
	return mIsPlainText;
}

void LabelProperties::setPlainTextMode(bool isPlainText)
{
	mIsPlainText = isPlainText;
}

qreal LabelProperties::rotation() const
{
	return mRotation;
}

void LabelProperties::setRotation(qreal degrees)
{
	if (mRotation != degrees) {
		mRotation = degrees;
		emit rotationChanged(degrees);
	}
}

QColor LabelProperties::background() const
{
	return mBackground;
}

void LabelProperties::setBackground(const QColor &background)
{
	if (mBackground != background) {
		mBackground = background;
		emit backgroundChanged(background);
	}
}

bool LabelProperties::scalingX() const
{
	return mScalingX;
}

void LabelProperties::setScalingX(bool enabled)
{
	if (mScalingX != enabled) {
		mScalingX = enabled;
		emit scalingXChanged(enabled);
	}
}

bool LabelProperties::scalingY() const
{
	return mScalingY;
}

void LabelProperties::setScalingY(bool enabled)
{
	if (mScalingY != enabled) {
		mScalingY = enabled;
		emit scalingYChanged(enabled);
	}
}

bool LabelProperties::isHard() const
{
	return mIsHard;
}

void LabelProperties::setHard(bool hard)
{
	if (mIsHard != hard) {
		mIsHard = hard;
		emit isHardChanged(hard);
	}
}

QString LabelProperties::prefix() const
{
	return mPrefix;
}

void LabelProperties::setPrefix(const QString &text)
{
	if (mPrefix != text) {
		mPrefix = text;
		emit prefixChanged(text);
	}
}

QString LabelProperties::suffix() const
{
	return mSuffix;
}

void LabelProperties::setSuffix(const QString &text)
{
	if (mSuffix != text) {
		mSuffix = text;
		emit suffixChanged(text);
	}
}

LabelProperties &LabelProperties::operator =(const LabelProperties &other)
{
	copyFrom(other);
	return *this;
}

void LabelProperties::copyFrom(const LabelProperties &other)
{
	this->mIndex = other.mIndex;
	this->mX = other.mX;
	this->mY = other.mY;
	this->mText = other.mText;
	this->mBinding = other.mBinding;
	this->mRoleName = other.mRoleName;
	this->mNameOfPropertyRole = other.mNameOfPropertyRole;
	this->mReadOnly = other.mReadOnly;
	this->mIsPlainText = other.mIsPlainText;
	this->mRotation = other.mRotation;
	this->mBackground = other.mBackground;
	this->mScalingX = other.mScalingX;
	this->mScalingY = other.mScalingY;
	this->mIsHard = other.mIsHard;
	this->mPrefix = other.mPrefix;
	this->mSuffix = other.mSuffix;
	this->mReadOnly = other.mReadOnly;
}
