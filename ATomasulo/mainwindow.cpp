#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/icon.ico"));
    //toolbar

    instructaction = new QAction(QIcon(":/document.ico"),"修改指令",this);
    ui->mainToolBar->addAction(instructaction);
    connect(instructaction,SIGNAL(triggered(bool)),this,SLOT(domodifyinstruct()));
    connect(ui->actionmodifyinstruct,SIGNAL(triggered(bool)),this,SLOT(domodifyinstruct()));

    memoryaction = new QAction(QIcon(":/memory.ico"),"修改内存",this);
    ui->mainToolBar->addAction(memoryaction);
    connect(memoryaction,SIGNAL(triggered(bool)),this,SLOT(domodifymemory()));
    connect(ui->actionmodifymemory,SIGNAL(triggered(bool)),this,SLOT(domodifymemory()));

    lockandstartaction = new QAction(QIcon(":/lock.ico"),"锁定并开始模拟",this);
    ui->mainToolBar->addAction(lockandstartaction);
    connect(lockandstartaction,SIGNAL(triggered(bool)),this,SLOT(dolockandstart()));
    connect(ui->actionLockandStart,SIGNAL(triggered(bool)),this,SLOT(dolockandstart()));

    nextstepaction = new QAction(QIcon(":/nextstep.ico"),"执行下一步",this);
    ui->mainToolBar->addAction(nextstepaction);
    connect(nextstepaction,SIGNAL(triggered(bool)),this,SLOT(donextstep()));
    connect(ui->actionnextStep,SIGNAL(triggered(bool)),this,SLOT(donextstep()));

    continueaction = new QAction(QIcon(":/run.ico"),"自动执行",this);
    ui->mainToolBar->addAction(continueaction);
    connect(continueaction,SIGNAL(triggered(bool)),this,SLOT(docontinue()));
    connect(ui->actionautorun,SIGNAL(triggered(bool)),this,SLOT(docontinue()));

    pauseaction = new QAction(QIcon(":/pause.ico"),"暂停自动执行",this);
    ui->mainToolBar->addAction(pauseaction);
    connect(pauseaction,SIGNAL(triggered(bool)),this,SLOT(dopause()));
    connect(ui->actionpause,SIGNAL(triggered(bool)),this,SLOT(dopause()));

    restartaction = new QAction(QIcon(":/restart.ico"),"重新执行模拟",this);
    ui->mainToolBar->addAction(restartaction);
    connect(restartaction,SIGNAL(triggered(bool)),this,SLOT(dorestart()));
    connect(ui->actionrestart,SIGNAL(triggered(bool)),this,SLOT(dorestart()));

    haltaction = new QAction(QIcon(":/halt.ico"),"终止模拟并解除锁定",this);
    ui->mainToolBar->addAction(haltaction);
    connect(haltaction,SIGNAL(triggered(bool)),this,SLOT(dohalt()));
    connect(ui->actionHalt,SIGNAL(triggered(bool)),this,SLOT(dohalt()));

    //end toolbar


    //other actions
    connect(ui->actionabout,SIGNAL(triggered(bool)),this,SLOT(doabout()));
    connect(ui->actionhelp,SIGNAL(triggered(bool)),this,SLOT(dohelp()));
    connect(ui->showmemory,SIGNAL(clicked(bool)),this,SLOT(doshowmemory()));
    //end other actions

    nowstatus = new Status();

    //content
    ui->horizontalLayoutWidget->resize(this->width(),this->height()-ui->mainToolBar->height()-ui->statusBar->height()-ui->menuBar->height());
    ui->instructionqueue->setColumnCount(8);
    ui->instructionqueue->setRowCount(max(10,nowstatus->InstructList.length()));
    QStringList insheader;
    insheader<<"指令名称"<<"操作数1"<<"操作数2"<<"操作数3"<<"开始时间"<<"剩余时间"<<"完成时间"<<"写回时间";
    ui->instructionqueue->setHorizontalHeaderLabels(insheader);
    ui->reservestation->setColumnCount(9);
    ui->reservestation->setRowCount(addreservation+multireservation);
    QStringList resheader;
    resheader<<"剩余时间"<<"名称"<<"运行状态"<<"运算符"<<"VJ"<<"VK"<<"QJ"<<"QK"<<"A";
    ui->reservestation->setHorizontalHeaderLabels(resheader);
    ui->reservestation->setMinimumHeight((ui->reservestation->rowCount()+1)*ui->reservestation->rowHeight(0));
    ui->FU->setColumnCount(registerlen);
    ui->FU->setRowCount(1);
    QStringList fheader;
    for (int i=0;i<ui->FU->columnCount();i++){
        fheader<<"F"+QString::number(i);
    }
    ui->FU->setHorizontalHeaderLabels(fheader);
    ui->RU->setColumnCount(registerlen);
    ui->RU->setRowCount(1);
    QStringList rheader;
    for (int i=0;i<ui->RU->columnCount();i++){
        rheader<<"R"+QString::number(i);
    }
    ui->RU->setHorizontalHeaderLabels(rheader);
    ui->loadqueue->setColumnCount(3);
    ui->loadqueue->setRowCount(loadbufferlen);
    QStringList loadheader;
    loadheader<<"名称"<<"运行状态"<<"地址";
    ui->loadqueue->setHorizontalHeaderLabels(loadheader);
    ui->storequeue->setColumnCount(3);
    ui->storequeue->setRowCount(storebufferlen);
    ui->storequeue->setHorizontalHeaderLabels(loadheader);
    for (int i=0;i<ui->instructionqueue->columnCount();i++){
        ui->instructionqueue->setColumnWidth(i,60);
    }
    for (int i=0;i<ui->reservestation->columnCount();i++){
        ui->reservestation->setColumnWidth(i,60);
    }
    for (int i=0;i<ui->FU->columnCount();i++){
        ui->FU->setColumnWidth(i,60);
    }
    for (int i=0;i<ui->RU->columnCount();i++){
        ui->RU->setColumnWidth(i,60);
    }
    for (int i=0;i<ui->loadqueue->columnCount();i++){
        ui->loadqueue->setColumnWidth(i,60);
    }
    for (int i=0;i<ui->storequeue->columnCount();i++){
        ui->storequeue->setColumnWidth(i,60);
    }
    //end content

    //consider LOCK
    DO_UNLOCK();
    //end consider

    //initialize status bar
    msgLabel = new QLabel();
    msgLabel->setMinimumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignHCenter);
    ui->statusBar->addWidget(msgLabel);
    //end initialize

    //initialize runstatus
    step = 0;
    SET_RUNSTATUS(0);
    consideritem();
    //end initialize

    //initialize showmemory
    showmemory = NULL;
    connect(ui->showmemory,SIGNAL(pressed()),this,SLOT(doshowmemory()));
    //end initialize
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->horizontalLayoutWidget->resize(this->width(),this->height()-ui->mainToolBar->height()-ui->statusBar->height()-ui->menuBar->height());
}
void MainWindow::donextstep()
{
    cout<<"do next step"<<endl;
    SET_RUNSTATUS(1);
}
void MainWindow::dolockandstart()
{
    cout<<"do lock and start"<<endl;
    DO_LOCK();
    SET_RUNSTATUS(0);
}
void MainWindow::docontinue()
{
    cout<<"do continue"<<endl;
    SET_RUNSTATUS(3);
}
void MainWindow::dopause()
{
    cout<<"do pause"<<endl;
    SET_RUNSTATUS(1);
}
void MainWindow::dorestart()
{
    cout<<"do restart"<<endl;
    SET_RUNSTATUS(0);
}
void MainWindow::dohalt()
{
    cout<<"do halt"<<endl;
    DO_UNLOCK();
    SET_RUNSTATUS(0);
}
void MainWindow::doabout()
{
    cout<<"do about"<<endl;
    QMessageBox::information(this, tr("关于"), "Powered By ttbachyinsda, Fate Faker and Fearless.");
}
void MainWindow::dohelp()
{
    cout<<"do help"<<endl;
    QMessageBox::information(this, tr("帮助"), "再写帮助就没时间刷恍惚套了");
}

void MainWindow::domodifyinstruct()
{
    cout<<"do modify instruct"<<endl;
    idialog = new InstructDialog(this);
    idialog->nowstatus = nowstatus;
    idialog->update();
    disconnect(idialog,SIGNAL(updatemain()),this,SLOT(doupdate()));
    connect(idialog,SIGNAL(updatemain()),this,SLOT(doupdate()));
    idialog->setWindowModality(Qt::ApplicationModal);
    idialog->show();
}
void MainWindow::domodifymemory()
{
    cout<<"do modify memory"<<endl;
    mdialog = new ModifyMemory(this);
    mdialog->nowstatus = nowstatus;
    mdialog->update();
    disconnect(mdialog,SIGNAL(updatemain()),this,SLOT(doupdate()));
    connect(mdialog,SIGNAL(updatemain()),this,SLOT(doupdate()));
    mdialog->setWindowModality(Qt::ApplicationModal);
    mdialog->show();
}
void MainWindow::doshowmemory()
{
    cout<<"do show memory"<<endl;
    if (showmemory == NULL){
        showmemory = new ShowMemory(this);
        showmemory->nowstatus = nowstatus;
        showmemory->update();
        disconnect(this,SIGNAL(updatememoryshower()),showmemory,SLOT(update()));
        connect(this,SIGNAL(updatememoryshower()),showmemory,SLOT(update()));
        showmemory->show();
    } else {
        showmemory->update();
        disconnect(this,SIGNAL(updatememoryshower()),showmemory,SLOT(update()));
        connect(this,SIGNAL(updatememoryshower()),showmemory,SLOT(update()));
        showmemory->show();
    }
}
void MainWindow::considerlock()
{
    if (LOCK == false){
        ui->menu->setEnabled(true);
        ui->actionmodifyinstruct->setEnabled(true);
        instructaction->setEnabled(true);
        ui->actionmodifymemory->setEnabled(true);
        memoryaction->setEnabled(true);
        ui->actionLockandStart->setEnabled(true);
        lockandstartaction->setEnabled(true);
    } else {
        ui->menu->setEnabled(false);
        ui->actionmodifyinstruct->setEnabled(false);
        instructaction->setEnabled(false);
        ui->actionmodifymemory->setEnabled(false);
        memoryaction->setEnabled(false);
        ui->actionLockandStart->setEnabled(false);
        lockandstartaction->setEnabled(false);
    }
}
void MainWindow::considerrunstatus()
{
    if (LOCK == false){
        ui->actionnextStep->setEnabled(false);
        ui->actionautorun->setEnabled(false);
        ui->actionHalt->setEnabled(false);
        ui->actionpause->setEnabled(false);
        ui->actionrestart->setEnabled(false);
        nextstepaction->setEnabled(false);
        continueaction->setEnabled(false);
        haltaction->setEnabled(false);
        pauseaction->setEnabled(false);
        restartaction->setEnabled(false);
    } else{
        if (runstatus == 0){
            ui->actionnextStep->setEnabled(true);
            ui->actionautorun->setEnabled(true);
            ui->actionHalt->setEnabled(true);
            ui->actionpause->setEnabled(false);
            ui->actionrestart->setEnabled(false);
            nextstepaction->setEnabled(true);
            continueaction->setEnabled(true);
            haltaction->setEnabled(true);
            pauseaction->setEnabled(false);
            restartaction->setEnabled(false);
        } else if (runstatus == 1){
            ui->actionnextStep->setEnabled(true);
            ui->actionautorun->setEnabled(true);
            ui->actionHalt->setEnabled(true);
            ui->actionpause->setEnabled(false);
            ui->actionrestart->setEnabled(true);
            nextstepaction->setEnabled(true);
            continueaction->setEnabled(true);
            haltaction->setEnabled(true);
            pauseaction->setEnabled(false);
            restartaction->setEnabled(true);
        } else if (runstatus == 2){
            ui->actionnextStep->setEnabled(false);
            ui->actionautorun->setEnabled(false);
            ui->actionHalt->setEnabled(true);
            ui->actionpause->setEnabled(false);
            ui->actionrestart->setEnabled(true);
            nextstepaction->setEnabled(false);
            continueaction->setEnabled(false);
            haltaction->setEnabled(true);
            pauseaction->setEnabled(false);
            restartaction->setEnabled(true);
        } else if (runstatus == 3){
            ui->actionnextStep->setEnabled(false);
            ui->actionautorun->setEnabled(false);
            ui->actionHalt->setEnabled(true);
            ui->actionpause->setEnabled(true);
            ui->actionrestart->setEnabled(true);
            nextstepaction->setEnabled(false);
            continueaction->setEnabled(false);
            haltaction->setEnabled(true);
            pauseaction->setEnabled(true);
            restartaction->setEnabled(true);
        }
    }
    considerstatusbar();
}
void MainWindow::considerstatusbar()
{
    QString totaltext;
    if (LOCK == true){
        this->setWindowTitle("Tomasulo simulator (LOCKED)");
        totaltext += "模拟器已处于锁定状态，";
    } else {
        this->setWindowTitle("Tomasulo simulator");
        totaltext += "模拟器处于可编辑状态，";
    }
    if (runstatus == 0){
        totaltext += "当前尚未运行中。";
    } else if (runstatus == 1) {
        totaltext += "当前正在运行中，已运行"+QString::number(step)+"步。";
    } else if (runstatus == 3) {
        totaltext += "当前正在自动运行中，已运行"+QString::number(step)+"步。";
    } else {
        totaltext += "当前运行完毕，共运行"+QString::number(step)+"步。";
    }
    msgLabel->setText(totaltext);
}
void MainWindow::consideritem()
{
    emit updatememoryshower();
    ui->instructionqueue->setColumnCount(8);
    ui->instructionqueue->setRowCount(max(10,nowstatus->InstructList.length()));
    QStringList insheader;
    insheader<<"指令名称"<<"操作数1"<<"操作数2"<<"操作数3"<<"开始时间"<<"剩余时间"<<"完成时间"<<"写回时间";
    ui->instructionqueue->setHorizontalHeaderLabels(insheader);
    for (int i=0;i<ui->instructionqueue->rowCount();i++){
        ui->instructionqueue->setItem(i,0,new QTableWidgetItem(""));
        ui->instructionqueue->setItem(i,1,new QTableWidgetItem(""));
        ui->instructionqueue->setItem(i,2,new QTableWidgetItem(""));
        ui->instructionqueue->setItem(i,3,new QTableWidgetItem(""));
    }
    for (int i=0;i<nowstatus->InstructList.size();i++){
        ui->instructionqueue->setItem(i,0,new QTableWidgetItem(nowstatus->InstructList[i].Op));
        ui->instructionqueue->setItem(i,1,new QTableWidgetItem(nowstatus->InstructList[i].F1));
        ui->instructionqueue->setItem(i,2,new QTableWidgetItem(nowstatus->InstructList[i].F2));
        ui->instructionqueue->setItem(i,3,new QTableWidgetItem(nowstatus->InstructList[i].F3));
        for (int k=0;k<=3;k++){
            ui->instructionqueue->item(i,k)->setTextAlignment(Qt::AlignCenter);
        }
    }
    for (int i=0;i<addreservation;i++){
        ui->reservestation->setItem(i,0,new QTableWidgetItem(QString::number(nowstatus->AddReservation[i].Time)));
        ui->reservestation->setItem(i,1,new QTableWidgetItem(nowstatus->AddReservation[i].Name));
        if (nowstatus->AddReservation[i].IsBusy){
            ui->reservestation->setItem(i,2,new QTableWidgetItem("Busy"));
            ui->reservestation->item(i,2)->setTextColor(Qt::red);
        } else {
            ui->reservestation->setItem(i,2,new QTableWidgetItem("Free"));
            ui->reservestation->item(i,2)->setTextColor(Qt::green);
        }
        ui->reservestation->setItem(i,3,new QTableWidgetItem(nowstatus->AddReservation[i].Op));
        ui->reservestation->setItem(i,4,new QTableWidgetItem(QString("%1").arg(nowstatus->AddReservation[i].VJ)));
        ui->reservestation->setItem(i,5,new QTableWidgetItem(QString("%1").arg(nowstatus->AddReservation[i].VK)));
        if (nowstatus->AddReservation[i].QJ){
            ui->reservestation->setItem(i,6,new QTableWidgetItem(nowstatus->AddReservation[i].QJ->Name));
        } else {
            ui->reservestation->setItem(i,6,new QTableWidgetItem(""));
        }
        if (nowstatus->AddReservation[i].QK){
            ui->reservestation->setItem(i,7,new QTableWidgetItem(nowstatus->AddReservation[i].QK->Name));
        } else {
            ui->reservestation->setItem(i,7,new QTableWidgetItem(""));
        }
        ui->reservestation->setItem(i,8,new QTableWidgetItem(QString::number(nowstatus->AddReservation[i].A)));
        for (int k=0;k<=8;k++){
            ui->reservestation->item(i,k)->setTextAlignment(Qt::AlignCenter);
        }
    }
    for (int i=0;i<multireservation;i++){
        int j = i + addreservation;
        ui->reservestation->setItem(j,0,new QTableWidgetItem(QString::number(nowstatus->MultiplyReservation[i].Time)));
        ui->reservestation->setItem(j,1,new QTableWidgetItem(nowstatus->MultiplyReservation[i].Name));
        if (nowstatus->MultiplyReservation[i].IsBusy){
            ui->reservestation->setItem(j,2,new QTableWidgetItem("Busy"));
            ui->reservestation->item(j,2)->setTextColor(Qt::red);
        } else {
            ui->reservestation->setItem(j,2,new QTableWidgetItem("Free"));
            ui->reservestation->item(j,2)->setTextColor(Qt::green);
        }
        ui->reservestation->setItem(j,3,new QTableWidgetItem(nowstatus->MultiplyReservation[i].Op));
        ui->reservestation->setItem(j,4,new QTableWidgetItem(QString("%1").arg(nowstatus->MultiplyReservation[i].VJ)));
        ui->reservestation->setItem(j,5,new QTableWidgetItem(QString("%1").arg(nowstatus->MultiplyReservation[i].VK)));
        if (nowstatus->MultiplyReservation[i].QJ){
            ui->reservestation->setItem(j,6,new QTableWidgetItem(nowstatus->MultiplyReservation[i].QJ->Name));
        } else {
            ui->reservestation->setItem(j,6,new QTableWidgetItem(""));
        }
        if (nowstatus->MultiplyReservation[i].QK){
            ui->reservestation->setItem(j,7,new QTableWidgetItem(nowstatus->MultiplyReservation[i].QK->Name));
        } else {
            ui->reservestation->setItem(j,7,new QTableWidgetItem(""));
        }
        ui->reservestation->setItem(j,8,new QTableWidgetItem(QString::number(nowstatus->MultiplyReservation[i].A)));
        for (int k=0;k<=8;k++){
            ui->reservestation->item(j,k)->setTextAlignment(Qt::AlignCenter);
        }
    }
    for (int i=0;i<registerlen;i++){
        ui->FU->setItem(0,i,new QTableWidgetItem(QString("%1").arg(nowstatus->FloatRegister[i].V)));
        ui->FU->item(0,i)->setTextAlignment(Qt::AlignCenter);
    }
    for (int i=0;i<registerlen;i++){
        ui->RU->setItem(0,i,new QTableWidgetItem(QString::number(nowstatus->IntRegister[i].V)));
        ui->RU->item(0,i)->setTextAlignment(Qt::AlignCenter);
    }
    for (int i=0;i<loadbufferlen;i++){
        ui->loadqueue->setItem(i,0,new QTableWidgetItem(nowstatus->LoadBuffer[i].Name));
        ui->loadqueue->item(i,0)->setTextAlignment(Qt::AlignCenter);
        if (nowstatus->LoadBuffer[i].IsBusy){
            ui->loadqueue->setItem(i,1,new QTableWidgetItem("Busy"));
            ui->loadqueue->item(i,1)->setTextColor(Qt::red);
            ui->loadqueue->item(i,1)->setTextAlignment(Qt::AlignCenter);
        } else {
            ui->loadqueue->setItem(i,1,new QTableWidgetItem("Free"));
            ui->loadqueue->item(i,1)->setTextColor(Qt::green);
            ui->loadqueue->item(i,1)->setTextAlignment(Qt::AlignCenter);
        }
        if (nowstatus->LoadBuffer[i].QJ){
            ui->loadqueue->setItem(i,2,new QTableWidgetItem(nowstatus->LoadBuffer[i].QJ->Name));
            ui->loadqueue->item(i,2)->setTextAlignment(Qt::AlignCenter);
        } else {
            ui->loadqueue->setItem(i,2,new QTableWidgetItem(""));
            ui->loadqueue->item(i,2)->setTextAlignment(Qt::AlignCenter);
        }
    }
    for (int i=0;i<storebufferlen;i++){
        ui->storequeue->setItem(i,0,new QTableWidgetItem(nowstatus->StoreBuffer[i].Name));
        ui->storequeue->item(i,0)->setTextAlignment(Qt::AlignCenter);
        if (nowstatus->StoreBuffer[i].IsBusy){
            ui->storequeue->setItem(i,1,new QTableWidgetItem("Busy"));
            ui->storequeue->item(i,1)->setTextColor(Qt::red);
            ui->storequeue->item(i,1)->setTextAlignment(Qt::AlignCenter);
        } else {
            ui->storequeue->setItem(i,1,new QTableWidgetItem("Free"));
            ui->storequeue->item(i,1)->setTextColor(Qt::green);
            ui->storequeue->item(i,1)->setTextAlignment(Qt::AlignCenter);
        }
        if (nowstatus->StoreBuffer[i].QJ){
            ui->storequeue->setItem(i,2,new QTableWidgetItem(nowstatus->StoreBuffer[i].QJ->Name));
            ui->storequeue->item(i,2)->setTextAlignment(Qt::AlignCenter);
        } else {
            ui->storequeue->setItem(i,2,new QTableWidgetItem(""));
            ui->storequeue->item(i,2)->setTextAlignment(Qt::AlignCenter);
        }
    }
}
void MainWindow::doupdate()
{
    cout<<"do update"<<endl;
    consideritem();
}
