#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QVideoWidget>

class VideoWidget : public QVideoWidget
{
    Q_OBJECT

public:
    VideoWidget(QWidget *parent = 0);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
};
#endif // VIDEOWIDGET_H
