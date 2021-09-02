#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QFileDialog"
#include "QFile"
#include "QDir"
#include "QMessageBox"
#include "QCloseEvent"
#include "QSettings"
#include "opencv2/opencv.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // 关闭程序事件
    void closeEvent(QCloseEvent *event);

private slots:
    // 点击第一个浏览按钮
    void on_browser_1_pressed();
    // 点击第二个浏览按钮
    void on_browser_2_pressed();

private:
    Ui::MainWindow *ui;
    void saveSettings();
    void loadSettings();
};
#endif // MAINWINDOW_H
