#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QtMultimediaWidgets/QVideoWidget>
#include "editpath.h"
#include "myplayer.h"
#include "QMouseEvent"
#include "videowidget.h"
#include "QLabel"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    EditPath *editpathwindow;
    QString Retry_btn_state;
    MyPlayer *myplayer;
    VideoWidget *videoWidget;
    QLabel *qlabel;
    void Change_Icon_Cycle_Btn();

private slots:
    void on_Edit_path_btn_clicked();

    void on_cycle_btn_clicked();

    void on_play_btn_clicked();

    void on_next_btn_clicked();

    void on_previous_btn_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void ReLoad_names_mediafiles_in_table();

    void Active_Media_Show();

    void Get_list_names_with_last_add_path();

    void Clear_Table();

    void on_fullscreen_btn_clicked();

    void Set_Max_Value_time_line_slider();

    void Set_Current_Position_slider();

    void on_comboBox_speed_player_currentIndexChanged(int index);

    void on_sound_btn_clicked();

    void Set_in_column_pack_names_media_files(QFileInfoList list_names);

    void Additional_void();

    void Set_Label_With_QPixmap();

    void Init_VideoWidget();

    void on_time_line_slider_valueChanged(int value);

    void closeEvent (QCloseEvent *event);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
