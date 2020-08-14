#include "mainwindow.h"
#include "Document.h"
#include "ui_mainwindow.h"
void Document::AddItemText(){
    QObject* item = QObject::sender();
    QVBoxLayout* boxlayout = qobject_cast<QVBoxLayout*>(item->parent());
    QWidget* newWidget = new QWidget();
    QHBoxLayout* newLayout = new QHBoxLayout();
    newLayout->addWidget(new QLabel(Kor("�� ��"),newWidget));
    newLayout->addWidget(new QLabel(Kor(" :"),newWidget));
    newLayout->addWidget(new QLineEdit(newWidget));
    QPushButton* delButton = new QPushButton(newWidget);
    newLayout->addWidget(delButton);
    connect(delButton,SIGNAL(clicked()),this,SLOT(deleteItem()));
    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);
}
void Document::deleteItem(){

    QObject* item = QObject::sender();
    disconnect(item,SIGNAL(clicked()),this,SLOT(deleteItem()));
    delete item->parent();
}

void Document::deleteBox(){
    QObject* item = QObject::sender();
    disconnect(item,SIGNAL(triggered()),this,SLOT(deleteBox()));
    delete item->parent();
}

void Document::make_doc0(){
    QGroupBox* box = new QGroupBox("", this);

    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    QVBoxLayout* layout=this->VBox;
    QWidget* nameWidget = new QWidget(box);
    QWidget* ageWidget = new QWidget(box);
    QWidget* addressWidget = new QWidget(box);

    box->setObjectName("AddText");


    QToolButton *tool = new QToolButton();

    QMenu * Menu= new QMenu();
    QMenu * InputMenu= new QMenu();

    QAction *TBADelete = new QAction (Kor("����"),box);
    TBADelete->setStatusTip(Kor("���������� �����մϴ�."));
    connect(TBADelete, SIGNAL(triggered()), this, SLOT(deleteBox()));

    QAction *TBAAdd = new QAction (Kor("�߰�"),box);
    TBAAdd->setStatusTip(Kor("���������� �߰��մϴ�."));

    QAction *TBAAddText = new QAction (Kor("�ؽ�Ʈ"),boxLayout);
    connect(TBAAddText, SIGNAL(triggered()), this, SLOT(AddItemText()));
    QAction *TBAAddTextarea = new QAction (Kor("�� ����"),box);
    QAction *TBAAddDropdown = new QAction (Kor("��� �ٿ�"),box);
    QAction *TBAAddDate = new QAction (Kor("��¥"),box);
    QAction *TBAAddImage = new QAction (Kor("�̹���"),box);

    Menu->addAction(TBADelete);
    Menu->addAction(TBAAdd);

    InputMenu->addAction(TBAAddText);
    InputMenu->addAction(TBAAddTextarea);
    InputMenu->addAction(TBAAddDropdown);
    InputMenu->addAction(TBAAddDate);
    InputMenu->addAction(TBAAddImage);

//    connect(TBADelete,SIGNAL(triggered()),this,SLOT());
//    connect(TBAAddText,SIGNAL(triggered()),this,SLOT());
//    connect(TBAAddTextarea,SIGNAL(triggered()),this,SLOT());
//    connect(TBAAddDropdown,SIGNAL(triggered()),this,SLOT());
//    connect(TBAAddDate,SIGNAL(triggered()),this,SLOT());
//    connect(TBAAddImage,SIGNAL(triggered()),this,SLOT());

    TBAAdd->setMenu(InputMenu);
    tool->setMenu(Menu);
    tool->setPopupMode(QToolButton::InstantPopup);

    boxLayout->addWidget(tool);

    boxLayout->addWidget(nameWidget);
    boxLayout->addWidget(ageWidget);
    boxLayout->addWidget(addressWidget);

    QPushButton *delButton;

    QHBoxLayout* nameLayout = new QHBoxLayout(nameWidget);
    nameLayout->addWidget(new QLabel(Kor("�� �� :")));
    nameLayout->addWidget(new QLineEdit(nameWidget));
    delButton = new QPushButton(nameWidget);
    nameLayout->addWidget(delButton);
    connect(delButton,SIGNAL(clicked()),this,SLOT(deleteItem()));

    QHBoxLayout* ageLayout = new QHBoxLayout(ageWidget);
    ageLayout->addWidget(new QLabel(Kor("�� �� :")));
    ageLayout->addWidget(new QLineEdit(ageWidget));
    delButton = new QPushButton(ageWidget);
    ageLayout->addWidget(delButton);
    connect(delButton,SIGNAL(clicked()),this,SLOT(deleteItem()));

    QHBoxLayout* addressLayout = new QHBoxLayout(addressWidget);
    addressLayout->addWidget(new QLabel(Kor("�� �� :")));
    addressLayout->addWidget(new QLineEdit(addressWidget));
    delButton = new QPushButton(addressWidget);
    addressLayout->addWidget(delButton);
    connect(delButton,SIGNAL(clicked()),this,SLOT(deleteItem()));

    box->setMinimumSize(600,200);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));

    int n=box->parent()->children().size();
    layout->insertWidget(n-3,box);
}

void Document::make_doc1(){

}

void Document::make_doc2(){

}

void Document::make_doc3(){

}

void Document::make_doc4(){

}

void Document::make_doc5(){

}

void Document::make_doc6(){

}

void Document::make_doc7(){

}

void Document::make_doc8(){

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
