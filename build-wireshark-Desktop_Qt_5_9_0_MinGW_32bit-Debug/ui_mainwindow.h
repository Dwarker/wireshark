/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionrunandstop;
    QAction *actionclear;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QTableWidget *tableWidget;
    QTreeWidget *treeWidget;
    QMenuBar *menuBar;
    QMenu *menuproject;
    QMenu *menurun;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 672);
        actionrunandstop = new QAction(MainWindow);
        actionrunandstop->setObjectName(QStringLiteral("actionrunandstop"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionrunandstop->setIcon(icon);
        actionclear = new QAction(MainWindow);
        actionclear->setObjectName(QStringLiteral("actionclear"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/empty.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionclear->setIcon(icon1);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setEnabled(true);
        comboBox->setMinimumSize(QSize(350, 0));

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout_2->addWidget(widget);

        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        splitter = new QSplitter(widget_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        tableWidget = new QTableWidget(splitter);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        splitter->addWidget(tableWidget);
        treeWidget = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        splitter->addWidget(treeWidget);

        verticalLayout->addWidget(splitter);


        verticalLayout_2->addWidget(widget_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 26));
        menuproject = new QMenu(menuBar);
        menuproject->setObjectName(QStringLiteral("menuproject"));
        menurun = new QMenu(menuBar);
        menurun->setObjectName(QStringLiteral("menurun"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuproject->menuAction());
        menuBar->addAction(menurun->menuAction());
        menurun->addAction(actionrunandstop);
        menurun->addAction(actionclear);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionrunandstop->setText(QApplication::translate("MainWindow", "runandstop", Q_NULLPTR));
        actionclear->setText(QApplication::translate("MainWindow", "clear", Q_NULLPTR));
        menuproject->setTitle(QApplication::translate("MainWindow", "project", Q_NULLPTR));
        menurun->setTitle(QApplication::translate("MainWindow", "run", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
