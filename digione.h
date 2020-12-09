#ifndef DIGIONE_H
#define DIGIONE_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#ifdef USE_FLITE
#include <flite/flite.h>
#endif
#include "Common/httpmanager.h"
#include "mbelib/mbedec.h"
#include "mbelib/mbeenc.h"
#include "ysf/ysfcodec.h"
#include "dmr/dmrcodec.h"
#include "m17/m17codec.h"
#include "m17/m17codec.h"
#include "dcs/dcscodec.h"

namespace Ui {
class Digione;
}

class DigiOne : public QMainWindow
{
    Q_OBJECT
public:
    explicit DigiOne(QWidget *parent = nullptr);
    ~DigiOne();

signals:
    void input_source_changed(int, QString);
    void dmr_tgid_changed(unsigned int);
    void dmr_tgid_changed_plus(unsigned int);
    void dmr_out_audio_vol_changed(qreal);
    void dmr_plus_out_audio_vol_changed(qreal);
    void ysf_out_audio_vol_changed(qreal);
    void m17_out_audio_vol_changed(qreal);
    void dcs_out_audio_vol_changed(qreal);
    void in_audio_vol_changed(qreal);
private:
    Ui::Digione *ui;
    void init_gui();
    void discover_vocoders();

    enum{
        DMR_DISCONNECTED,
        DMR_CONNECTING,
        DMR_AUTH,
        DMR_CONF,
        DMR_OPTS,
        DMR_CONNECTED_RW,
        DMR_CONNECTED_RO
    } dmr_status;

    enum{
        DMR_PLUS_DISCONNECTED,
        DMR_PLUS_CONNECTING,
        DMR_PLUS_DMR_AUTH,
        DMR_PLUS_DMR_CONF,
        DMR_PLUS_DMR_OPTS,
        DMR_PLUS_CONNECTED_RW,
        DMR_PLUS_CONNECTED_RO
    } dmr_plus_status;

    enum{
        YSF_DISCONNECTED,
        YSF_CONNECTING,
        YSF_DMR_AUTH,
        YSF_DMR_CONF,
        YSF_DMR_OPTS,
        YSF_CONNECTED_RW,
        YSF_CONNECTED_RO
    } ysf_status;

    enum{
        M17_DISCONNECTED,
        M17_CONNECTING,
        M17_DMR_AUTH,
        M17_DMR_CONF,
        M17_DMR_OPTS,
        M17_CONNECTED_RW,
        M17_CONNECTED_RO
    } m17_status;

    enum{
        DCS_DISCONNECTED,
        DCS_CONNECTING,
        DCS_DMR_AUTH,
        DCS_DMR_CONF,
        DCS_DMR_OPTS,
        DCS_CONNECTED_RW,
        DCS_CONNECTED_RO
    } dcs_status;

    QTime startTime;
    QTimer t;
    QTimer TxEOT;
    QTimer dmrTimerReceived;
    QTimer dmrPlusTimerReceived;
    QTimer ysfTimerReceived;
    QTimer dcsTimerReceived;
    QTimer m17TimerReceived;
    uint16_t usb_pid;
    uint16_t usb_vid;
    QLabel *status_txt;
    QString host;
    QString hostname;
    QString hosts_filename;
    bool m_update_host_files;
    int port;
    QHostAddress address;
    QString config_path;
    QString callsign;
    //QString serial;
    QString dmr_password;
    QString dmr_options;
    QString dmr_repeater;
    QString saved_refhost;
    QString saved_dcshost;
    QString saved_xrfhost;
    QString saved_ysfhost;
    QString saved_dmrhost;
    QString saved_p25host;
    QString saved_nxdnhost;
    QString saved_m17host;
    char module;
    uint32_t dmrid;
    uint32_t dmr_srcid;
    uint32_t dmr_destid;
    uint32_t dmrcc;
    uint32_t dmrslot;
    uint8_t dmrcalltype;
    QString protocol;
    uint64_t ping_cnt;
    QThread *m_modethread_ysf;
    QThread *m_modethread_m17;
    QThread *m_modethread_dmr;
    QThread *m_modethread_dcs;
    QThread *m_modethread_dmr_plus;
    YSFCodec *m_ysf;
    M17Codec *m_m17;
    DMRCodec *m_dmr;
    DCSCodec *m_dcs;
    DMRCodec *m_dmr_plus;
    QString dmr_connection_status;
    QString dmr_plus_connection_status;
    QString ysf_connection_status;
    QString m17_connection_status;
    QString dcs_connection_status;
    QByteArray user_data;
    QString dmr_src;
    QString dmr_previous_src;
    QString dmr_plus_src;
    QString dmr_plus_previous_src;
    QString ysf_src;
    QString ysf_previous_src;
    QString m17_src;
    QString m17_previous_src;
    QString dcs_src;
    QString dcs_previous_src;
    QMap<uint32_t, QString> m_dmrids;
    QStringList dmrList;
    QStringList dmrPlusList;
    QStringList ysfList;
    QStringList m17List;
    QStringList dcsList;
    QStringListModel dmrModel;
    QStringListModel dmrPlusModel;
    QStringListModel ysfModel;
    QStringListModel dcsModel;
    QStringListModel m17Model;
    QPushButton *cronoButton;
    bool dmr_muted;
    bool dmr_plus_muted;
    bool ysf_muted;
    bool m17_muted;
    bool dcs_muted;
    bool dmr_input_muted;
    bool dmr_plus_input_muted;
    bool ysf_input_muted;
    bool m17_input_muted;
    bool dcs_input_muted;
    bool tx;
    bool hwtx;
    bool hwrx;
    bool hw_ambe_present;
private slots:
    void process_dmr_connect();
    void process_volume_changed(int n);
    void process_mute_out();
    void process_mute_in();
    void process_input_volume_changed(int n);
    void save_settings(QString path);
    void save_settings_from_menu();
    void open_settings_from_menu();
    void process_mute_channel(QString c);
    void process_dmr_mute_channel();
    void process_dmr_plus_mute_channel();
    void process_ysf_mute_channel();
    void process_m17_mute_channel();
    void process_dcs_mute_channel();
    void process_dcs_connect();
    void process_dmr_plus_connect();
    void process_ysf_connect();
    void process_m17_connect();
    void process_ysf_hosts();
    void process_dmr_ids();
    void process_m17_hosts();
    void process_dmr_hosts();
    void process_dcs_hosts();
    void update_dmr_data();
    void update_dmr_plus_data();
    void update_sound_dmr_plus_data();
    void dmrChangeButtonColor();
    void dmrPlusChangeButtonColor();
    void ysfChangeButtonColor();
    void dcsChangeButtonColor();
    void m17ChangeButtonColor();
    void update_sound_dmr_data();
    void update_ysf_data();
    void update_sound_ysf_data();
    void update_sound_dcs_data();
    void update_m17_data();
    void update_sound_m17_data();
    void update_dcs_data();
    void tgid_text_changed(QString s);
    void tgid_text_changed_plus(QString s);
    void download_file_ysf(QString f);
    void update_files();
    void download_file_dmr(QString f);
    void download_file_m17(QString f);
    void download_file_dcs(QString f);
    void download_file_dmr_ids(QString f);
    void load_initial_settings();
    void process_settings(QString path);
    void about();
    void updateTime();
    void start(bool checked);
    void cleanDmrLog();
    void cleanDmrPlusLog();
    void cleanYsfLog();
    void cleanDcsLog();
    void cleanM17Log();
    void stopAllTx();
};

#endif // DIGIONE_H
