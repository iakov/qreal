#include "generatorBase/parts/threads.h"

#include <qrutils/nameNormalizer.h>

using namespace generatorBase;
using namespace parts;

Threads::Threads(const QString &pathToTemplates)
	: TemplateParametrizedEntity(pathToTemplates)
{
}

void Threads::registerThread(const qReal::Id &id)
{
	if (!mUnprocessedThreads.contains(id) && !mProcessedThreads.keys().contains(id)) {
		mUnprocessedThreads.insert(id);
	}
}

void Threads::threadProcessed(const qReal::Id &id, semantics::SemanticTree &tree)
{
	if (!mUnprocessedThreads.contains(id)) {
		return;
	}

	mProcessedThreads[id] = &tree;
	mUnprocessedThreads.remove(id);
}

bool Threads::hasUnprocessedThreads() const
{
	return !mUnprocessedThreads.empty();
}

qReal::Id Threads::nextUnprocessedThread() const
{
	return *mUnprocessedThreads.begin();
}

QList<semantics::SemanticTree *> Threads::threads() const
{
	return mProcessedThreads.values();
}

QStringList Threads::threadNames() const
{
	QStringList result;
	for (semantics::SemanticTree const *thread : threads()) {
		result << name(thread);
	}

	return result;
}

QString Threads::generateDeclarations() const
{
	const QStringList threads = threadNames();
	const QString forwardDeclaration = readTemplate("threads/forwardDeclaration.t");
	if (forwardDeclaration.isEmpty() || threads.isEmpty()) {
		return QString();
	}

	const QString declarationsHeader = readTemplate("threads/declarationsSectionHeader.t");
	QStringList declarations;
	for (const QString &thread : threads) {
		declarations << QString(forwardDeclaration).replace("@@NAME@@", thread);
	}

	return declarationsHeader + declarations.join("\n");
}

QString Threads::generateImplementations(const QString &indentString) const
{
	QList<semantics::SemanticTree *> const threads = this->threads();
	const QString implementation = readTemplate("threads/implementation.t");
	if (implementation.isEmpty() || threads.isEmpty()) {
		return QString();
	}

	const QString implementationsHeader = readTemplate("threads/implementationsSectionHeader.t");
	QStringList implementations;
	for (semantics::SemanticTree const *thread : threads) {
		const QString code = thread->toString(1, indentString);
		implementations << QString(implementation).replace("@@NAME@@", name(thread)).replace("@@BODY@@", code);
	}

	return implementationsHeader + implementations.join("\n");
}

QString Threads::name(semantics::SemanticTree const *tree) const
{
	return utils::NameNormalizer::normalizeStrongly(tree->initialBlock().id(), false);
}
