#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Calculator)
{
    clear = false;

    ui->setupUi(this);

    connect(ui->num_0, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num_1, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num_2, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num_3, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num_4, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num_5, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num_6, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num_7, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num_8, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));
    connect(ui->num_9, SIGNAL(clicked()), this, SLOT(numberButtonClicked()));

    connect(ui->expr_add, SIGNAL(clicked()), this, SLOT(operationButtonClicked()));
    connect(ui->expr_sub, SIGNAL(clicked()), this, SLOT(operationButtonClicked()));
    connect(ui->expr_mul, SIGNAL(clicked()), this, SLOT(operationButtonClicked()));
    connect(ui->expr_div, SIGNAL(clicked()), this, SLOT(operationButtonClicked()));

    connect(ui->paren_begin, SIGNAL(clicked()), this, SLOT(parenthesisButtonClicked()));
    connect(ui->paren_end, SIGNAL(clicked()), this, SLOT(parenthesisButtonClicked()));

    connect(ui->func_sin, SIGNAL(clicked()), this, SLOT(functionButtonClicked()));
    connect(ui->func_cos, SIGNAL(clicked()), this, SLOT(functionButtonClicked()));
    connect(ui->func_tan, SIGNAL(clicked()), this, SLOT(functionButtonClicked()));
    connect(ui->func_sinh, SIGNAL(clicked()), this, SLOT(functionButtonClicked()));
    connect(ui->func_cosh, SIGNAL(clicked()), this, SLOT(functionButtonClicked()));
    connect(ui->func_tanh, SIGNAL(clicked()), this, SLOT(functionButtonClicked()));

    connect(ui->pow_2, SIGNAL(clicked()), this, SLOT(powerButtonClicked()));
    connect(ui->pow_3, SIGNAL(clicked()), this, SLOT(powerButtonClicked()));
    connect(ui->pow_n, SIGNAL(clicked()), this, SLOT(powerButtonClicked()));
    connect(ui->pow_half, SIGNAL(clicked()), this, SLOT(powerButtonClicked()));
    connect(ui->pow_minus_one, SIGNAL(clicked()), this, SLOT(powerButtonClicked()));

    connect(ui->memory_clear, SIGNAL(clicked()), this, SLOT(memoryButtonClicked()));
    connect(ui->memory_save, SIGNAL(clicked()), this, SLOT(memoryButtonClicked()));
    connect(ui->memory_recall, SIGNAL(clicked()), this, SLOT(memoryButtonClicked()));

    connect(ui->backspace, SIGNAL(clicked()), this, SLOT(removeLastChar()));
    connect(ui->num_dot, SIGNAL(clicked()), this, SLOT(dotButtonClicked()));
    connect(ui->eval, SIGNAL(clicked()), this, SLOT(evaluate()));
    connect(ui->factorial, SIGNAL(clicked()), this, SLOT(factButtonClicked()));
    connect(ui->all_clear, SIGNAL(clicked()), this, SLOT(acButtonClicked()));

    // reset for the first time
    acButtonClicked();
    
    setWindowTitle("Minhaz Calc");
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::numberButtonClicked()
{
    QString numString = QObject::sender()->objectName().remove("num_");

    if(clear)
    {
        clear = false;
        ui->expression->clear();
    }
    ui->expression->insert(numString);
}

void Calculator::operationButtonClicked()
{
    QString oprString = QObject::sender()->objectName().remove("expr_");

    if(oprString == "add")
        oprString = "+";
    else if(oprString == "sub")
        oprString = "-";
    else if(oprString == "mul")
        oprString = "*";
    else if(oprString == "div")
        oprString = "/";

    if(clear)
    {
        clear = false;
        ui->expression->clear();
    }
    ui->expression->insert(oprString);
}

void Calculator::parenthesisButtonClicked()
{
    QString parenString = QObject::sender()->objectName().remove("paren_");

    if(parenString == "begin")
        parenString = "(";
    else if(parenString == "end")
        parenString = ")";

    if(clear)
    {
        clear = false;
        ui->expression->clear();
    }
    ui->expression->insert(parenString);
}

void Calculator::functionButtonClicked()
{
    QString funcName = QObject::sender()->objectName().remove("func_");

    if(clear)
    {
        clear = false;
        ui->expression->clear();
    }

    ui->expression->insert(funcName + "(");
}

void Calculator::removeLastChar()
{
    QString exprStr = ui->expression->text();
    exprStr.remove(exprStr.length()-1, 1);
    ui->expression->setText(exprStr);
}

void Calculator::powerButtonClicked()
{
    QString powName = QObject::sender()->objectName().remove("pow_");

    if(powName == "2")
        powName = "^2";
    else if(powName == "3")
        powName = "^3";
    else if(powName == "n")
        powName = "^";
    else if(powName == "half")
        powName = "^0.5";
    else if(powName == "minus_one")
        powName = "^-1";

    if(clear)
    {
        clear = false;
        ui->expression->clear();
    }

    ui->expression->insert(powName);
}

void Calculator::acButtonClicked()
{
    clear = false;
    ui->expression->clear();
    ui->result->setText(0);
    ui->memory->setDisabled(true);
    memory = 0;
}

void Calculator::memoryButtonClicked()
{
    QString memStr = QObject::sender()->objectName().remove("memory_");

    if(memStr == "clear")
    {
        ui->memory->setDisabled(true);
        memory = 0;
    }
    else if(memStr == "save")
    {
        memory = ui->result->text().toDouble();
        ui->memory->setEnabled(true);
    }
    else if(memStr == "recall")
    {
        ui->expression->insert(QString::number(memory));
    }

    if(clear)
    {
        clear = false;
        ui->expression->clear();
    }
}

void Calculator::factButtonClicked()
{
    ui->expression->insert("!");

    if(clear)
    {
        clear = false;
        ui->expression->clear();
    }
}

void Calculator::dotButtonClicked()
{
    ui->expression->insert(".");

    if(clear)
    {
        clear = false;
        ui->expression->clear();
    }
}

void Calculator::evaluate()
{
    try
    {
        QRegularExpression re("(\\d)*!");
        QString expr = ui->expression->text();

        QRegularExpressionMatch match = re.match(expr);

        if (match.hasMatch())
        {
            QString cap = match.captured(0);
            QString capBackup = cap;

            int num = cap.remove("!").toInt();
            unsigned long long int fact = 1;

            for(int i=2; i<=num; i++)
                fact *= i;

            expr.replace(capBackup, QString::number(fact));
        }

        double value = parser.parse(expr.toStdString()).evaluate();
        //qDebug() << value;
        ui->result->setText(QString::number(value));
    }
    catch(Lepton::Exception e)
    {
        ui->result->setText("error");
    }

    clear = true;
}
