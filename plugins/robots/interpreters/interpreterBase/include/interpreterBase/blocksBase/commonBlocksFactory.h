#pragma once

#include "blocksFactoryInterface.h"
#include "interpreterBase/interpreterBaseDeclSpec.h"

namespace qReal {
namespace interpretation {
class Block;
}
}

namespace interpreterBase {
namespace blocksBase {

/// Base implementation of all blocks factories. Provides common functionality and default implementations for
/// BlocksFactoryInterface methods.
class ROBOTS_INTERPRETER_BASE_EXPORT CommonBlocksFactory : public BlocksFactoryInterface
{
public:
	CommonBlocksFactory();

	qReal::interpretation::BlockInterface *block(const qReal::Id &element) override;

	void configure(qReal::GraphicalModelAssistInterface const &graphicalModelApi
			, qReal::LogicalModelAssistInterface const &logicalModelApi
			, interpreterBase::robotModel::RobotModelManagerInterface &robotModelManager
			, qReal::ErrorReporterInterface &errorReporter
			, qrtext::LanguageToolboxInterface &textLanguageToolbox
			) final;

	/// May be overrided to disable some blocks from palette when binded to this factory
	/// robot model is active. Default implementation disables nothing.
	qReal::IdList blocksToDisable() const override;

protected:
	static qReal::Id id(const QString &metatype);
	static bool elementMetatypeIs(const qReal::Id &element, const QString &metatype);

	/// Implementation must instantiate a concrete block object by the given id. Future preparation
	/// is performed in parent code.
	virtual qReal::interpretation::Block *produceBlock(const qReal::Id &element) = 0;

	/// @todo: there is no such thing as protected fields. One can not trust its descendants.
	interpreterBase::robotModel::RobotModelManagerInterface *mRobotModelManager;  // Does not have ownership.
	qReal::GraphicalModelAssistInterface const *mGraphicalModelApi;  // Does not have ownership.
	qReal::LogicalModelAssistInterface const *mLogicalModelApi;  // Does not have ownership.
	qReal::ErrorReporterInterface *mErrorReporter;  // Does not have ownership.
	qrtext::LanguageToolboxInterface *mParser;  // Does not have ownership.
};

}
}
