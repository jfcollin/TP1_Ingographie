/********************************************************************************
** Form generated from reading UI file 'Window.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Animation1.h"
#include "Animation2.h"

QT_BEGIN_NAMESPACE

class Ui_WindowClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tabWidgetPage1;
    QVBoxLayout *verticalLayout;
    Animation1 *openGLWidget;
    QWidget *tabWidgetPage2;
    QVBoxLayout *verticalLayout_2;
    Animation2 *openGLWidget_2;

    void setupUi(QMainWindow *WindowClass)
    {
        if (WindowClass->objectName().isEmpty())
            WindowClass->setObjectName(QStringLiteral("WindowClass"));
        WindowClass->resize(800, 600);
        centralWidget = new QWidget(WindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setAutoFillBackground(true);
        tabWidget->setTabPosition(QTabWidget::East);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidgetPage1 = new QWidget();
        tabWidgetPage1->setObjectName(QStringLiteral("tabWidgetPage1"));
        verticalLayout = new QVBoxLayout(tabWidgetPage1);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        openGLWidget = new Animation1(tabWidgetPage1);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

        verticalLayout->addWidget(openGLWidget);

        tabWidget->addTab(tabWidgetPage1, QString());
        tabWidgetPage2 = new QWidget();
        tabWidgetPage2->setObjectName(QStringLiteral("tabWidgetPage2"));
        verticalLayout_2 = new QVBoxLayout(tabWidgetPage2);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        openGLWidget_2 = new Animation2(tabWidgetPage2);
        openGLWidget_2->setObjectName(QStringLiteral("openGLWidget_2"));

        verticalLayout_2->addWidget(openGLWidget_2);

        tabWidget->addTab(tabWidgetPage2, QString());

        verticalLayout_3->addWidget(tabWidget);

        WindowClass->setCentralWidget(centralWidget);

        retranslateUi(WindowClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *WindowClass)
    {
        WindowClass->setWindowTitle(QApplication::translate("WindowClass", "D\303\251mo OpenGL", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage1), QApplication::translate("WindowClass", "Sc\303\250ne 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage2), QApplication::translate("WindowClass", "Sc\303\250ne2", 0));
    } // retranslateUi

};

namespace Ui {
    class WindowClass: public Ui_WindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
