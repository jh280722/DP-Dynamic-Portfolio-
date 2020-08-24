#include "mainwindow.h"
#include "Document.h"
#include "sortation.h"
#include "ui_mainwindow.h"

QString srtTitle[9]={Kor("���� ����"), Kor("�з� ����"),Kor("��� ����"),Kor("Ȱ�� �� ���� ���"),
                     Kor("�ڰ���"),Kor("������Ʈ"),Kor("�ڱ�Ұ���"),Kor("��Ʈ������"), Kor("��Ÿ")};

QVector<QWidget*> docList[9];
QVector<QPushButton*> docBtnList[9];
Sortation *sortation;
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sortation = new Sortation(ui->centralwidget);
    //    int w=ui->intro->width();
    //    int h=ui->intro->height();
    //    QPixmap pix(":/img/Start.png");
    //ui->intro->setPixmap(pix);
    //ui->intro->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    QMenu *pFileMenu;
    QAction *pSlotNewFile = new QAction(Kor("����"), this);
    pSlotNewFile->setShortcut(Kor("Ctrl+S"));
    pSlotNewFile->setStatusTip(Kor("���������� �����մϴ�."));
    connect(pSlotNewFile, SIGNAL(triggered()), this, SLOT(Main_SlotTest1()));
    pFileMenu = menuBar()->addMenu(Kor("����"));
    pFileMenu->addAction(pSlotNewFile); // �׽�Ʈ

//    docTab1= new TabWidget(ui->docTab);
//    docTab1->setObjectName("docTab");
//    docTab1->setTabsClosable(true);
    ui->docTab->setTabsClosable(true);
//    connect(docTab1, SIGNAL(tabCloseRequested(int)), this, SLOT(on_docTab_deleteTab(int)));
    connect(ui->docTab, SIGNAL(tabCloseRequested(int)), this, SLOT(on_docTab_deleteTab(int)));

    //    this->setStyleSheet("#pushButton:hover { background-color: red; "
    //                        "border-style: outset; border-width: 2px;border-radius: 10px; border-color: beige;"
    //                        "font: bold 14px;min-width: 10em;padding: 6px; }");
}

//void MainWindow::Main_SlotTest1(){
//    QString fileName = QFileDialog::getSaveFileName(this,
//                                                    tr("Resume Resume"), "",
//                                                    tr("ReRe (*.rr);;All Files (*)"));

//    if(fileName.isEmpty())return;
//    else{
//        QFile file(fileName);
//        if(!file.open(QIODevice::WriteOnly)){           return;
//        }
//        QDataStream in(&file);
//        //in.setVersion(QDataStream::Qt_5_14);

//    }


//}

MainWindow::~MainWindow()
{
    delete ui;

}

QPushButton* MainWindow::new_button(QString name, QString str)
{
    QPushButton* button = new QPushButton(str);
    button->setObjectName(name);
    return button;
}


void MainWindow::on_docTab_deleteTab(int idx) {
    ui->docTab->removeTab(idx);
}
