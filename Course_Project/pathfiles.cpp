#include "pathfiles.h"
#include "QDebug"
#include "QMessageBox"

PathFiles::PathFiles()
{
    name_file = "path.txt";
    file_save_path.setFileName(name_file);
}

PathFiles::~PathFiles()
{

}

void PathFiles::Remove_old_paths()
{
    all_paths.clear();
}

void PathFiles::Read_All_Paths()
{
    all_paths.clear();
    if (file_save_path.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!file_save_path.atEnd())
        {
            QString line = file_save_path.readLine();
            all_paths.push_back(line);
        }
        file_save_path.close();
    }
}

QStringList PathFiles::Get_All_Paths()
{
    Read_All_Paths();
    return all_paths;
}

void PathFiles::ReWritePath(QString path_catalog_music)
{
    if (file_save_path.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        file_save_path.write(path_catalog_music.toUtf8() + "\n");
        file_save_path.close();
    }
}

bool PathFiles::Add_new_Path(QString path_catalog_music)
{
    Read_All_Paths();
    bool path_exist = false;
    for(int i = 0; i < all_paths.size(); i++)
    {
        if(path_catalog_music + '\n' == all_paths[i])
        {
            path_exist = true;
        }
    }
    if(path_catalog_music == "")
    {
        return 0;
    }
    if(path_exist == false)
    {
        if (file_save_path.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        {
            file_save_path.write(path_catalog_music.toUtf8() + "\n");
            file_save_path.close();
            QMessageBox msgBox;
            msgBox.setText("Success add new PATH!");
            msgBox.exec();
            return 1;
        }
        return 0;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Please, input the correct PATH");
        msgBox.exec();
        return 0;
    }
}
