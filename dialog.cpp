#include "dialog.h"
#include "ui_dialog.h"
#include "usergroups.h"

#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage User Group Membership");

    ui->treeWidget_groups->setColumnWidth(0, 200);
    ui->treeWidget_groups->setColumnWidth(1, 60);

    populate_treeWidget_groups();
}

Dialog::~Dialog()
{
    delete ui;
}

QString get_username()
{
    QString name = qgetenv("USER");
    if (name.isEmpty())
        name = qgetenv("USERNAME");
    return name;
}

void Dialog::populate_treeWidget_groups()
{
    QString username = get_username();    
    QList<UserGroups::Group> groups_list;

    ui->lineEdit_username->setText(username);
    ui->treeWidget_groups->clear();

    groups_list = UserGroups::get_groups();

    foreach (const auto &group, groups_list)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget_groups);
        item->setText(0, group.name);

        if (group.members.contains(username))
            item->setCheckState(1, Qt::Checked);
        else
            item->setCheckState(1, Qt::Unchecked);
    }

    ui->treeWidget_groups->sortItems(0, Qt::AscendingOrder);
}

void Dialog::on_pushButton_Apply_clicked()
{
    QStringList groups;
    QString username = get_username();

    for (int i = 0; i < ui->treeWidget_groups->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem* item = ui->treeWidget_groups->topLevelItem(i);

        if (item->checkState(1) == Qt::Checked)
            groups.append(item->text(0));
    }
    UserGroups::set_groups(groups, username);
    populate_treeWidget_groups();
}
