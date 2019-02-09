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

#include "changePropertyCommand.h"

using namespace qReal::commands;

ChangePropertyCommand::ChangePropertyCommand(models::LogicalModelAssistApi * const model
		, const QString &property, const Id &id, const QVariant &newValue)
	: mLogicalModel(model)
	, mLogicalRepoApi(nullptr)
	, mId(id)
	, mPropertyName(property)
	, mOldValue(mLogicalModel->propertyByRoleName(mId, mPropertyName))
	, mNewValue(newValue)
{
}

ChangePropertyCommand::ChangePropertyCommand(qrRepo::LogicalRepoApi * const model
		, const QString &property, const Id &id, const QVariant &oldValue, const QVariant &newValue)
	: mLogicalModel(nullptr)
	, mLogicalRepoApi(model)
	, mId(id)
	, mPropertyName(property)
	, mOldValue(oldValue)
	, mNewValue(newValue)
{
}

ChangePropertyCommand::ChangePropertyCommand(qReal::models::LogicalModelAssistApi * const model
		, const QString &property, const qReal::Id &id, const QVariant &oldValue, const QVariant &newValue)
	: mLogicalModel(model)
	, mLogicalRepoApi(nullptr)
	, mId(id)
	, mPropertyName(property)
	, mOldValue(oldValue)
	, mNewValue(newValue)
{
}

bool ChangePropertyCommand::execute()
{
	return setProperty(mNewValue);
}

bool ChangePropertyCommand::restoreState()
{
	return setProperty(mOldValue);
}

bool ChangePropertyCommand::setProperty(const QVariant &value)
{
	if (mLogicalModel) {
		mLogicalModel->setPropertyByRoleName(mId, value, mPropertyName);
	} else if (mLogicalRepoApi) {
		mLogicalRepoApi->setProperty(mId, mPropertyName, value);
	}

	return true;
}
