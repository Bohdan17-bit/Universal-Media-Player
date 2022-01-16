#include "editpath.h"
#include "ui_editpath.h"
#include "QMessageBox"

EditPath::EditPath(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditPath)
{
    ui->setupUi(this);
    Refresh_Paths();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setWindowTitle("EDIT");
}

EditPath::~EditPath()
{
    delete ui;
}

void EditPath::Refresh_Paths()
{
    ui->tableWidget->setRowCount(0);
    Load_Paths();
}

void EditPath::on_AddPathBtn_clicked()
{
    QString str;
    str = QFileDialog::getExistingDirectory();
    if(PathFileobj.Add_new_Path(str))
    {
        last_file = str;
        emit SendSignalAddAndUpdataMainWindow();
    }
    Refresh_Paths();
}

QString EditPath::Get_Last_Path()
{
    return last_file;
}

void EditPath::Load_Paths()
{
    QStringList list_paths = PathFileobj.Get_All_Paths();
    for(int i = 0; i < list_paths.size(); i++)
    {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() +1);
        QTableWidgetItem *newItem = new QTableWidgetItem();
        newItem->setText(list_paths[i]);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, newItem);
    }
}

void EditPath::ReWritePathsInFile(QStringList list_paths)
{
    PathFiles *temp = new PathFiles();
    temp->Remove_old_paths();
    if(QFileInfo("path.txt").exists())
    {
        QFile::remove("path.txt");
    }
    for(QString path : list_paths)
    {
        path.chop(1);
        temp->ReWritePath(path);
    }
    Refresh_Paths();
    temp = nullptr;
    delete temp;
}

void EditPath::on_RemovePathBtn_clicked()
{
    PathFiles *temp = new PathFiles();
    QStringList actual_list = temp->Get_All_Paths();
    QModelIndexList indexes_selected = ui->tableWidget->selectionModel()->selectedRows();
    QStringList list_re_write;
    QModelIndexList normal_index;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        bool save_this_path = true;
        for(QModelIndex index_selected : indexes_selected)
        {
            if(index_selected.row() == i)
            {
                save_this_path = false;
                break;
            }
        }
        if(save_this_path)
            list_re_write.push_back(actual_list[i]);
    }
    ReWritePathsInFile(list_re_write);
    emit SendSignalDelAndUpdataMainWindow();
    temp = nullptr;
    delete temp;
}
