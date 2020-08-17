#include "mainwindow.h"
#include "Document.h"
#include "ui_mainwindow.h"

//���� ���鶧 �� �� ����Ǵ� �Լ�
void MainWindow::add_box(QWidget* docTab, int listIdx) {

    //��ũ�� ���� ���� ����
    Document* SAW=new Document(docTab, srtIdx, listIdx);
    //����, ����, �̸�����, Ȱ��ȭ ��ư ����
    QWidget* Par = new QWidget(SAW);

    QHBoxLayout* HBox = new QHBoxLayout(Par);
    QPushButton* PB;
    PB=new QPushButton(Kor("����"),Par);
    connect(PB, SIGNAL(clicked()), SAW, SLOT(save_doc()));
    HBox->addWidget(PB);
    PB=new QPushButton(Kor("����"),Par);
    connect(PB, SIGNAL(clicked()), SAW, SLOT(delete_doc()));
    connect(PB, SIGNAL(clicked()), this, SLOT(deleteTab()));
    HBox->addWidget(PB);
    PB=new QPushButton(Kor("�̸�����"),Par);
    connect(PB, SIGNAL(clicked()), SAW, SLOT(preview_doc()));
    HBox->addWidget(PB);
    PB=new QPushButton(Kor("Ȱ��ȭ"),Par);
    connect(PB, SIGNAL(clicked()), SAW, SLOT(active_doc_select()));
    HBox->addWidget(PB);
    Par->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));

    SAW->VBox->addWidget(Par);

    Par = new QWidget(SAW);
    QHBoxLayout* plusButton = new QHBoxLayout(Par);
    PB=new QPushButton(Kor("�߰�"),Par);
    plusButton->addWidget(PB);
    plusButton->setAlignment(Qt::AlignRight);
    SAW->VBox->addWidget(Par);

    switch(srtIdx){ //srt���� ��� ����
    //connect�� �Լ��� ����
    case 0:
        SAW->make_doc0();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc0()));
        break;
    case 1:
        SAW->make_doc1();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc1()));
        break;
    case 2:
        SAW->make_doc2();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc2()));
        break;
    case 3:
        SAW->make_doc3();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc3()));
        break;
    case 4:
        SAW->make_doc4();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc4()));
        break;
    case 5:
        SAW->make_doc5();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc5()));
        break;
    case 6:
        SAW->make_doc6();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc6()));
        break;
    case 7:
        SAW->make_doc7();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc7()));
        break;
    case 8:
        SAW->make_doc8();
        connect(PB, SIGNAL(clicked()), SAW, SLOT(make_doc8()));
        break;
    }
}
