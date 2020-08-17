#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sortation.h"

Sortation::Sortation(QWidget *parent)
    : QWidget(parent)
{
    QStringList sortations = {Kor("���� ����"), Kor("�з� ����"), Kor("��� ����"), Kor("Ȱ�� �� ������"),
                              Kor("�ڰ���"), Kor("������Ʈ"), Kor("�ڱ�Ұ���"), Kor("��Ʈ������"), Kor("��Ÿ")};

    QWidget* srtAreaWidgetContents = parent->findChild<QWidget*>("srtAreaWidgetContents");
    QVBoxLayout* srtAreaLayout = new QVBoxLayout(srtAreaWidgetContents);

    // ���� ��, ���� ���� ����
    for (int i=0; i<sortations.length(); i++) {
        QWidget* srt = new QWidget(srtAreaWidgetContents);
        QHBoxLayout* srtLayout = new QHBoxLayout(srt);
        QPushButton* open = new QPushButton(sortations.value(i).prepend(" "), srt);
        QPushButton* add = new QPushButton(srt);

        open->setObjectName("srt"+QString::number(i+1)+"open");
        open->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        open->setStyleSheet("padding-left: 10px; text-align: left; font-family: Malgun Gothic; font-weight: bold; color: white;");
        open->setIcon(QIcon(":/images/plus_white.png"));
        open->setIconSize(QSize(16, 16));
        open->setFlat(true);
        connect(open, SIGNAL(clicked()), this, SLOT(on_srtopen_clicked()));
        add->setObjectName("srt"+QString::number(i+1)+"add");
        add->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        add->setFixedWidth(41);
        add->setIcon(QIcon(":/images/portable-document-format-white.png"));
        add->setIconSize(QSize(16, 16));
        add->setFlat(true);
        connect(add, SIGNAL(clicked()), this, SLOT(on_srtadd_clicked()));

        srtLayout->setSpacing(0);
        srtLayout->setContentsMargins(0, 0, 0, 0);
        srtLayout->addWidget(open);
        srtLayout->addWidget(add);
        srt->setObjectName("srt"+QString::number(i+1));
        srt->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        srt->setFixedHeight(41);
        srt->setStyleSheet("background-color: rgb(44, 62, 80);");
        srt->setLayout(srtLayout);
        srtAreaLayout->addWidget(srt);


        QWidget* docList = new QWidget(srtAreaWidgetContents);
        QVBoxLayout* docListLayout = new QVBoxLayout(docList);

        docListLayout->setSpacing(0);
        docListLayout->setContentsMargins(0, 0, 0, 0);
        docList->setObjectName("srt"+QString::number(i+1)+"docList");
        //docList->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        docList->setMinimumHeight(11);
        docList->setLayout(docListLayout);
        srtAreaLayout->addWidget(docList);
        docList->hide();

    }

    srtAreaLayout->setSpacing(0);
    srtAreaLayout->setContentsMargins(0, 0, 0, 0);
    srtAreaLayout->setAlignment(Qt::AlignTop);
    srtAreaWidgetContents->setObjectName("srtAreaWidgetContents");
    srtAreaWidgetContents->setLayout(srtAreaLayout);
}

Sortation::~Sortation()
{
    //delete ui;
}

void Sortation::on_srtopen_clicked()
{
    QObject* sel = QObject::sender();
    QPushButton* selBtn = (QPushButton*)sel;
    QWidget* srt = (QWidget*)sel->parent();
    QString docListName = srt->objectName().append("docList");
    QWidget* docList = srt->parent()->findChild<QWidget*>(docListName);

    if (docList->isHidden()) {
        selBtn->setIcon(QIcon(":/images/minus_white.png"));
        docList->show();
    }
    else {
        selBtn->setIcon(QIcon(":/images/plus_white.png"));
        docList->hide();
    }
}


void Sortation::connect_doc() {
    QWidget* sel = (QWidget*)QObject::sender();
    bool existList = false;
    int tabIdx = -1;
    int subSrtIdx = -1;
    QTabWidget* docTab=parent()->findChild<QTabWidget*>("docTab");

    QPushButton *selPB=(QPushButton*)(QObject::sender());

    subSrtIdx= docBtnList[srtIdx].indexOf(selPB);
    for (int i = 0; i < docTab->count(); ++i) {
        if (selPB->text() == docTab->tabText(i)) {
            existList = true;
            tabIdx = i;
            break;
        }
    }
    if (existList) {
        docTab->setCurrentIndex(tabIdx);
    }
    else {
        QWidget* new_tab = docList[srtIdx][subSrtIdx];
        docTab->addTab(new_tab, selPB->text());
        docTab->setCurrentIndex(docTab->count() - 1);
    }
}

//���� ���鶧 �� �� ����Ǵ� �Լ�
void Sortation::add_box(QWidget* docTab, int listIdx) {

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
    connect(PB, SIGNAL(clicked()), this, SLOT(delete_tab()));
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

void Sortation::on_srtadd_clicked()
{
    bool ok;

    QString docName = QInputDialog::getText(this, Kor("�� ����"), Kor("�̸��� �Է��ϼ���:"), QLineEdit::Normal, "", &ok);

    if (ok && !docName.isEmpty()) {
        QObject* sel = QObject::sender();
        QWidget* srt = (QWidget*)sel->parent();
        QString openName = srt->objectName().append("open");
        QString docListName = srt->objectName().append("docList");
        QPushButton* open = srt->findChild<QPushButton*>(openName);
        QWidget* docBtn = srt->parent()->findChild<QWidget*>(docListName);
        QPushButton* newDoc = new QPushButton(docName, docBtn);
        newDoc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        newDoc->setFixedHeight(31);
        newDoc->setStyleSheet("padding-left: 20px; text-align: left; font-family: Malgun Gothic; font-size: 12px;");
        newDoc->setFlat(true);
        docBtn->layout()->addWidget(newDoc);

        //��ư ����Ʈ�� �߰� | connect ���ֱ�
        QString srtN=srt->objectName().remove(0,3);
        srtIdx=srtN.toInt();
        connect(newDoc, SIGNAL(clicked()), this, SLOT(connect_doc()));
        int sz=docList[srtIdx].size();
        QWidget* new_tab = new QWidget();
        add_box(new_tab, sz);
        docList[srtIdx].push_back(new_tab);
        docBtnList[srtIdx].push_back(newDoc);
        docBtn->setFixedHeight(docBtnList[srtIdx].size() >0 ? docBtnList[srtIdx].size()*30 + 1 : 11);

        if (docBtn->isHidden()) {
            open->setIcon(QIcon(":/images/minus_white.png"));
            docBtn->show();
        }
    }
}


void Sortation::delete_tab() {
    QTabWidget* docTab=parent()->findChild<QTabWidget*>("docTab");
    docTab->removeTab(docTab->currentIndex());
    QWidget* docBtn = parent()->findChild<QWidget*>("srt"+QString::number(srtIdx)+"docList");
    docBtn->setFixedHeight(docBtnList[srtIdx].size() >0 ? docBtnList[srtIdx].size()*30 + 1 : 11);
}
