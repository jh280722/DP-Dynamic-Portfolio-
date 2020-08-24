#include "mainwindow.h"
#include "Document.h"
#include "sortation.h"
#include "ui_mainwindow.h"

extern Sortation *sortation;

Document::Document(QWidget*parent, int srtIdx):QWidget(parent){
    //setObjectName("doc");
    this->srtIdx=srtIdx;
    add_box();
}

Document::~Document(){
    delete this->PBS;
    delete this->tab;
    delete this;
}

//���� ���鶧 �� �� ����Ǵ� �Լ�
void Document::add_box() {

    //��ũ�� ���� ���� ����
    tab=new DocTab(this,srtIdx);
    //����, ����, �̸�����, Ȱ��ȭ ��ư ����
    QWidget* Par = new QWidget(tab);

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

    tab->VBox->addWidget(Par);

    Par = new QWidget(tab);
    QHBoxLayout* plusButton = new QHBoxLayout(Par);
    PB=new QPushButton(Kor("�߰�"),Par);
    plusButton->addWidget(PB);
    plusButton->setAlignment(Qt::AlignRight);
    tab->VBox->addWidget(Par);

    switch(srtIdx){ //srt���� ��� ����
    //connect�� �Լ��� ����
    case 0:
        tab->make_doc0();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc0()));
        break;
    case 1:
        tab->make_doc1();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc1()));
        break;
    case 2:
        tab->make_doc2();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc2()));
        break;
    case 3:
        tab->make_doc3();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc3()));
        break;
    case 4:
        tab->make_doc4();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc4()));
        break;
    case 5:
        tab->make_doc5();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc5()));
        break;
    case 6:
        tab->make_doc6();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc6()));
        break;
    case 7:
        tab->make_doc7();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc7()));
        break;
    case 8:
        tab->make_doc8();
        connect(PB, SIGNAL(clicked()), tab, SLOT(make_doc8()));
        break;
    }
}

void Document::save_doc(){

}

void Document::delete_doc(){
    sortation->srtIdx=srtIdx;
    for(auto it : sortation->docList[srtIdx]){
        if(it==this){
            delete(it->PBS);
            sortation->docList[srtIdx].removeOne(it);
            break;
        }
    }
    sortation->delete_tab(srtIdx);
}

void Document::preview_doc(){

}

void Document::active_doc_select(){

}

