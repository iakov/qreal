/* Copyright 2015-2016 Kogutich Denis
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

#include "shapeWidget.h"
#include "dynamicPropertiesDialog.h"

using namespace qReal;
using namespace gui;

const QRectF bounds = QRectF(12.5, 12.5, 50.0, 50.0);

ShapeWidget::ShapeWidget(int index, QWidget *parent)
	: QWidget(parent)
	, mSelected(false)
	, mIndex(index)
{
	setFixedSize(75, 75);
}

void ShapeWidget::setShape(const QString &shape)
{
	mShape = shape;
	const QString shapeXml = DynamicPropertiesDialog::generateShapeXml(mShape);
	QDomDocument dynamicShape;
	dynamicShape.setContent(shapeXml);
	mRenderer.load(dynamicShape);
	repaint();
}

void ShapeWidget::addSelection()
{
	mSelected = true;
	repaint();
}

void ShapeWidget::removeSelection()
{
	mSelected = false;
	repaint();
}

int ShapeWidget::index() const
{
	return mIndex;
}

QString ShapeWidget::shape() const
{
	return mShape;
}

void ShapeWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	if (mSelected) {
		painter.setPen(QPen(Qt::gray, 5));
		painter.drawRect(rect());
	}

	mRenderer.render(&painter, bounds);
}

void ShapeWidget::mousePressEvent(QMouseEvent *)
{
	addSelection();
	emit clicked();
}
