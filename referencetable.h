#ifndef REFERENCETABLE_H
#define REFERENCETABLE_H

#include <QDialog>

namespace Ui {
class referenceTable;
}

class referenceTable : public QDialog
{
    Q_OBJECT

public:
    explicit referenceTable(QWidget *parent = nullptr);
    ~referenceTable();

private:
    Ui::referenceTable *ui;
};

#endif // REFERENCETABLE_H
