#include "usergroups.h"

#include <QtGui>
#include <QFile>
#include <QDebug>

UserGroups::UserGroups()
{
    qDebug() << "Class UserGroups created!";
}

UserGroups::~UserGroups()
{
     qDebug() << "Class UserGroups destroyed!";
}

QList<UserGroups::Group> UserGroups::get_groups()
{
    QList<Group> groups_list;

    const QString groupconfFilePath {"/etc/group"};
    QFile file(groupconfFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "file not opened !";

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QStringList split = in.readLine().split("#", Qt::KeepEmptyParts).first().split(":", Qt::KeepEmptyParts);

        if (split.size() < 4)
            continue;

        Group group;
        group.name = split.at(0);
        group.members = split.at(3).split(",", Qt::SkipEmptyParts);

        if (group.name.isEmpty())
            continue;

        groups_list.append(group);
    }

    file.close();
    return groups_list;
}

void UserGroups::set_groups(QStringList groups_list_to_set, QString username)
{
    QProcess cmd_process;
    QString command;

    command = "pkexec usermod -G " + groups_list_to_set.join(",") + " " + username;
    //qDebug() << command;

    cmd_process.start(command);
    //cmd_process.start(command, QStringList{""});
    cmd_process.waitForFinished();
}
