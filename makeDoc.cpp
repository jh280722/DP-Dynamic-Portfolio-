#include "mainwindow.h"
#include "ui_mainwindow.h"

void make_doc0(QWidget* docTab, QVBoxLayout* layout){
    QGroupBox* box = new QGroupBox(Kor("�⺻ ����"), docTab);
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

    QScrollArea* SA=new QScrollArea();
    SA->setWidget(docTab);
    SA->setWidgetResizable(true);
    SA->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );

    QVBoxLayout* VBox = new QVBoxLayout(SA);

    docTab->setLayout(VBox);
    QWidget* Par = new QWidget(SA);
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
    VBox->addWidget(Par);
    Par->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    switch(srtIdx){
    //connect�� �Լ��� ����
    case 0:
        make_doc0(SA, VBox);
        make_doc0(SA, VBox);
        break;
    case 1:
        make_doc1(docTab, VBox);
        break;
    case 2:
        make_doc2(docTab, VBox);
        break;
    case 3:
        make_doc3(docTab, VBox);
        break;
    case 4:
        make_doc4(docTab, VBox);
        break;
    case 5:
        make_doc5(docTab, VBox);
        break;
    case 6:
        make_doc6(docTab, VBox);
        break;
    case 7:
        make_doc7(docTab, VBox);
        break;
    case 8:
        make_doc8(docTab, VBox);
        break;
    }
}
