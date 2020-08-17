#include "mainwindow.h"
#include "Document.h"
#include "sortation.h"
#include "ui_mainwindow.h"

QString srtTitle[9]={Kor("���� ����"), Kor("�з� ����"),Kor("��� ����"),Kor("Ȱ�� �� ���� ���"),
                     Kor("�ڰ���"),Kor("������Ʈ"),Kor("�ڱ�Ұ���"),Kor("��Ʈ������"), Kor("��Ÿ")};

QSet<QWidget*> docList2[9];
QVector<QWidget*> docList[9];
QVector<QPushButton*> docBtnList[9];
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Sortation *sortation = new Sortation(ui->centralwidget);
    //    int w=ui->intro->width();
    //    int h=ui->intro->height();
    //    QPixmap pix(":/img/Start.png");
    //ui->intro->setPixmap(pix);
    //ui->intro->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    QMenu *pFileMenu;
    QAction *pSlotNewFile = new QAction(Kor("����"), this);
    pSlotNewFile->setShortcut(Kor("Ctrl+S"));
    pSlotNewFile->setStatusTip(Kor("���������� �����մϴ�."));
    //connect(pSlotNewFile, SIGNAL(triggered()), this, SLOT(Main_SlotTest1()));
    pFileMenu = menuBar()->addMenu(Kor("����"));
    pFileMenu->addAction(pSlotNewFile); // �׽�Ʈ

    ui->docTab->setTabsClosable(true);
    connect(ui->docTab, SIGNAL(tabCloseRequested(int)), this, SLOT(on_docTab_deleteTab(int)));

//    for(int i=0;i<9;i++){
//        docNum[i]=0;
//        srtInit(i);
//    }

    //    this->setStyleSheet("#pushButton:hover { background-color: red; "
    //                        "border-style: outset; border-width: 2px;border-radius: 10px; border-color: beige;"
    //                        "font: bold 14px;min-width: 10em;padding: 6px; }");
}

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


//void MainWindow::on_plus_clicked() {
//    QObject* sel = QObject::sender();
//    QString name;
//    QWidget* menu = 0;
//    for(int i=0;i<9;i++){
//        if(sel==srtPlusBtn[i]){
//            srtIdx = i;
//            name = srtTitle[srtIdx] + QString::number(++docNum[srtIdx]);
//            menu = ui->srtArea->findChild<QWidget*>("srt"+QString::number(srtIdx));
//            break;
//        }
//    }
//    int sz=docBtnList[srtIdx].size();

//    srtPlusBtn[srtIdx]->setText(name);
//    disconnect(sel, SIGNAL(clicked()), this, SLOT(on_plus_clicked()));

//    docBtnList[srtIdx].push_back(new_button("plusButton" + QString::number(srtIdx), Kor("�׸��߰�")));
//    srtPlusBtn[srtIdx] = docBtnList[srtIdx][sz];
//    menu->layout()->addWidget(docBtnList[srtIdx][sz]);

//    QWidget* new_tab = new QWidget();
//    add_box(new_tab, sz-1);
//    docList[srtIdx].push_back(new_tab);
//    connect(docBtnList[srtIdx][sz], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
//    connect(docBtnList[srtIdx][sz], SIGNAL(clicked()), this, SLOT(connect_doc()));

//}

void MainWindow::srtInit(int srtIdx) {
//    QWidget* menu = 0;

//    menu = ui->srtArea->findChild<QWidget*>("srt"+QString::number(srtIdx));

//    int sz=docBtnList[srtIdx].size();
//    docBtnList[srtIdx].push_back(new_button("plusButton" + QString::number(srtIdx), Kor("�׸��߰�")));

//    srtPlusBtn[srtIdx] = docBtnList[srtIdx][sz];
//    menu->layout()->addWidget(docBtnList[srtIdx][sz]);
//    menu->layout()->setAlignment(Qt::AlignTop);

//    connect(docBtnList[srtIdx][sz], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
//�̰� srt���� ���̱�    connect(docBtnList[srtIdx][sz], SIGNAL(clicked()), this, SLOT(connect_doc()));
}

void MainWindow::deleteTab() {
    ui->docTab->removeTab(ui->docTab->currentIndex());
}

void MainWindow::on_docTab_deleteTab(int idx) {
    ui->docTab->removeTab(idx);
}

void MainWindow::on_toolBox_currentChanged(int index)
{
    srtIdx = index-1;
}
