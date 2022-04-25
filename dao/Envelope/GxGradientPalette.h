#ifndef GX_GRADIENT_PALETTE_H
#define GX_GRADIENT_PALETTE_H


#include <QObject>
#include <QColor>

class GxGradientPalette : public QObject
{
	Q_OBJECT

public:
	GxGradientPalette(const QList<QColor> &colors, QObject *parent = nullptr);

	GxGradientPalette(const GxGradientPalette &palette);

	GxGradientPalette &operator =(GxGradientPalette &palette);

	~GxGradientPalette();

	void setColors(const QList<QColor> &colors);

	QColor colorAt(double value);

	QList<QColor> colors() const;

private:
	QColor interpolate(QColor start, QColor end, double ratio);

private:
	QList<QColor> m_gradientColors;
};

#endif // !GX_GRADIENT_PALETTE_H
