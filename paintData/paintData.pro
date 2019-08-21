#-------------------------------------------------
#
# Project created by QtCreator 2019-08-16T20:28:48
#
#1. 鼠标在图表上移动时，在状态栏里显示鼠标当前位置的坐标数值
#2. 图例具有类似于QCheckBox的功能，单击图例的图标可以显示或隐藏对应的序列
#3. 通过工具栏按钮可以进行图标缩放操作
#4. 鼠标在图标上可以选择矩形区域进行放大，单击鼠标右键则恢复图标大小
#5. 使用按键可以实现图标的快捷操作，如‘+’键进行放大，“-”键进行缩小，Home键恢复原始大小，使用上，下，左，右光标键可以移动序列的显示位置
#
#
#-------------------------------------------------

QT       += core gui
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = paintData
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qwchartview.cpp

HEADERS += \
        mainwindow.h \
    qwchartview.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
