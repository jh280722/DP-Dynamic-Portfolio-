#include "mainwindow.h"
#include "ui_mainwindow.h"

void make_doc0(QWidget* docTab, QVBoxLayout* layout){
    QGroupBox* box = new QGroupBox(Kor("�⺻ ����"), docTab);
    QVBoxLayout* boxLayout = new QVBoxLayout(box);

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
   // box->setMinimumSize(400,500);
   //box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
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

//���� ���鶧 �� �� ����Ǵ� �Լ�
void MainWindow::add_box(QWidget* docTab) {
    //����, ���� �̸�����, Ȱ��ȭ ��ư ����

    //��ũ�� ���� ���� �� �� �θ� ����
    QScrollArea* SA=new QScrollArea(docTab);
    QVBoxLayout* VBox = new QVBoxLayout(docTab);
    VBox->addWidget(SA);

    //���� ��ũ�ѹ� ����
    SA->setWidgetResizable(1);
    SA->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );

    //��ũ�� ���� ���� ����
    QWidget *SAW = new QWidget();
    SA->setWidget(SAW);
    QVBoxLayout* VBox2 = new QVBoxLayout();//VBox�� ����
    SAW->setLayout( VBox2 );

    //����, ����, �̸�����, Ȱ��ȭ ��ư ����
    QWidget* Par = new QWidget(SAW);
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
    VBox2->addWidget(Par);
    Par->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));

    switch(srtIdx){ //srt���� ��� ����
    //connect�� �Լ��� ����
    case 0:
        make_doc0(SAW, VBox2);
        make_doc0(SAW, VBox2);
        break;
    case 1:
        make_doc1(SAW, VBox2);
        break;
    case 2:
        make_doc2(SAW, VBox2);
        break;
    case 3:
        make_doc3(SAW, VBox2);
        break;
    case 4:
        make_doc4(SAW, VBox2);
        break;
    case 5:
        make_doc5(SAW, VBox2);
        break;
    case 6:
        make_doc6(SAW, VBox2);
        break;
    case 7:
        make_doc7(SAW, VBox2);
        break;
    case 8:
        make_doc8(SAW, VBox2);
        break;
    }
    //���� �����̼� ����
    QSpacerItem* VS= new QSpacerItem(500,500);
    VBox2->addItem(VS);
}
