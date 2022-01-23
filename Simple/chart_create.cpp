#include<chart_create.h>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    m_axisX(new QValueAxis()),
    m_axisY(new QValueAxis()),
    m_x(5),
    m_y(1)
{
    m_series = new QSplineSeries(this);
    QPen green(Qt::red);
    green.setWidth(3);
    m_series->setPen(green);
    m_series->append(m_x, m_y);

    addSeries(m_series);

    //對齊X Y座標位置
    addAxis(m_axisX, Qt::AlignBottom);
    addAxis(m_axisY, Qt::AlignLeft);

    m_series->attachAxis(m_axisX);
    m_axisX->setLabelFormat("%d");
    m_series->attachAxis(m_axisY);
    m_axisX->setTickCount(5);  //設定X軸最大分割數

    // 設置X Y範圍
    m_axisX->setRange(0, 0);
    m_axisY->setRange(0, 1);
}

Chart::~Chart()
{

}
