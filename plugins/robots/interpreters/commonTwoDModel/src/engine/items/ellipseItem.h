#pragma once
#include <QtCore/QList>
#include <QtWidgets/QGraphicsItem>
#include <QtGui/QPainter>
#include <QtXml/QDomDocument>

#include <qrutils/graphicsUtils/abstractItem.h>
#include <qrutils/graphicsUtils/rectangleImpl.h>

#include "colorFieldItem.h"

namespace twoDModel {
namespace items {

class EllipseItem : public QObject, public ColorFieldItem
{
	Q_OBJECT

public:
	EllipseItem(const QPointF &begin, const QPointF &end);

	QRectF boundingRect() const override;
	QRectF calcNecessaryBoundingRect() const override;
	void drawItem(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget = 0) override;

	QDomElement serialize(QDomDocument &document, const QPoint &topLeftPicture) override;
	void deserialize(QDomElement const &element) override;

private:
	void setPrivateData();

	graphicsUtils::RectangleImpl mEllipseImpl;
};

}
}
