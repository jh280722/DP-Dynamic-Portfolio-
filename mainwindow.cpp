#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int w=ui->intro->width();
    int h=ui->intro->height();
    QPixmap pix(":/img/Start.png");
    //ui->intro->setPixmap(pix);
    //ui->intro->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    QMenu *pFileMenu;
    QAction *pSlotNewFile = new QAction(Kor("����"), this);
    pSlotNewFile->setShortcut(Kor("Ctrl+S"));
    pSlotNewFile->setStatusTip(Kor("���������� �����մϴ�."));
    connect(pSlotNewFile, SIGNAL(triggered()), this, SLOT(Main_SlotTest1()));
    pFileMenu = menuBar()->addMenu(Kor("����"));
    pFileMenu->addAction(pSlotNewFile); // �׽�Ʈ


    ui->docTab->setTabsClosable(true);
    connect(ui->docTab, SIGNAL(tabCloseRequested(int)), this, SLOT(on_docTab_deleteTab(int)));
    for(int i=0;i<9;i++){
        docNum[i]=0;
        srtInit(i);
    }
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

void MainWindow::add_box(QWidget* docTab) {
    QWidget* widget = docTab;
    QVBoxLayout* layout = new QVBoxLayout(widget);

    widget->setLayout(layout);

    QGroupBox* box = new QGroupBox(Kor("�⺻ ����"), widget);
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    layout->addWidget(box);

    QWidget* nameWidget = new QWidget(box);
    QWidget* ageWidget = new QWidget(box);
    QWidget* addressWidget = new QWidget(box);

    boxLayout->addWidget(nameWidget);
    boxLayout->addWidget(ageWidget);
    boxLayout->addWidget(addressWidget);

    QHBoxLayout* nameLayout = new QHBoxLayout(nameWidget);
    nameLayout->addWidget(new QLabel(Kor("�� �� :")));
    nameLayout->addWidget(new QLineEdit(nameWidget));


    QHBoxLayout* ageLayout = new QHBoxLayout(ageWidget);
    ageLayout->addWidget(new QLabel(Kor("�� �� :")));
    ageLayout->addWidget(new QLineEdit(ageWidget));

    QHBoxLayout* addressLayout = new QHBoxLayout(addressWidget);
    addressLayout->addWidget(new QLabel(Kor("�� �� :")));
    addressLayout->addWidget(new QLineEdit(addressWidget));


    QWidget* validateWidget = new QWidget(widget);
    QHBoxLayout* validateLayout = new QHBoxLayout(validateWidget);
    validateLayout->addWidget(new QPushButton(Kor("Ȯ ��"), validateWidget));
    validateLayout->addWidget(new QPushButton(Kor("�� ��"), validateWidget));
    validateLayout->addWidget(new QPushButton(Kor("�� ��"), validateWidget));
    layout->addWidget(validateWidget);
}

QString srtTitle[9]={Kor("���� ����"), Kor("�з� ����"),Kor("��� ����"),Kor("Ȱ�� �� ���� ���"),
                     Kor("�ڰ���"),Kor("������Ʈ"),Kor("�ڱ�Ұ���"),Kor("��Ʈ������"), Kor("��Ÿ")};

void MainWindow::on_plus_clicked() {
    QObject* sel = QObject::sender();
    QString name;
    QWidget* menu = 0;
    for(int i=0;i<9;i++){
        if(sel==srtPlusBtn[i]){
            srtIdx = i;
            name = srtTitle[srtIdx] + QString::number(docNum[srtIdx]);
            menu = ui->toolBox->findChild<QWidget*>("srt"+QString::number(srtIdx));
            break;
        }
    }

    srtPlusBtn[srtIdx]->setText(name);
    disconnect(sel, SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
    docBtnList[srtIdx].push_back(new_button("dm" + QString::number(srtIdx) + "_" + QString::number(docNum[srtIdx]), Kor("�׸��߰�")));
    srtPlusBtn[srtIdx] = docBtnList[srtIdx][docNum[srtIdx]];
    menu->layout()->addWidget(docBtnList[srtIdx][docNum[srtIdx]]);
    QWidget* new_tab = new QWidget;
    add_box(new_tab);
    docList[srtIdx].push_back(new_tab);
    connect(docBtnList[srtIdx][docNum[srtIdx]], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
    connect(docBtnList[srtIdx][docNum[srtIdx]++], SIGNAL(clicked()), this, SLOT(connect_doc()));
}

void MainWindow::srtInit(int srtIdx) {
    QWidget* menu = 0;

     menu = ui->toolBox->findChild<QWidget*>("srt"+QString::number(srtIdx));

        docBtnList[srtIdx].push_back(new_button("dm" + QString::number(srtIdx) + "_" + QString::number(docNum[srtIdx]),
            Kor("�׸��߰�")));
        srtPlusBtn[srtIdx] = docBtnList[srtIdx][docNum[srtIdx]];
        menu->layout()->addWidget(docBtnList[srtIdx][docNum[srtIdx]]);

        connect(docBtnList[srtIdx][docNum[srtIdx]], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
        connect(docBtnList[srtIdx][docNum[srtIdx]++], SIGNAL(clicked()), this, SLOT(connect_doc()));
//    else if (flg == 1) {
//        flg = 2;
//        for (int i = 0; i < docNum[srtIdx]; i++)
//        {
//            docBtnList[srtIdx][i]->show();
//        }
//    }
//    else if (flg == 2) {
//        flg = 1;
//        for (int i = 0; i < docNum[srtIdx]; i++)
//        {
//            docBtnList[srtIdx][i]->hide();
//        }
//    }
}

void MainWindow::connect_doc() {
    QObject* sel = QObject::sender();
    bool existList = false;
    int tmpIdx = -1;
    int subSrtIdx = -1;


    for(int j=0;j<9;j++){
        bool ok=0;
        for (int i = 0; i < docBtnList[j].size(); ++i) {
            if (docBtnList[j][i] == sel) {
                srtIdx = j;
                subSrtIdx = i;
                ok=1;
                break;
            }
        }
        if(ok)
            break;
    }
    for (int i = 0; i < ui->docTab->count(); ++i) {
        if (docBtnList[srtIdx][subSrtIdx]->text() == ui->docTab->tabText(i)) {
            existList = true;
            tmpIdx = i;
            break;
        }
    }
    if (existList) {
        ui->docTab->setCurrentIndex(tmpIdx);
    }
    else {
        pBtn = docBtnList[srtIdx][subSrtIdx];
        add_docTab(subSrtIdx);
        ui->docTab->setCurrentIndex(ui->docTab->count() - 1);
    }
}

void MainWindow::on_docTab_deleteTab(int idx) {
    ui->docTab->removeTab(idx);
}
void MainWindow::add_docTab(int subSrtIdx) {
    QWidget* new_tab = docList[srtIdx][subSrtIdx];
    ui->docTab->addTab(new_tab, pBtn->text());
}

void MainWindow::on_toolBox_currentChanged(int index)
{
    srtIdx = index-1;
}
