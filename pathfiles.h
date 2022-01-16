#ifndef PATHFILES_H
#define PATHFILES_H
#include "QString"
#include "QFile"
#include "QDir"

class PathFiles
{
private:
    QFile file_save_path;
    QString name_file;
    QStringList all_paths;
    void Read_All_Paths();
public:
    PathFiles();
   ~PathFiles();
    bool Add_new_Path(QString path_catalog_music);
    QStringList Get_All_Paths();
    void Remove_old_paths();
    void ReWritePath(QString path_catalog_music);
};

#endif // PATHFILES_H
