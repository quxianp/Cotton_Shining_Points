#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QRandomGenerator>
#include <QStyleFactory>
#include <QSplashScreen>
#include <QDateTime>
#include <QPixmap>
#include <QImage>
#include <QProgressBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QThread>
#include <QScreen>
#include <QGuiApplication>
#include <QFontDatabase>
#include <QDebug>

//注册字体
void registerFont(const QString &path) {
    int id = QFontDatabase::addApplicationFont(path);
    if (id == -1) {
        qWarning() << "Failed to load font:" << path;
        return;
    }
    QStringList families = QFontDatabase::applicationFontFamilies(id);
    qDebug() << "Loaded font:" << path << "-> families:" << families;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 注册6个字体
    registerFont(":/res/font/PangMenZhengDaoBiaoTiTiMianFeiBan-2.ttf");
    registerFont(":/res/font/FangZhengShuSong-GBK-1.ttf");
    registerFont(":/res/font/Dengl.ttf");
    registerFont(":/res/font/fzletter-2.ttf");
    registerFont(":/res/font/times.ttf");
    registerFont(":/res/font/Didot Bold.ttf");
    registerFont(":/res/font/Didot-Italic-2.ttf");

    //获取屏幕尺寸 缩放尺寸到1/2
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeo = screen->geometry();
    int scrW = screenGeo.width();
    int scrH = screenGeo.height();

    int targetW = scrW / 2;
    int targetH = scrH / 2;

    QPixmap original(":/res/start.png");
    QPixmap scaled = original.scaled(targetW, targetH, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QSplashScreen splash(scaled);

    int x = (scrW - scaled.width()) / 2;
    int y = (scrH - scaled.height()) / 2;
    splash.move(x, y);

    splash.showMessage(QObject::tr("Loading..."), Qt::AlignBottom | Qt::AlignCenter, Qt::white);
    splash.show();
    a.processEvents();

    QElapsedTimer timer;
    timer.start();

    MainWindow w;

    //延时2.5s
    int remaining = 2500 - static_cast<int>(timer.elapsed());
    if (remaining > 0) {
        QThread::msleep(remaining);
    }

    a.setStyle(QStyleFactory::create("Macintosh"));



    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Cotton_Shining_Points_GUI_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }


    a.setStyle(QStyleFactory::create("Macintosh"));
    w.show();
    splash.finish(&w);
    splash.close();
    return a.exec();
}
