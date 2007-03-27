#include <QtGui>

#include "editorview.h"

EditorView::EditorView(QWidget *parent)
    : QGraphicsView(parent)
{
    setScene(new EditorViewScene(this));
    mvciface = new EditorViewMViface(this,dynamic_cast<EditorViewScene *>(scene()));
    
    setRenderHints(QPainter::Antialiasing);
}

EditorView::~EditorView()
{
}

void EditorView::mousePressEvent(QMouseEvent *event)
{
    if (QGraphicsItem *item = itemAt(event->pos())) {
	mvciface->raiseClick(item);
    }

    QGraphicsView::mousePressEvent(event);
}

