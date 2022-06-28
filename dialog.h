#ifndef DIALOG_H
#define DIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

public slots:

private:
    Ui::Dialog *ui;

private slots:
    void populate_treeWidget_groups();
    void on_pushButton_Apply_clicked();
};
#endif // DIALOG_H
