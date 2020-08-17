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
void Document::AddItemTextarea(){
    QObject* item = QObject::sender();
    QVBoxLayout* boxlayout = qobject_cast<QVBoxLayout*>(item->parent());
    QWidget* newWidget = new QWidget();
    QHBoxLayout* newLayout = new QHBoxLayout();
    QLabel* name = new QLabel(Kor("�� ��"),newWidget);
    QLabel* sep = new QLabel((" :"),newWidget);
    QTextEdit* textedit=new QTextEdit(newWidget);
    textedit->setMinimumHeight(150);
    textedit->setMaximumHeight(150);

    newLayout->addWidget(name);
    newLayout->addWidget(sep);
    newLayout->addWidget(textedit);
    QPushButton* delButton = new QPushButton(newWidget);

    newLayout->addWidget(delButton);
    connect(delButton,SIGNAL(clicked()),this,SLOT(deleteItem()));
    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);


    newLayout->setAlignment(name,Qt::AlignTop);
    newLayout->setAlignment(sep,Qt::AlignTop);
    newLayout->setAlignment(delButton,Qt::AlignTop);
}
void Document::imageUpload(){
    QObject* item = QObject::sender();
    //Qwidget* par = qobject_cast<QWidget*>(item->parent());
    qDebug()<<item->parent()->objectName();
    QFileDialog  dlg;
    QString filepath=dlg.getOpenFileName(this, "Load Image", "", "Image Files (*.png *.jpg *.bmp)");
    QString fileName = filepath.section("/", -1);
    // par->setText(filepath);
}

void Document::AddItemImage(){
    QObject* item = QObject::sender();
    QVBoxLayout* boxlayout = qobject_cast<QVBoxLayout*>(item->parent());
    QWidget* newWidget = new QWidget();
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* name = new QLabel(Kor("�� ��"),newWidget);
    QLabel* sep = new QLabel((" :"),newWidget);
    QLabel* path = new QLabel(Kor("���"),newWidget);
    QPushButton* addButton = new QPushButton(Kor("���ε�"),newWidget);
    path->setObjectName("123");
    newLayout->addWidget(name);
    newLayout->addWidget(sep);
    newLayout->addWidget(addButton);
    newLayout->addWidget(path);
    newLayout->addStretch();
    newLayout->addWidget(delButton);
    connect(addButton,SIGNAL(clicked()),this,SLOT(imageUpload()));
    connect(delButton,SIGNAL(clicked()),this,SLOT(deleteItem()));
    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);
}
void Document::AddItemDate(){
    QObject* item = QObject::sender();
    QVBoxLayout* boxlayout = qobject_cast<QVBoxLayout*>(item->parent());
    QWidget* newWidget = new QWidget();
    QHBoxLayout* newLayout = new QHBoxLayout();
    QDateEdit * newdate = new QDateEdit();
    QLabel* name = new QLabel(Kor("�� ��"),newWidget);
    QLabel* sep = new QLabel((" :"),newWidget);
    QPushButton* delButton = new QPushButton(newWidget);

    newdate->setCalendarPopup(1);
    newdate->setDate(QDate::currentDate());

    newLayout->addWidget(name);
    newLayout->addWidget(sep);
    newLayout->addWidget(newdate);
    newLayout->addStretch();
    delButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    newLayout->addWidget(delButton);
    connect(delButton,SIGNAL(clicked()),this,SLOT(deleteItem()));
    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);
    newLayout->setAlignment(name,Qt::AlignLeft);
    newLayout->setAlignment(sep,Qt::AlignLeft);
    newLayout->setAlignment(newdate,Qt::AlignLeft);
    newLayout->setAlignment(delButton,Qt::AlignRight);
}
void Document::AddItemDropdown(){
    QObject* item = QObject::sender();
    QVBoxLayout* boxlayout = qobject_cast<QVBoxLayout*>(item->parent());
    QWidget* newWidget = new QWidget();
    QHBoxLayout* newLayout = new QHBoxLayout();
    QComboBox * newdd = new QComboBox();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* name = new QLabel(Kor("�� ��"),newWidget);
    QLabel* sep = new QLabel((" :"),newWidget);


    newLayout->addWidget(name);
    newLayout->addWidget(sep);
    newLayout->addWidget(newdd);
    newLayout->addStretch();
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
    QWidget* toolWidget = new QWidget(box);

    QToolButton *tool = new QToolButton(toolWidget);
    QHBoxLayout* toolLayout = new QHBoxLayout(toolWidget);
    QMenu * Menu= new QMenu();
    QMenu * InputMenu= new QMenu();
    toolLayout->addStretch();
    toolLayout->addWidget(tool,Qt::AlignRight);
    //tool->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    QAction *TBAAdd = new QAction (Kor("�߰�"),box);
    TBAAdd->setStatusTip(Kor("���������� �߰��մϴ�."));
    QAction *TBADelete = new QAction (Kor("����"),box);
    TBADelete->setStatusTip(Kor("���������� �����մϴ�."));
    connect(TBADelete, SIGNAL(triggered()), this, SLOT(deleteBox()));


    QAction *TBAAddText = new QAction (Kor("�ؽ�Ʈ"),boxLayout);
    connect(TBAAddText, SIGNAL(triggered()), this, SLOT(AddItemText()));
    QAction *TBAAddTextarea = new QAction (Kor("�� ����"),boxLayout);
    connect(TBAAddTextarea, SIGNAL(triggered()), this, SLOT(AddItemTextarea()));
    QAction *TBAAddDropdown = new QAction (Kor("��� �ٿ�"),boxLayout);
    connect(TBAAddDropdown, SIGNAL(triggered()), this, SLOT(AddItemDropdown()));
    QAction *TBAAddDate = new QAction (Kor("��¥"),boxLayout);
    connect(TBAAddDate, SIGNAL(triggered()), this, SLOT(AddItemDate()));
    QAction *TBAAddImage = new QAction (Kor("�̹���"),boxLayout);
    connect(TBAAddImage, SIGNAL(triggered()), this, SLOT(AddItemImage()));

    Menu->addAction(TBAAdd);
    Menu->addAction(TBADelete);
    InputMenu->addAction(TBAAddText);
    InputMenu->addAction(TBAAddTextarea);
    InputMenu->addAction(TBAAddDropdown);
    InputMenu->addAction(TBAAddDate);
    InputMenu->addAction(TBAAddImage);

    TBAAdd->setMenu(InputMenu);
    tool->setMenu(Menu);
    tool->setPopupMode(QToolButton::InstantPopup);

    boxLayout->addWidget(toolWidget);

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

    box->setMinimumSize(800,800);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    boxLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

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

Document::Document(QWidget* parent, int srtIdx, int listIdx):QWidget(parent){
    this->SA=new QScrollArea(parent);
    QVBoxLayout* VBox = new QVBoxLayout(parent);
    VBox->addWidget(SA);

    //���� ��ũ�ѹ� ����
    SA->setWidgetResizable(1);
    SA->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );

    SA->setWidget(this);
    this->VBox = new QVBoxLayout();//VBox�� ����
    this->setLayout( this->VBox );

    this->srtIdx=srtIdx;
    this->listIdx=listIdx;
}

Document::~Document(){
    delete this->VBox;
    delete this->SA;
    delete this;
}


void Document::save_doc(){

}


void Document::delete_doc(){
    delete(docBtnList[srtIdx][listIdx]);
    docList[srtIdx].remove(listIdx);
    docBtnList[srtIdx].remove(listIdx);
}

void Document::preview_doc(){

}

void Document::active_doc_select(){

}

