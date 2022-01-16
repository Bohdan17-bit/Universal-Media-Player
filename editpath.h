#ifndef EDITPATH_H
#define EDITPATH_H

#include <QWidget>
#include "pathfiles.h"
#include "QFileDialog"

namespace Ui {
class EditPath;
}

class EditPath : public QWidget
{
    Q_OBJECT

public:
    explicit EditPath(QWidget *parent = nullptr);
    ~EditPath();
    PathFiles PathFileobj;
    void Load_Paths();
    void Refresh_Paths();
    QString Get_Last_Path();
    QString last_file;
signals:
    void SendSignalAddAndUpdataMainWindow();
    void SendSignalDelAndUpdataMainWindow();
private slots:
    void on_AddPathBtn_clicked();
    void on_RemovePathBtn_clicked();
    void ReWritePathsInFile(QStringList list_paths);

private:
    Ui::EditPath *ui;
};

#endif // EDITPATH_H
