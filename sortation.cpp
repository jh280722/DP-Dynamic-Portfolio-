#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sortation.h"

QStringList sortations = {Kor("���� ����"), Kor("�з� ����"), Kor("��� ����"), Kor("Ȱ�� �� ������"),
        Kor("�ڰ���"), Kor("������Ʈ"), Kor("�ڱ�Ұ���"), Kor("��Ʈ������"), Kor("��Ÿ")};
int srtRange[11] = {0, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

Sortation::Sortation(QWidget *parent)
    : QWidget(parent)
{
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

        QWidget* empty = new QWidget(srtAreaWidgetContents);

        empty->setObjectName("srt"+QString::number(i+1)+"empty");
        empty->setMinimumHeight(11);
        srtAreaLayout->addWidget(empty);
        empty->hide();

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
    int srtIdx = srt->objectName().remove(0,3).toInt();
    QString emptyName = srt->objectName().append("empty");
    QWidget* empty = srt->parent()->findChild<QWidget*>(emptyName);

    if (empty->isHidden()) {
        selBtn->setIcon(QIcon(":/images/minus_white.png"));
        empty->show();

        QList<QWidget*>::iterator i;
        for (i=docBtnList[srtIdx].begin(); i!=docBtnList[srtIdx].end(); i++) {
            QWidget* doc = *i;
            doc->show();
        }
    }
    else {
        selBtn->setIcon(QIcon(":/images/plus_white.png"));
        empty->hide();

        QList<QWidget*>::iterator i;
        for (i=docBtnList[srtIdx].begin(); i!=docBtnList[srtIdx].end(); i++) {
            QWidget* doc = *i;
            doc->hide();
        }
    }
}

//���� ���鶧 �� �� ����Ǵ� �Լ�
void Sortation::add_box(QWidget* docTab, int srtIdx, int listIdx) {

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
        QWidget* srtAreaWidgetContents = srt->parentWidget();
        QVBoxLayout* srtAreaLayout = (QVBoxLayout*)srtAreaWidgetContents->layout();
        QString selOpenName = srt->objectName().append("open");
        QPushButton* selOpen = srt->findChild<QPushButton*>(selOpenName);
        int srtIdx = srt->objectName().remove(0,3).toInt();

        QWidget* newDoc = new QWidget(srtAreaWidgetContents);
        QHBoxLayout* newDocLayout = new QHBoxLayout(newDoc);
        QPushButton* open = new QPushButton(docName, newDoc);
        QPushButton* active = new QPushButton(newDoc);

        open->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        open->setStyleSheet("padding-left: 20px; text-align: left; font-family: Malgun Gothic; font-size: 12px;");
        open->setFlat(true);
        connect(open, SIGNAL(clicked()), this, SLOT(on_docopen_clicked()));
        active->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        active->setFixedWidth(41);
        active->setFlat(true);
        active->setIconSize(QSize(12, 12));
        connect(active, SIGNAL(clicked()), this, SLOT(on_docactive_clicked()));

        newDocLayout->setSpacing(0);
        newDocLayout->setContentsMargins(0, 0, 0, 0);
        newDocLayout->addWidget(open);
        newDocLayout->addWidget(active);
        //newDoc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        newDoc->setFixedHeight(31);
        newDoc->setLayout(newDocLayout);
        srtAreaLayout->insertWidget(srtRange[srtIdx+1]-1, newDoc);
        //srtAreaWidgetContents->layout()->addWidget(newDoc);
        //newDoc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

        //��ư ����Ʈ�� �߰� | connect ���ֱ�
        int sz=docList[srtIdx].size();
        QWidget* new_tab = new QWidget();
        add_box(new_tab, srtIdx, sz);
        docList[srtIdx].push_back(new_tab);
        docBtnList[srtIdx].append(newDoc);
        for (int i = srtIdx + 1; i < 11; i++){
            srtRange[i]++;
        }

        QString emptyName = srt->objectName().append("empty");
        QWidget* empty = srt->parent()->findChild<QWidget*>(emptyName);

        if (empty->height() > 0) empty->setFixedHeight(0);
        if (empty->isHidden()) {
            empty->show();
            selOpen->setIcon(QIcon(":/images/minus_white.png"));
        }
    }
}

void Sortation::on_docopen_clicked() {
    QObject* sel = QObject::sender();
    QPushButton* selPB = (QPushButton*)sel;
    QWidget* selDoc = (QWidget*)sel->parent();
    bool existList = false;
    int tabIdx = -1;
    int srtIdx = -1;
    int subSrtIdx = -1;
    QTabWidget* docTab=parent()->findChild<QTabWidget*>("docTab");

    for (int i=0; i<9; i++) {
        if (docBtnList[i].contains(selDoc)) {
            srtIdx = i;
            break;
        }
    }
    subSrtIdx= docBtnList[srtIdx].indexOf(selDoc);

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

void Sortation::on_docactive_clicked()
{
    QObject* sel = QObject::sender();
    QPushButton* active = (QPushButton*)sel;

    if (active->icon().isNull()) {
        active->setIcon(QIcon(":/images/dot.png"));
    }
    else {
        active->setIcon(QIcon());
    }

}

void Sortation::delete_tab(int srtIdx) {
    QTabWidget* docTab=parent()->findChild<QTabWidget*>("docTab");
    QWidget* empty = parent()->findChild<QWidget*>("srt" + QString::number(srtIdx) + "empty");
    docTab->removeTab(docTab->currentIndex());
    for (int i = srtIdx + 1; i < 11; i++){
        srtRange[i]--;
    }
    if (docList[srtIdx].size() == 0) {
        empty->setFixedHeight(11);
    }
}
