#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <map>
#include <vector>
#include <QLineSeries>
#include <QtCharts>

using namespace QtCharts;

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel * labXYValue;//状态栏显示文字标签
    void createChart();//创建图表
    void prepareData();//准备数据

    QString fileName = "";
    void process_line(QString & line);
    int readFlag = 0;
    map<double, vector<double>> readResult;

     QLineSeries * series0 = nullptr;
     QLineSeries * series1 = nullptr;
     QLineSeries * series2 = nullptr;
     QLineSeries * series3 = nullptr;
     QLineSeries * series4 = nullptr;
     QLineSeries * series5 = nullptr;
     QLineSeries * series6 = nullptr;

     void iniStartData();


private slots:
    void on_mouseMovePoint(QPoint point);//鼠标移动事件，自定义槽函数
    void on_actionOpen_triggered();
    void on_LegendMarkerClicked();
    void on_actionZoomIn_triggered();
    void on_actionZoomOut_triggered();
    void on_actionRealSize_triggered();
    void on_actionExit_triggered();
};

#endif // MAINWINDOW_H
