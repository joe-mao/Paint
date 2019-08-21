#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::createChart()
{
   //创建图表

        QChart * chart = new QChart();
        chart->setTitle("YTF Test Result");
        this->ui->myChartView->setChart(chart);

        //创建折线序列
        series0 = new QLineSeries();
        series0->setName("Current(mA)");
        chart->addSeries(series0);

        series1 = new QLineSeries();
        series1->setName("YTF Central Frequency(GHz)");
        chart->addSeries(series1);

        series2 = new QLineSeries();
        series2->setName("-3dBBW(MHz)");
        chart->addSeries(series2);

        series3 = new QLineSeries();
        series3->setName("LOSS(dB)");
        chart->addSeries(series3);

        series4 = new QLineSeries();
        series4->setName("Flatness(dB)");
        chart->addSeries(series4);

        series5 = new QLineSeries();
        series5->setName("Offset(MHz)");
        chart->addSeries(series5);

        series6 = new QLineSeries();
        series6->setName("|BW - Offset|(MHz)");
        chart->addSeries(series6);

        //创建坐标轴
        QValueAxis * axisX = new QValueAxis;//x轴
        axisX->setTitleText("GHz(frequency)");//标题
        axisX->setRange(3, 27);
        axisX->setTickCount(11);
        axisX->setMinorTickCount(5);

        QValueAxis * axisY = new QValueAxis;//Y轴
        axisY->setTitleText("value");
        axisY->setRange(-20, 620);
        axisY->setTickCount(11);
        axisY->setMinorTickCount(5);

        chart->setAxisX(axisX, series0);//为序列设置坐标轴
        chart->setAxisY(axisY, series0);

        chart->setAxisX(axisX, series1);//为序列设置坐标轴
        chart->setAxisY(axisY, series1);

        chart->setAxisX(axisX, series2);//为序列设置坐标轴
        chart->setAxisY(axisY, series2);

        chart->setAxisX(axisX, series3);//为序列设置坐标轴
        chart->setAxisY(axisY, series3);

        chart->setAxisX(axisX, series4);//为序列设置坐标轴
        chart->setAxisY(axisY, series4);

        chart->setAxisX(axisX, series5);//为序列设置坐标轴
        chart->setAxisY(axisY, series5);

        chart->setAxisX(axisX, series6);//为序列设置坐标轴
        chart->setAxisY(axisY, series6);

        foreach(QLegendMarker * marker, chart->legend()->markers()){
            connect(marker, SIGNAL(clicked()), this, SLOT(on_LegendMarkerClicked()));
        }
}

void MainWindow::prepareData()
{
    //序列添加值
    for(map<double, vector<double>>::iterator it = readResult.begin(); it != readResult.end(); ++it){
        // qDebug()<<it->first<<" " <<it->second[0];
        series0->append(it->first, it->second[0]);
        series1->append(it->first, it->second[1]);
        series2->append(it->first, it->second[2]);
        series3->append(it->first, it->second[3]);
        series4->append(it->first, it->second[4]);
        series5->append(it->first, it->second[5]);
        series6->append(it->first, it->second[6]);
    }
}

void MainWindow::process_line(QString &line)
{
    if(0 == readFlag){
        return;
    }
    QStringList stringList = line.split(",");
    readResult[stringList[0].toDouble()].push_back(stringList[1].toDouble());//Current(mA)
    readResult[stringList[0].toDouble()].push_back(stringList[2].toDouble());//YTF Central Frequency(GHz)
    readResult[stringList[0].toDouble()].push_back(stringList[3].toDouble());//-3dBBW(MHz)

    readResult[stringList[0].toDouble()].push_back(stringList[4].toDouble());//LOSS(dB)
    readResult[stringList[0].toDouble()].push_back(stringList[5].toDouble());//Flatness(dB)
    readResult[stringList[0].toDouble()].push_back(stringList[6].toDouble());//Offset(MHz)
    readResult[stringList[0].toDouble()].push_back(stringList[7].toDouble());//|BW - Offset|(MHz)
}

void MainWindow::iniStartData()
{
    fileName = "";
    readFlag = 0;
    readResult.clear();
    series0->clear();
    series1->clear();
    series2->clear();
    series3->clear();
    series4->clear();
    series5->clear();
    series6->clear();
    this->ui->myChartView->chart()->zoomReset();//恢复原始大小
}

void MainWindow::on_mouseMovePoint(QPoint point)
{
    //鼠标移动响应
    QPointF pt = this->ui->myChartView->chart()->mapToValue(point);//转换为图表的数值
    labXYValue->setText(QString::asprintf("X = %.1f, Y = %.2f", pt.x(), pt.y()));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(this->ui->myChartView);
    labXYValue = new QLabel("X=, Y= ");//状态栏显示鼠标点的坐标
    labXYValue->setMinimumWidth(200);
    this->ui->statusBar->addWidget(labXYValue);
    createChart();//创建图表
    prepareData();//生成数据
    QObject::connect(this->ui->myChartView, SIGNAL(mouseMovePoint(QPoint)), this, SLOT(on_mouseMovePoint(QPoint)));//鼠标移动事件

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{

    iniStartData();
    fileName = QFileDialog::getOpenFileName(this, "Open File", "./", "*");

    if(fileName == ""){
        return;
    }

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){ return; }
    QTextStream in(&file);

    while(!in.atEnd()){
        QString line = in.readLine();
        process_line(line);
        ++readFlag;
    }
    file.close();
    fileName = "";
    prepareData();
}

void MainWindow::on_LegendMarkerClicked()
{
    QLegendMarker * marker = qobject_cast<QLegendMarker *>(sender());
    switch (marker->type()) {
        case QLegendMarker::LegendMarkerTypeXY://QLineSeries序列
            {
                marker->series()->setVisible(!marker->series()->isVisible());
                marker->setVisible(true);
            }
    }
}

void MainWindow::on_actionZoomIn_triggered()
{
    this->ui->myChartView->chart()->zoom(1.2);//放大
}

void MainWindow::on_actionZoomOut_triggered()
{
    this->ui->myChartView->chart()->zoom(0.8);//缩小
}

void MainWindow::on_actionRealSize_triggered()
{
    this->ui->myChartView->chart()->zoomReset();//恢复原始大小
}

void MainWindow::on_actionExit_triggered()
{

}
