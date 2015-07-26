QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleScientificCalculator
TEMPLATE = app

SOURCES += main.cpp\
        calculator.cpp \
    lepton/CompiledExpression.cpp \
    lepton/ExpressionProgram.cpp \
    lepton/ExpressionTreeNode.cpp \
    lepton/Operation.cpp \
    lepton/ParsedExpression.cpp \
    lepton/Parser.cpp

HEADERS  += calculator.h \
    lepton/CompiledExpression.h \
    lepton/CustomFunction.h \
    lepton/Exception.h \
    lepton/ExpressionProgram.h \
    lepton/ExpressionTreeNode.h \
    lepton/Lepton.h \
    lepton/Operation.h \
    lepton/ParsedExpression.h \
    lepton/Parser.h \
    lepton/windowsIncludes.h

FORMS    += calculator.ui
