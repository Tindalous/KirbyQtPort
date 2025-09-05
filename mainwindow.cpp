#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <chrono>

#ifdef __cplusplus
extern "C" {
#endif

    #include "mainOG.h"

#ifdef __cplusplus
}
#endif


QImage* DrawBuffer() {
    QImage* ret = new QImage(128, 64, QImage::Format_RGB32);
    QColor* fg = new QColor(57,41,51);
    QColor* bg = new QColor(255,234,248);
    ret->fill(*bg);
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 128; x++) {
            byte temp = getBuffer(x,y);

            byte mask = 0x01;
            for (int y2 = 0; y2 < 8; y2++) {
                if ((temp & mask) != 0) {
                    ret->setPixelColor(x,y*8+y2,*fg);
                }
                mask = mask << 1;
            }
        }
    }
    return ret;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case 65: //A
        inputButtons[0] = 1;
        break;
    case 68: //D
        inputButtons[1] = 1;
        break;
    case 74: //J
        inputButtons[2] = 1;
        if (partOfTutorial != -1) advanceTutorial(0);
        break;
    case 75: //K
        inputButtons[3] = 1;
        if (partOfTutorial != -1) advanceTutorial(1);
        break;
    case 70: //F - Bigger screen
        screenSize+=2;
        if (screenSize > 16) screenSize = 4;
        if (partOfTutorial != -1) resizeTutorial();
        //TODO pensar como hacer para que siempre esté centrado
        break;
    }


}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
    switch (event->key()) {
    case 65:
        inputButtons[0] = 0;
        break;
    case 68:
        inputButtons[1] = 0;
        break;
    case 74:
        inputButtons[2] = 0;
        break;
    case 75:
        inputButtons[3] = 0;
        break;
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QPixmap* pix = new QPixmap(":/all/basic/Tutorial0.png");
    scene->addPixmap(*pix);
    //QDebug() << pix;
}

void MainWindow::resizeTutorial() {

    QString str(":/all/basic/Tutorial%1.png");
    str = str.arg(partOfTutorial);
    QPixmap* pix = new QPixmap(str);
    SetWindowItem(pix);
}

void MainWindow::SetWindowItem(QPixmap* pix) {

    scene->clear();
    *pix = pix->scaledToWidth(128*screenSize);
    scene->addPixmap(*pix);
    scene->setSceneRect(0,0,128*screenSize,64*screenSize);
}

void MainWindow::advanceTutorial(int input) {

    if (input == 0) partOfTutorial++;
    if (partOfTutorial > 5) {
        partOfTutorial = 4;
    }
    QString str(":/all/basic/Tutorial%1.png");
    str = str.arg(partOfTutorial);
    QPixmap* pix = new QPixmap(str);
    SetWindowItem(pix);

    if (input == 1 && partOfTutorial >= 4) {

        setLevel(partOfTutorial - 4);
        //qDebug() << partOfTutorial;
        partOfTutorial = -1;
        //Iniciar juego
        initFrame();


        QPixmap* pix = new QPixmap();
        QImage* rets = DrawBuffer();
        *pix = pix->fromImage(*rets);
        SetWindowItem(pix);

        frameTimer = new QTimer();
        frameTimer->setInterval(1000);
        frameTimer->start();
        connect(frameTimer,SIGNAL(timeout()),this,SLOT(ProcessInitGame()));
    }
}

void MainWindow::ProcessInitGame() {
    frameTimer->stop();
    initGame();
    frameTimer = new QTimer();
    frameTimer->setInterval(33);
    frameTimer->start();
    connect(frameTimer,SIGNAL(timeout()),this,SLOT(ProcessNewFrame()));
}

void MainWindow::ProcessNewFrame() {
    //auto start = std::chrono::system_clock::now();
    char* s = frame(inputButtons[0],inputButtons[1],inputButtons[2],inputButtons[3]);

    //qDebug() << s;

    QPixmap* pix = new QPixmap();
    QImage* rets = DrawBuffer();
    *pix = pix->fromImage(*rets);
    SetWindowItem(pix);

    //auto end = std::chrono::system_clock::now();
    //std::chrono::duration<float,std::milli> duration = end - start;
    //qDebug() << duration.count();

    frameTimer->setInterval(33);
}


MainWindow::~MainWindow()
{
    delete ui;
}
