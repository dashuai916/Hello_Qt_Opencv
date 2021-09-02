#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 构造函数
    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_browser_1_pressed()
{
    // QFileDialog打开文件对话框，QDir处理目录路径，QFile处理文件
    QString filename = QFileDialog::getOpenFileName(this, "打开图片", QDir::currentPath(),
                                                    "Images (*.jpg *.png *.bmp)");
    if(QFile::exists(filename))
    {
        ui->lineEdit_1->setText(filename);
    }
}


void MainWindow::on_browser_2_pressed()
{
    QString filename = QFileDialog::getSaveFileName(this, "选择输出图片", QDir::currentPath(),
                                                    "Images *.jpg *.png *.bmp");
    if(!filename.isEmpty())
    {
        ui->lineEdit_2->setText(filename);
        using namespace cv;
        Mat inputImg, outputImg;
        inputImg = imread(ui->lineEdit_1->text().toStdString());
        if(ui->mediumBlur->isChecked())
        {
            cv::medianBlur(inputImg, outputImg, 5);
        }
        else if(ui->gaussBlur->isChecked())
        {
            cv::GaussianBlur(inputImg, outputImg, Size(5, 5), 1.25);
        }
        imwrite(filename.toStdString(), outputImg);
        if(ui->checkOpenBox->isChecked())
        {
            namedWindow("show picture", WINDOW_NORMAL);
            imshow("show picture", outputImg);
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int result = QMessageBox::warning(this, "退出", "要关闭程序吗?", QMessageBox::Yes, QMessageBox::No);
    if(result == QMessageBox::Yes)
    {
        saveSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::saveSettings()
{
    QSettings settings("Yu", "Hello_Qt_Opencv", this);
    settings.setValue("input_line_edit", ui->lineEdit_1->text());
    settings.setValue("output_line_edit", ui->lineEdit_2->text());
    settings.setValue("medianBlur", ui->mediumBlur->isChecked());
    settings.setValue("gaussBlur", ui->gaussBlur->isChecked());
    settings.setValue("if_display_img", ui->checkOpenBox->isChecked());
}

void MainWindow::loadSettings()
{
    QSettings settings("Yu", "Hello_Qt_Opencv", this);
    ui->lineEdit_1->setText(settings.value("input_line_edit").toString());
    ui->lineEdit_2->setText(settings.value("output_line_edit").toString());
    ui->mediumBlur->setChecked(settings.value("medianBlur").toBool());
    ui->gaussBlur->setChecked(settings.value("gaussBlur").toBool());
    ui->checkOpenBox->setChecked(settings.value("if_display_img").toBool());
}
