#include "GxGradientPalette.h"

GxGradientPalette::GxGradientPalette(const QList<QColor> &colors, QObject *parent)
{
	Q_ASSERT(colors.size() > 0);
	m_gradientColors = colors;
}

GxGradientPalette::GxGradientPalette(const GxGradientPalette &palette)
{
	m_gradientColors = palette.m_gradientColors;
}

GxGradientPalette &GxGradientPalette::operator=(GxGradientPalette &palette)
{
	m_gradientColors = palette.m_gradientColors;
	return *this;
}

GxGradientPalette::~GxGradientPalette()
{
}

void GxGradientPalette::setColors(const QList<QColor> &colors)
{
	Q_ASSERT(colors.size() > 0);
	m_gradientColors = colors;
}

QColor GxGradientPalette::colorAt(double dValue)
{
	if (dValue < 0.0)
	{
		return m_gradientColors.first();
	}
	if (dValue > 1.0)
	{
		return m_gradientColors.last();
	}

	double stepbase = 1.0 / (m_gradientColors.count() - 1);
	int interval = m_gradientColors.count() - 1; //to fix 1<=0.99999999;

	for (int i = 1; i < m_gradientColors.count(); i++)//remove begin and end
	{
		if (dValue <= i*stepbase) { interval = i; break; }
	}
	double percentage = (dValue - stepbase*(interval - 1)) / stepbase;
	QColor color(interpolate(m_gradientColors[interval], m_gradientColors[interval - 1], percentage));
	return color;
}

QList<QColor> GxGradientPalette::colors() const
{
	return m_gradientColors;
}

QColor GxGradientPalette::interpolate(QColor start, QColor end, double ratio)
{
	int r = (int)(ratio*start.red() + (1 - ratio)*end.red());
	int g = (int)(ratio*start.green() + (1 - ratio)*end.green());
	int b = (int)(ratio*start.blue() + (1 - ratio)*end.blue());
	int a = (int)(ratio*start.alpha() + (1 - ratio)*end.alpha());
	return QColor::fromRgb(r, g, b, a);
}
