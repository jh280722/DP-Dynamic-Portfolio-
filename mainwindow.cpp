#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    num[0]=num[1]=num[2]=0;
//    int w=ui->label_pic->width();
//    int h=ui->label_pic->height();
//    QPixmap pix(":/img/tmp.jpg");
//    ui->label_pic->setPixmap(pix);
//    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;

}


QPushButton* MainWindow::new_button(QString name, QString str)
{
       QPushButton* button = new QPushButton(str);
       button->setObjectName(name);
       return button;
}

void MainWindow::make_tab(QWidget* Tab){
    QWidget *widget = Tab;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    widget->setLayout(layout);

    QGroupBox *box = new QGroupBox(Kor("�⺻ ����"), widget);
    QVBoxLayout *boxLayout = new QVBoxLayout(box);
    layout->addWidget(box);

    QWidget* nameWidget = new QWidget(box);
    QWidget* ageWidget = new QWidget(box);
    QWidget* addressWidget = new QWidget(box);

    boxLayout->addWidget(nameWidget);
    boxLayout->addWidget(ageWidget);
    boxLayout->addWidget(addressWidget);

    QHBoxLayout *nameLayout = new QHBoxLayout(nameWidget);
    nameLayout->addWidget(new QLabel(Kor("�� �� :")));
    nameLayout->addWidget(new QLineEdit(nameWidget));


    QHBoxLayout *ageLayout = new QHBoxLayout(ageWidget);
    ageLayout->addWidget(new QLabel(Kor("�� �� :")));
    ageLayout->addWidget(new QLineEdit(ageWidget));

    QHBoxLayout *addressLayout = new QHBoxLayout(addressWidget);
    addressLayout->addWidget(new QLabel(Kor("�� �� :")));
    addressLayout->addWidget(new QLineEdit(addressWidget));


    QWidget* validateWidget = new QWidget(widget);
    QHBoxLayout *validateLayout = new QHBoxLayout(validateWidget);
    validateLayout->addWidget(new QPushButton(Kor("Ȯ ��"), validateWidget));
    validateLayout->addWidget(new QPushButton(Kor("�� ��"), validateWidget));
    validateLayout->addWidget(new QPushButton(Kor("�� ��"), validateWidget));
    layout->addWidget(validateWidget);
}


void MainWindow::on_plus_clicked(){
    QObject *sel=QObject::sender();
    QString name;
    QWidget *menu=0;
    if(sel==mb[0]){
        idx=0;
        name=Kor("�⺻ ���� ")+QString::number(num[idx]);
        menu=ui->dropmenu0;
    }
    else if(sel==mb[1]){
        idx=1;
        name=Kor("���� ���� ")+QString::number(num[idx]);
        menu=ui->dropmenu1;
    }
    else if(sel==mb[2]){
        idx=2;
        name=Kor("�� �� �� ")+QString::number(num[idx]);
        menu=ui->dropmenu2;
    }
    mb[idx]->setText(name);
    disconnect(mb[idx], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
    PBList[idx].push_back(new_button("dm"+QString::number(idx)+"_"+QString::number(num[idx]),Kor("�׸��߰�")));
    mb[idx]=PBList[idx][num[idx]];
    menu->layout()->addWidget(PBList[idx][num[idx]]);

    connect(PBList[idx][num[idx]], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
    connect(PBList[idx][num[idx]++], SIGNAL(clicked()), this, SLOT(connect_subTopic()));
}

void MainWindow::hide_show(int idx, int &flg){
    QWidget* menu=0;
    if(idx==0)
        menu=ui->dropmenu0;
    else if(idx==1)
        menu=ui->dropmenu1;
    else if(idx==2)
        menu=ui->dropmenu2;

    if(flg==0){
        flg=2;
        PBList[idx].push_back(new_button("dm"+QString::number(idx)+"_"+QString::number(num[idx]),
                                         Kor("�׸��߰�")));
        mb[idx]=PBList[idx][num[idx]];
        menu->layout()->addWidget(PBList[idx][num[idx]]);

        connect(PBList[idx][num[idx]], SIGNAL(clicked()), this, SLOT(on_plus_clicked()));
        connect(PBList[idx][num[idx]++], SIGNAL(clicked()), this, SLOT(connect_subTopic()));
        ui->Tb1->setTabsClosable(true);
        connect(ui->Tb1,SIGNAL(tabCloseRequested(int)),this,SLOT(on_Tb1_deleteTab(int)));
    }
    else if(flg==1){
        flg=2;
        for(int i = 0; i < num[idx]; i++)
        {
             PBList[idx][i]->show();
        }
    }
    else if(flg==2){
        flg=1;
        for(int i = 0; i < num[idx]; i++)
        {
             PBList[idx][i]->hide();
        }
    }
}
void MainWindow::connect_subTopic(){
    QObject *sel=QObject::sender();
    bool existList=false;
    int tmpidx=-1;
    int subTopicidx=-1;


    for(int i=0;i<PBList[0].size();++i){
        if(PBList[0][i]==sel){
            Topicidx=0;
            subTopicidx=i;
        }
    }
    for(int i=0;i<PBList[1].size();++i){
        if(PBList[1][i]==sel){
            Topicidx=1;
            subTopicidx=i;
        }
    }
    for(int i=0;i<PBList[2].size();++i){
        if(PBList[2][i]==sel){
            Topicidx=2;
            subTopicidx=i;
        }
    }
    for(int i=0;i<ui->Tb1->count();++i){
        if(PBList[Topicidx][subTopicidx]->text()== ui->Tb1->tabText(i)){
            existList=true;
            tmpidx=i;
            break;
        }
    }



    if(existList){
        ui->Tb1->setCurrentIndex(tmpidx);

    }
    else{
        mbt=PBList[Topicidx][subTopicidx];
        on_Tb1_addTab();
       // connect(mbt,SIGNAL(clicked()),this,SLOT(on_Tb1_addTab()));
        ui->Tb1->setCurrentIndex(ui->Tb1->count()-1);
    }

}
void MainWindow::on_Tb1_deleteTab(int idx){
   ui->Tb1->removeTab(idx);

//   disconnect(mbt,SIGNAL(clicked()),this,SLOT(connect_subTopic()));
//   disconnect( mbt,SIGNAL(clicked()),this,SLOT(on_Tb1_addTab()));
}
void MainWindow::on_Tb1_addTab(){
    QWidget* new_tab= new QWidget;
    ui->Tb1->addTab(new_tab,mbt->text());
    //ui->Tb1->show();
    make_tab(new_tab);
    TList[Topicidx].push_back(new_tab);

    if(ui->Tb1->indexOf(new_tab)!=-1){
       // disconnect( mbt,SIGNAL(clicked()),this,SLOT(on_Tb1_addTab()));
       // connect( mbt,SIGNAL(clicked()),this,SLOT(on_Tb1_addTab()));
        //ui->Tb1->removeTab(ui->Tb1->indexOf(new_tab));
    }
}


void MainWindow::on_dm0_clicked()
{
    static int flg=0;
    idx=0;
    hide_show(idx,flg);
}

void MainWindow::on_dm1_clicked()
{
    static int flg=0;
    idx=1;
    hide_show(idx,flg);
}

void MainWindow::on_dm2_clicked()
{
    static int flg=0;
    idx=2;
    hide_show(idx,flg);
}