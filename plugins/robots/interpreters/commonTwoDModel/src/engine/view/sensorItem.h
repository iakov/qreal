#pragma once

#include <QtCore/QSet>
#include <QtWidgets/QGraphicsItem>
#include <QtGui/QPainter>

#include <qrutils/graphicsUtils/abstractItem.h>
#include <qrutils/graphicsUtils/pointImpl.h>
#include <qrutils/graphicsUtils/rotateItem.h>

#include <interpreterBase/robotModel/portInfo.h>

#include "rotater.h"
#include "src/engine/model/sensorsConfiguration.h"

namespace twoDModel {
namespace view {

/// Class that represents sensor in 2D model.
class SensorItem : public QObject, public graphicsUtils::RotateItem
{
	Q_OBJECT

public:
	SensorItem(model::SensorsConfiguration &configuration
			, const interpreterBase::robotModel::PortInfo &port, const QString &pathToImage, QRect const &imageSize);

	void setRotation(qreal angle) override;
	QRectF rect() const override;
	void setSelected(bool isSelected) override;
	void setRotater(Rotater *rotater);
	void checkSelection() override;

	/// Draws selection rect around sensorBoundingBox
	void drawItem(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;
	void drawExtractionForItem(QPainter* painter) override;

	QRectF boundingRect() const override;

	void changeDragState(qreal x, qreal y) override;
	void resizeItem(QGraphicsSceneMouseEvent *event) override;

	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

	void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

	void setRotatePoint(const QPointF &rotatePoint);

protected:
	class PortItem : public QGraphicsItem
	{
	public:
		explicit PortItem(const interpreterBase::robotModel::PortInfo &port);

		QRectF boundingRect() const override;

	protected:
		void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) override;

	private:
		const interpreterBase::robotModel::PortInfo mPort;
		QFont const mFont;
		QRect const mBoundingRect;
	};

	QRectF imageRect() const;
	QString name() const;
	QString pathToImage() const;

	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

	model::SensorsConfiguration &mConfiguration;
	const interpreterBase::robotModel::PortInfo mPort;
	QPointF mRotatePoint;
	graphicsUtils::PointImpl mPointImpl;
	Rotater *mRotater;

	const QRectF mImageRect;
	const QRectF mBoundingRect;
	QImage const mImage;
	PortItem *mPortItem;  // Has ownership.
};

}
}
