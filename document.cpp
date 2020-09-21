#include "mainwindow.h"
#include "document.h"
#include "sortation.h"
#include "ui_mainwindow.h"
#include "data.h"
#include <QFile>
extern Sortation *sortation;

class Widget : public QWidget{

public:
    Widget(QWidget *parent=nullptr): QWidget(parent){
        this->installEventFilter(this);
    };

protected:
    bool eventFilter(QObject *obj,QEvent *ev) override{
        QPushButton * delButton= obj->findChild<QPushButton*>("delButton");
        this->show();
        if(ev->type()==QEvent::Enter){
            delButton->setAutoFillBackground(0);
            delButton->setFlat(0);
            return false;
        }
        else if(ev->type()==QEvent::Leave){
            delButton->setAutoFillBackground(0);
            delButton->setFlat(1);
            return false;
        }
    }
};

class DoubleClickedWidget : public QLabel{
    Q_GADGET
public:
    DoubleClickedWidget(QLabel *parent=nullptr): QLabel(parent){
        this->setText(parent->text());
        this->setMaximumWidth(200);
        this->setFixedWidth(100);
        this->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    };
    ~DoubleClickedWidget(){

    };
public slots:
    void hideText();
signals:
    void doubleClicked();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event)
    {
        emit doubleClicked();
    }

};
void  DoubleClickedWidget::hideText(){
    QLabel* label=qobject_cast<QLabel*>(this);
    QLineEdit* edit=this->parent()->findChild<QLineEdit*>("titleEdit");
    label->setText(edit->text());
    label->show();
    edit->hide();
};
void DoubleClickedWidget:: doubleClicked(){

    QLabel* label= qobject_cast<QLabel*>(this);
    QLineEdit * text= label->parent()->findChild<QLineEdit*>("titleEdit");

    text->setText(label->text());
    text->show();
    label->hide();
    text->setFocus();
}

Document::Document(QString name, int srtIdx, bool load):QWidget(){
    setObjectName("document");
    this->name=name;
    this->srtIdx=srtIdx;
    docPath=srtPath+QString::number(srtIdx) +"/"+this->name+"/";
    QDir Directory(docPath); // ���� ����
    if(!Directory.exists()) // ������ �������� �������
    {
        Directory.mkdir(AppPath+"/Data"); // ���� ����
        Directory.mkdir(srtPath+QString::number(srtIdx)); // ���� ����
        Directory.mkdir(docPath); // ���� ����
    }
    init_docTab(load);
}

Document::~Document(){
    delete this->PBS;
    delete this->tab;
    delete this;
}


//���� ���鶧 �� �� ����Ǵ� �Լ�
void Document::init_docTab(bool load) {

    //��ũ�� ���� ���� ����
    tab=new DocTab(this,srtIdx);
    tab->setObjectName("doctab");
    //����, ����, �̸�����, Ȱ��ȭ ��ư ����
    QWidget* Par = new QWidget(tab);
    Par->setObjectName("docMenu");
    QHBoxLayout* HBox = new QHBoxLayout(Par);
    QPushButton* PB;
    PB=new QPushButton(Kor("����"),Par);
    PB->setObjectName("save");
    connect(PB, SIGNAL(clicked()), this, SLOT(save_doc()));
    HBox->addWidget(PB);
    PB=new QPushButton(Kor("����"),Par);
    PB->setObjectName("delete");
    connect(PB, SIGNAL(clicked()), this, SLOT(delete_doc()));
    HBox->addWidget(PB);
    PB=new QPushButton(Kor("�̸�����"),Par);
    PB->setObjectName("preview");
    connect(PB, SIGNAL(clicked()), this, SLOT(load_doc()));
    HBox->addWidget(PB);
    PB=new QPushButton(Kor("Ȱ��ȭ"),Par);
    PB->setObjectName("active");
    connect(PB, SIGNAL(clicked()), this, SLOT(active_doc_select()));
    HBox->addWidget(PB);
    Par->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));

    tab->VLayout->addWidget(Par);
    tab->VLayout->addWidget(tab->box);

    Par = new QWidget(tab);
    Par->setObjectName("addBoxButton");
    QHBoxLayout* plusButton = new QHBoxLayout(Par);

    plusButton->addStretch();
    PB=new QPushButton(Kor("ǥ �߰�"),Par);
    PB->setObjectName("addTable");
    connect(PB, SIGNAL(clicked()), this, SLOT(add_table_box()));

    plusButton->addWidget(PB);
    PB=new QPushButton(Kor("�߰�"),Par);
    PB->setObjectName("addBox");
    plusButton->addWidget(PB);
    plusButton->setAlignment(Qt::AlignTop);

    tab->VLayout->addWidget(Par);

    switch(srtIdx){ //srt���� ��� ����
    //connect�� �Լ��� ����
    case 0:
        make_doc0();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc0()));
        break;
    case 1:
        make_doc1();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc1()));
        break;
    case 2:
        make_doc2();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc2()));
        break;
    case 3:
        make_doc3();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc3()));
        break;
    case 4:
        make_doc4();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc4()));
        break;
    case 5:
        make_doc5();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc5()));
        break;
    case 6:
        make_doc6();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc6()));
        break;
    case 7:
        make_doc7();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc7()));
        break;
    case 8:
        make_doc8();
        connect(PB, SIGNAL(clicked()), this, SLOT(make_doc8()));
        break;
    }
    if(!load)
        this->save_doc();
}

QVBoxLayout* Document::load_add_box() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    boxLayout->setObjectName("groupBoxLayout");
    QVBoxLayout* layout = tab->boxArea;

    add_tool_option(box,boxLayout);

    box->setAlignment(Qt::AlignTop);
    box->setMinimumSize(800, 800);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    boxLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    boxLayout->setAlignment(Qt::AlignTop);

    layout->addWidget(box);

    return boxLayout;
}
void Document::AddItemText() {
    QObject* item = QObject::sender();
    QVBoxLayout* boxlayout = qobject_cast<QVBoxLayout*>(item->parent());
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(Kor("�ؽ�Ʈ"));
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QLineEdit* LineEdit=new QLineEdit(newWidget);

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(LineEdit);


    titleEdit->hide();
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    LineEdit->setObjectName("QLineEdit");
    newWidget->setObjectName("text");
}
void Document::AddItemText(QVBoxLayout * boxlayout,QString name,QString value) {
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(name);
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QLineEdit* LineEdit=new QLineEdit(value,newWidget);

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(LineEdit);

    titleEdit->hide();
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    LineEdit->setObjectName("QLineEdit");
    newWidget->setObjectName("text");
}
void Document::AddItemTextarea() {
    QObject* item = QObject::sender();
    QVBoxLayout* boxlayout = qobject_cast<QVBoxLayout*>(item->parent());
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(Kor("�ؽ�Ʈ"));
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QTextEdit* TextEdit = new QTextEdit(newWidget);

    TextEdit->setMinimumHeight(150);

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignTop|Qt::AlignRight);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(TextEdit);

    titleEdit->hide();
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    newLayout->setAlignment(title, Qt::AlignTop);
    newLayout->setAlignment(titleEdit, Qt::AlignTop|Qt::AlignRight);
    newLayout->setAlignment(sep, Qt::AlignTop);
    newLayout->setAlignment(delButton, Qt::AlignTop);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    TextEdit->setObjectName("QTextEdit");
    newWidget->setObjectName("textArea");
}
void Document::AddItemTextarea(QVBoxLayout * boxlayout,QString name,QString value) {
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(name);
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QTextEdit* TextEdit = new QTextEdit(value,newWidget);

    TextEdit->setPlainText(value);
    TextEdit->setMinimumHeight(150);

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignTop|Qt::AlignRight);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(TextEdit);

    titleEdit->hide();
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    newLayout->setAlignment(title, Qt::AlignTop);
    newLayout->setAlignment(sep, Qt::AlignTop);
    newLayout->setAlignment(titleEdit, Qt::AlignTop|Qt::AlignRight);
    newLayout->setAlignment(delButton, Qt::AlignTop);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    TextEdit->setObjectName("QTextEdit");
    newWidget->setObjectName("textArea");
}
void Document::imageUpload() {
    QObject* item = QObject::sender();
    QLabel* path = item->parent()->findChild<QLabel*>("path");
    QFileDialog  dlg;
    QString filepath = dlg.getOpenFileName(this, "Load Image", "", "Image Files (*.png *.jpg *.bmp)");
    QString fileName = filepath.section("/", -1);
    path->setText(fileName);
    QObjectList box=item->parent()->parent()->children();
    int idx=0;
    for(;idx<box.size();idx++){
        if(box[idx]==item->parent()){
            break;
        }
    }
    QString newName = docPath + QString::number(idx)+"_"+fileName;
    QFile::copy ( filepath, newName );
}

void Document::AddItemImage() {
    QObject* item = QObject::sender();
    QVBoxLayout* boxlayout = qobject_cast<QVBoxLayout*>(item->parent());
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(Kor("�̹���"));
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QPushButton* addButton = new QPushButton(Kor("���ε�"), newWidget);
    QLabel* path = new QLabel(Kor("���"), newWidget);

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(addButton);
    newLayout->addWidget(path);
    newLayout->addStretch();
    newLayout->addWidget(delButton);

    titleEdit->hide();

    connect(addButton, SIGNAL(clicked()), this, SLOT(imageUpload()));
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    path->setObjectName("path");
    newWidget->setObjectName("image");
}
void Document::AddItemImage(QVBoxLayout * boxlayout,QString name,QString path) {
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(name);
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QPushButton* addButton = new QPushButton(Kor("���ε�"), newWidget);
    QLabel* newpath = new QLabel(path, newWidget);

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(sep);
    newLayout->addWidget(addButton);
    newLayout->addWidget(newpath);
    newLayout->addStretch();
    titleEdit->hide();

    connect(addButton, SIGNAL(clicked()), this, SLOT(imageUpload()));
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    newpath->setObjectName("path");
    newWidget->setObjectName("image");
}
void Document::AddItemDate() {
    QObject* item = QObject::sender();
    QVBoxLayout* boxlayout = qobject_cast<QVBoxLayout*>(item->parent());
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(Kor("�� ¥"));
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QDateEdit* newdate = new QDateEdit();

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);

    newdate->setCalendarPopup(1);
    newdate->setDate(QDate::currentDate());
    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(newdate);
    newLayout->addStretch();

    titleEdit->hide();

    //delButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    newLayout->setAlignment(title, Qt::AlignLeft);
    newLayout->setAlignment(sep, Qt::AlignLeft);
    newLayout->setAlignment(newdate, Qt::AlignLeft);
    newLayout->setAlignment(delButton, Qt::AlignRight);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    newdate->setObjectName("QDate");
    newWidget->setObjectName("date");
}
void Document::AddItemDate(QVBoxLayout * boxlayout,QString name,QString date) {
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(name);
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QDateEdit* newdate = new QDateEdit();

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);

    newdate->setCalendarPopup(1);
    newdate->setDate(QDate::fromString(date,"yyyy-MM-dd"));
    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(sep);
    newLayout->addWidget(newdate);
    newLayout->addStretch();
    titleEdit->hide();

    //delButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    newLayout->setAlignment(title, Qt::AlignLeft);
    newLayout->setAlignment(sep, Qt::AlignLeft);
    newLayout->setAlignment(newdate, Qt::AlignLeft);
    newLayout->setAlignment(delButton, Qt::AlignRight);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    newdate->setObjectName("QDate");
    newWidget->setObjectName("date");
}
void Document::AddItemDropdown() {
    QObject* item = QObject::sender();
    QVBoxLayout* boxlayout = qobject_cast<QVBoxLayout*>(item->parent());
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(Kor("��Ӵٿ�"));
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QComboBox* newdd = new QComboBox();

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);


    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(newdd);
    newLayout->addStretch();

    titleEdit->hide();
    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);

    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    newdd->setObjectName("QComboBox");
    newWidget->setObjectName("dropDown");
}
void Document::AddItemDropdown(QVBoxLayout * boxlayout,QString name,QString setting) {
    QWidget* tmp=new QWidget();
    Widget* newWidget = new Widget(tmp);
    QHBoxLayout* newLayout = new QHBoxLayout();
    QPushButton* delButton = new QPushButton(newWidget);
    QLabel* titleLabel=new QLabel(name);
    QLineEdit* titleEdit=new QLineEdit(newWidget);
    DoubleClickedWidget* title = new DoubleClickedWidget(titleLabel);
    QLabel* sep = new QLabel((" :"), newWidget);
    QComboBox* newdd = new QComboBox();

    newLayout->setObjectName("newlayer");
    titleEdit->setObjectName("titleEdit");

    titleEdit->setMaxLength(10);
    titleEdit->setFixedWidth(100);
    titleEdit->setAlignment(Qt::AlignRight);

    newLayout->addWidget(delButton);
    newLayout->addWidget(title);
    newLayout->addWidget(titleEdit);
    newLayout->addWidget(sep);
    newLayout->addWidget(newdd);
    newLayout->addStretch();
    titleEdit->hide();

    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(titleEdit,&QLineEdit::editingFinished,title,&DoubleClickedWidget::hideText);
    newWidget->setLayout(newLayout);
    boxlayout->addWidget(newWidget);

    delButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFlat(1);

    delButton->setObjectName("delButton");
    title->setObjectName("QLabel");
    newdd->setObjectName("QComboBox");
    newWidget->setObjectName("dropDown");
}

void Document::add_tool_option(QGroupBox* box, QVBoxLayout * boxLayout){
    QWidget* toolWidget = new QWidget(box);

    QToolButton* tool = new QToolButton(toolWidget);
    QHBoxLayout* toolLayout = new QHBoxLayout(toolWidget);
    QMenu* Menu = new QMenu();
    QMenu* InputMenu = new QMenu();
    toolLayout->addStretch();
    toolLayout->addWidget(tool, Qt::AlignRight);

    QAction* TBAAdd = new QAction(Kor("�߰�"), tool);
    TBAAdd->setStatusTip(Kor("���������� �߰��մϴ�."));
    QAction* TBADelete = new QAction(Kor("����"), tool);
    TBADelete->setStatusTip(Kor("���������� �����մϴ�."));
    connect(TBADelete, SIGNAL(triggered()), this, SLOT(deleteBox()));

    QAction* TBAAddText = new QAction(Kor("�ؽ�Ʈ"), boxLayout);
    connect(TBAAddText, SIGNAL(triggered()), this, SLOT(AddItemText()));
    QAction* TBAAddTextarea = new QAction(Kor("�� ����"), boxLayout);
    connect(TBAAddTextarea, SIGNAL(triggered()), this, SLOT(AddItemTextarea()));
    QAction* TBAAddDropdown = new QAction(Kor("��� �ٿ�"), boxLayout);
    connect(TBAAddDropdown, SIGNAL(triggered()), this, SLOT(AddItemDropdown()));
    QAction* TBAAddDate = new QAction(Kor("��¥"), boxLayout);
    connect(TBAAddDate, SIGNAL(triggered()), this, SLOT(AddItemDate()));
    QAction* TBAAddImage = new QAction(Kor("�̹���"), boxLayout);
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
    toolWidget->setObjectName("tool");

    boxLayout->addWidget(toolWidget);
}

void Document::deleteItem() {

    QObject* item = QObject::sender();
    disconnect(item, SIGNAL(clicked()), this, SLOT(deleteItem()));
    delete item->parent();
}

void Document::deleteBox() {
    QObject* item = QObject::sender();
    disconnect(item, SIGNAL(triggered()), this, SLOT(deleteBox()));
    delete item->parent()->parent()->parent();
}

void Document::make_doc0() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    boxLayout->setObjectName("groupBoxLayout");
    QVBoxLayout* layout = tab->boxArea;

    add_tool_option(box, boxLayout);

    box->setAlignment(Qt::AlignTop);
    box->setMinimumSize(800, 800);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    boxLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    boxLayout->setAlignment(Qt::AlignTop);

    layout->addWidget(box);
}

void Document::make_doc1() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    boxLayout->setObjectName("groupBoxLayout");
    QVBoxLayout* layout = tab->boxArea;

    add_tool_option(box, boxLayout);
    AddItemText(boxLayout, Kor("�̸�"),"");
    AddItemText(boxLayout, Kor("����"),"");
    AddItemText(boxLayout, Kor("�ּ�"),"");

    box->setAlignment(Qt::AlignTop);
    box->setMinimumSize(800, 800);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    boxLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    boxLayout->setAlignment(Qt::AlignTop);

    layout->addWidget(box);
}

void Document::make_doc2() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    boxLayout->setObjectName("groupBoxLayout");
    QVBoxLayout* layout = tab->boxArea;

    add_tool_option(box, boxLayout);

    box->setAlignment(Qt::AlignTop);
    box->setMinimumSize(800, 800);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    boxLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    boxLayout->setAlignment(Qt::AlignTop);

    layout->addWidget(box);
}

void Document::make_doc3() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    boxLayout->setObjectName("groupBoxLayout");
    QVBoxLayout* layout = tab->boxArea;

    add_tool_option(box, boxLayout);

    box->setAlignment(Qt::AlignTop);
    box->setMinimumSize(800, 800);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    boxLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    boxLayout->setAlignment(Qt::AlignTop);

    layout->addWidget(box);
}

void Document::make_doc4() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    boxLayout->setObjectName("groupBoxLayout");
    QVBoxLayout* layout = tab->boxArea;

    add_tool_option(box, boxLayout);

    box->setAlignment(Qt::AlignTop);
    box->setMinimumSize(800, 800);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    boxLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    boxLayout->setAlignment(Qt::AlignTop);

    layout->addWidget(box);
}

void Document::make_doc5() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    boxLayout->setObjectName("groupBoxLayout");
    QVBoxLayout* layout = tab->boxArea;

    add_tool_option(box, boxLayout);

    box->setAlignment(Qt::AlignTop);
    box->setMinimumSize(800, 800);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    boxLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    boxLayout->setAlignment(Qt::AlignTop);

    layout->addWidget(box);
}

void Document::make_doc6() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    boxLayout->setObjectName("groupBoxLayout");
    QVBoxLayout* layout = tab->boxArea;

    add_tool_option(box, boxLayout);

    box->setAlignment(Qt::AlignTop);
    box->setMinimumSize(800, 800);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    boxLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    boxLayout->setAlignment(Qt::AlignTop);

    layout->addWidget(box);
}

void Document::make_doc7() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    boxLayout->setObjectName("groupBoxLayout");
    QVBoxLayout* layout = tab->boxArea;

    add_tool_option(box, boxLayout);

    box->setAlignment(Qt::AlignTop);
    box->setMinimumSize(800, 800);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    boxLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    boxLayout->setAlignment(Qt::AlignTop);

    layout->addWidget(box);
}

void Document::make_doc8() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    boxLayout->setObjectName("groupBoxLayout");
    QVBoxLayout* layout = tab->boxArea;

    add_tool_option(box, boxLayout);

    box->setAlignment(Qt::AlignTop);
    box->setMinimumSize(800, 800);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    boxLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    boxLayout->setAlignment(Qt::AlignTop);

    layout->addWidget(box);
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
