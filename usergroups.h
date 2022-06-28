#ifndef USERGROUPS_H
#define USERGROUPS_H

#include <QObject>

class UserGroups : public QObject
{
    Q_OBJECT
public:

    explicit UserGroups();

    ~UserGroups();

    struct Group
    {
        QString name;
        QStringList members;
    };

    static QList<Group> get_groups();
    static void set_groups(QStringList groups_list_to_set, QString username);
    static QList<UserGroups::Group> Groups();
};

#endif // USERGROUPS_H
