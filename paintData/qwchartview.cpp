#include "qwchartview.h"

void QWChartView::mousePressEvent(QMouseEvent *event)
{
    //鼠标左键按下
    if(event->button() == Qt::LeftButton){
        beginPoint = event->pos();
    }
    QChartView::mousePressEvent(event);
}

void QWChartView::mouseMoveEvent(QMouseEvent *event)
{
    //鼠标移动事件
    QPoint point = event->pos();
    emit mouseMovePoint(point);
    QChartView::mouseMoveEvent(event);
}

void QWChartView::mouseReleaseEvent(QMouseEvent *event)
{
    //鼠标左键释放事件
    if(event->button() == Qt::LeftButton){
        //鼠标左键释放，获取矩形框的endPoint,进行缩放
        endPoint = event->pos();
        QRectF rectF;
        rectF.setTopLeft(this->beginPoint);
        rectF.setBottomRight(this->endPoint);
        this->chart()->zoomIn(rectF);
    }else if(event->button() == Qt::RightButton){
        this->chart()->zoomReset();//鼠标右键释放，resetZoom
    }

    QChartView::mouseReleaseEvent(event);
}

void QWChartView::keyPressEvent(QKeyEvent *event)
{
    //按键控制
    switch (event->key()) {
        case Qt::Key_Plus:
            chart()->zoom(1.2); break;
        case Qt::Key_Minus:
            chart()->zoom(0.8); break;
        case Qt::Key_Left:
            chart()->scroll(10, 0); break;
        case Qt::Key_Right:
            chart()->scroll(-10, 0); break;
        case Qt::Key_Up:
            chart()->scroll(0, -10); break;
        case Qt::Key_Down:
            chart()->scroll(0, 10); break;
        case Qt::Key_PageUp:
            chart()->scroll(0, 50); break;
        case Qt::Key_PageDown:
            chart()->scroll(0, -50); break;
        case Qt::Key_Home:
            chart()->zoomReset(); break;
       default:
            QGraphicsView::keyPressEvent(event);
    }
}

QWChartView::QWChartView(QWidget * parent)
    :QChartView (parent)
{
    //构造函数
    this->setDragMode(QGraphicsView::RubberBandDrag);
    this->setMouseTracking(true);
}


