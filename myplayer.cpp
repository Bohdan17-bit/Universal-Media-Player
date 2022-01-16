#include "myplayer.h"
#include "QDir"
#include <QAudioDeviceInfo>

MyPlayer::MyPlayer()
{
    player = new QMediaPlayer();
    playlist = new QMediaPlaylist();
    player->setPlaylist(playlist);
    Set_Default_Settings();
    Set_Search_Media_Formats();
    last_value = 0;
    last_state = "Sequential";
}

MyPlayer::~MyPlayer()
{
    playlist->clear();
    player = nullptr;
    playlist = nullptr;
    delete player;
    delete playlist;
}

bool MyPlayer::Clear_Playlist()
{
    return playlist->clear();
}

int MyPlayer::Get_Last_Value_Volume()
{
    return last_value;
}

void MyPlayer::Set_Last_Value_Volume(int value)
{
    last_value = value;
}

int MyPlayer::Get_Current_Index_Playlist()
{
    return playlist->currentIndex();
}

void MyPlayer::Default_Mode()
{
    qDebug("Set default mode ");
    playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
}

void MyPlayer::Retry_Current_Mode()
{
    qDebug("Set retry current mode ");
    playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::CurrentItemInLoop);
}

void MyPlayer::Retry_ALL_Mode()
{
    qDebug("Set retry all mode ");
    playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::Loop);
}

void MyPlayer::Set_Search_Media_Formats()
{
    list_audio_formats << "*.mpg" << "*.mp2" << "*.mp3" << "*.mp4" << "*.mpeg";
    list_audio_formats << "*.asf" << "*.wma" << "*.wmv";
    list_audio_formats << "*asx" << "*.wax" << "*.wmx";
    list_audio_formats << "*.flac" << "*.aac" << "*.ogg";
    list_audio_formats << "*.mid" << "*.midi" << "*.dvr-ms";
    list_audio_formats << "*.wmd" << "*.avi" << "*.wav";
    list_audio_formats << "*.mov" << "*.m2ts" << "*.cdda";
}

void MyPlayer::Set_Volume(int value)
{
    player->setVolume(value);
}

void MyPlayer::Set_Default_Settings()
{
    player->setVolume(100);
    playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
}

bool MyPlayer::GetStatusMediaPasuseOrPlay()
{
    if(player->state() == QMediaPlayer::State::PlayingState)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void MyPlayer::Go_to_Loop()
{
    if(last_state == "Sequential")
    {
        playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
    }
    else if(last_state == "CurrentItemInLoop")
    {
        playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::CurrentItemInLoop);
    }
    else
    {
        playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::Loop);
    }
}

void MyPlayer::Go_from_Loop()
{
    if(playlist->playbackMode() == QMediaPlaylist::PlaybackMode::CurrentItemInLoop)
    {
        last_state = "CurrentItemInLoop";
    }
    else if(playlist->playbackMode() == QMediaPlaylist::PlaybackMode::Sequential)
    {
        last_state = "Sequential";
    }
    else
    {
        last_state = "Loop";
    }
    playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::Loop);
}

void MyPlayer::Next()
{
    qDebug(QString::number(playlist->currentIndex()).toUtf8());
    Go_from_Loop();
    playlist->setCurrentIndex(playlist->nextIndex());
    if(playlist->currentIndex() == -1)
    {
        playlist->setCurrentIndex(playlist->nextIndex());
        player->play();
    }
    Go_to_Loop();
}

void MyPlayer::Previous()
{
 if(playlist->currentIndex() == -1)
 {
     playlist->setCurrentIndex(0);
  }
 Go_from_Loop();
 playlist->setCurrentIndex(playlist->previousIndex());
 Go_to_Loop();
}

void MyPlayer::Turn_ON_OFF()
{
    qDebug(QString::number(playlist->currentIndex()).toUtf8());
    if(player->state() == QMediaPlayer::State::PlayingState)
    {
        Pause_Player();
    }
    else
    {
        Start_Player();
    }
}

void MyPlayer::Clear_list_name_files()
{
    name_files.clear();
}

void MyPlayer::Add_Media_From_Path(QString path)
{
    QDir dir(path);
    QFileInfoList new_pack_media_files = dir.entryInfoList(list_audio_formats, QDir::Files | QDir::NoDotAndDotDot);
    name_files += new_pack_media_files;
    foreach (QFileInfo media_file, new_pack_media_files)
    {
        playlist->addMedia(QUrl(media_file.absoluteFilePath()));
    }
}

void MyPlayer::Start_Player()
{
    player->play();
}

void MyPlayer::Pause_Player()
{
    player->pause();
}

QFileInfoList MyPlayer::Get_List_Files()
{
    return name_files;
}

