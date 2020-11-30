#include "mainwindow.h"
#include "document.h"
#include "sortation.h"
#include "ui_mainwindow.h"

QString srtTitle[9]={Kor("���� ����"), Kor("�з� ����"),Kor("��� ����"),Kor("Ȱ�� �� ���� ���"),
                     Kor("�ڰ���"),Kor("������Ʈ"),Kor("�ڱ�Ұ���"),Kor("��Ʈ������"), Kor("��Ÿ")};

QVector<QWidget*> docList[9];
QVector<QPushButton*> docBtnList[9];
Sortation *sortation;
QString AppPath=QApplication::applicationDirPath();
QString srtPath = AppPath+"/Data/Srt";

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AppPath=QApplication::applicationDirPath();
    srtPath = AppPath+"/Data/Srt";

    ui->startImg->setStyleSheet("background-color: rgb(158, 158, 158)");
    sortation = new Sortation(ui->centralwidget);
    sortation->hide();
    ui->docTab->hide();

    QMenu *pFileMenu;
    QAction *pSlotNewFile = new QAction(Kor("����"), this);
    pSlotNewFile->setShortcut(Kor("Ctrl+S"));
    pSlotNewFile->setStatusTip(Kor("���������� �����մϴ�."));
    connect(pSlotNewFile, SIGNAL(triggered()), sortation, SLOT(save_docList()));
    pFileMenu = menuBar()->addMenu(Kor("����"));
    pFileMenu->addAction(pSlotNewFile); // ���� �ɼ�

    pSlotNewFile = new QAction(Kor("�ٸ� �̸����� ����"), this);
    pSlotNewFile->setShortcut(Kor("Ctrl+Shift+S"));
    pSlotNewFile->setStatusTip(Kor("�ٸ� �̸����� �����մϴ�."));
    connect(pSlotNewFile, SIGNAL(triggered()), sortation, SLOT(save_pdf()));
    pFileMenu->addAction(pSlotNewFile); // pdf ����

    ui->docTab->setTabsClosable(true);
    connect(ui->docTab, SIGNAL(tabCloseRequested(int)), this, SLOT(on_docTab_deleteTab(int)));

    //    this->setStyleSheet("#pushButton:hover { background-color: red; "
    //                        "border-style: outset; border-width: 2px;border-radius: 10px; border-color: beige;"
    //                        "font: bold 14px;min-width: 10em;padding: 6px; }");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_docTab_deleteTab(int idx) {
    ui->docTab->removeTab(idx);
    if (ui->docTab->count() == 0) {
        ui->docTab->hide();
        ui->startImg->show();
    }
}
