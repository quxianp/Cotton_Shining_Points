#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->input_of_points, SIGNAL(returnPressed()), this, SLOT(on_done_clicked())); //连接回车信号和输出槽
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_done_clicked()
{
    ui->output_of_points->setText(""); //清空输出
    QString chr = ui->input_of_points->text(); //获取input number
    unsigned long long num = chr.toInt(); //字符串转整型
    for(unsigned long long i = 0; i < num; i++) {
        //ui->output_of_points->append("."); //append自带追加换行
        ui->output_of_points->insertPlainText("."); //insertplaintext追加字符 不自带换行
    }
}


void MainWindow::on_exit_clicked()
{
    this->close(); //关闭窗口
}


void MainWindow::on_random_clicked()
{
    int random_num = QRandomGenerator::global()->bounded(1,10000); //生成随机数
    QString chr_random_num = QString::number(random_num); //将int转为QString
    ui->input_of_points->setText(chr_random_num); //显示到input
}

