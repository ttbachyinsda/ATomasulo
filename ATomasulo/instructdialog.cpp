#include "instructdialog.h"
#include "ui_instructdialog.h"

InstructDialog::InstructDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InstructDialog)
{
    ui->setupUi(this);
    connect(ui->addinstruction,SIGNAL(clicked()),this,SLOT(additem()));
    connect(ui->deleteinstruction,SIGNAL(clicked()),this,SLOT(deleteitem()));
    connect(ui->cancelbutton,SIGNAL(clicked(bool)),this,SLOT(cancel()));
    connect(this,SIGNAL(accepted()),this,SLOT(updateitem()));
}
void InstructDialog::update()
{
    for (int i=0;i<nowstatus->InstructList.size();i++)
    {
        if (nowstatus->InstructList[i].F3 == "")
            ui->listWidget->addItem(nowstatus->InstructList[i].Op+" "+nowstatus->InstructList[i].F1+" "+nowstatus->InstructList[i].F2);
        else
            ui->listWidget->addItem(nowstatus->InstructList[i].Op+" "+nowstatus->InstructList[i].F1+" "+nowstatus->InstructList[i].F2+" "+nowstatus->InstructList[i].F3);
    }
}

InstructDialog::~InstructDialog()
{
    delete ui;
}

void InstructDialog::cancel()
{
    int result = QMessageBox::question(this, "提示", "是否退出编辑？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (result == QMessageBox::Yes){
        this->close();
    }
}

void InstructDialog::deleteitem()
{
    int rownum = ui->listWidget->currentRow();
    if (rownum != -1){
        ui->listWidget->takeItem(rownum);
    }
}

void InstructDialog::additem()
{
    QString instruction = ui->lineEdit->text();
    auto res = validate(instruction);
    if (res.second){
        ui->listWidget->addItem(res.first);
    } else {
        QMessageBox::critical(this,"警告","输入指令格式有误");
    }
}

pair<QString, bool> InstructDialog::validate(QString instruction)
{
    instruction = instruction.toUpper();
    instruction = instruction.simplified();
    instruction = instruction.replace(", ",",");
    instruction = instruction.replace(" ,",",");
    instruction = instruction.replace(" ",",");
    //qDebug()<<instruction;
    QString str1 = instruction.section(',',0,0);
    QString str2 = instruction.section(',',1,1);
    QString str3 = instruction.section(',',2,2);
    QString str4 = instruction.section(',',3,3);
    QString str5 = instruction.section(',',4,4);
    //qDebug()<<str1;
    //qDebug()<<str2;
    //qDebug()<<str3;
    //qDebug()<<str4;
    //qDebug()<<str5;
    if (str1 == "LD" || str1 == "ST"){
        if (str4 != "" || str5 != "")
            return make_pair(instruction,false);
        if (str2[0] == 'F' || str2[0] == 'R'){
            bool can=true;
            QString ts = str2.mid(1,str2.length());
            bool ok1,ok2;
            int num1 = ts.toInt(&ok1);
            if (!ok1) can=false;
            int num2 = str3.toInt(&ok2);
            if (!ok2) can=false;

            //cout<<num1<<' '<<num2<<endl;

            if (num1 < 0 || num1 >= registerlen) can=false;
            if (num2 < 0 || num2 >= memorylen) can=false;

            if (!can) return make_pair(instruction,false);
        } else return make_pair(instruction,false);
    } else if (str1 == "ADDD" || str1 == "SUBD" || str1 == "MULD" || str1 == "DIVD") {
        if (str5 != "") return make_pair(instruction,false);
        bool can=true;
        if (str2[0] != 'F' && str2[0] != 'R') can=false;
        if (str3[0] != 'F' && str3[0] != 'R') can=false;
        if (str4[0] != 'F' && str4[0] != 'R') can=false;
        if (!can) return make_pair(instruction,false);
        QString ts1 = str2.mid(1,str2.length());
        QString ts2 = str3.mid(1,str3.length());
        QString ts3 = str4.mid(1,str4.length());
        bool ok1,ok2,ok3;
        int num1 = ts1.toInt(&ok1);
        int num2 = ts2.toInt(&ok2);
        int num3 = ts3.toInt(&ok3);
        cout<<num1<<' '<<num2<<' '<<num3<<endl;
        if (!ok1 || !ok2 || !ok3) can=false;
        if (num1 < 0 || num1 >= registerlen) can=false;
        if (num2 < 0 || num2 >= registerlen) can=false;
        if (num3 < 0 || num3 >= registerlen) can=false;
        if (!can) return make_pair(instruction,false);
    } else return make_pair(instruction,false);
    instruction = instruction.replace(',',' ');
    return make_pair(instruction,true);
}
void InstructDialog::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter)
    {
        //cout<<"add item"<<endl;
        additem();
    }
}
void InstructDialog::updateitem()
{
    nowstatus->InstructList.clear();
    for (int i=0;i<ui->listWidget->count();i++){
        qDebug()<<ui->listWidget->item(i)->text();
        QString realinstruct = ui->listWidget->item(i)->text();
        Instruction instruction;
        instruction.Op = realinstruct.section(' ',0,0);
        instruction.F1 = realinstruct.section(' ',1,1);
        instruction.F2 = realinstruct.section(' ',2,2);
        instruction.F3 = realinstruct.section(' ',3,3);
        nowstatus->InstructList.append(instruction);
    }
    emit updatemain();
}
