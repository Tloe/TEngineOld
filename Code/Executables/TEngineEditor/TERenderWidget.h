#ifndef TERENDERWIDGET_H
#define TERENDERWIDGET_H

#include <QtGui>

class TEngineRenderWidget : public QWidget
{
public:
	TEngineRenderWidget(QWidget *parent);
	QPaintEngine* paintEngine () const;

	virtual void resizeEvent( QResizeEvent * );

private:


};

#endif