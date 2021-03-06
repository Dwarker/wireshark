#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include "multhread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showNetworkCard();
    statusBar()->showMessage("welcome to shark!");
    ui->toolBar->addAction(ui->actionrunandstop);
    ui->toolBar->addAction(ui->actionclear);
    countNumber = 0;

    //因为这里是gui线程,如果抓包逻辑也放在gui线程,会将界面卡死,所以将相关逻辑放在新线程中
    multhread* thread = new multhread;

    static bool index = false;
    //把信号和槽联系起来,选中runandup,然后执行capture()
    connect(ui->actionrunandstop, &QAction::triggered, this, [=](){
        index = !index;
        if(index)
        {
            //每次捕获前,先清空数据
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(0);
            countNumber = 0;

            int dataSize = this->pData.size();
            for(int i = 0; i < dataSize; i++)
            {
                free((char*)(this->pData[i].pkt_content));
                this->pData[i].pkt_content = nullptr;
            }

            QVector<datapackage>().swap(pData);
            //
            int res = capture();
            if(res != -1 && pointer)
            {
                thread->setPointer(pointer);
                thread->setFlag();
                thread->start();
                //切换为抓包状态后,将开始图片切换为停止图片(共用按钮)
                ui->actionrunandstop->setIcon(QIcon(":/stop.png"));
                //因为选中网卡在抓包了,所以该下拉框不能再进行选择
                ui->comboBox->setEnabled(false);
            }
            else
            {
                //打开设备失败
                index = !index;
                countNumber = 0;
            }
        }
        else
        {
            thread->resetFlag();
            thread->quit();
            thread->wait();
            ui->actionrunandstop->setIcon(QIcon(":/start.png"));
            ui->comboBox->setEnabled(true);
            pcap_close(pointer);
            pointer = nullptr;
        }
    });

    //第一个参数是信号的发送者, 第二个是发送的地址,第三个是信号的接收者,信号接收的地址
    connect(thread, &multhread::send, this, &MainWindow::HandleMessage);

    //设置工具栏相关属性
    ui->toolBar->setMovable(false);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(30);
    QStringList title = {"NO", "Time", "Source", "Destination",
                        "Protocol", "Length", "Info"};
    ui->tableWidget->setHorizontalHeaderLabels(title);

#if 0
    ui->tableWidget->setColumnWidth(0, 50);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 300);
    ui->tableWidget->setColumnWidth(3, 300);
    ui->tableWidget->setColumnWidth(4, 100);
    ui->tableWidget->setColumnWidth(5, 100);
    ui->tableWidget->setColumnWidth(6, 1000);
#endif

    //设置网格线
    ui->tableWidget->setShowGrid(false);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//显示所有网卡设备
void MainWindow::showNetworkCard()
{
    int n = pcap_findalldevs(&all_device, errbuf);

    if(n == -1)
    {
        ui->comboBox->addItem("error: " + QString(errbuf));
    }
    else
    {
        ui->comboBox->clear();
        ui->comboBox->addItem("please choose card!");
        for(device = all_device; device != nullptr; device = device->next)
        {
            QString device_name = device->name;
            device_name.replace("\\Device\\", "");//去掉多余的前缀
            QString des = device->description;
            QString item = device_name + des;
            ui->comboBox->addItem(item);
        }
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    //选中哪个网卡时,会将该index的值传过来,锁定该设备
    int i = 0;
    if(index != 0)//第0个是提示信息,所以从后面开始
    {
        for(device = all_device; i < index - 1; device = device->next, i++)
            ;
        return;
    }
}

int MainWindow::capture()
{
    if(device)
    {
        pointer = pcap_open_live(device->name, 65535, 1, 1000, errbuf);
    }
    else
    {
        return -1;
    }

    if(!pointer)
    {
        pcap_freealldevs(all_device);
        device = nullptr;
        return -1;
    }
    else
    {
        if(pcap_datalink(pointer) != DLT_EN10MB)
        {
            pcap_close(pointer);
            pcap_freealldevs(all_device);
            device = nullptr;
            pointer = nullptr;
            return -1;
        }
        statusBar()->showMessage(device->name);
    }
    return 0;
}
void MainWindow::HandleMessage(datapackage data)
{
#if 1
    //qDebug() << data.getTimeStamp() << " " << data.getInfo();
    //每个数据包都会触发一次槽函数,所以槽函数只需要处理一个数据包的内容
    ui->tableWidget->insertRow(countNumber);
    this->pData.push_back(data);
    QString type = data.getPackageType();
    QColor color;
    if(type == "TCP")
        color = QColor(216, 191, 216);
    else if(type == "UDP")
        color = QColor(144, 238, 144);
    else if(type == "ARP")
        color = QColor(238, 238, 0);
    else if(type == "DNS")
        color = QColor(255, 255, 224);
    else
        color = QColor(255, 218, 185);

    ui->tableWidget->setItem(countNumber, 0, new QTableWidgetItem(QString::number(countNumber)));
    ui->tableWidget->setItem(countNumber, 1, new QTableWidgetItem(data.getTimeStamp()));
    ui->tableWidget->setItem(countNumber, 2, new QTableWidgetItem(data.getSource()));
    ui->tableWidget->setItem(countNumber, 3, new QTableWidgetItem(data.getDestination()));
    ui->tableWidget->setItem(countNumber, 4, new QTableWidgetItem(type));
    ui->tableWidget->setItem(countNumber, 5, new QTableWidgetItem(data.getDataLength()));
    ui->tableWidget->setItem(countNumber, 6, new QTableWidgetItem(data.getInfo()));

    for(int i = 0; i < 7; i++)
    {
        ui->tableWidget->item(countNumber, i)->setBackgroundColor(color);
    }
    countNumber++;
#endif
}
