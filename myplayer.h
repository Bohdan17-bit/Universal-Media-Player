#ifndef MYPLAYER_H
#define MYPLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "QFileInfoList"

class MyPlayer
{
public:
    MyPlayer();
    ~MyPlayer();
    void Add_Media_From_Path(QString path);
    void Turn_ON_OFF();
    void Next();
    void Previous();
    void Set_Volume(int value);
    void Retry_ALL_Mode();
    void Retry_Current_Mode();
    void Default_Mode();
    QFileInfoList Get_List_Files();
    int Get_Current_Index_Playlist();
    bool GetStatusMediaPasuseOrPlay();
    void Clear_list_name_files();
    QMediaPlaylist *playlist;
    QMediaPlayer *player;
    int Get_Last_Value_Volume();
    void Set_Last_Value_Volume(int value);
    bool Clear_Playlist();
private:
    QStringList list_audio_formats;
    QFileInfoList name_files;
    int last_value;
    void Start_Player();
    void Pause_Player();
    void Set_Search_Media_Formats();
    void Set_Default_Settings();
    void Go_from_Loop();
    void Go_to_Loop();
    QString last_state;
};

#endif // MYPLAYER_H
