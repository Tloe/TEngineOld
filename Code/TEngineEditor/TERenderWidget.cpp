#include <TERenderWidget.h>

TEngineRenderWidget::TEngineRenderWidget( QWidget *parent )
{
	setAttribute( Qt::WA_PaintOnScreen );
	setAttribute( Qt::WA_OpaquePaintEvent );
	setAttribute( Qt::WA_NoSystemBackground );
	setAutoFillBackground( false );
	setFocusPolicy( Qt::StrongFocus );
}

QPaintEngine* TEngineRenderWidget::paintEngine() const
{
	return 0;
}

void TEngineRenderWidget::resizeEvent( QResizeEvent * )
{
	//redraw, change renderer->SetBufferSize
}
