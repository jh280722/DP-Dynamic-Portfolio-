#include "mainwindow.h"
#include "document.h"
#include "sortation.h"
#include "ui_mainwindow.h"
#include "data.h"
#include "doubleclickedwidget.h"
#include <QFile>
#include <QTableWidget>
#include <QHeaderView>
#include <QFrame>
#include <QAbstractTableModel>
#include <QAbstractItemModel>

class myTable : public QTableWidget{
public:
    QLineEdit* Line;
    int sectionedit;
    QRect edit_geometry;
    myTable(QWidget *parent = nullptr) : QTableWidget(parent){
        //click, move����
        horizontalHeader()->setSectionsMovable(1);
        horizontalHeader()->setSectionsClickable(1);

        // ����� viewport�� �θ�� ���ο����� ����
        Line = new QLineEdit(horizontalHeader()->viewport());  //#Create
        Line->setAlignment(Qt::AlignTop); //# Set the Alignmnet
        Line->setHidden(1);// # Hide it till its needed
        Line->blockSignals(1);
        sectionedit = 0;

        //����Ŭ���� �� ������ �Լ� ����, �� ���� ���� �ؽ�Ʈ ���� �Լ� ����
        connect(horizontalHeader(), &QHeaderView::sectionDoubleClicked,this,&myTable::editHeader);
        connect(Line, &QLineEdit::editingFinished,this,&myTable::doneEditing);
    }

    void doneEditing(){
        //���� ���������� �ٽ� �ñ׳��� ���� �������ش�.
        Line->blockSignals(true);
        Line->setHidden(true);
        QString newname = Line->text();
        QString oldname = horizontalHeaderItem(sectionedit)->text();

        Line->setText("");

        horizontalHeaderItem(sectionedit)->setText(newname); //�� �̸����� ����

        resizeColumnsToContents(); //���� ���̿� ���� �� ����
        setCurrentIndex(QModelIndex()); //���� �ε����� ����
    }

    void editHeader(int section){
        edit_geometry = Line->geometry(); //���� �������� ��ǥ�� �޾ƿ´�.
        //���õ� ����� ���ǿ� �°� ��ġ�� �����Ѵ�.
        edit_geometry.setWidth(horizontalHeader()->sectionSize(section));
        edit_geometry.moveLeft(horizontalHeader()->sectionViewportPosition(section));
        Line->setGeometry(edit_geometry);

        QString oldname = horizontalHeaderItem(sectionedit)->text();
        Line->setText(oldname);

        //���� �������� hidden,blocksignal�� Ǯ�� ��Ŀ�����ش��� ��ü�� �������ش�.
        Line->setHidden(false);
        Line->blockSignals(false);
        Line->setFocus();
        Line->selectAll();

        sectionedit = section; //���� ���õ� ������ �ε����� �����Ѵ�.
    }
};


void Document::add_table_box() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    boxLayout->setObjectName("tableBox");
    QLayout* layout = tab->boxArea;

    add_table_tool_option(box, boxLayout);

    QStringList tableHeader;
    tableHeader << "1" << "2";
    myTable* table=new myTable(box);
    table->setColumnCount(2); // Column�� 2���� ����
    table->setRowCount(2);
    table->setHorizontalHeaderLabels(tableHeader); // Table Header ����

    table->setObjectName("table");
    boxLayout->addWidget(table);

    table->resizeColumnsToContents();
    table->resizeRowsToContents();

    int h = table->horizontalHeader()->height() + 68;
    if(DPI==1.25){
        h+=13;
    }
    else if(DPI==1.5){
        h+=27;
    }
    //��� ���� + �� ��ư 30 + ���� 9��(�� 18, table 18) 36 + box margin 2 = 68
    for(int i=0;i<table->rowCount();i++){
        h += table->rowHeight(i);
    }
    box->setAlignment(Qt::AlignTop);
    box->setMinimumSize(800,h);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    boxLayout->setSizeConstraint(QLayout::SetMinimumSize);
    boxLayout->setAlignment(Qt::AlignTop);
    layout->addWidget(box);

    box->setFixedSize(box->width(),h);
}

void Document::add_row(){
    QGroupBox* box = qobject_cast<QGroupBox*>(QObject::sender()->parent());
    QTableWidget* table = box->findChild<QTableWidget*>("table");

    table->setRowCount(table->rowCount()+1);
    table->resizeRowsToContents();

    int h = table->horizontalHeader()->height() + 68;
    if(DPI==1.25){
        h+=13;
    }
    else if(DPI==1.5){
        h+=27;
    }
    //��� ���� + �� ��ư 30 + ���� 9��(�� 18, table 18) 36 + box margin 2 = 68
    for(int i=0;i<table->rowCount();i++){
        h += table->rowHeight(i);
    }

    box->setFixedSize(box->width(),h);
}

void Document::add_col(){
    QGroupBox* box = qobject_cast<QGroupBox*>(QObject::sender()->parent());
    QTableWidget* table = box->findChild<QTableWidget*>("table");

    QStringList label;
    for(int i=0;i<table->columnCount();i++){
        label<<table->horizontalHeaderItem(i)->text();
    }
    label << QString::number(table->columnCount()+1);
    //QString�� �Ѵٰ� �Ǵ°� �ƴ϶� ���� ī��Ʈ�� �÷��־���Ѵ�.
    table->setColumnCount(table->columnCount()+1);
    //headerview�� ������ �ȵǹǷ�(? �� ã�����Ƿ�) QString���� set���־ ������ �Ѵ�.
    table->setHorizontalHeaderLabels(label);

    table->resizeColumnsToContents();
    table->resizeRowsToContents();

    int h = table->horizontalHeader()->height()+68;
    if(DPI==1.25){
        h+=13;
    }
    else if(DPI==1.5){
        h+=27;
    }
    //��� ���� + �� ��ư 30 + ���� 9��(�� 18, table 18) 36 + box margin 2 = 68
    for(int i=0;i<table->rowCount();i++){
        h += table->rowHeight(i);
    }

    box->setFixedSize(box->width(),h);
}

void Document::add_table_tool_option(QGroupBox* box, QLayout * boxLayout){
    QWidget* toolWidget = new QWidget(box);
    QToolButton* tool = new QToolButton(toolWidget);
    QHBoxLayout* toolLayout = new QHBoxLayout(toolWidget);
    QMenu* Menu = new QMenu();
    QMenu* InputMenu = new QMenu();
    toolLayout->addStretch();
    toolLayout->addWidget(tool, Qt::AlignRight);


    QAction* TBAAddRow = new QAction(Kor("�� �߰�"), box);
    connect(TBAAddRow, SIGNAL(triggered()), this, SLOT(add_row()));
    TBAAddRow->setStatusTip(Kor("���� �߰��մϴ�."));

    QAction* TBAAddCol = new QAction(Kor("�� �߰�"), box);
    connect(TBAAddCol, SIGNAL(triggered()), this, SLOT(add_col()));
    TBAAddCol->setStatusTip(Kor("���� �߰��մϴ�."));

    QAction* TBADelete = new QAction(Kor("����"), tool);
    TBADelete->setStatusTip(Kor("�ڽ��� �����մϴ�."));
    connect(TBADelete, SIGNAL(triggered()), this, SLOT(deleteBox()));

    Menu->addAction(TBAAddRow);
    Menu->addAction(TBAAddCol);
    Menu->addAction(TBADelete);

    tool->setMenu(Menu);
    tool->setPopupMode(QToolButton::InstantPopup);
    toolWidget->setObjectName("tool");
    boxLayout->addWidget(toolWidget);
}
