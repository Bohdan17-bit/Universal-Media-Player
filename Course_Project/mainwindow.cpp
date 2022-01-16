#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLabel"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("MediaPlayer");
    editpathwindow = new EditPath();
    Retry_btn_state = "OFF";
    myplayer = new MyPlayer();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ReLoad_names_mediafiles_in_table();
    Active_Media_Show();

    connect(editpathwindow, &EditPath::SendSignalAddAndUpdataMainWindow, this, &MainWindow::Get_list_names_with_last_add_path);
    connect(editpathwindow, &EditPath::SendSignalDelAndUpdataMainWindow, this, &MainWindow::ReLoad_names_mediafiles_in_table);
    connect(myplayer->playlist, &QMediaPlaylist::currentMediaChanged, this, &MainWindow::Active_Media_Show);

    Init_VideoWidget();

    connect(myplayer->player, &QMediaPlayer::durationChanged, this, &MainWindow::Set_Max_Value_time_line_slider);
    connect(myplayer->player, &QMediaPlayer::positionChanged, this, &MainWindow::Set_Current_Position_slider);
    connect(myplayer->player, &QMediaPlayer::stateChanged, this, &MainWindow::Additional_void);

    Set_Label_With_QPixmap();
    videoWidget->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent (QCloseEvent *event)
{
   event->accept();
   editpathwindow->close();
   delete myplayer;
   delete editpathwindow;
   delete videoWidget;
   exit(0);
}

void MainWindow::Set_Label_With_QPixmap()
{
    qlabel = new QLabel();
    QPixmap p;
    p.load(":/images/video.png");
    int w = qlabel->width()/2;
    int h = qlabel->height()/2;
    qlabel->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
    qlabel->setAlignment(Qt::AlignCenter);
    ui->video_layout->addWidget(qlabel);
}

void MainWindow::Init_VideoWidget()
{
    videoWidget = new VideoWidget();
    myplayer->player->setVideoOutput(videoWidget);
    ui->video_layout->addWidget(videoWidget);
}

void MainWindow::Additional_void()
{
    QIcon *icon = new QIcon();
    if(myplayer->player->state() == QMediaPlayer::State::PlayingState)
    {
        qDebug("Player has state : play");
        icon->addPixmap(QPixmap(":/images/stop.png"));
    }
    else
    {
        qDebug("Player has state : pause");
        icon->addPixmap(QPixmap(":/images/play.png"));
    }
    ui->play_btn->setIcon(*icon);
    delete icon;
}

void MainWindow::Set_Current_Position_slider()
{
    if(ui->time_line_slider->isSliderDown() == false)
    {
        ui->time_line_slider->setValue(myplayer->player->position() / 1000);
    }
}

void MainWindow::on_time_line_slider_valueChanged(int value)
{
    if(value != myplayer->player->position() / 1000)
    {
        myplayer->player->setPosition(value * 1000);
    }
}

void MainWindow::Set_Max_Value_time_line_slider()
{

    if(myplayer->player->isVideoAvailable())
    {
         qlabel->hide();
         videoWidget->show();
    }
    else
    {
        videoWidget->hide();
        qlabel->show();
    }
    ui->time_line_slider->setMaximum(myplayer->player->duration() / 1000);
}

void MainWindow::Active_Media_Show()
{
    QModelIndex newIndex = ui->tableWidget->model()->index(myplayer->Get_Current_Index_Playlist(), 0);
    ui->tableWidget->setCurrentIndex(newIndex);
}

void MainWindow::Clear_Table()
{
    ui->tableWidget->setRowCount(0);
}

void MainWindow::ReLoad_names_mediafiles_in_table()
{
    Clear_Table();
    myplayer->Clear_list_name_files();
    myplayer->Clear_Playlist();
    PathFiles temp;
    QStringList list_paths = temp.Get_All_Paths();
    for (QString path : list_paths)
    {
        path.chop(1);
        myplayer->Add_Media_From_Path(path);
    }
    Set_in_column_pack_names_media_files(myplayer->Get_List_Files());
}

void MainWindow::Set_in_column_pack_names_media_files(QFileInfoList list_names)
{
    for(int i = 0; i < list_names.size(); i++)
    {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() +1);
        QTableWidgetItem *newItem = new QTableWidgetItem();
        newItem->setText(list_names[i].fileName());
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, newItem);
        Active_Media_Show();
    }
}

void MainWindow::Get_list_names_with_last_add_path()
{
    QString path = editpathwindow->Get_Last_Path();
    qDebug("Now we add new path : " + path.toUtf8());
    myplayer->Add_Media_From_Path(path);
    Clear_Table();
    Set_in_column_pack_names_media_files(myplayer->Get_List_Files());
}

void MainWindow::on_Edit_path_btn_clicked()
{
    editpathwindow->show();
}

void MainWindow::Change_Icon_Cycle_Btn()
{
    QIcon *icon = new QIcon();
    if(Retry_btn_state == "OFF")
    {
        icon->addPixmap(QPixmap(":images/cycle.png"));
        Retry_btn_state = "ON_ONE";
        myplayer->Retry_Current_Mode();
    }
    else if(Retry_btn_state == "ON_ONE")
    {
        icon->addPixmap(QPixmap(":images/cycle_all.png"));
        Retry_btn_state = "ON_ALL";
        myplayer->Retry_ALL_Mode();
    }
    else
    {
        icon->addPixmap(QPixmap(":images/black_cycle.png"));
        Retry_btn_state = "OFF";
        myplayer->Default_Mode();
    }
    ui->cycle_btn->setIcon(*icon);
    delete icon;
}

void MainWindow::on_cycle_btn_clicked()
{
    Change_Icon_Cycle_Btn();
}

void MainWindow::on_play_btn_clicked()
{
    if(myplayer->playlist->isEmpty() == false)
    {
        QIcon *icon = new QIcon();
        if(myplayer->GetStatusMediaPasuseOrPlay())
        {
            icon->addPixmap(QPixmap(":/images/play.png"));
        }
        else
        {
            icon->addPixmap(QPixmap(":/images/stop.png"));
        }
        ui->play_btn->setIcon(*icon);
        myplayer->Turn_ON_OFF();
        delete icon;
    }
}

void MainWindow::on_next_btn_clicked()
{
    myplayer->Next();
}

void MainWindow::on_previous_btn_clicked()
{
    myplayer->Previous();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    QIcon *icon = new QIcon();
    if(value == 0)
    {
        icon->addPixmap(QPixmap(":/images/no_audio.png"));
    }
    else
    {
        icon->addPixmap(QPixmap(":/images/sound.png"));
    }
     myplayer->Set_Volume(value);
     ui->sound_btn->setIcon(*icon);
     delete icon;
}

void MainWindow::on_fullscreen_btn_clicked()
{
    if(myplayer->player->isVideoAvailable())
        videoWidget->setFullScreen(true);
}

void MainWindow::on_comboBox_speed_player_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0: myplayer->player->setPlaybackRate(0.75);
    break;
    case 1: myplayer->player->setPlaybackRate(1);
    break;
    case 2: myplayer->player->setPlaybackRate(1.25);
    break;
    }
}

void MainWindow::on_sound_btn_clicked()
{
    QIcon *icon = new QIcon();
    if(myplayer->player->isMuted())
    {
        icon->addPixmap(QPixmap(":/images/sound.png"));
        myplayer->player->setMuted(false);
        ui->horizontalSlider->setValue(myplayer->Get_Last_Value_Volume());
    }
    else
    {
        icon->addPixmap(QPixmap(":/images/no_audio.png"));
        myplayer->Set_Last_Value_Volume(ui->horizontalSlider->value());
        myplayer->player->setMuted(true);
        ui->horizontalSlider->setValue(0);
    }
    ui->sound_btn->setIcon(*icon);
    delete icon;
}
