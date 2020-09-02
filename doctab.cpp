#include "mainwindow.h"
#include "doctab.h"
#include "sortation.h"
#include "ui_mainwindow.h"

extern Sortation *sortation;

//class Widget : public QWidget{
//    Q_OBJECT

//public:
//    Widget(QWidget *parent = nullptr);
//    ~Widget();
//    void moussMoveEvent(QMouseEvent *ev);
//    bool eventFilter(QObject *obj,QEvent *ev);
//    void leaveEvent(QEvent *);
//    void enterEvent(QEvent *event) override;
//};

//void Widget:: enterEvent(QEvent *event){

//}

DocTab::DocTab(QWidget* parent, int srtIdx):QWidget(parent){
    setObjectName("doctab");
    this->SA=new QScrollArea(parent);
    QVBoxLayout* VBox = new QVBoxLayout(parent);
    VBox->addWidget(SA);
    //���� ��ũ�ѹ� ����
    SA->setWidgetResizable(1);
    SA->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );

    SA->setWidget(this);
    this->VLayout = new QVBoxLayout();//VBox�� ����
    this->setLayout( this->VLayout );

    this->srtIdx=srtIdx;
    this->SA->setObjectName("SA");
    this->VLayout->setObjectName("VLayout");
    this->box=new QWidget(this);
    this->box->setObjectName("boxAreaWidget");
    this->boxArea=new QVBoxLayout(box);
    this->boxArea->setObjectName("boxAreaLayout");
    box->setLayout(boxArea);
}

DocTab::~DocTab(){
    delete this->VLayout;
    delete this->boxArea;
    delete this->SA;
    delete this;
}

