#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QString>
#include <QDoubleValidator>
#include <QDebug>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QDate> // Include this line for QDate

class ExpenseApp : public QWidget {
public:
    ExpenseApp(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("Expense Tracking App");
        setGeometry(100, 100, 600, 400);


        productNameInput = new QLineEdit(this);
        productNameInput->setPlaceholderText("Enter Product Name");
        expenseInput = new QLineEdit(this);
        expenseInput->setPlaceholderText("Expnse amount");
        expenseInput->setValidator(new QDoubleValidator(this));
        reasonInput = new QLineEdit(this);
        reasonInput->setPlaceholderText("reason");



        addExpenseButton = new QPushButton("Add Expense", this);
        totalLabel = new QLabel("Total Expenses: $0.00", this);

        expenseTable = new QTableWidget(this);
        expenseTable->setColumnCount(4);
        expenseTable->setHorizontalHeaderLabels(QStringList() << "Product Name" << "Expense Amount" << "Date" << "reason");

        QVBoxLayout *layout = new QVBoxLayout;
        QHBoxLayout *inputLayout = new QHBoxLayout;

        inputLayout->addWidget(productNameInput);
        inputLayout->addWidget(expenseInput);
        inputLayout->addWidget(reasonInput);
        inputLayout->addWidget(addExpenseButton);
        layout->addLayout(inputLayout);
        layout->addWidget(expenseTable);
        layout->addWidget(totalLabel);

        connect(addExpenseButton, &QPushButton::clicked, this, &ExpenseApp::addExpense);

        setLayout(layout);
    }

private slots:
    void addExpense() {
        QString productName = productNameInput->text();
        QString expenseText = expenseInput->text();
        QString reason = reasonInput->text();

        if (!productName.isEmpty() && !expenseText.isEmpty()) {
            double expenseAmount = expenseText.toDouble();

            int row = expenseTable->rowCount();
            expenseTable->insertRow(row);
            expenseTable->setItem(row, 0, new QTableWidgetItem(productName));
            expenseTable->setItem(row, 1, new QTableWidgetItem(QString("$%1").arg(expenseAmount, 0, 'f', 2)));
            expenseTable->setItem(row, 2, new QTableWidgetItem(QDate::currentDate().toString(Qt::ISODate)));
            expenseTable->setItem(row, 3, new QTableWidgetItem(reason));
            totalExpenses += expenseAmount;
            updateTotalLabel();

            productNameInput->clear();
            expenseInput->clear();
        }
    }

    void updateTotalLabel() {
        totalLabel->setText(QString("Total Expenses: $%1").arg(totalExpenses, 0, 'f', 2));
    }

private:
    QLineEdit *productNameInput;
    QLineEdit *expenseInput;
    QLineEdit *reasonInput;
    QPushButton *addExpenseButton;
    QLabel *totalLabel;
    QTableWidget *expenseTable;
    double totalExpenses = 0.0;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ExpenseApp window;
    window.show();

    return app.exec();
}
