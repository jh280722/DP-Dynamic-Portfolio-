#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sortation.h"

QStringList sortations = {Kor("���� ����"), Kor("�з� ����"), Kor("��� ����"), Kor("Ȱ�� �� ������"),
                          Kor("�ڰ���"), Kor("������Ʈ"), Kor("�ڱ�Ұ���"), Kor("��Ʈ������"), Kor("��Ÿ")};
int srtRange[11] = {0, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

Sortation::Sortation(QWidget *parent)
    : QWidget(parent)
{
    setAcceptDrops(true);

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
        open->setAcceptDrops(true); //hahahahahaha
        open->installEventFilter(this);
        connect(open, SIGNAL(clicked()), this, SLOT(on_srtopen_clicked()));
        add->setObjectName("srt"+QString::number(i+1)+"add");
        add->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        add->setFixedWidth(41);
        add->setIcon(QIcon(":/images/portable-document-format-white.png"));
        add->setIconSize(QSize(16, 16));
        add->setFlat(true);
        add->setAcceptDrops(true); //hahahahahaha
        add->installEventFilter(this);
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
        //srt->installEventFilter(this);
        srtAreaLayout->addWidget(srt);

        QWidget* empty = new QWidget(srtAreaWidgetContents);

        empty->setObjectName("srt"+QString::number(i+1)+"empty");
        empty->setMinimumHeight(11);
        empty->setAcceptDrops(true);
        empty->installEventFilter(this);
        srtAreaLayout->addWidget(empty);
        empty->hide();

    }

    srtAreaLayout->setSpacing(0);
    srtAreaLayout->setContentsMargins(0, 0, 0, 0);
    srtAreaLayout->setAlignment(Qt::AlignTop);
    srtAreaWidgetContents->setObjectName("srtAreaWidgetContents");
    srtAreaWidgetContents->setLayout(srtAreaLayout);

    load_docList();
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
    int srtIdx = srt->objectName().mid(3).toInt();
    QString emptyName = srt->objectName().append("empty");
    QWidget* empty = srt->parent()->findChild<QWidget*>(emptyName);

    if (empty->isHidden()) {
        selBtn->setIcon(QIcon(":/images/minus_white.png"));
        empty->show();

        for (auto i : docList[srtIdx]) {
            QWidget* doc = i->PBS;
            doc->show();
        }
    }
    else {
        selBtn->setIcon(QIcon(":/images/plus_white.png"));
        empty->hide();
        for (auto i : docList[srtIdx]) {
            QWidget* doc = i->PBS;
            doc->hide();
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
        for(auto it:docList[i]){
            if(it->PBS==selDoc){
                srtIdx = i;
                subSrtIdx=docList[i].indexOf(it);
                break;
            }
        }
        if(srtIdx!=-1)
            break;
    }

    for (int i = 0; i < docTab->count(); ++i) {
        if (QString::number(srtIdx)+'_'+ selPB->text() == docTab->tabText(i)) {
            existList = true;
            tabIdx = i;
            break;
        }
    }
    if (existList) {
        docTab->setCurrentIndex(tabIdx);
    }
    else {
        docList[srtIdx][subSrtIdx]->load_doc();
        QWidget* new_tab = docList[srtIdx][subSrtIdx];

        docTab->tabBar()->setStyleSheet(QString("QTabBar::tab { width:100; }"));
        docTab->addTab(new_tab, QString::number(srtIdx)+'_'+ selPB->text());
        docTab->setCurrentIndex(docTab->count() - 1);
    }
}

QString Sortation:: name_check(QString docName,int srtIdx){
    QStringList currentNameList;
    for (auto i : docList[srtIdx]) {
        QPushButton* docOpen = i->PBS->findChildren<QPushButton*>().first();
        currentNameList.append(docOpen->text());
    }

    if (currentNameList.contains(docName)) {
        int i = 2;
        QString alterName = docName;
        while(currentNameList.contains(alterName)) {
            alterName = docName + " (" + QString::number(i++) + ")";
        };
        QMessageBox msgBox;
        msgBox.setText("\"" + docName + Kor("\"���� \"") + alterName + Kor("\"(��)�� �̸��� �����Ͻðڽ��ϱ�?"));
        msgBox.setInformativeText(Kor("�� ��ġ�� �̸��� ���� ������ �ֽ��ϴ�."));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        if (ret == QMessageBox::No)docName="";
        else docName = alterName;
    }
    return docName;
}
void Sortation::on_srtadd_clicked()
{
    QObject* sel = QObject::sender();
    QWidget* srt = (QWidget*)sel->parent();
    int srtIdx = srt->objectName().mid(3).toInt();

    bool ok;

    QString docName = QInputDialog::getText(this, Kor("�� ����"), Kor("�̸��� �Է��ϼ���:"), QLineEdit::Normal, "", &ok);
    QString getName =name_check(docName,srtIdx);

    if (ok && !getName.isEmpty()) {
        make_docBtn(getName, srtIdx, false);
    }
}

void Sortation::make_docBtn(QString docName, int srtIdx, bool isLoad){
    QWidget* srt = this->parent()->findChild<QWidget*>("srt"+QString::number(srtIdx));
    QWidget* srtAreaWidgetContents = srt->parentWidget();
    QVBoxLayout* srtAreaLayout = (QVBoxLayout*)srtAreaWidgetContents->layout();
    QString selOpenName = srt->objectName().append("open");
    QPushButton* selOpen = srt->findChild<QPushButton*>(selOpenName);

    QWidget* newPBS = new QWidget(srtAreaWidgetContents);
    QHBoxLayout* newPBSLayout = new QHBoxLayout(newPBS);
    QPushButton* open = new QPushButton(docName, newPBS);
    QPushButton* active = new QPushButton(newPBS);

    open->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    open->setStyleSheet("padding-left: 20px; text-align: left; font-family: Malgun Gothic; font-size: 12px;");
    open->setFlat(true);
    open->installEventFilter(this);
    open->setAcceptDrops(true);
    connect(open, SIGNAL(clicked()), this, SLOT(on_docopen_clicked()));
    active->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    active->setFixedWidth(41);
    active->setFlat(true);
    active->installEventFilter(this);
    active->setAcceptDrops(true);
    active->setIconSize(QSize(12, 12));
    connect(active, SIGNAL(clicked()), this, SLOT(on_docactive_clicked()));

    newPBSLayout->setSpacing(0);
    newPBSLayout->setContentsMargins(0, 0, 0, 0);
    newPBSLayout->addWidget(open);
    newPBSLayout->addWidget(active);
    //newDoc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    newPBS->setObjectName(QString::number(srtIdx) + "_" + docName);
    newPBS->setFixedHeight(31);
    newPBS->setLayout(newPBSLayout);
    srtAreaLayout->insertWidget(srtRange[srtIdx+1]-2, newPBS);
    //srtAreaWidgetContents->layout()->addWidget(newDoc);
    //newDoc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    //��ư ����Ʈ�� �߰� | connect ���ֱ�
    Document* newDoc = new Document(docName, srtIdx, 1);
    newDoc->PBS=newPBS;
    if(isLoad) newDoc->load_doc();
    docList[srtIdx].push_back(newDoc);

    for (int i = srtIdx + 1; i < 11; i++){
        srtRange[i]++;
    }
    qDebug() << srtRange[0] << ", " << srtRange[1] << ", " << srtRange[2] << ", " << srtRange[3] << ", " << srtRange[4] << ", " << srtRange[5] << ", " << srtRange[6] << ", " << srtRange[7] << ", " << srtRange[8] << ", " << srtRange[9] << ", " << srtRange[10];
    QString emptyName = srt->objectName().append("empty");
    QWidget* empty = srt->parent()->findChild<QWidget*>(emptyName);

    if (empty->height() > 0) empty->setFixedHeight(0);
    if (empty->isHidden()) {
        empty->show();
        selOpen->setIcon(QIcon(":/images/minus_white.png"));
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

void Sortation::save_docList(){
    QString ApplicationPath=QApplication::applicationDirPath();
    qDebug()<<ApplicationPath;
    QDir Directory(ApplicationPath+"/Data/Srt.ini"); // ���� ����
    if(!Directory.exists()) // ������ �������� �������
    {
        Directory.mkdir(ApplicationPath+"/Data"); // ���� ����
    }
    QFile File(ApplicationPath+"/Data/Srt.ini");
    File.open(QFile::WriteOnly|QFile::Text); // ���� ����, �ؽ�Ʈ, �̾��
    QTextStream out(&File);
    for(int i=0;i<10;i++){
        out<<i<<'\n';
        out<<docList[i].size()<<'\n';
        for(auto doc:docList[i]){
            out<<doc->name<<'\n';
            doc->save_doc();
        }
    }
    File.close(); // ���ϴݱ�
}

void Sortation::load_docList(){

    QString ApplicationPath=QApplication::applicationDirPath();
    QDir Directory(ApplicationPath+"/Data/Srt.ini"); // ���� ����
    if(!Directory.exists()) // ������ �������� �������
    {
        Directory.mkdir(ApplicationPath+"/Data"); // ���� ����
    }
    QFile File(ApplicationPath+"/Data/Srt.ini");
    File.open(QFile::ReadOnly|QFile::Text); // ���� ����, �ؽ�Ʈ
    QTextStream in(&File);

    while(!in.atEnd())  // ���� ������ �о
    {
        int srtIdx,num;
        srtIdx=in.readLine().toInt();
        num=in.readLine().toInt();
        for(int i=0;i<num;i++){
            QString name;
            name = in.readLine();
            make_docBtn(name, srtIdx, true);
        }
    }
    File.close(); // ���ϴݱ�
}

bool Sortation::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::Drop) {
        QDropEvent*e= static_cast<QDropEvent *>(event);
        if(e->mimeData()->hasFormat("application/x-qtcustomitem")) {
            QWidget* targetObj;
            //���� Ŭ���� targetObj�� object
            if((*object).objectName().right(5) == "empty")
                targetObj = (QWidget*)object;
            //������ư�̳� �з��� ��ư Ŭ���� targetObj�� object->parent
            else targetObj = (QWidget*)object->parent();
            if(targetObj->objectName().left(3)== "srt"){//����ϴ� ��ġ�� �з���ư�̰ų� �����Ͻ�
                QWidget* srtAreaWidgetContents = targetObj->parentWidget();
                QWidget* srt;
                //���� Ŭ���� srt ã��
                if(targetObj->objectName().right(5) == "empty") {
                    QString srtName = targetObj->objectName().left(4);
                    srt = srtAreaWidgetContents->findChild<QWidget*>(srtName);
                }
                else srt = targetObj;
                QVBoxLayout* srtAreaLayout = (QVBoxLayout*)srt->parentWidget()->layout();
                QString selOpenName = srt->objectName().append("open");
                QPushButton* selOpen = srt->findChild<QPushButton*>(selOpenName);
                QString selDocObjName = e->mimeData()->text();
                QString selDocName = selDocObjName.mid(2);
                QWidget * selDoc = srtAreaWidgetContents->findChild<QWidget*>(selDocObjName);
                int subSrtIdx;

                int srtIdxTo = srt->objectName().mid(3).toInt();
                int srtIdxFrom = selDocObjName[0].unicode()-'0';

                //qDebug()<<srtIdxTo;
                //qDebug()<<srtIdxFrom;

                if (srtIdxTo != srtIdxFrom) {
                    selDocName = name_check(selDocName, srtIdxTo);
                    if (selDocName.isEmpty()) return false;
                    selDocObjName = QString::number(srtIdxTo) + "_" + selDocName;
                    selDoc->setObjectName(selDocObjName);
                    selDoc->findChild<QPushButton*>()->setText(selDocName);
                }

                for(auto it:docList[srtIdxFrom]){

                    if(it->PBS==selDoc){
                        subSrtIdx=docList[srtIdxFrom].indexOf(it);
                        docList[srtIdxTo].push_back(it);
                        docList[srtIdxFrom].remove(subSrtIdx);
                        break;
                    }
                }

                srtAreaLayout->insertWidget(srtRange[srtIdxTo+1]-2,selDoc);

                for (int i = srtIdxTo+1; i < srtIdxFrom+1; i++){
                    srtRange[i]++;
                }
                for (int i = srtIdxFrom+1; i < srtIdxTo+1; i++){
                    srtRange[i]--;
                }

                //�ٸ� �з������� �ű� �� ��������
                //������ ���� �����־��� ��� -> empty: 0
                //�����־��� ��� -> empty: 0, show
                QString emptyToName = srt->objectName().append("empty");
                QWidget* emptyTo = srt->parent()->findChild<QWidget*>(emptyToName);
                if (emptyTo->height() > 0) emptyTo->setFixedHeight(0);
                if (emptyTo->isHidden()) {
                    emptyTo->show();
                    selOpen->setIcon(QIcon(":/images/minus_white.png"));
                }
                //�ٸ� �з������� �ű� �� �������
                //������ 0�� �� ���
                QWidget* srtFrom = targetObj->parent()->findChild<QWidget*>("srt"+QString::number(srtIdxFrom));
                QString emptyFromName = srtFrom->objectName().append("empty");
                QWidget* emptyFrom = srt->parent()->findChild<QWidget*>(emptyFromName);
                if (docList[srtIdxFrom].empty()) {
                    emptyFrom->setFixedHeight(11);
                }

                QByteArray itemData = e->mimeData()->data("application/x-qtcustomitem");
                QDataStream dataStream(&itemData, QIODevice::ReadOnly);

                QPixmap pixmap;
                QPoint offset;
                dataStream >> pixmap >> offset;
            }
            else{//����ϴ� ��ġ�� ������ư�Ͻ�
                int srtIdxTo = targetObj->objectName().left(1).toInt();
                QWidget* srt = targetObj->parent()->findChild<QWidget*>("srt"+QString::number(srtIdxTo));
                QWidget* srtAreaWidgetContents = srt->parentWidget();
                QVBoxLayout* srtAreaLayout = (QVBoxLayout*)srt->parentWidget()->layout();
                QString selOpenName = srt->objectName().append("open");
                QPushButton* selOpen = srt->findChild<QPushButton*>(selOpenName);
                QString selDocObjName = e->mimeData()->text();
                QString selDocName = selDocObjName.mid(2);
                QWidget * selDoc = srtAreaWidgetContents->findChild<QWidget*>(selDocObjName);
                int subSrtIdxTo, subSrtIdxFrom;

                int srtIdxFrom = selDocObjName[0].unicode()-'0';

                if (srtIdxTo != srtIdxFrom) {//�з��� �ٸ��� �̸�����
                    selDocName = name_check(selDocName, srtIdxTo);
                    if (selDocName.isEmpty()) return false;
                    selDocObjName = QString::number(srtIdxTo) + "_" + selDocName;
                    selDoc->setObjectName(selDocObjName);
                    selDoc->findChild<QPushButton*>()->setText(selDocName);
                }

                for(auto it:docList[srtIdxTo]){//����ϴ� ��ġ�� �ε��� ã��
                    if(it->PBS==targetObj){
                        subSrtIdxTo=docList[srtIdxTo].indexOf(it);
                        break;
                    }
                }

                QMouseEvent*MouseE= static_cast<QMouseEvent *>(event);
                //qDebug()<<targetObj->y();
                //qDebug()<<MouseE->globalY();

                if(16 < MouseE->globalY()){// ���� ���� ����
                    subSrtIdxTo++;
                }

                for(auto it:docList[srtIdxFrom]){

                    if(it->PBS==selDoc){
                        subSrtIdxFrom=docList[srtIdxFrom].indexOf(it);
                        if(srtIdxTo!=srtIdxFrom || subSrtIdxTo!=subSrtIdxFrom+1) {
                            if(subSrtIdxTo>subSrtIdxFrom){
                                docList[srtIdxTo].insert(subSrtIdxTo,it);
                                docList[srtIdxFrom].remove(subSrtIdxFrom);
                            }
                            else{

                                docList[srtIdxFrom].remove(subSrtIdxFrom);
                                docList[srtIdxTo].insert(subSrtIdxTo,it);
                            }
                        }
                        break;
                    }
                }

                if(srtIdxTo==srtIdxFrom && subSrtIdxTo> subSrtIdxFrom)
                    subSrtIdxTo--;
                srtAreaLayout->insertWidget(srtRange[srtIdxTo]+subSrtIdxTo,selDoc);

                for (int i = srtIdxTo+1; i < srtIdxFrom+1; i++){
                    srtRange[i]++;
                }
                for (int i = srtIdxFrom+1; i < srtIdxTo+1; i++){
                    srtRange[i]--;
                }

                //�ٸ� �з������� �ű� �� ��������
                //������ ���� �����־��� ��� -> empty: 0
                //�����־��� ��� -> empty: 0, show
                QString emptyToName = srt->objectName().append("empty");
                QWidget* emptyTo = srt->parent()->findChild<QWidget*>(emptyToName);
                if (emptyTo->height() > 0) emptyTo->setFixedHeight(0);
                if (emptyTo->isHidden()) {
                    emptyTo->show();
                    selOpen->setIcon(QIcon(":/images/minus_white.png"));
                }
                //�ٸ� �з������� �ű� �� �������
                //������ 0�� �� ���
                QWidget* srtFrom = targetObj->parent()->findChild<QWidget*>("srt"+QString::number(srtIdxFrom));
                QString emptyFromName = srtFrom->objectName().append("empty");
                QWidget* emptyFrom = srt->parent()->findChild<QWidget*>(emptyFromName);
                if (docList[srtIdxFrom].empty()) {
                    emptyFrom->setFixedHeight(11);
                }

                QByteArray itemData = e->mimeData()->data("application/x-qtcustomitem");
                QDataStream dataStream(&itemData, QIODevice::ReadOnly);

                QPixmap pixmap;
                QPoint offset;
                dataStream >> pixmap >> offset;
            }


        } else {
            e->ignore();
        }
    }
    if(event->type()==QEvent::DragEnter){
        QDragEnterEvent*e= static_cast<QDragEnterEvent *>(event);
        qDebug() << "Possible actions : " << e->possibleActions();
        if(e->mimeData()->hasFormat("application/x-qtcustomitem")) {
            if(e->source() == this) {
                e->setDropAction(Qt::MoveAction);
                e->accept();
            } else {
                e->acceptProposedAction();
            }
        } else {
            e->ignore();
        }
    }
    if(event->type()==QEvent::MouseMove){
        QMouseEvent*e= static_cast<QMouseEvent *>(event);
        if(e->buttons() & Qt::LeftButton) {
            QDrag * drag = new QDrag(this);
            QMimeData * mimeData = new QMimeData;
            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);

            if((*object).objectName().left(3)!= "srt"){//���õ� ������Ʈ�� ������ư�Ͻ� �巡�� ����
                QPushButton *targetBtn = qobject_cast<QPushButton*>(object);
                QWidget *target = (QWidget*)targetBtn->parent();
                QPixmap *widgetPixmap = new QPixmap(target->size());
                target->render(widgetPixmap);
                QPixmap *resultPixmap = new QPixmap(target->size());
                resultPixmap->fill(Qt::transparent);
                QPainter p;
                p.begin(resultPixmap);
                p.setOpacity(0.5);
                p.drawPixmap(0, 0, *widgetPixmap);
                p.end();

                drag->setHotSpot(e->pos() - target->rect().topLeft());



                mimeData->setData("application/x-qtcustomitem", itemData);
                mimeData->setText(target->objectName());
                drag->setMimeData(mimeData);
                drag->setPixmap(*resultPixmap);
                drag->exec();
            }


        }
    }

    return false;
}
