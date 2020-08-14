#include "mainwindow.h"
#include "Document.h"
#include "ui_mainwindow.h"

void Document::make_doc0(){
    QGroupBox* box = new QGroupBox("", this);
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    QVBoxLayout* layout=this->VBox;
    QWidget* nameWidget = new QWidget(box);
    QWidget* ageWidget = new QWidget(box);
    QWidget* addressWidget = new QWidget(box);

    boxLayout->addWidget(nameWidget);
    boxLayout->addWidget(ageWidget);
    boxLayout->addWidget(addressWidget);


    QToolBar *toolbar=new QToolBar(this);
    QToolButton *tool = new QToolButton(toolbar);
    toolbar->addWidget(tool);
    QMenu *pFileMenu=new QMenu(tool);
    QAction *pSlotNewFile = new QAction(Kor("�߰�"), pFileMenu);
    pSlotNewFile->setShortcut(Kor("Ctrl+S"));
    pSlotNewFile->setStatusTip(Kor("���������� �߰��մϴ�."));

    connect(pSlotNewFile, SIGNAL(triggered()), this, SLOT(make_doc0()));

   // pFileMenu = tool->menu()->addMenu(Kor("����"));
    pFileMenu->addAction(pSlotNewFile); // �߰�

    tool->setMenu(pFileMenu);
    tool->setDefaultAction(pSlotNewFile);

    QHBoxLayout* nameLayout = new QHBoxLayout(nameWidget);
    nameLayout->addWidget(new QLabel(Kor("�� �� :")));
    nameLayout->addWidget(new QLineEdit(nameWidget));
    nameLayout->addWidget(toolbar);


    QHBoxLayout* ageLayout = new QHBoxLayout(ageWidget);
    ageLayout->addWidget(new QLabel(Kor("�� �� :")));
    ageLayout->addWidget(new QLineEdit(ageWidget));

    QHBoxLayout* addressLayout = new QHBoxLayout(addressWidget);
    addressLayout->addWidget(new QLabel(Kor("�� �� :")));
    addressLayout->addWidget(new QLineEdit(addressWidget));


    box->setMinimumSize(600,200);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    layout->addWidget(box);

}

void make_doc1(QWidget* docTab, QVBoxLayout* layout){

}

void make_doc2(QWidget* docTab, QVBoxLayout* layout){

}

void make_doc3(QWidget* docTab, QVBoxLayout* layout){

}

void make_doc4(QWidget* docTab, QVBoxLayout* layout){

}

void make_doc5(QWidget* docTab, QVBoxLayout* layout){

}

void make_doc6(QWidget* docTab, QVBoxLayout* layout){

}

void make_doc7(QWidget* docTab, QVBoxLayout* layout){

}

void make_doc8(QWidget* docTab, QVBoxLayout* layout){

}

void save_doc(){

}

void delete_doc(){

}

void preview_doc(){

}

void active_doc_select(){

}

Document::Document(QWidget* parent):QWidget(parent){
    QScrollArea* SA=new QScrollArea(parent);
    QVBoxLayout* VBox = new QVBoxLayout(parent);
    VBox->addWidget(SA);

    //���� ��ũ�ѹ� ����
    SA->setWidgetResizable(1);
    SA->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    SA->setWidget(this);
    this->VBox = new QVBoxLayout();//VBox�� ����
    this->setLayout( this->VBox );
}
Document::~Document(){
}

//���� ���鶧 �� �� ����Ǵ� �Լ�
void MainWindow::add_box(QWidget* docTab) {

    //��ũ�� ���� ���� ����
    Document* SAW=new Document(docTab);

    //����, ����, �̸�����, Ȱ��ȭ ��ư ����
    QWidget* Par = new QWidget(docTab);

    QHBoxLayout* HBox = new QHBoxLayout(Par);
    QPushButton* PB;
    PB=new QPushButton(Kor("����"),Par);
    connect(PB, SIGNAL(clicked()), this, SLOT(save_doc()));
    HBox->addWidget(PB);
    PB=new QPushButton(Kor("����"),Par);
    connect(PB, SIGNAL(clicked()), this, SLOT(delete_doc()));
    HBox->addWidget(PB);
    PB=new QPushButton(Kor("�̸�����"),Par);
    connect(PB, SIGNAL(clicked()), this, SLOT(preview_doc()));
    HBox->addWidget(PB);
    PB=new QPushButton(Kor("Ȱ��ȭ"),Par);
    connect(PB, SIGNAL(clicked()), this, SLOT(active_doc_select()));
    HBox->addWidget(PB);
    Par->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));

    SAW->VBox->addWidget(Par);

    switch(srtIdx){ //srt���� ��� ����
    //connect�� �Լ��� ����
    case 0:
        SAW->make_doc0();
        break;
//    case 1:
//        make_doc1(SAW, VBox2);
//        break;
//    case 2:
//        make_doc2(SAW, VBox2);
//        break;
//    case 3:
//        make_doc3(SAW, VBox2);
//        break;
//    case 4:
//        make_doc4(SAW, VBox2);
//        break;
//    case 5:
//        make_doc5(SAW, VBox2);
//        break;
//    case 6:
//        make_doc6(SAW, VBox2);
//        break;
//    case 7:
//        make_doc7(SAW, VBox2);
//        break;
//    case 8:
//        make_doc8(SAW, VBox2);
//        break;
    }
    //���� �����̼� ����
    QSpacerItem* VS= new QSpacerItem(500,500);
    //SAW->VBox->addItem(VS);
}
