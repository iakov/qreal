#pragma once

#include <QtCore/QMap>

#include "editor/private/resizeHandler.h"
#include "editor/commands/reshapeEdgeCommand.h"
#include "editor/commands/nodeElementCommand.h"
#include "controller/commands/trackingEntity.h"

namespace qReal
{
namespace commands
{

class ResizeCommand : public NodeElementCommand, public TrackingEntity
{
public:
	/// Creating new instance of command in tracking-based style
	ResizeCommand(EditorViewScene const *scene, const Id &id);

	/// Creating new instance of command in tracking-based style
	ResizeCommand(EditorView const *view, const Id &id);

	/// Creating new instance of command in usial style
	ResizeCommand(EditorViewScene const *scene, const Id &id
			, const QRectF &oldGeometry, const QRectF &newGeometry);
	virtual ~ResizeCommand() {}

	static ResizeCommand *create(NodeElement const * const element, const QRectF &newContents
			, const QPointF &newPos, const QRectF &oldContents, const QPointF &oldPos);

	virtual void startTracking();
	virtual void stopTracking();
	virtual void rejectTracking();

	QRectF geometryBeforeDrag() const;
	bool modificationsHappened() const;

protected:
	bool execute();
	bool restoreState();

private:
	void resize(NodeElement * const element, const QRectF &geometry);

	/// Performs geometries snapshot for all selected items hierarchies
	void makeCommonSnapshot(QMap<Id, QRectF> &target);

	/// Performs geometries snapshot for specified item`s hierarchy: its parent and child items
	void makeHierarchySnapshot(NodeElement *node, QMap<Id, QRectF> &target);

	/// Performs geometries snapshot for specified item`s children
	void makeChildrenSnapshot(NodeElement const *element, QMap<Id, QRectF> &target);

	void addEdges(NodeElement const *node);
	void startEdgeTracking();
	void stopEdgeTracking();

	void resizeHierarchy(QMap<Id, QRectF> const &snapshot);
	void resizeTree(QMap<Id, QRectF> const &snapshot, const Id &root);

	QRectF geometryOf(NodeElement const *element) const;

	QMap<Id, QRectF> mOldGeometrySnapshot;
	QMap<Id, QRectF> mNewGeometrySnapshot;

	QSet<EdgeElement *> mEdges;
	QSet<ReshapeEdgeCommand *> mEdgeCommands;
};

}
}
