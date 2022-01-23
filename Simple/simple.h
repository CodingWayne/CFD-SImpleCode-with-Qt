#ifndef SIMPLE_H
#define SIMPLE_H
#if !defined(Q_ASSERT_X)
#  if defined(QT_NO_DEBUG) && !defined(QT_FORCE_ASSERTS)
#    define Q_ASSERT_X(cond, where, what) qt_noop()
#  else
#    define Q_ASSERT_X(cond, where, what) ((!(cond)) ? qt_assert_x(where, what,__FILE__,__LINE__) : qt_noop())
#  endif
#endif
#include <chart_create.h>
#include <qcustomplot.h>
#include <QWidget>
#include <QString>
#include <QScrollBar>
#include <QLabel>
#include <QAbstractSlider>
#include <QEventLoop>
#include <QTimer>
#include <QTime>
#include <QCloseEvent>
#include<QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Simple; }
QT_END_NAMESPACE

class Simple : public QWidget
{
    Q_OBJECT

public:
    Simple(QWidget *parent = nullptr);
    ~Simple();
    int method, load_method;
    int *save;
    int i, j;
    double rho;
    double miu;
    double d_miu;
    double d_Re;
    double dx, dy, Lx, Ly, dxi, dyi, dti;
    int mx, my;
    int tx, ty;
    int total_mesh;
    int total_in_mesh;
    Chart *d_chart;
    double y_init;
    //-----邊界條件 宣告
    double u_top, v_top;
    double u_left, v_left;
    double u_bottom, v_bottom;
    double u_right, v_right;
    double u_init, v_init;
    //------------------
    double Re;
    double CFL;
    double min_err;
    int ite, total_ite;
    double dt;
    double t;
    double D;
    QCPColorMap *colorMap;
    double num;
    double U_relax;//速度鬆弛系數
    double P_relax;//壓力鬆弛系數
    double continuity;

    typedef struct //存 u,v
    {
        double u;
        double v;
        double p;
        double p_delta, p_tmp;
        double p_new;
        double u_tmp;
        double v_tmp;
        double u_new;
        double v_new;
        double con;
        double u_mom;
        double v_mom;
        double u1, u2, u3, u4, u5, u6, u7, u8, u9, u_nb, u_jk, E, d;
        double v1, v2, v3, v4, v5, v6, v7, v8, v9, v_nb, v_jk, F, e;
        double p_nb, p_jk, p_c;
        double u_star, v_star;
    }Mesh, * pmesh;
    double u1, u2, u3, u4, v1, v2, v3, v4, p1, p2, p3;



private slots:
    void on_load_clicked();         //load按鈕
    void mesh_build();              //simple開始
    void on_pushButton_clicked();   //暫停&開始按鈕
    void on_pushButton_2_clicked(); //出檔按鈕



public slots:
    void generateData();           //生成chart1 continuity數據
    void on_pushButton_3_clicked();//Reset plot
    void get_umax();               //生成chart2 全域Umax值

private:

    Ui::Simple *ui;
    int *status;          //暫停啟動狀態值
    double *continuity_;  //Continuity指標
    QTimer *m_timer;
    Chart *m_chart;


    Chart *createdChart() const;   //chart2創建
    void closeEvent( QCloseEvent*);//退出事件

};

#endif // SIMPLE_H


