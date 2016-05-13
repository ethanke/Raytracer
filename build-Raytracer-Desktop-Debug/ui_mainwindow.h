/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <glwindow.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox_3;
    QPushButton *loadButton;
    GlWindow *myGlWindow;
    QPushButton *pushButton;
    QPushButton *renderButton;
    QPushButton *pushButton_2;
    QTabWidget *tabWidget;
    QWidget *camera;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_cpx;
    QLabel *label_3;
    QLineEdit *lineEdit_cpy;
    QLabel *label_4;
    QLineEdit *lineEdit_cpz;
    QLabel *label_5;
    QLineEdit *lineEdit_laz;
    QLabel *label_6;
    QLineEdit *lineEdit_lax;
    QLabel *label_7;
    QLineEdit *lineEdit_lay;
    GlWindow *myGlWindow_2;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QComboBox *comboBox_wx;
    QComboBox *comboBox_wy;
    QSlider *horizontalSlider_fov;
    QLabel *LabelAA;
    QLabel *labelFOV;
    QSlider *horizontalSlider_aa;
    QWidget *tab_2;
    QTableWidget *listObject;
    QPushButton *editButtonObj;
    QWidget *tab;
    QTableWidget *listLight;
    QWidget *tab_3;
    QTableWidget *listMat;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(1920, 1080);
        MainWindow->setMinimumSize(QSize(1920, 1080));
        MainWindow->setMaximumSize(QSize(1920, 1080));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 10, 1101, 61));
        loadButton = new QPushButton(groupBox_3);
        loadButton->setObjectName(QStringLiteral("loadButton"));
        loadButton->setGeometry(QRect(0, 0, 161, 61));
        QIcon icon;
        icon.addFile(QStringLiteral("../../../../Downloads/open-folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        loadButton->setIcon(icon);
        loadButton->setIconSize(QSize(32, 32));
        loadButton->setAutoDefault(true);
        loadButton->setFlat(false);
        myGlWindow = new GlWindow(centralWidget);
        myGlWindow->setObjectName(QStringLiteral("myGlWindow"));
        myGlWindow->setGeometry(QRect(420, 130, 1080, 720));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setEnabled(true);
        pushButton->setGeometry(QRect(10, 970, 113, 32));
        pushButton->setMaximumSize(QSize(1080, 720));
        pushButton->setAutoDefault(false);
        pushButton->setFlat(false);
        renderButton = new QPushButton(centralWidget);
        renderButton->setObjectName(QStringLiteral("renderButton"));
        renderButton->setGeometry(QRect(420, 70, 120, 40));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 90, 113, 32));
        pushButton_2->setMaximumSize(QSize(1080, 720));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 120, 311, 841));
        tabWidget->setStyleSheet(QLatin1String(" QTabBar::tab {\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                 stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\n"
"                                 stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);\n"
"     border: 2px solid #C4C4C3;\n"
"     border-bottom-color: #C2C7CB; /* same as the pane color */\n"
"     border-top-left-radius: 4px;\n"
"     border-top-right-radius: 4px;\n"
"     min-width: 8ex;\n"
"     padding: 2px;\n"
" }\n"
" \n"
" QTabBar::tab:selected, QTabBar::tab:hover {\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                 stop: 0 #fafafa, stop: 0.4 #f4f4f4,\n"
"                                 stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);\n"
" }\n"
" \n"
" QTabBar::tab:selected {\n"
"     border-color: #9B9B9B;\n"
"     border-bottom-color: #C2C7CB; /* same as pane color */\n"
" }\n"
" \n"
" QTabBar::tab:!selected {\n"
"     margin-top: 2px; /* make non-selected tabs look smaller */\n"
" }\n"
""));
        tabWidget->setTabBarAutoHide(true);
        camera = new QWidget();
        camera->setObjectName(QStringLiteral("camera"));
        label = new QLabel(camera);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 121, 21));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(10);
        sizePolicy.setVerticalStretch(10);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label_2 = new QLabel(camera);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 121, 21));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        lineEdit_cpx = new QLineEdit(camera);
        lineEdit_cpx->setObjectName(QStringLiteral("lineEdit_cpx"));
        lineEdit_cpx->setGeometry(QRect(150, 100, 113, 21));
        label_3 = new QLabel(camera);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 100, 121, 21));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        lineEdit_cpy = new QLineEdit(camera);
        lineEdit_cpy->setObjectName(QStringLiteral("lineEdit_cpy"));
        lineEdit_cpy->setGeometry(QRect(150, 140, 113, 21));
        label_4 = new QLabel(camera);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 140, 121, 21));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        lineEdit_cpz = new QLineEdit(camera);
        lineEdit_cpz->setObjectName(QStringLiteral("lineEdit_cpz"));
        lineEdit_cpz->setGeometry(QRect(150, 180, 113, 21));
        label_5 = new QLabel(camera);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 180, 121, 21));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        lineEdit_laz = new QLineEdit(camera);
        lineEdit_laz->setObjectName(QStringLiteral("lineEdit_laz"));
        lineEdit_laz->setGeometry(QRect(150, 300, 113, 21));
        label_6 = new QLabel(camera);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 260, 121, 21));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        lineEdit_lax = new QLineEdit(camera);
        lineEdit_lax->setObjectName(QStringLiteral("lineEdit_lax"));
        lineEdit_lax->setGeometry(QRect(150, 220, 113, 21));
        label_7 = new QLabel(camera);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 300, 121, 21));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        lineEdit_lay = new QLineEdit(camera);
        lineEdit_lay->setObjectName(QStringLiteral("lineEdit_lay"));
        lineEdit_lay->setGeometry(QRect(150, 260, 113, 21));
        myGlWindow_2 = new GlWindow(camera);
        myGlWindow_2->setObjectName(QStringLiteral("myGlWindow_2"));
        myGlWindow_2->setGeometry(QRect(410, 240, 1080, 720));
        label_8 = new QLabel(camera);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 220, 121, 21));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_9 = new QLabel(camera);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 350, 121, 21));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_10 = new QLabel(camera);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(170, 350, 121, 21));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);
        comboBox_wx = new QComboBox(camera);
        comboBox_wx->setObjectName(QStringLiteral("comboBox_wx"));
        comboBox_wx->setGeometry(QRect(150, 20, 111, 26));
        comboBox_wy = new QComboBox(camera);
        comboBox_wy->setObjectName(QStringLiteral("comboBox_wy"));
        comboBox_wy->setGeometry(QRect(150, 60, 111, 26));
        horizontalSlider_fov = new QSlider(camera);
        horizontalSlider_fov->setObjectName(QStringLiteral("horizontalSlider_fov"));
        horizontalSlider_fov->setGeometry(QRect(160, 380, 141, 22));
        horizontalSlider_fov->setMinimum(50);
        horizontalSlider_fov->setMaximum(360);
        horizontalSlider_fov->setValue(70);
        horizontalSlider_fov->setOrientation(Qt::Horizontal);
        LabelAA = new QLabel(camera);
        LabelAA->setObjectName(QStringLiteral("LabelAA"));
        LabelAA->setGeometry(QRect(30, 370, 59, 16));
        labelFOV = new QLabel(camera);
        labelFOV->setObjectName(QStringLiteral("labelFOV"));
        labelFOV->setGeometry(QRect(200, 370, 59, 16));
        horizontalSlider_aa = new QSlider(camera);
        horizontalSlider_aa->setObjectName(QStringLiteral("horizontalSlider_aa"));
        horizontalSlider_aa->setGeometry(QRect(0, 380, 141, 22));
        horizontalSlider_aa->setMinimum(1);
        horizontalSlider_aa->setMaximum(16);
        horizontalSlider_aa->setValue(2);
        horizontalSlider_aa->setOrientation(Qt::Horizontal);
        tabWidget->addTab(camera, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        listObject = new QTableWidget(tab_2);
        if (listObject->columnCount() < 1)
            listObject->setColumnCount(1);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem->setFont(font);
        __qtablewidgetitem->setForeground(brush);
        listObject->setHorizontalHeaderItem(0, __qtablewidgetitem);
        listObject->setObjectName(QStringLiteral("listObject"));
        listObject->setGeometry(QRect(30, 10, 256, 192));
        listObject->setStyleSheet(QLatin1String("QTableView {\n"
"   	text-align: center;\n"
"\n"
"}"));
        listObject->setLineWidth(1);
        editButtonObj = new QPushButton(tab_2);
        editButtonObj->setObjectName(QStringLiteral("editButtonObj"));
        editButtonObj->setGeometry(QRect(30, 210, 41, 41));
        QIcon icon1;
        icon1.addFile(QStringLiteral("../../../../Downloads/pencil-edit-button.png"), QSize(), QIcon::Normal, QIcon::Off);
        editButtonObj->setIcon(icon1);
        editButtonObj->setIconSize(QSize(32, 32));
        editButtonObj->setAutoDefault(true);
        editButtonObj->setFlat(false);
        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        listLight = new QTableWidget(tab);
        if (listLight->columnCount() < 1)
            listLight->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem1->setFont(font);
        __qtablewidgetitem1->setForeground(brush);
        listLight->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        listLight->setObjectName(QStringLiteral("listLight"));
        listLight->setGeometry(QRect(30, 10, 256, 192));
        listLight->setStyleSheet(QLatin1String("QTableView {\n"
"   	text-align: center;\n"
"\n"
"}"));
        listLight->setLineWidth(1);
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        listMat = new QTableWidget(tab_3);
        if (listMat->columnCount() < 1)
            listMat->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem2->setFont(font);
        __qtablewidgetitem2->setForeground(brush);
        listMat->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        listMat->setObjectName(QStringLiteral("listMat"));
        listMat->setGeometry(QRect(30, 10, 256, 192));
        listMat->setStyleSheet(QLatin1String("QTableView {\n"
"   	text-align: center;\n"
"\n"
"}"));
        listMat->setLineWidth(1);
        tabWidget->addTab(tab_3, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1920, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(CloseWindow()));
        QObject::connect(renderButton, SIGNAL(clicked()), myGlWindow, SLOT(raytrace_button()));

        loadButton->setDefault(false);
        pushButton->setDefault(false);
        tabWidget->setCurrentIndex(0);
        editButtonObj->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Raytracer", 0));
        groupBox_3->setTitle(QString());
        loadButton->setText(QApplication::translate("MainWindow", "Load scene", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Quit", 0));
        renderButton->setText(QApplication::translate("MainWindow", "Raytrace it!", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Add Object", 0));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Windows Size (x) :</span></p></body></html>", 0));
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Windows Size (y) :</span></p></body></html>", 0));
        lineEdit_cpx->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Camera pos (x) :</span></p><p><span style=\" font-size:14pt;\"><br/></span></p><p><span style=\" font-size:14pt;\"><br/></span></p></body></html>", 0));
        lineEdit_cpy->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Camera pos (y) :</span></p><p><span style=\" font-size:14pt;\"><br/></span></p><p><span style=\" font-size:14pt;\"><br/></span></p></body></html>", 0));
        lineEdit_cpz->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Camera pos (z) :</span></p><p><span style=\" font-size:14pt;\"><br/></span></p><p><span style=\" font-size:14pt;\"><br/></span></p></body></html>", 0));
        lineEdit_laz->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Look at (y) :</span></p><p><span style=\" font-size:14pt;\"><br/></span></p></body></html>", 0));
        lineEdit_lax->setText(QString());
        label_7->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Look at (z) :</span></p></body></html>", 0));
        lineEdit_lay->setText(QString());
        label_8->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Look at (x) : </span></p></body></html>", 0));
        label_9->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Anti-Aliasing :</span></p><p><br/></p></body></html>", 0));
        label_10->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">FOV :</p><p align=\"center\"><br/></p></body></html>", 0));
        LabelAA->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">2</p></body></html>", 0));
        labelFOV->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">70</p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(camera), QApplication::translate("MainWindow", "Camera", 0));
        QTableWidgetItem *___qtablewidgetitem = listObject->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "type", 0));
        editButtonObj->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Objets", 0));
        QTableWidgetItem *___qtablewidgetitem1 = listLight->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "intensiter", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Lumi\303\250res", 0));
        QTableWidgetItem *___qtablewidgetitem2 = listMat->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "intensiter", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Mat\303\251riaux", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
