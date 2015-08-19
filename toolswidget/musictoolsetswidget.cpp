#include "musictoolsetswidget.h"
#include "musicapplication.h"
#include "musicaudiorecorderwidget.h"
#include "musictimerwidget.h"
#include "musiclocalsongsmanagerwidget.h"
#include "musictransformwidget.h"
#include "musicspectrumwidget.h"
#include "musicdesktopwallpaperwidget.h"
#include <QProcess>

MusicToolSetsWidget::MusicToolSetsWidget(MusicApplication *parent)
    : QListWidget(parent),m_parentWidget(parent),m_process(NULL),
      m_musicSpectrumWidget(NULL),m_wallpaper(NULL)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    setFrameShape(QFrame::NoFrame);//Set No Border
    setStyleSheet(MusicUIObject::MScrollBarStyle01);
    setIconSize(QSize(60,60));
    setViewMode(QListView::IconMode);
    setMovement(QListView::Static);
    setSpacing(15);
    setTransparent(50);
    connect(this,SIGNAL(itemClicked(QListWidgetItem*)),
            SLOT(itemHasClicked(QListWidgetItem*)));

    addListWidgetItem();
}

MusicToolSetsWidget::~MusicToolSetsWidget()
{
    delete m_wallpaper;
    delete m_musicSpectrumWidget;
    delete m_process;
    clearAllItems();
}

void MusicToolSetsWidget::setSongStringList(const QStringList& l)
{
    m_songlist = l;
}

void MusicToolSetsWidget::setTransparent(int angle)
{
    QPalette pal = palette();
    pal.setBrush(QPalette::Base,QBrush(QColor(255,255,255,angle)));
    setPalette(pal);
    repaint();
}

void MusicToolSetsWidget::clearAllItems()
{
    clear();
}

void MusicToolSetsWidget::addListWidgetItem()
{
    QListWidgetItem *item = new QListWidgetItem(QIcon(":/tools/localmanager")
                                                ,tr("localmanager"),this);
    item->setSizeHint(QSize(80,90));
    addItem(item);
                     item = new QListWidgetItem(QIcon(":/tools/recorder")
                                                ,tr("recorder"),this);
    item->setSizeHint(QSize(80,90));
    addItem(item);
                     item = new QListWidgetItem(QIcon(":/tools/bell")
                                                ,tr("bell"),this);
    item->setSizeHint(QSize(80,90));
    addItem(item);
                     item = new QListWidgetItem(QIcon(":/tools/timer")
                                                ,tr("timer"),this);
    item->setSizeHint(QSize(80,90));
    addItem(item);
                     item = new QListWidgetItem(QIcon(":/tools/transform")
                                                ,tr("transform"),this);
    item->setSizeHint(QSize(80,90));
    addItem(item);
                     item = new QListWidgetItem(QIcon(":/tools/spectrum")
                                                ,tr("spectrum"),this);
    item->setSizeHint(QSize(80,90));
    addItem(item);
                     item = new QListWidgetItem(QIcon(":/tools/wallpaper")
                                                ,tr("wallpaper"),this);
    item->setSizeHint(QSize(80,90));
    addItem(item);
                     item = new QListWidgetItem(QIcon(":/tools/ktv")
                                                    ,tr("ktv"),this);
    item->setSizeHint(QSize(80,90));
    addItem(item);
                     item = new QListWidgetItem(QIcon(":/tools/live")
                                                ,tr("live"),this);
    item->setSizeHint(QSize(80,90));
    addItem(item);
                     item = new QListWidgetItem(QIcon(":/tools/game")
                                                ,tr("game"),this);
    item->setSizeHint(QSize(80,90));
    addItem(item);
                     item = new QListWidgetItem(QIcon(":/tools/lottery")
                                                ,tr("lottery"),this);
    item->setSizeHint(QSize(80,90));
    addItem(item);
                     item = new QListWidgetItem(QIcon(":/tools/phone")
                                                ,tr("phone"),this);
    item->setSizeHint(QSize(80,90));
    addItem(item);
                     item = new QListWidgetItem(QIcon(":/tools/radio")
                                                ,tr("radio"),this);
    item->setSizeHint(QSize(80,90));
    addItem(item);
                     item = new QListWidgetItem(QIcon(":/tools/speed")
                                                ,tr("speed"),this);
    item->setSizeHint(QSize(80,90));
    addItem(item);
                     item = new QListWidgetItem(QIcon(":/tools/vip")
                                                ,tr("vip"),this);
    item->setSizeHint(QSize(80,90));
    addItem(item);

}

void MusicToolSetsWidget::itemHasClicked(QListWidgetItem* it)
{
    switch(row(it))
    {
        case 0:
           {
                MusicLocalSongsManagerWidget local(this);
                connect(&local,SIGNAL(addSongToPlay(QStringList)),
                        m_parentWidget,SLOT(addSongToPlayList(QStringList)));
                local.exec();
                break;
           }
        case 1:
            MusicAudioRecorderWidget(this).exec();
            break;
        case 2:
           {
                if(!QFile(MAKE_RING).exists())
                    return;
                if(m_process)
                    delete m_process;
                m_process = new QProcess(this);
                m_process->start(MAKE_RING);
                break;
           }
        case 3:
           {
                MusicTimerWidget timer(this);
                timer.setSongStringList(m_songlist);
                connect(&timer,SIGNAL(timerParameterChanged()),
                        m_parentWidget,SLOT(musicToolSetsParameter()));
                timer.exec();
                break;
            }
        case 4:
            MusicTransformWidget(this).exec();
            break;
        case 5:
           {
                delete m_musicSpectrumWidget;
                m_musicSpectrumWidget = new MusicSpectrumWidget;
                connect(m_musicSpectrumWidget,SIGNAL(setSpectrum(HWND,int,int)),
                        SIGNAL(setSpectrum(HWND,int,int)));
                m_musicSpectrumWidget->show();
                break;
           }
        case 6:
           {
                delete m_wallpaper;
                m_wallpaper = new MusicDesktopWallpaperWidget(this);
                m_wallpaper->show();
           }
    }
}
