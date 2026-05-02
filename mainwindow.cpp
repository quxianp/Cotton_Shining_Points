#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QRandomGenerator>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //菜单栏 about
    connect(ui->actionProducer, &QAction::triggered, this, &MainWindow::onProducerTriggered);   //producer
    connect(ui->actionCotton_s_Bilibili_Space, &QAction::triggered, this, &MainWindow::onOpenSourceTriggered);  //source address

    //内容居中
    QWidget *central = ui->centralwidget;
    if (central) {
        //收集所有子控件，并计算它们占据的最大范围
        QList<QWidget*> widgets;
        int maxX = 0, maxY = 0;
        for (QObject *obj : central->children()) {
            if (QWidget *w = qobject_cast<QWidget*>(obj)) {
                widgets.append(w);
                maxX = qMax(maxX, w->x() + w->width());
                maxY = qMax(maxY, w->y() + w->height());
            }
        }

        if (!widgets.isEmpty()) {
            //创建内容容器，把所有控件移进去
            QWidget *content = new QWidget(central);
            content->setFixedSize(maxX + 40, maxY + 40); // 留一点边距

            for (QWidget *w : widgets) {
                w->setParent(content);  // 转移父对象，坐标保持不变
            }

            //给 centralWidget 设置网格布局，让 content 始终居中
            QGridLayout *grid = new QGridLayout(central);
            grid->setContentsMargins(0, 0, 0, 0);
            grid->addWidget(content, 0, 0, Qt::AlignCenter);
            grid->setRowStretch(0, 1);
            grid->setColumnStretch(0, 1);
        }
    }

    ui->statusbar->setSizeGripEnabled(false); //去掉状态栏右下角的三角
    ui->statusbar->setStyleSheet(QString("QStatusBar::item{border: 0px}")); //设置不显示label的边框
    QLabel *permanent=new QLabel(this);
    //permanent->setFrameStyle(QFrame::Box|QFrame::Sunken);
    permanent->setText(tr("Produced by QuXian"));
    ui->statusbar->addPermanentWidget(permanent); //显示永久信息

    connect(ui->input_of_points, SIGNAL(returnPressed()), this, SLOT(on_done_clicked())); //连接回车信号和输出槽
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_done_clicked()
{
    ui->output_of_points->clear();              // 清空输出
    QString chr = ui->input_of_points->text();
    unsigned long long num = chr.toULongLong(); // 安全转换，避免溢出

    if (num == 0) {
        ui->output_of_points->setHtml(R"(<span style="font-family:'庞门正道标题体'; font-size:46pt"><b>?</b></span>)");
        return;
    }

    //预分配内存  批量填充只操作一次 UI
    QString dots;
    dots.resize(static_cast<int>(num));         // 一次申请够用的内存
    dots.fill('.');                             // 全部填成 '.'

    ui->output_of_points->setPlainText(dots);   // 一次性写入，不卡界面
}


void MainWindow::on_exit_clicked()
{
    this->close(); //关闭窗口
}


void MainWindow::on_random_clicked()
{
    const unsigned long long MAX_SAFE = 100000;

    // 随机数[1, 100000]
    unsigned long long random_num = QRandomGenerator::global()->bounded(MAX_SAFE) + 1;

    ui->input_of_points->setText(QString::number(random_num));

    QString chr_random_num = QString::number(random_num); //将int转为QString
    ui->input_of_points->setText(chr_random_num); //显示到input
}


void MainWindow::onProducerTriggered()
{
    QDesktopServices::openUrl(QUrl("https://space.bilibili.com/631151779"));

}

void MainWindow::onOpenSourceTriggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/quxianp/Cotton_Shining_Points"));
}

