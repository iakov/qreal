#include "reservedVariablesConverter.h"

#include "generatorBase/lua/luaProcessor.h"

using namespace generatorBase::converters;
using namespace qReal;

ReservedVariablesConverter::ReservedVariablesConverter(const QString &pathToTemplates
		, qReal::ErrorReporterInterface &errorReporter
		, const interpreterBase::robotModel::RobotModelInterface &robotModel
		, QMap<interpreterBase::robotModel::PortInfo, interpreterBase::robotModel::DeviceInfo> const &devices
		, const simple::Binding::ConverterInterface *inputPortConverter
		, parts::DeviceVariables const &deviceVariables)
	: TemplateParametrizedConverter(pathToTemplates)
	, mErrorReporter(errorReporter)
	, mRobotModel(robotModel)
	, mDevices(devices)
	, mInputConverter(inputPortConverter)
	, mDeviceVariables(deviceVariables)
{
}

ReservedVariablesConverter::~ReservedVariablesConverter()
{
	delete mInputConverter;
}

QString ReservedVariablesConverter::convert(const QString &variable) const
{
	for (const interpreterBase::robotModel::PortInfo &port : mRobotModel.availablePorts()) {
		const QString reservedVariable = port.reservedVariable();
		if (!reservedVariable.isEmpty() && variable == reservedVariable) {
			return deviceExpression(port);
		}
	}

	return variable;
}

QString ReservedVariablesConverter::deviceExpression(const interpreterBase::robotModel::PortInfo &port) const
{
	const interpreterBase::robotModel::DeviceInfo device = mDevices[port];
	if (device.isNull()) {
		mErrorReporter.addError(QObject::tr("Device on port %1 is not configured."\
				" Please select it on the left-side panel.").arg(port.name()));
		return QObject::tr("/* ERROR: SELECT DEVICE TYPE */");
	}

	const QString templatePath = mDeviceVariables.variableTemplatePath(device, port);

	// Converter must take a string like "1" or "2" (and etc) and return correct value
	return readTemplate(templatePath).replace("@@PORT@@", mInputConverter->convert(port.name()));
}
