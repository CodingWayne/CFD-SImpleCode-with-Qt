#include "simple.h"
#include "ui_simple.h"
#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include <windows.h>
#include <time.h>
#include <QChartView>
#include <QRandomGenerator>
#include <QValueAxis>
#include <QSplineSeries>

Simple::Simple(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Simple)
{
    ui->setupUi(this);
    this->setWindowTitle("Simple-Algorithm for 2D Poseii Flow");//視窗標題設定

    connect(ui->load,SIGNAL(clicked()),this,SLOT(mesh_build()));//當load按鈕按下時連接mesh_build函式

    *status = 1;        //暫停變數指標
    int out_mode = 0;   //出檔變數
    save = &out_mode;   //出檔變數指標連接
    continuity_ = &continuity; //Continuity指標連接



    //----------------------------------Continuity Chart-------------------------------------------
    m_timer = new QTimer();                         //chart計時器實體化
    m_chart = new Chart();                          //Continuity chart實體化
    m_chart->setTitle("<b>Continuity</b>");         //Continuity chart 標題設定
    m_chart->legend()->hide();                      //Continuity chart 隱藏圖例
    //m_chart->setAnimationOptions(QChart::AllAnimations); //控制圖表動畫方式 預設=全不動
    QChartView *chartView = new QChartView(m_chart); //畫布實體化 內容為Continuity chart
    chartView->setRenderHint(QPainter::Antialiasing);//畫布反鋸齒
    chartView->chart()->setTheme(QChart::ChartTheme(2));//設定樣式 2為黑色
    ui->vLayout->addWidget(chartView);//將畫布連結vLayout
    connect(m_timer, SIGNAL(timeout()), this, SLOT(generateData()));//計時器倒數結束 更新Continuity值

    //----------------------------------U_max      Chart-------------------------------------------
    d_chart = new Chart();                           //U_max chart實體化
    chartView = new QChartView(createdChart());      //畫布實體化 U_max chart
    chartView->setRenderHint(QPainter::Antialiasing);//畫布反鋸齒
    chartView->chart()->setTheme(QChart::ChartTheme(2));//設定樣式
    ui->dLayout->addWidget(chartView);//將畫布連結dLayout
    connect(m_timer, SIGNAL(timeout()), this, SLOT(get_umax()));//計時器倒數結束 更新U_max值

    //---------------------------------Qcustomplot colormap------------------------------------------
    //  軸配置
    ui->customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui->customPlot->axisRect()->setupFullAxesBox(true);//顯示所有軸
    ui->customPlot->xAxis2->setVisible(true);//顯示y軸2
    ui->customPlot->xAxis->setTickLabels(false);
    ui->customPlot->xAxis->setTicks(false);
    ui->customPlot->xAxis2->setTicks(false);
    ui->customPlot->yAxis->setTickLabels(false);
    ui->customPlot->yAxis->setTicks(false);
    ui->customPlot->yAxis2->setTicks(false);
    ui->customPlot->axisRect()->setAutoMargins(QCP::msNone);//取消全域margin

    //實體化畫布QCPColorMap 將軸放入
    colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);


    //實體化QCPColorScale (color bar) 內容為畫布本體
    QCPColorScale *colorScale = new QCPColorScale(ui->customPlot);
    ui->customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorMap->setColorScale(colorScale); // associate the color map with the color scale 將畫布與color bar連結
    colorScale->axis()->setLabel("U");//color bar標題設置
    QFont font;
    font.setPointSize(20);//color bar標題像素大小
    colorScale->axis()->setLabelFont(font);
    //colorScale->axis()->setTickLabelFont(font);
    colorScale->axis()->setSubTicks(false);//關閉color bar subTicks

    colorMap->setGradient(QCPColorGradient::gpJet);//畫布顯示使用內建梯度



}

Simple::~Simple()
{
    delete ui;
}


void Simple::on_load_clicked() //load按鈕 加載參數
{
    Lx = ui->Lx->text().toDouble();
    Ly = ui->Ly->text().toDouble();
    mx = ui->mx->text().toInt();
    my = ui->my->text().toInt();
    tx = mx + 2;
    ty = my + 2;

    u_top = ui->u_top->text().toDouble();
    v_top = ui->v_top->text().toDouble();
    u_right = ui->u_right->text().toDouble();
    v_right = ui->v_right->text().toDouble();
    u_left = ui->u_left->text().toDouble();
    v_left = ui->v_left->text().toDouble();
    u_bottom = ui->u_bottom->text().toDouble();
    v_bottom = ui->v_bottom->text().toDouble();
    rho = ui->rho->text().toDouble();
    miu = ui->miu->text().toDouble();
    CFL = ui->CFL->text().toDouble();
    U_relax = ui->U_relax->text().toDouble();
    P_relax = ui->P_relax->text().toDouble();
    dx = Lx / mx;//delta_x = 長度 / 網格數
    dy = Ly / my;
    dt = CFL * dx / 0.01;
    dxi = 1.0 / dx;// dxi 為 1 / delta_x
    dyi = 1.0 / dy;
    dti = 1.0 / dt;
    total_in_mesh = mx * my;
    total_mesh = tx * ty;;
    d_miu = miu / rho;
    Re = (rho * u_left * Lx) / miu;
    y_init = Ly / 2.0;
    colorMap->data()->setSize(mx, my);//設定畫布x y 網格數
//    qDebug()<<Lx<<" "<<Ly;
//    qDebug()<<mx<<" "<<my;
//    qDebug()<<u_top<<" "<<v_top;
//    qDebug()<<u_right<<" "<<v_right;
//    qDebug()<<u_left<<" "<<v_left;
//    qDebug()<<u_bottom<<" "<<v_bottom;
//    qDebug()<<rho;
//    qDebug()<<miu;
//    qDebug()<<CFL;
//    qDebug()<<U_relax;
//    qDebug()<<P_relax;
    *status = 1; //暫停狀態=1 為1毫秒
    m_timer->start(50);//50毫秒更新chart
    m_chart->m_series->clear();//清除圖表
    d_chart->m_series->clear();




}

void Simple::mesh_build()
{

    Mesh **mesh = (Mesh**)malloc(ty * sizeof(Mesh*));
    for ( i = 0; i < ty; i++)
    {
        mesh[i] = (Mesh*)malloc(tx * sizeof(Mesh));
    }
    //-----------------------------------------Initial condition--------------------------------

        for (i = 0; i < ty; i++)
        {
            for (j = 0; j < tx; j++)
            {
                mesh[i][j].u = 0;
                mesh[i][j].v = 0;
                mesh[i][j].u_tmp = 0;
                mesh[i][j].v_tmp = 0;
                mesh[i][j].u_star = 0;
                mesh[i][j].v_star = 0;
                mesh[i][j].u_new = 0;
                mesh[i][j].v_new = 0;
                mesh[i][j].p_new = 0;
                mesh[i][j].p_delta = 0;
                mesh[i][j].p_tmp = 0;
                mesh[i][j].p = 0;
                mesh[i][j].u = u_init;
                mesh[i][j].v = v_init;
                mesh[i][j].E = 0;
                mesh[i][j].d = 0;
                mesh[i][j].F = 0;
                mesh[i][j].e = 0;
                mesh[i][j].u1 = 0;
                mesh[i][j].u2 = 0;
                mesh[i][j].u3 = 0;
                mesh[i][j].u4 = 0;
                mesh[i][j].u5 = 0;
                mesh[i][j].u6 = 0;
                mesh[i][j].u7 = 0;
                mesh[i][j].u8 = 0;
                mesh[i][j].u9 = 0;
                mesh[i][j].u_nb = 0;
                mesh[i][j].u_jk = 0;
                mesh[i][j].v1 = 0;
                mesh[i][j].v2 = 0;
                mesh[i][j].v3 = 0;
                mesh[i][j].v4 = 0;
                mesh[i][j].v5 = 0;
                mesh[i][j].v6 = 0;
                mesh[i][j].v7 = 0;
                mesh[i][j].v8 = 0;
                mesh[i][j].v9 = 0;
                mesh[i][j].v_nb = 0;
                mesh[i][j].v_jk = 0;
                mesh[i][j].p_nb = 0;
                mesh[i][j].p_jk = 0;
                mesh[i][j].p_c = 0;

                //左U
                if (i >= 1 && i <= ty - 2 && j == 0)
                {
                    mesh[i][j].u = u_left;
                }
                //右U
                if (i >= 1 && i <= ty - 2 && j == tx - 2)
                {
                    mesh[i][j].u = u_right;
                }
                //上V
                if (i == 1 && j >= 1 && j <= tx - 2)
                {
                    mesh[i][j].v = v_top;
                }
                //下V
                if (i == ty - 1 && j >= 1 && j <= tx - 2)
                {
                    mesh[i][j].v = v_bottom;
                }
            }
        }


        /*printf("[U_init,V_init]\n");
        for(i=0;i<ty;i++)
        {
            for(j=0;j<tx;j++)
            {
                printf("[%d,%d]=(%10.6lf,%10.6lf) ",i,j,mesh[i][j].u,mesh[i][j].v);
            }
            printf("\n");
        }*/
        //system("pause");
        //--------------------------------開始迭代----------------------------------------
        ite = 0;
        t = 0;

        while(1)
        {

            //connect(timer1,SIGNAL(timeout()),this,SLOT(myfunc1()));
            QEventLoop loop;
            QTimer t1;
            t1.connect(&t1, &QTimer::timeout, &loop, &QEventLoop::quit);
            t1.start(*status);
            loop.exec();
            continuity = 0;
            for (i = 1; i <= ty - 2; i++)
            {
                for (j = 1; j <= tx - 2; j++)
                {
                    continuity += 10000 * (fabs((mesh[i][j].u - mesh[i][j - 1].u) * dy + (mesh[i][j].v - mesh[i + 1][j].v) * dx));
                }
            }
            //qDebug()<<*continuity_;
            QString str = QString::number(continuity);
            QString str1 = QString::number(ite);
            QString str2 = QString::number(t);
            QString show;
            show = QString::asprintf("Ite= %6d Time= %11.4lf Continuity= %10.6lf\n",str1.toInt(),str2.toDouble(),str.toDouble());
            qApp->processEvents();
            //printf("Ite = %5d  Time = %9.4lf   Continuity = %11.9lf---------------------------------------------------------------------------------------------------------------------------------\r", ite, t, fabs(continuity));
            //滾動條保持底部
            QScrollBar *scrollbar = ui->text_show->verticalScrollBar();
            if(scrollbar){
                scrollbar->setSliderPosition(scrollbar->maximum());
            }
            //输入数据

            ui->text_show->insertPlainText(show);//更新文字框內文字
            QApplication::processEvents();

            //-------------------------------STEP[1] 矩陣求解[1] 求出u_star,v_star------------------------
            for (i = 0; i <= ty - 1; i++)
            {
                for (j = 0; j <= tx - 1; j++)
                {
                    mesh[i][j].u_star = mesh[i][j].u;
                    mesh[i][j].v_star = mesh[i][j].v;
                    mesh[i][j].u_tmp = 0;
                    mesh[i][j].v_tmp = 0;
                }
            }
            while (1)
            {
                //-------------------------------更新"Ghost"邊界條件-------------------------------------
                //上U&U&左V&右V的邊無法直接定義B.C.，因此需進行內插得出Ghost上的(上U&U&左V&右V)來使邊上滿足B.C.

                for (j = 1; j <= tx - 3; j++)//上U&下U
                {
                    //上下U = 內插
                    mesh[0][j].u_star = mesh[1][j].u_star - 2.0 * (mesh[1][j].u_star - u_top);
                    mesh[ty - 1][j].u_star = mesh[ty - 2][j].u_star - 2.0 * (mesh[ty - 2][j].u_star - u_bottom);
                    //上下V = 0
                    mesh[1][j].v_star = v_top;
                    mesh[ty - 1][j].v_star = v_bottom;
                }
                for (i = 1; i <= ty - 2; i++)// 左V&右V
                {
                    //右U.V = 內U.V
                    mesh[i][tx - 1].v_star = mesh[i][tx - 2].v_star;
                    mesh[i][tx - 2].u_star = mesh[i][tx - 3].u_star;

                    //左U = U_left
                    mesh[i][0].u_star = u_left;
                    //左V = 0
                    mesh[i][0].v_star = v_left;
                }

                min_err = 0;
                //U
                for (i = 1; i <= ty - 2; i++)
                {
                    for (j = 1; j <= tx - 3; j++)
                    {
                        mesh[i][j].u1 = 0.25 * mesh[i][j].u_star + 0.5 * mesh[i][j + 1].u_star + d_miu * dxi;
                        mesh[i][j].u2 = 0.25 * mesh[i][j].u_star + 0.5 * mesh[i][j - 1].u_star - d_miu * dxi;
                        mesh[i][j].u3 = 0.25 * (mesh[i][j].v_star + mesh[i][j + 1].v_star) + d_miu * dyi;
                        mesh[i][j].u4 = 0.25 * (mesh[i + 1][j].v_star + mesh[i + 1][j + 1].v_star) - d_miu * dyi;
                        mesh[i][j].u5 = 0.25 * mesh[i][j + 1].u_star - d_miu * dxi;
                        mesh[i][j].u6 = 0.25 * mesh[i][j - 1].u_star + d_miu * dxi;
                        mesh[i][j].u7 = 0.25 * (mesh[i][j].v_star + mesh[i][j + 1].v_star) - d_miu * dyi;
                        mesh[i][j].u8 = 0.25 * (mesh[i + 1][j].v_star + mesh[i + 1][j + 1].v_star) + d_miu * dyi;
                        mesh[i][j].u9 = -1.0 * dx * dy * dti * mesh[i][j].u_star;
                        mesh[i][j].u_nb = (mesh[i][j].u5 * mesh[i][j + 1].u_star * dy) - (mesh[i][j].u6 * mesh[i][j - 1].u_star * dy) + (mesh[i][j].u7 * mesh[i - 1][j].u_star * dx) - (mesh[i][j].u8 * mesh[i + 1][j].u_star * dx);
                        mesh[i][j].u_jk = (mesh[i][j].u1 * dy) - (mesh[i][j].u2 * dy) + (mesh[i][j].u3 * dx) - (mesh[i][j].u4 * dx);

                        mesh[i][j].u_tmp = -1.0 * (mesh[i][j].u9 + dy * (mesh[i][j + 1].p / rho - mesh[i][j].p / rho) + mesh[i][j].u_nb) / (dx * dy * dti + mesh[i][j].u_jk);
                        if (fabs(mesh[i][j].u_tmp - mesh[i][j].u_star) > min_err)
                        {
                            min_err = fabs(mesh[i][j].u_tmp - mesh[i][j].u_star);
                        }
                    }
                }
                //V
                for (i = 2; i <= ty - 2; i++)
                {
                    for (j = 1; j <= tx - 2; j++)
                    {
                        mesh[i][j].v1 = 0.25 * (mesh[i - 1][j].u_star + mesh[i][j].u_star) + d_miu * dxi;
                        mesh[i][j].v2 = 0.25 * (mesh[i - 1][j - 1].u_star + mesh[i][j - 1].u_star) - d_miu * dxi;
                        mesh[i][j].v3 = 0.25 * mesh[i][j].v_star + 0.5 * mesh[i - 1][j].v_star + d_miu * dyi;
                        mesh[i][j].v4 = 0.25 * mesh[i][j].v_star + 0.5 * mesh[i + 1][j].v_star - d_miu * dyi;
                        mesh[i][j].v5 = 0.25 * (mesh[i - 1][j].u_star + mesh[i][j].u_star) - d_miu * dxi;
                        mesh[i][j].v6 = 0.25 * (mesh[i - 1][j - 1].u_star + mesh[i][j - 1].u_star) + d_miu * dxi;
                        mesh[i][j].v7 = 0.25 * mesh[i - 1][j].v_star - d_miu * dyi;
                        mesh[i][j].v8 = 0.25 * mesh[i + 1][j].v_star + d_miu * dyi;
                        mesh[i][j].v9 = -1.0 * dx * dy * dti * mesh[i][j].v_star;
                        mesh[i][j].v_nb = (mesh[i][j].v5 * mesh[i][j + 1].v_star * dy) - (mesh[i][j].v6 * mesh[i][j - 1].v_star * dy) + (mesh[i][j].v7 * mesh[i - 1][j].v_star * dx) - (mesh[i][j].v8 * mesh[i + 1][j].v_star * dx);
                        mesh[i][j].v_jk = (mesh[i][j].v1 * dy) - (mesh[i][j].v2 * dy) + (mesh[i][j].v3 * dx) - (mesh[i][j].v4 * dx);

                        mesh[i][j].v_tmp = -1.0 * (mesh[i][j].v9 + dx * (mesh[i - 1][j].p / rho - mesh[i][j].p / rho) + mesh[i][j].v_nb) / (dx * dy * dti + mesh[i][j].v_jk);
                        if (fabs(mesh[i][j].v_tmp - mesh[i][j].v_star) > min_err)
                        {
                            min_err = fabs(mesh[i][j].v_tmp - mesh[i][j].v_star);
                        }
                    }
                }

                if (min_err <= pow(10, -6))
                {
                    break;
                }

                for (i = 1; i <= ty - 2; i++)//更新u
                {
                    for (j = 1; j <= tx - 3; j++)
                    {
                        mesh[i][j].u_star = mesh[i][j].u_tmp;
                    }
                }

                for (i = 2; i <= ty - 2; i++)//更新v
                {
                    for (j = 1; j <= tx - 2; j++)
                    {
                        mesh[i][j].v_star = mesh[i][j].v_tmp;
                    }
                }

            }
            /*printf("[U_star,V_star]\n");
            for (i = 0; i <= ty - 1; i++)
            {
                for (j = 0; j <= tx - 1; j++)
                {
                    printf("[%d,%d]=(%10.6lf,%10.6lf) ", i, j, mesh[i][j].u_star, mesh[i][j].v_star);
                }
                printf("\n");
            }*/

            //-------------------------------STEP[3] 矩陣求解[2] 求出p_delta-------------------------------
            while (1)
            {
                min_err = 0;
                for (j = 0; j <= tx - 1; j++)// P_delta 上 下
                {
                    //mesh[0][j].p_delta = 0;				//上
                    //mesh[ty - 1][j].p_delta = 0;	//下
                    mesh[0][j].d = 0;				//上
                    mesh[0][j].e = 0;				//上
                    mesh[ty - 1][j].d = 0;	//下
                    mesh[ty - 1][j].e = 0;	//下
                }
                for (i = 0; i <= ty - 1; i++)//P_deltaP 左右
                {
                    //mesh[i][0].p_delta = 0;//左
                    mesh[i][0].d = 0;//左
                    mesh[i][0].e = 0;//左
                    //mesh[i][0].p_delta = 0;				//左
                    //mesh[i][tx - 1].p_delta = 0;		//右
                    mesh[i][tx - 1].d = 0;		//右
                    mesh[i][tx - 1].e = 0;		//右
                }

                for (i = 1; i <= ty - 2; i++)
                {
                    for (j = 1; j <= tx - 2; j++)
                    {
                        mesh[i][j].E = dt * mesh[i][j].u_jk * dxi * dyi;
                        if(j==tx-2)
                        {
                            mesh[i][j].d = 0;
                        }
                        else
                        {
                            mesh[i][j].d = (mesh[i][j].E * dy) / ((1.0 + mesh[i][j].E) * mesh[i][j].u_jk);
                        }



                        mesh[i][j].F = dt * mesh[i][j].v_jk * dxi * dyi;
                        if(i==1)
                        {
                            mesh[i][j].e = 0;
                        }
                        else
                        {
                            mesh[i][j].e = (mesh[i][j].F * dx) / ((1.0 + mesh[i][j].F) * mesh[i][j].v_jk);
                        }


                        mesh[i][j].p_nb = (mesh[i][j].d * dy * mesh[i][j + 1].p_delta / rho + mesh[i][j - 1].d * dy * mesh[i][j - 1].p_delta / rho + mesh[i][j].e * dx * mesh[i - 1][j].p_delta / rho + mesh[i + 1][j].e * dx * mesh[i + 1][j].p_delta / rho);
                        mesh[i][j].p_c = -1.0 * ((mesh[i][j].u_star - mesh[i][j - 1].u_star) * dy + (mesh[i][j].v_star - mesh[i + 1][j].v_star) * dx);
                        mesh[i][j].p_jk = (mesh[i][j].d + mesh[i][j - 1].d) * dy + (mesh[i][j].e + mesh[i + 1][j].e) * dx;

                        mesh[i][j].p_tmp = (mesh[i][j].p_nb + mesh[i][j].p_c) / mesh[i][j].p_jk;

                        if (fabs(mesh[i][j].p_tmp - mesh[i][j].p_delta) > min_err)
                        {
                            min_err = fabs(mesh[i][j].p_tmp - mesh[i][j].p_delta);
                        }

                    }
                }
                for (i = 1; i <= ty - 2; i++)//更新p_delta
                {
                    for (j = 1; j <= tx - 2; j++)
                    {
                        mesh[i][j].p_delta = mesh[i][j].p_tmp;
                    }
                }


                if (min_err <= pow(10, -6))
                {
                    break;
                }


            }
//            printf("[P_delta]\n");
//            for (i = 0; i <= ty - 1; i++)
//            {
//                for (j = 0; j <= tx - 1; j++)
//                {
//                    printf("[%d,%d]=(%10.6lf) ", i, j, mesh[i][j].p_delta);
//                }
//                printf("\n");
//            }
            //system("pause");
            //-------------------------------STEP[4] 更新P_n+1-------------------------------


            for (i = 1; i <= ty - 2; i++)//更新p
            {
                for (j = 1; j <= tx - 2; j++)
                {
                    mesh[i][j].p = mesh[i][j].p + P_relax * mesh[i][j].p_delta;

                }
            }
            for (j = 1; j <= tx - 2; j++)// P上 下
            {
                mesh[0][j].p = mesh[1][j].p;				//上
                mesh[ty - 1][j].p = mesh[ty - 2][j].p;	//下
            }
            for (i = 1; i <= ty - 2; i++)//P 左右
            {
                mesh[i][0].p = mesh[i][1].p;
                mesh[i][tx - 1].p = 0;		//右
            }
            //-------------------------------STEP[5] 更新U,V-------------------------------
             num = 0;
            for (i = 1; i <= ty - 2; i++)
            {
                for (j = 0; j <= tx - 2; j++)
                {
                    /*mesh[i][j].E = dt * mesh[i][j].u_jk * dxi * dyi;
                    mesh[i][j].d = (mesh[i][j].E * dy) / ((1.0 + mesh[i][j].E) * mesh[i][j].u_jk);*/

                    mesh[i][j].u = (mesh[i][j].u_star + U_relax * mesh[i][j].d * (mesh[i][j].p_delta - mesh[i][j + 1].p_delta));
                    if(mesh[i][j].u>num)
                    {
                        num = mesh[i][j].u;//u max計算
                    }

                }
            }

            for (i = 1; i <= ty - 1; i++)
            {
                for (j = 1; j <= tx - 2; j++)
                {
                    /*mesh[i][j].F = dt * mesh[i][j].v_jk * dxi * dyi;
                    mesh[i][j].e = (mesh[i][j].F * dx) / ((1.0 + mesh[i][j].F) * mesh[i][j].v_jk);*/

                    mesh[i][j].v = (mesh[i][j].v_star + U_relax * mesh[i][j].e * (mesh[i][j].p_delta - mesh[i - 1][j].p_delta));
                }
            }
            for (j = 0; j <= tx - 1; j++)//更新Ghost mesh--"U,V"
            {
                //上下U = 內插
                mesh[0][j].u = mesh[1][j].u - 2.0 * (mesh[1][j].u - u_top);
                mesh[ty - 1][j].u = mesh[ty - 2][j].u - 2.0 * (mesh[ty - 2][j].u - u_bottom);
                //上下V = 0
                mesh[1][j].v = v_top;
                mesh[ty - 1][j].v = v_bottom;
            }


            /*printf("[Total_U]\n");
            for (i = 0; i <= ty - 1; i++)
            {
                for (j = 0; j <= tx - 1; j++)
                {
                    printf("[%d,%d]=(%10.6lf) ", i, j, mesh[i][j].u);
                }
                printf("\n");
            }
            printf("[Total_V]\n");
            for (i = 0; i <= ty - 1; i++)
            {
                for (j = 0; j <= tx - 1; j++)
                {
                    printf("[%d,%d]=(%10.6lf) ", i, j, mesh[i][j].v);
                }
                printf("\n");
            }
            printf("[Total_P]\n");
            for (i = 0; i <= ty - 1; i++)
            {
                for (j = 0; j <= tx - 1; j++)
                {
                    printf("[%d,%d]=(%10.6lf) ", i, j, mesh[i][j].p);
                }
                printf("\n");
            }*/
            //printf("[--------------------------------------------------------------------------------------------------------------------------------------------------------]\n");
            ite++;
            t += dt;
            double z,x,y;
            //colormap資料放入 左下[0][0] 右上End
            for (int xIndex=0; xIndex<mx; ++xIndex)
              {
               for (int yIndex=0; yIndex<my; ++yIndex)
              {
                colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);//將xIndex yIndex轉化為color map之x y
                z=(mesh[(ty-2) - yIndex ][(xIndex + 1)].u );//u內插
                colorMap->data()->setCell(xIndex, yIndex, z);//放入x y z
              }
            }
            ui->customPlot->rescaleAxes(true);//自動縮放軸範圍
            colorMap->rescaleDataRange(true);//自動縮放color bar範圍
            //ui->customPlot->replot(QCustomPlot::rpQueuedReplot);
            ui->customPlot->replot();//更新畫布
            if(*save == 1)//出檔
            {
                FILE *fp;
                //輸出流場
                fp = fopen("Poseii Flow.TEC", "w");
                fprintf(fp, "TITLE = \" Poseii Flow \" \n");
                fprintf(fp, " VARIABLES=\"x\",\"y\",\"u\",\"v\",\"p\"\n");
                fprintf(fp, "ZONE T=\"%5d \" I =   %d, J =   %d F = POINT\n", ite, mx + 1, my + 1);
                for (i = ty - 2; i >= 0; i--)
                {
                    for (j = 1; j <= tx - 1; j++)
                    {
                        fprintf(fp, "%7.4lf %7.4lf %10.6lf %10.6lf %10.6lf\n", (j - 1) * dx, abs(i - my) * dy - y_init, 0.5 * (mesh[i][j - 1].u + mesh[i + 1][j - 1].u), 0.5 * (mesh[i + 1][j].v + mesh[i + 1][j - 1].v), 0.25 * (mesh[i][j].p + mesh[i][j - 1].p + mesh[i + 1][j].p + mesh[i + 1][j - 1].p));
                    }
                }
                fclose(fp);

                //輸出U_profile
                fp = fopen("Centerline Velocity Profile.TEC", "w");
                fprintf(fp, "TITLE=\" title \"\n");
                fprintf(fp, "VARIABLES=\" u(m/s) \", \" Y[m] \"\n");
                fprintf(fp, "ZONE T=\"%3dx%3d Centerline Velocity Profile\" I =   %d, J = 1, F = POINT\n", mx, my, my + 1);
                for (i = ty - 2; i >= 0; i--)
                {
                    if (mx % 2 != 0)//要平均
                    {
                        int right = mx / 2;
                        int left = (mx / 2) + 1;
                        fprintf(fp, "%10.6lf %10.6lf\n", 0.5 * (0.5 * (mesh[i][right].u + mesh[i + 1][right].u) + 0.5 * (mesh[i][left].u + mesh[i + 1][left].u)), abs(i - my) * dy - y_init);
                    }
                    if (mx % 2 == 0)//在mesh上
                    {
                        int temp = (mx / 2);
                        fprintf(fp, "%10.6lf %10.6lf\n", 0.5 * (mesh[i][temp].u + mesh[i + 1][temp].u), abs(i - my) * dy - y_init);
                    }
                }
                fclose(fp);

                //輸出壓力梯度
                fp = fopen("Pressure Gradient.TEC", "w");
                fprintf(fp, "TITLE=\" title \"\n");
                fprintf(fp, "VARIABLES=\" X[m] \", \" P[Pa] \"\n");
                fprintf(fp, "ZONE T=\"%3dx%3d Pressure Gradient\" I =   %d, J = 1, F = POINT\n", mx, my, mx + 1);
                for (j = 1; j <= tx - 1; j++)
                {
                    if (my % 2 != 0)
                    {
                        int temp = (my / 2) + 1;
                        fprintf(fp, "%10.6lf %10.6lf\n", (j - 1) * dx, 0.25 * (mesh[temp - 1][j - 1].p + mesh[temp - 1][j].p + mesh[temp + 1][j - 1].p + mesh[temp + 1][j].p) + 0.5 * (mesh[temp][j - 1].p + mesh[temp][j].p));
                    }
                    if (my % 2 == 0)//在mesh上
                    {
                        int temp = (my / 2);
                        fprintf(fp, "%10.6lf %10.6lf\n", (j - 1) * dx, 0.25 * (mesh[temp][j].p + mesh[temp][j - 1].p + mesh[temp + 1][j].p + mesh[temp + 1][j - 1].p));
                    }
                }
                fclose(fp);
                *save = 0;//出檔完歸0
                ui->text_show->insertPlainText("Output Done!\n");
                qDebug()<<"output";

            }
        }




}


void Simple::on_pushButton_clicked()//Pause & run
{
    if(*status == 1 )// 暫停6秒
    {
        *status = 6000;
        m_timer->start(6000);
        qDebug()<<"Pause";
    }
    else if(*status == 6000)//如以暫停 恢復
    {
        *status = 1;
        m_timer->start(50);
        qDebug()<<"Run";
    }


}


void Simple::on_pushButton_2_clicked()//Output
{
    *save = 1;//1為出檔訊號
}



void Simple::generateData()//抓取continuity
{
    int * step = &ite;
    //qDebug()<<*continuity_;
    m_chart->m_x = *step;  //即時更新continuity chart x點
    m_chart->m_y = *continuity_ ;  //即時更新continuity chart y點
    m_chart->m_series->append(m_chart->m_x, m_chart->m_y);//放入點
    m_chart->m_series->setColor(QColor(255,0,0));//將線改為紅色
    m_chart->m_axisX->setRange(0,*step);//即時調整x軸值=iteration number
    if(*continuity_ >= 0.99)
    {
        m_chart->m_axisY->setRange(0,*continuity_*1.25);
    }    


}


void Simple::on_pushButton_3_clicked()//Reset plot
{
    m_chart->m_series->clear();
    d_chart->m_series->clear();    
}

void Simple::get_umax()
{

    int * step = &ite;
    double *U_max = &num;
    //qDebug()<<*U_max;
    d_chart->m_x = *step;  //即時更新U_max chart x點
    d_chart->m_y = *U_max ;  //即時更新U_max chart y點
    d_chart->m_series->append(d_chart->m_x, d_chart->m_y);
    d_chart->m_axisY->setRange(0,*U_max*2);//即時調整Y軸範圍=0 到 2倍U_max
    d_chart->m_axisX->setRange(0,*step);//即時調整x軸值=iteration number

}
Chart *Simple::createdChart() const
{

    d_chart->setTitle("<b>U<sub>max</sub></b>");
    d_chart->legend()->hide();
    d_chart->m_axisY->setRange(0,0.02);

    return d_chart;
}

void Simple::closeEvent( QCloseEvent * event)
{
    switch( QMessageBox::information( this, tr("exit tip"), tr("Do you really want exit?"), tr("Yes"), tr("No"), 0, 1 ) )
   {
     case 0:
          event->accept();
          exit(EXIT_FAILURE);//手動關閉應用程式 確保完整結束
          break;
     case 1:
     default:
         event->ignore();
         break;
   }
}
