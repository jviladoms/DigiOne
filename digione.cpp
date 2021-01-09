#include "digione.h"
#include "ui_digione.h"

#define ENDLINE "\n"

DigiOne::DigiOne(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Digione)
{
    dmr_muted = false;
    dmr_plus_muted = false;
    ysf_muted = false;
    m17_muted = false;
    dcs_muted = false;

    config_path = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
#ifndef Q_OS_WIN
    config_path += "/digione";
#endif
    if(!QDir(config_path).exists()){
        QDir().mkdir(config_path);
    }

    ui->setupUi(this);
    init_gui();
    discover_vocoders();
    process_dmr_hosts();
    process_ysf_hosts();
    qDebug() << "m17";
    process_m17_hosts();
        qDebug() << "dcs";
    process_dcs_hosts();
        qDebug() << "dmr_id";
    process_dmr_ids();
     qDebug() << "initial settings";
    load_initial_settings();
         qDebug() << "minimum size";
    this->window()->setMinimumSize(1800, 1200);
          qDebug() << "maximized";
    QWidget::showMaximized();
}

DigiOne::~DigiOne()
{
    save_settings(config_path + "/settings.conf");
    delete ui;
}

void DigiOne::load_initial_settings()
{
    process_settings(config_path + "/settings.conf");
}

void DigiOne::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");
    ui->lcdNumber->display(text);
    //ui->label_2->setText(text);
}

void DigiOne::process_settings(QString path)
{
    QFileInfo check_file(path);
    if(check_file.exists() && check_file.isFile()){
        QFile f(path);
        if(f.open(QIODevice::ReadOnly)){
            while(!f.atEnd()){
                QString s = f.readLine();
                QStringList sl = s.split(':');
                if(sl.at(0) == "PLAYBACK"){
                    ui->AudioOutCombo->setCurrentText(sl.at(1).simplified());
                }
                if(sl.at(0) == "CAPTURE"){
                    ui->AudioInCombo->setCurrentText(sl.at(1).simplified());
                }
                if(sl.at(0) == "DCSHOST"){
                    saved_dcshost = sl.at(1).simplified();
                    int i = ui->DCSServers->findText(saved_dcshost);
                    ui->DCSServers->setCurrentIndex(i);
                }
                if(sl.at(0) == "YSFHOST"){
                    saved_ysfhost = sl.at(1).simplified();
                    int i = ui->ysfservers->findText(saved_ysfhost);
                    ui->ysfservers->setCurrentIndex(i);
                }
                if(sl.at(0) == "DMRHOST"){
                    saved_dmrhost = sl.at(1).simplified();
                        int i = ui->dmrservers->findText(saved_dmrhost);
                        ui->dmrservers->setCurrentIndex(i);
                }
                if(sl.at(0) == "DMR_PLUS_HOST"){
                    int i = ui->dmrPlusServers->findText(sl.at(1).simplified());
                    ui->dmrPlusServers->setCurrentIndex(i);
                }

                if(sl.at(0) == "M17HOST"){
                    saved_m17host = sl.at(1).simplified();
                    int i = ui->m17servers->findText(saved_m17host);
                    ui->m17servers->setCurrentIndex(i);
                }

                if(sl.at(0) == "DCS_MODULE"){
                    ui->dcsComboMod->setCurrentText(sl.at(1).simplified());
                }
                if(sl.at(0) == "M17_MODULE"){
                    ui->m17comboMod->setCurrentText(sl.at(1).simplified());
                }
                if(sl.at(0) == "DMR_CALLSIGN"){
                    ui->dmrcallsign->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "DMR_PLUS_CALLSIGN"){
                    ui->dmrplusCallsign->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "YSF_CALLSIGN"){
                    ui->ysfcallsign->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "M17_CALLSIGN"){
                    ui->m17callsign->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "DCS_CALLSIGN"){
                    ui->dcsCallsign->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "DMRID"){
                    ui->dmrid->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "DMR_PLUS_ID"){
                    ui->dmridplus->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "DMR_ESSID"){
                    ui->essid->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "DMR_PLUS_ESSID"){
                    ui->essidplus->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "DMR_OPTIONS"){
                    ui->dmrOptions->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "DMR_PLUS_OPTIONS"){
                    ui->dmrOptionsPlus->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "DMRPASSWORD"){
                    ui->password->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "DMR_PLUS_PASSWORD"){
                    ui->passwordplus->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "DMRTGID"){
                    ui->talkgroup->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "DMR_PLUS_TGID"){
                    ui->talkgroupplus->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "MYCALL"){
                    ui->dcsCallsign->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "URCALL"){
                    ui->urcall->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "RPTR1"){
                    ui->rptr1->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "RPTR2"){
                    ui->rptr2->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "USRTXT"){
                    ui->usertext->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "LOCATION"){
                    ui->poblacio->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "LATITUDE"){
                    ui->latitud->setText(sl.at(1).simplified());
                }
                if(sl.at(0) == "LONGITUDE"){
                    ui->longitud->setText(sl.at(1).simplified());
                }
            }
        }
    }
}

void DigiOne::discover_vocoders()
{
    QMap<QString, QString> l = SerialAMBE::discover_devices();
    QMap<QString, QString>::const_iterator i = l.constBegin();
    ui->AmbeCombo->addItem("Programari vocoder", "");
    while (i != l.constEnd()) {
        ui->AmbeCombo->addItem(i.value(), i.key());
        ++i;
    }
}

void DigiOne::init_gui()
{
    QPalette palette;
    palette.setColor(QPalette::Base, QColor(40, 40, 40));
    palette.setColor(QPalette::Window, QColor(55, 55, 55));
    palette.setColor(QPalette::Button, QColor(49, 49, 49));
    palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    palette.setColor(QPalette::ButtonText, QColor(155, 155, 155));
    palette.setColor(QPalette::WindowText, QColor(155, 155, 155));
    palette.setColor(QPalette::Text, QColor(155, 155, 155));
    palette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    palette.setColor(QPalette::Link, QColor(42, 130, 218));
    palette.setColor(QPalette::Disabled, QPalette::Base, QColor(49, 49, 49));
    palette.setColor(QPalette::Disabled, QPalette::Text, QColor(90, 90, 90));
    palette.setColor(QPalette::Disabled, QPalette::Button, QColor(42, 42, 42));
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(90, 90, 90));
    palette.setColor(QPalette::Disabled, QPalette::Window, QColor(49, 49, 49));
    palette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(90, 90, 90));
    qApp->setPalette(palette);


    QTimer *timer = new QTimer(this);
    timer->start(1000);

    connect(timer, &QTimer::timeout, this, &DigiOne::showTime);
    connect(ui->connect, SIGNAL(clicked()), this, SLOT(process_dmr_connect()));
    connect(ui->dmrPlusConnect, SIGNAL(clicked()), this, SLOT(process_dmr_plus_connect()));
    connect(ui->ysfconnect, SIGNAL(clicked()), this, SLOT(process_ysf_connect()));
    connect(ui->m17connect, SIGNAL(clicked()), this, SLOT(process_m17_connect()));
    connect(ui->DCSConnect, SIGNAL(clicked()), this, SLOT(process_dcs_connect()));
    connect(ui->volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(process_volume_changed(int)));
    connect(ui->involSlider, SIGNAL(valueChanged(int)), this, SLOT(process_input_volume_changed(int)));
    connect(ui->muteInAll, SIGNAL(clicked()), this, SLOT(process_mute_in()));
    connect(ui->muteOutAll, SIGNAL(clicked()), this, SLOT(process_mute_out()));
    connect(ui->talkgroup, SIGNAL(textChanged(QString)), this, SLOT(tgid_text_changed(QString)));
    connect(ui->talkgroupplus, SIGNAL(textChanged(QString)), this, SLOT(tgid_text_changed_plus(QString)));
    connect(ui->dmrMute, SIGNAL(clicked()), this, SLOT(process_dmr_mute_channel()));
    connect(ui->dmrPlusMute, SIGNAL(clicked()), this, SLOT(process_dmr_plus_mute_channel()));
    connect(ui->ysfMute, SIGNAL(clicked()), this, SLOT(process_ysf_mute_channel()));
    connect(ui->m17Mute, SIGNAL(clicked()), this, SLOT(process_m17_mute_channel()));
    connect(ui->dcsMute, SIGNAL(clicked()), this, SLOT(process_dcs_mute_channel()));
    connect(ui->actionGuardar, SIGNAL(triggered()), this, SLOT(save_settings_from_menu()));
    connect(ui->actionObrir, SIGNAL(triggered()), this, SLOT(open_settings_from_menu()));
    connect(ui->actionSortir, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionQuant_a, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionUpdateFiles, SIGNAL(triggered()), this, SLOT(update_files()));
    connect(ui->Transmit, SIGNAL(clicked(bool)), this, SLOT(start(bool)));
    connect(ui->TransmitPlus, SIGNAL(clicked(bool)), this, SLOT(start(bool)));
    connect(ui->ysftransmit, SIGNAL(clicked(bool)), this, SLOT(start(bool)));
    connect(ui->m17transmit, SIGNAL(clicked(bool)), this, SLOT(start(bool)));
    connect(ui->dcsTransmit, SIGNAL(clicked(bool)), this, SLOT(start(bool)));
    connect(&t, SIGNAL(timeout()), this, SLOT(updateTime()));
    connect(&TxEOT, SIGNAL(timeout()), this, SLOT(stopAllTx()));


    connect(&dmrTimerReceived, SIGNAL(timeout()), this, SLOT(dmrChangeButtonColor()));
    connect(&dmrPlusTimerReceived, SIGNAL(timeout()), this, SLOT(dmrPlusChangeButtonColor()));
    connect(&ysfTimerReceived, SIGNAL(timeout()), this, SLOT(ysfChangeButtonColor()));
    connect(&dcsTimerReceived, SIGNAL(timeout()), this, SLOT(dcsChangeButtonColor()));
    connect(&m17TimerReceived, SIGNAL(timeout()), this, SLOT(m17ChangeButtonColor()));

    connect(ui->dmrDeleteLog, SIGNAL(clicked()), this, SLOT(cleanDmrLog()));
    connect(ui->dmrPlusDeleteLog, SIGNAL(clicked()), this, SLOT(cleanDmrPlusLog()));
    connect(ui->ysfDeleteLog, SIGNAL(clicked()), this, SLOT(cleanYsfLog()));
    connect(ui->dcsDeleteLog, SIGNAL(clicked()), this, SLOT(cleanDcsLog()));
    connect(ui->m17DeleteLog, SIGNAL(clicked()), this, SLOT(cleanM17Log()));

    for(char m = 0x41; m < 0x5b; ++m){
        ui->m17comboMod->addItem(QString(m));
        ui->dcsComboMod->addItem(QString(m));
    }

    ui->Transmit->setStyleSheet("QPushButton:enabled { background-color: rgb(128, 195, 66); color: rgb(0,0,0); } QPushButton:checked{ background-color: red; }");
    ui->TransmitPlus->setStyleSheet("QPushButton:enabled { background-color: rgb(128, 195, 66); color: rgb(0,0,0); } QPushButton:checked{ background-color: red; }");
    ui->ysftransmit->setStyleSheet("QPushButton:enabled { background-color: rgb(128, 195, 66); color: rgb(0,0,0); } QPushButton:checked{ background-color: red; }");
    ui->m17transmit->setStyleSheet("QPushButton:enabled { background-color: rgb(128, 195, 66); color: rgb(0,0,0); } QPushButton:checked{ background-color: red; }");
    ui->dcsTransmit->setStyleSheet("QPushButton:enabled { background-color: rgb(128, 195, 66); color: rgb(0,0,0); } QPushButton:checked{ background-color: red; }");
    ui->muteInAll->setStyleSheet("QPushButton:checked{ background-color: rgb(255, 255, 20); }");
    ui->muteOutAll->setStyleSheet("QPushButton:checked{ background-color: rgb(255, 255, 20); }");

    ui->dmrMute->setStyleSheet("QPushButton:checked{ background-color: rgb(255, 255, 20); }");
    ui->dmrPlusMute->setStyleSheet("QPushButton:checked{ background-color: rgb(255, 255, 20) }");
    ui->ysfMute->setStyleSheet("QPushButton:checked{ background-color: rgb(255, 255, 20); }");
    ui->m17Mute->setStyleSheet("QPushButton:checked{ background-color: rgb(255, 255, 20); }");
    ui->dcsMute->setStyleSheet("QPushButton:checked{ background-color: rgb(255, 255, 20); }");

    ui->lineEdit->setStyleSheet("QLineEdit:disabled{ background-color: rgb(55, 55, 55)" );
    ui->lineEdit_2->setStyleSheet("QLineEdit:disabled{ background-color: rgb(55, 55, 55)");
    ui->lineEdit_3->setStyleSheet("QLineEdit:disabled{ background-color: rgb(55, 55, 55)" );
    ui->lineEdit_4->setStyleSheet("QLineEdit:disabled{ background-color: rgb(55, 55, 55)" );
    ui->lineEdit_5->setStyleSheet("QLineEdit:disabled{ background-color: rgb(55, 55, 55)" );
    ui->lineEdit_6->setStyleSheet("QLineEdit:disabled{ background-color: rgb(55, 55, 55)");
    ui->lineEdit_7->setStyleSheet("QLineEdit:disabled{ background-color: rgb(55, 55, 55)" );
    ui->lineEdit_8->setStyleSheet("QLineEdit:disabled{ background-color: rgb(55, 55, 55)" );

    ui->dmrHistory->setStyleSheet("font-family: Courier;font-size: 10pt;font-weight: bold");
    ui->dmrPlusHistory->setStyleSheet("font-family: Courier;font-size: 10pt;font-weight: bold");
    ui->DCSHistory->setStyleSheet("font-family: Courier;font-size: 10pt;font-weight: bold");
    ui->ysfhistory->setStyleSheet("font-family: Courier;font-size: 10pt;font-weight: bold");
    ui->m17history->setStyleSheet("font-family: Courier;font-size: 10pt;font-weight: bold");

    ui->Transmit->setDisabled(true);
    ui->TransmitPlus->setDisabled(true);
    ui->ysftransmit->setDisabled(true);
    ui->m17transmit->setDisabled(true);
    ui->dcsTransmit->setDisabled(true);

    ui->volumeSlider->setRange(0, 100);
    ui->volumeSlider->setValue(100);

    ui->involSlider->setRange(0, 100);
    ui->involSlider->setValue(100);

    discover_vocoders();
    ui->AudioOutCombo->addItem("Per defecte");
    ui->AudioOutCombo->addItems(AudioEngine::discover_audio_devices(AUDIO_OUT));
    ui->AudioInCombo->addItem("Per defecte");
    ui->AudioInCombo->addItems(AudioEngine::discover_audio_devices(AUDIO_IN));

}

void DigiOne::stopAllTx(){
    if(ui->Transmit->isChecked()){
        ui->Transmit->click();
    }

    if(ui->TransmitPlus->isChecked()){
        ui->TransmitPlus->click();
    }

    if(ui->ysftransmit->isChecked()){
        ui->ysftransmit->click();
    }

    if(ui->m17transmit->isChecked()){
        ui->m17transmit->click();
    }

    if(ui->dcsTransmit->isChecked()){
        ui->dcsTransmit->click();
    }
}

void DigiOne::cleanDmrLog(){
    dmrList.clear();
    dmrModel.setStringList(dmrList);
    ui->dmrHistory->setModel(&dmrModel);
}

void DigiOne::cleanDmrPlusLog(){
    dmrPlusList.clear();
    dmrPlusModel.setStringList(dmrPlusList);
    ui->dmrPlusHistory->setModel(&dmrPlusModel);
}

void DigiOne::cleanYsfLog(){
    ysfList.clear();
    ysfModel.setStringList(ysfList);
    ui->ysfhistory->setModel(&ysfModel);
}

void DigiOne::cleanDcsLog(){
    dcsList.clear();
    dcsModel.setStringList(dcsList);
    ui->DCSHistory->setModel(&dcsModel);
}

void DigiOne::cleanM17Log(){
    m17List.clear();
    m17Model.setStringList(m17List);
    ui->m17history->setModel(&m17Model);
}

void DigiOne::about()
{
    QMessageBox::about(this, tr("Sobre DigiOne v1.2"),
                       tr("Aquesta es una distribució de l'eina DigiOne creada per Jordi Viladoms EA3IHG. \n\n S'ha creat a partir "
                          "d'un fork de l'eina dudestar i donant resposta de les funcionalitats i millores suggerides per radioaficionats de Catalunya.\n "
                          "Agraïment especial als companys Josep EA3FZS, Xavier EA3W per les hores de proves que han fet de l'aplicació, al company Jordi EA3FET pels seus consells de GUI i al company Jordi EA3HSL per el logo de l'aplicació. \n\n"
                          "Aquest programa és programari lliure. El podeu redistribuir i/o modificar sota els termes del GNU General Public "
                          "license publicada per la Free Software Foundation.\n Aquest programa es distribueix amb l'esperança que serà útil, però SENSE CAP GARANTIA,"
                          " sense ni tan sols la garantia implícita de COMERCIALITZACIÓ o IDONEITAT PER A FINALITAT PARTICULAR.\n Vegeu la llicència pública general de GNU per més detalls."
                          "Hauríeu d'haver rebut una còpia del GNU Llicència pública general juntament amb aquest programa. Si no, consulteu <http://www.gnu.org/licenses/>").arg(VERSION_NUMBER));

}

void DigiOne::updateTime() {
    if(cronoButton){
        cronoButton->setText(QTime(0, 0).addMSecs(startTime.elapsed()).toString());
    }
}

void DigiOne::start(bool checked) {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    cronoButton = button;
    if(checked){
      button->setText(QTime(0, 0).toString());
      startTime.restart();
      t.start(1000);
      if(!TxEOT.isActive()){
          TxEOT.start(183000);
      }
    } else {
      button->setText("PTT");
      t.stop();
      cronoButton = NULL;

      qDebug() << "object name " + button->objectName();

      if(button->objectName() == "TransmitPlus"){
          dmrPlusList.push_front(ui->dmrplusCallsign->text().leftJustified(10, ' ') + " - TG:" + ui->talkgroupplus->text().leftJustified(6, ' ') + " - Time: " + QTime::currentTime().toString());
          dmrPlusModel.setStringList(dmrPlusList);
          ui->dmrPlusHistory->setModel(&dmrPlusModel);
          dmr_plus_previous_src = ui->dmrplusCallsign->text();
      }

      if(button->objectName() == "Transmit"){
          dmrList.push_front(ui->dmrcallsign->text().leftJustified(10, ' ') + " - TG:" + ui->talkgroup->text().leftJustified(6, ' ') + " - Time: " + QTime::currentTime().toString());
          dmrModel.setStringList(dmrList);
          ui->dmrHistory->setModel(&dmrModel);
          dmr_previous_src = ui->dmrid->text();
      }

      if(button->objectName() == "ysftransmit"){
          ysfList.push_front(ui->ysfcallsign->text().leftJustified(10, ' ') + " - Time: " + QTime::currentTime().toString());
          ysfModel.setStringList(ysfList);
          ui->ysfhistory->setModel(&ysfModel);
          ysf_previous_src = ui->ysfcallsign->text();
      }

      if(!ui->Transmit->isChecked() &&
         !ui->TransmitPlus->isChecked() &&
         !ui->ysftransmit->isChecked() &&
         !ui->m17transmit->isChecked() &&
         !ui->dcsTransmit->isChecked()
      ){
         TxEOT.stop();
      }
    }
}

void DigiOne::process_mute_out()
{
    if(ui->muteOutAll->isChecked()){
        process_volume_changed(0);
    } else {
        process_volume_changed(ui->volumeSlider->value());
    }
}

void DigiOne::process_mute_in()
{
    if(ui->muteInAll->isChecked()){
        process_input_volume_changed(0);
    } else {
        process_input_volume_changed(ui->involSlider->value());
    }
}

void DigiOne::process_volume_changed(int v)
{
    qreal linear_vol = QAudio::convertVolume(v / qreal(100.0),QAudio::LogarithmicVolumeScale,QAudio::LinearVolumeScale);
    if(!dmr_muted){
        emit dmr_out_audio_vol_changed(linear_vol);
    }
    if(!dmr_plus_muted){
        emit dmr_plus_out_audio_vol_changed(linear_vol);
    }
    if(!ysf_muted){
        emit ysf_out_audio_vol_changed(linear_vol);
    }
    if(!m17_muted){
        emit m17_out_audio_vol_changed(linear_vol);
    }
    if(!dcs_muted){
        emit dcs_out_audio_vol_changed(linear_vol);
    }
}

void DigiOne::save_settings_from_menu(){
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Fitxer de configuració"), "",
        tr("DigiOne (*.dg1);;All Files (*)"));
    save_settings(fileName) ;
}

void DigiOne::open_settings_from_menu(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Fitxer de configuració"), "",
        tr("DigiOne (*.dg1);;All Files (*)"));
    process_settings(fileName) ;
}

void DigiOne::save_settings(QString path) {
    QFile f(path);
    f.open(QIODevice::WriteOnly);
    QTextStream stream(&f);
    stream << "PLAYBACK:" << ui->AudioOutCombo->currentText() << ENDLINE;
    stream << "CAPTURE:" << ui->AudioInCombo->currentText() << ENDLINE;
    stream << "DCSHOST:" << ui->DCSServers->currentText() << ENDLINE;
    stream << "YSFHOST:" << ui->ysfservers->currentText() << ENDLINE;
    stream << "DMRHOST:" << ui->dmrservers->currentText() << ENDLINE;
    stream << "DMR_PLUS_HOST:" << ui->dmrPlusServers->currentText() << ENDLINE;
    stream << "M17HOST:" << ui->m17servers->currentText() << ENDLINE;
    stream << "DCS_MODULE:" << ui->dcsComboMod->currentText() << ENDLINE;
    stream << "M17_MODULE:" << ui->m17comboMod->currentText() << ENDLINE;
    stream << "DMR_CALLSIGN:" << ui->dmrcallsign->text() << ENDLINE;
    stream << "DMR_PLUS_CALLSIGN:" << ui->dmrplusCallsign->text() << ENDLINE;
    stream << "YSF_CALLSIGN:" << ui->ysfcallsign->text() << ENDLINE;
    stream << "M17_CALLSIGN:" << ui->m17callsign->text() << ENDLINE;
    stream << "DCS_CALLSIGN:" << ui->dcsCallsign->text() << ENDLINE;
    stream << "DMRID:" << ui->dmrid->text() << ENDLINE;
    stream << "DMR_PLUS_ID:" << ui->dmridplus->text() << ENDLINE;
    stream << "DMR_PLUS_ESSID:" << ui->essidplus->text() << ENDLINE;
    stream << "DMR_ESSID:" << ui->essid->text() << ENDLINE;
    stream << "DMR_OPTIONS:" << ui->dmrOptions->text() << ENDLINE;
    stream << "DMR_PLUS_OPTIONS:" << ui->dmrOptionsPlus->text() << ENDLINE;
    stream << "DMRPASSWORD:" << ui->password->text() << ENDLINE;
    stream << "DMR_PLUS_PASSWORD:" << ui->passwordplus->text() << ENDLINE;
    stream << "DMRTGID:" << ui->talkgroup->text() << ENDLINE;
    stream << "DMR_PLUS_TGID:" << ui->talkgroupplus->text() << ENDLINE;
    stream << "MYCALL:" << ui->dcsCallsign->text().simplified() << ENDLINE;
    stream << "URCALL:" << ui->urcall->text().simplified() << ENDLINE;
    stream << "RPTR1:" << ui->rptr1->text().simplified() << ENDLINE;
    stream << "RPTR2:" << ui->rptr2->text().simplified() << ENDLINE;
    stream << "USRTXT:" << ui->usertext->text() << ENDLINE;
    stream << "LOCATION:" << ui->poblacio->text() << ENDLINE;
    stream << "LATITUDE:" << ui->latitud->text() << ENDLINE;
    stream << "LONGITUDE:" << ui->longitud->text() << ENDLINE;
    f.close();
}

void DigiOne::process_input_volume_changed(int v)
{
    qreal linear_vol = QAudio::convertVolume(v / qreal(100.0),QAudio::LogarithmicVolumeScale,QAudio::LinearVolumeScale);
        emit in_audio_vol_changed(linear_vol);
}

void DigiOne::process_dmr_mute_channel(){
    process_mute_channel("DMR");
}

void DigiOne::process_dmr_plus_mute_channel(){
    process_mute_channel("DMR_PLUS");
}

void DigiOne::process_ysf_mute_channel(){
    process_mute_channel("YSF");
}

void DigiOne::process_m17_mute_channel(){
    process_mute_channel("M17");
}

void DigiOne::process_dcs_mute_channel(){
    process_mute_channel("DCS");
}

void DigiOne::process_mute_channel(QString channel){
    int v = ui->volumeSlider->value();
    qreal linear_vol = QAudio::convertVolume(v / qreal(100.0),QAudio::LogarithmicVolumeScale,QAudio::LinearVolumeScale);

    qDebug() << "channel: " << channel;
    if(channel == "DMR"){
        if (dmr_muted == false){
            emit dmr_out_audio_vol_changed(0.0);
            dmr_muted = true;
        } else {
            emit dmr_out_audio_vol_changed(linear_vol);
            dmr_muted = false;
            ui->dmrMute->setText("Silenciar");
        }
    }

    if(channel == "DMR_PLUS"){
        if (dmr_plus_muted == false){
            emit dmr_plus_out_audio_vol_changed(0.0);
            dmr_plus_muted = true;
        } else {
            emit dmr_plus_out_audio_vol_changed(linear_vol);
            dmr_plus_muted = false;
            ui->dmrPlusMute->setText("Silenciar");
        }
    }

    if(channel == "YSF"){
        if (ysf_muted == false){
            emit ysf_out_audio_vol_changed(0.0);
            ysf_muted = true;
        } else {
            emit ysf_out_audio_vol_changed(linear_vol);
            ysf_muted = false;
            ui->ysfMute->setText("Silenciar");
        }
    }

    if(channel == "M17"){
        if (m17_muted == false){
            emit m17_out_audio_vol_changed(0.0);
            m17_muted = true;
        } else {
            emit m17_out_audio_vol_changed(linear_vol);
            m17_muted = false;
            ui->m17Mute->setText("Silenciar");
        }
    }

    if(channel == "DCS"){
        if (dcs_muted == false){
            emit dcs_out_audio_vol_changed(0.0);
            dcs_muted = true;
        } else {
            emit dcs_out_audio_vol_changed(linear_vol);
            dcs_muted = false;
            ui->dcsMute->setText("Silenciar");
        }
    }
}

void DigiOne::process_dmr_connect(){
    QString dmr_options;
    if(dmr_connection_status == DMR_CONNECTED_RW || dmr_connection_status == DMR_CONNECTING){
        m_modethread_dmr->quit();
        dmr_connection_status = DMR_DISCONNECTED;
        ui->connect->setText("Connectar");
        if(ui->Transmit->isChecked()){
            ui->Transmit->click();
        }
        if(ui->dmrMute->isChecked()){
            ui->dmrMute->click();
        }
        ui->Transmit->setDisabled(true);
        ui->dmrOptions->setDisabled(false);
        ui->dmrservers->setDisabled(false);
        ui->dmrcallsign->setDisabled(false);
        ui->dmrid->setDisabled(false);
        ui->password->setDisabled(false);
        ui->essid->setDisabled(false);
    } else {
        ui->connect->setText("Connectant");
        dmr_connection_status = DMR_CONNECTING;
        QStringList sl = ui->dmrservers->currentData().toString().simplified().split(':');
        QString host = sl.at(0).simplified();
        int port = sl.at(1).toInt();

        QString hostname = ui->dmrservers->currentText().simplified();
        QString callsign = ui->dmrcallsign->text().toUpper();
        uint32_t dmrid = ui->dmrid->text().toUInt();
        QString dmr_password = ui->password->text();
        uint32_t dmr_destid = ui->talkgroup->text().toUInt();
        QString dmr_repeater = ui->dmrid->text() + ui->essid->text();

        if(hostname.startsWith("DMR+")){
           dmr_options = ui->dmrOptions->text();
           m_dmr = new DMRCodec(callsign, dmrid, dmr_password, dmr_options, dmr_repeater.toUInt(), dmr_destid, host, port, ui->AmbeCombo->currentData().toString().simplified(), ui->AudioInCombo->currentText(), ui->AudioOutCombo->currentText(), hostname, ui->poblacio->text(), ui->latitud->text(), ui->longitud->text());
        } else {
           dmr_options = "";
           m_dmr = new DMRCodec(callsign, dmrid, dmr_password, dmr_options, dmr_repeater.toUInt(), dmr_destid, host, port, ui->AmbeCombo->currentData().toString().simplified(), ui->AudioInCombo->currentText(), ui->AudioOutCombo->currentText(), hostname, ui->poblacio->text(), ui->latitud->text(), ui->longitud->text());
        }

        m_modethread_dmr = new QThread;
        m_dmr->moveToThread(m_modethread_dmr);
        connect(m_dmr, SIGNAL(update_sound()), this, SLOT(update_sound_dmr_data()));
        connect(m_dmr, SIGNAL(update()), this, SLOT(update_dmr_data()));
        connect(m_modethread_dmr, SIGNAL(started()), m_dmr, SLOT(send_connect()));
        connect(m_modethread_dmr, SIGNAL(finished()), m_dmr, SLOT(deleteLater()));
        connect(ui->dmrPrivateCall, SIGNAL(stateChanged(int)), m_dmr, SLOT(dmrpc_state_changed(int)));
        connect(this, SIGNAL(input_source_changed(int, QString)), m_dmr, SLOT(input_src_changed(int, QString)));
        connect(this, SIGNAL(dmr_tgid_changed(unsigned int)), m_dmr, SLOT(dmr_tgid_changed(unsigned int)));
        connect(ui->Transmit, SIGNAL(clicked()), m_dmr, SLOT(tx_management()));
        connect(this, SIGNAL(dmr_out_audio_vol_changed(qreal)), m_dmr, SLOT(out_audio_vol_changed(qreal)));
        connect(this, SIGNAL(in_audio_vol_changed(qreal)), m_dmr, SLOT(in_audio_vol_changed(qreal)));
        m_modethread_dmr->start();
    }
}

void DigiOne::update_dmr_data(){
    if(m_dmr->get_status() == DMR_CONNECTED_RW){
        dmr_connection_status = DMR_CONNECTED_RW;
        ui->connect->setText("Desconnectar");
        ui->Transmit->setDisabled(false);
        ui->dmrOptions->setDisabled(true);
        ui->dmrservers->setDisabled(true);
        ui->dmrcallsign->setDisabled(true);
        ui->dmrid->setDisabled(true);
        ui->password->setDisabled(true);
        ui->essid->setDisabled(true);
    }
}

void DigiOne::update_sound_dmr_data(){
    dmr_src = QString::number(m_dmr->get_src());
    if(dmr_src != dmr_previous_src && m_dmrids[m_dmr->get_src()] != ""){
        dmrList.push_front(m_dmrids[m_dmr->get_src()].leftJustified(10, ' ') + " - TG:" + QString::number(m_dmr->get_dst()).leftJustified(6, ' ') + " - Time: " + QTime::currentTime().toString());
        dmrModel.setStringList(dmrList);
        ui->dmrHistory->setModel(&dmrModel);
        dmr_previous_src = dmr_src;
    }

    dmrTimerReceived.start(1000);
    ui->dmrLabel->setStyleSheet("background-color: rgb(0,255,0)");

    ui->dmrLast->setText("Rebent Àudio...");
    ui->dmrPlusLast->setText("");
    ui->ysfLast->setText("");
    ui->dcsLast->setText("");
    ui->m17Last->setText("");

}

void DigiOne::process_dcs_connect(){
    if(dcs_connection_status == DCS_CONNECTED_RW || dcs_connection_status == DCS_CONNECTING){
        m_modethread_dcs->quit();
        dcs_connection_status = DCS_DISCONNECTED;
        ui->DCSConnect->setText("Connectar");
        if(ui->dcsTransmit->isChecked()){
            ui->dcsTransmit->click();
        }
        if(ui->dcsMute->isChecked()){
            ui->dcsMute->click();
        }
        ui->dcsTransmit->setDisabled(true);
        ui->DCSServers->setDisabled(false);
    } else {
        dcs_connection_status = DCS_CONNECTING;
        ui->DCSConnect->setText("Connectant");
        QStringList sl = ui->DCSServers->currentData().toString().simplified().split(':');
        QString host = sl.at(0).simplified();
        int port = sl.at(1).toInt();

        QString callsign = ui->dcsCallsign->text().toUpper();
        QString hostname = ui->DCSServers->currentText().simplified();

        m_dcs = new DCSCodec(callsign, hostname, host, port, ui->AmbeCombo->currentData().toString().simplified(), ui->AudioInCombo->currentText(), ui->AudioOutCombo->currentText());
        m_modethread_dcs = new QThread;
        m_dcs->moveToThread(m_modethread_dcs);

        connect(m_dcs, SIGNAL(update_sound()), this, SLOT(update_sound_dcs_data()));
        connect(m_dcs, SIGNAL(update()), this, SLOT(update_dcs_data()));
        connect(m_modethread_dcs, SIGNAL(started()), m_dcs, SLOT(send_connect()));
        connect(m_modethread_dcs, SIGNAL(finished()), m_dcs, SLOT(deleteLater()));
        connect(this, SIGNAL(input_source_changed(int, QString)), m_dcs, SLOT(input_src_changed(int, QString)));
        connect(ui->dcsComboMod, SIGNAL(currentIndexChanged(int)), m_dcs, SLOT(module_changed(int)));
        connect(ui->dcsCallsign, SIGNAL(textChanged(QString)), m_dcs, SLOT(mycall_changed(QString)));
        connect(ui->urcall, SIGNAL(textChanged(QString)), m_dcs, SLOT(urcall_changed(QString)));
        connect(ui->rptr1, SIGNAL(textChanged(QString)), m_dcs, SLOT(rptr1_changed(QString)));
        connect(ui->rptr2, SIGNAL(textChanged(QString)), m_dcs, SLOT(rptr2_changed(QString)));
        connect(ui->dcsTransmit, SIGNAL(clicked()), m_dcs, SLOT(tx_management()));
        connect(this, SIGNAL(dcs_out_audio_vol_changed(qreal)), m_dcs, SLOT(out_audio_vol_changed(qreal)));
        connect(this, SIGNAL(in_audio_vol_changed(qreal)), m_dcs, SLOT(in_audio_vol_changed(qreal)));
        emit ui->dcsComboMod->currentIndexChanged(ui->dcsComboMod->currentIndex());
        emit ui->dcsCallsign->textChanged(ui->dcsCallsign->text());
        emit ui->urcall->textChanged(ui->urcall->text());
        emit ui->rptr1->textChanged(ui->rptr1->text());
        emit ui->rptr2->textChanged(ui->rptr2->text());
        m_modethread_dcs->start();
    }
}

void DigiOne::update_dcs_data(){
    if(m_dcs->get_status() == DCS_CONNECTED_RW){
        dcs_connection_status = DCS_CONNECTED_RW;
        ui->DCSConnect->setText("Desconnectar");
        ui->dcsTransmit->setDisabled(false);
        ui->DCSServers->setDisabled(true);
    }
}

void DigiOne::update_sound_dcs_data(){
    dcs_src = m_dcs->get_mycall();
    if(dcs_src != dcs_previous_src){
        dcsList.push_front(dcs_src + " - Time: " + QTime::currentTime().toString());
        dcsModel.setStringList(dcsList);
        ui->DCSHistory->setModel(&dcsModel);

        dcs_previous_src = dcs_src;
    }

    dcsTimerReceived.start(1000);
    ui->dcsLabel->setStyleSheet("background-color: rgb(0,255,0)");

    ui->dmrLast->setText("");
    ui->dmrPlusLast->setText("");
    ui->ysfLast->setText("");
    ui->dcsLast->setText("Rebent Àudio...");
    ui->m17Last->setText("");
}

void DigiOne::process_dmr_plus_connect(){
    QString dmr_options;
    if(dmr_plus_connection_status == DMR_PLUS_CONNECTED_RW || dmr_plus_connection_status == DMR_PLUS_CONNECTING){
        m_dmr_plus->send_disconnect();
        m_modethread_dmr_plus->quit();
        dmr_plus_connection_status = DMR_PLUS_DISCONNECTED;
        ui->dmrPlusConnect->setText("Connectar");
        if(ui->TransmitPlus->isChecked()){
            ui->TransmitPlus->click();
        }
        if(ui->dmrPlusMute->isChecked()){
            ui->dmrPlusMute->click();
        }
        ui->TransmitPlus->setDisabled(true);
        ui->dmrOptionsPlus->setDisabled(false);
        ui->dmrPlusServers->setDisabled(false);
        ui->dmrplusCallsign->setDisabled(false);
        ui->dmridplus->setDisabled(false);
        ui->passwordplus->setDisabled(false);
        ui->essidplus->setDisabled(false);
    } else {
        QStringList sl = ui->dmrPlusServers->currentData().toString().simplified().split(':');
        dmr_plus_connection_status = DMR_PLUS_CONNECTING;
        ui->dmrPlusConnect->setText("Connectant");
        QString host = sl.at(0).simplified();
        int port = sl.at(1).toInt();

        QString hostname = ui->dmrPlusServers->currentText().simplified();
        QString callsign = ui->dmrplusCallsign->text().toUpper();
        uint32_t dmrid = ui->dmridplus->text().toUInt();
        QString dmr_password = ui->passwordplus->text();
        uint32_t dmr_destid = ui->talkgroupplus->text().toUInt();
        QString dmr_repeater = ui->dmridplus->text() + ui->essidplus->text();

        if(hostname.startsWith("DMR+")){
           dmr_options = ui->dmrOptionsPlus->text();
           m_dmr_plus = new DMRCodec(callsign, dmrid, dmr_password, dmr_options, dmr_repeater.toUInt(), dmr_destid, host, port, ui->AmbeCombo->currentData().toString().simplified(), ui->AudioInCombo->currentText(), ui->AudioOutCombo->currentText(), hostname, ui->poblacio->text(), ui->latitud->text(), ui->longitud->text());
        } else {
           dmr_options = "";
           m_dmr_plus = new DMRCodec(callsign, dmrid, dmr_password, dmr_options, dmr_repeater.toUInt(), dmr_destid, host, port, ui->AmbeCombo->currentData().toString().simplified(), ui->AudioInCombo->currentText(), ui->AudioOutCombo->currentText(), hostname, ui->poblacio->text(), ui->latitud->text(), ui->longitud->text());
        }

        m_modethread_dmr_plus = new QThread;
        m_dmr_plus->moveToThread(m_modethread_dmr_plus);
        connect(m_dmr_plus, SIGNAL(update_sound()), this, SLOT(update_sound_dmr_plus_data()));
        connect(m_dmr_plus, SIGNAL(update()), this, SLOT(update_dmr_plus_data()));
        connect(m_modethread_dmr_plus, SIGNAL(started()), m_dmr_plus, SLOT(send_connect()));
        connect(m_modethread_dmr_plus, SIGNAL(finished()), m_dmr_plus, SLOT(deleteLater()));
        connect(ui->dmrPlusPrivateCall, SIGNAL(stateChanged(int)), m_dmr_plus, SLOT(dmrpc_state_changed(int)));
        connect(this, SIGNAL(input_source_changed(int, QString)), m_dmr_plus, SLOT(input_src_changed(int, QString)));
        connect(this, SIGNAL(dmr_tgid_changed_plus(unsigned int)), m_dmr_plus, SLOT(dmr_tgid_changed(unsigned int)));
        connect(ui->TransmitPlus, SIGNAL(clicked()), m_dmr_plus, SLOT(tx_management()));
        connect(this, SIGNAL(dmr_plus_out_audio_vol_changed(qreal)), m_dmr_plus, SLOT(out_audio_vol_changed(qreal)));
        connect(this, SIGNAL(in_audio_vol_changed(qreal)), m_dmr_plus, SLOT(in_audio_vol_changed(qreal)));
        m_modethread_dmr_plus->start();
   }
}

void DigiOne::update_dmr_plus_data(){
    if(m_dmr_plus->get_status() == DMR_PLUS_CONNECTED_RW){
        dmr_plus_connection_status = DMR_PLUS_CONNECTED_RW;
        ui->dmrPlusConnect->setText("Desconnectar");
        ui->TransmitPlus->setDisabled(false);
        ui->dmrOptionsPlus->setDisabled(true);
        ui->dmrPlusServers->setDisabled(true);
        ui->dmrplusCallsign->setDisabled(true);
        ui->dmridplus->setDisabled(true);
        ui->passwordplus->setDisabled(true);
        ui->essidplus->setDisabled(true);
    }
}

void DigiOne::update_sound_dmr_plus_data(){
    dmr_plus_src = QString::number(m_dmr_plus->get_src());

    if(dmr_plus_src != dmr_plus_previous_src && m_dmrids[m_dmr_plus->get_src()] != ""){
        dmrPlusList.push_front(m_dmrids[m_dmr_plus->get_src()].leftJustified(10, ' ') + " - TG:" + QString::number(m_dmr_plus->get_dst()).leftJustified(6, ' ') + " - Time: " + QTime::currentTime().toString());
        dmrPlusModel.setStringList(dmrPlusList);
        ui->dmrPlusHistory->setModel(&dmrPlusModel);

        dmr_plus_previous_src = dmr_plus_src;
    }

    dmrPlusTimerReceived.start(1000);
    ui->dmrPlusLabel->setStyleSheet("background-color: rgb(0,255,0)");

    ui->dmrLast->setText("");
    ui->dmrPlusLast->setText("Rebent Àudio...");
    ui->ysfLast->setText("");
    ui->dcsLast->setText("");
    ui->m17Last->setText("");

}

void DigiOne::process_ysf_connect(){
    if(ysf_connection_status == YSF_CONNECTED_RW || ysf_connection_status == YSF_CONNECTING){
        m_modethread_ysf->quit();
        ysf_connection_status = YSF_DISCONNECTED;
        ui->ysfconnect->setText("Connectar");
        if(ui->ysftransmit->isChecked()){
            ui->ysftransmit->click();
        }
        if(ui->ysfMute->isChecked()){
            ui->ysfMute->click();
        }
        ui->ysftransmit->setDisabled(true);
        ui->ysfcallsign->setDisabled(false);
        ui->ysfservers->setDisabled(false);
    } else {
        ysf_connection_status = YSF_CONNECTING;
        ui->ysfconnect->setText("Connectant");
        QStringList sl = ui->ysfservers->currentData().toString().simplified().split(':');
        QString host = sl.at(0).simplified();
        int port = sl.at(1).toInt();

        QString callsign = ui->ysfcallsign->text();
        QString hostname = ui->ysfservers->currentText().simplified();

        m_ysf = new YSFCodec(callsign, hostname, host, port, ui->AmbeCombo->currentData().toString().simplified(), ui->AudioInCombo->currentText(), ui->AudioOutCombo->currentText());
        m_modethread_ysf = new QThread;
        m_ysf->moveToThread(m_modethread_ysf);

        connect(m_ysf, SIGNAL(update_sound()), this, SLOT(update_sound_ysf_data()));
        connect(m_ysf, SIGNAL(update()), this, SLOT(update_ysf_data()));
        connect(m_modethread_ysf, SIGNAL(started()), m_ysf, SLOT(send_connect()));
        connect(m_modethread_ysf, SIGNAL(finished()), m_ysf, SLOT(deleteLater()));
        connect(this, SIGNAL(input_source_changed(int, QString)), m_ysf, SLOT(input_src_changed(int, QString)));
        connect(ui->ysftransmit, SIGNAL(clicked()), m_ysf, SLOT(tx_management()));
        connect(this, SIGNAL(ysf_out_audio_vol_changed(qreal)), m_ysf, SLOT(out_audio_vol_changed(qreal)));
        connect(this, SIGNAL(in_audio_vol_changed(qreal)), m_ysf, SLOT(in_audio_vol_changed(qreal)));
        m_modethread_ysf->start();
    }
}

void DigiOne::update_sound_ysf_data(){
    ysf_src = m_ysf->get_src();

    if((ysf_src != ysf_previous_src) && !ysf_src.isEmpty() && ysf_src.isSimpleText()){
        ysfList.push_front(m_ysf->get_src().leftJustified(10, ' ') + " - Time: " + QTime::currentTime().toString());
        ysfModel.setStringList(ysfList);
        ui->ysfhistory->setModel(&ysfModel);

        ysf_previous_src = ysf_src;
    }

    ysfTimerReceived.start(1000);
    ui->ysfLabel->setStyleSheet("background-color: rgb(0,255,0)");

    ui->dmrLast->setText("");
    ui->dmrPlusLast->setText("");
    ui->ysfLast->setText("Rebent Àudio...");
    ui->dcsLast->setText("");
    ui->m17Last->setText("");
}

void DigiOne::update_ysf_data(){
    if(m_ysf->get_status() == YSF_CONNECTED_RW){
        ysf_connection_status = YSF_CONNECTED_RW;
        ui->ysfconnect->setText("Desconnectar");
        ui->ysftransmit->setDisabled(false);
        ui->ysfcallsign->setDisabled(true);
        ui->ysfservers->setDisabled(true);
    }
}

void DigiOne::process_m17_connect(){
    if(m17_connection_status == M17_CONNECTED_RW || m17_connection_status == M17_CONNECTING){
        m_modethread_m17->quit();
        m17_connection_status = M17_DISCONNECTED;
        ui->m17connect->setText("Connectar");
        if(ui->m17transmit->isChecked()){
            ui->m17transmit->click();
        }
        if(ui->m17Mute->isChecked()){
            ui->m17Mute->click();
        }
        ui->m17transmit->setDisabled(true);
        ui->m17callsign->setDisabled(false);
        ui->m17comboMod->setDisabled(false);
        ui->m17servers->setDisabled(false);
    } else {
        ui->m17connect->setText("Connectant");
        QStringList sl = ui->m17servers->currentData().toString().simplified().split(':');
        m17_connection_status = M17_CONNECTING;
        QString host = sl.at(0).simplified();
        int port = sl.at(1).toInt();

        QString hostname = ui->m17servers->currentText().simplified();
        QString callsign = ui->m17callsign->text().toUpper();
        char module = ui->m17comboMod->currentText().toStdString()[0];
        m_m17 = new M17Codec(callsign, module, hostname, host, port, ui->AudioInCombo->currentText(), ui->AudioOutCombo->currentText());
        m_modethread_m17 = new QThread;
        m_m17->moveToThread(m_modethread_m17);
        connect(m_m17, SIGNAL(update()), this, SLOT(update_m17_data()));
        connect(m_m17, SIGNAL(update_sound()), this, SLOT(update_sound_m17_data()));
        connect(m_modethread_m17, SIGNAL(started()), m_m17, SLOT(send_connect()));
        connect(m_modethread_m17, SIGNAL(finished()), m_m17, SLOT(deleteLater()));
        connect(this, SIGNAL(input_source_changed(int, QString)), m_m17, SLOT(input_src_changed(int, QString)));
        connect(ui->m17transmit, SIGNAL(clicked()), m_m17, SLOT(tx_management()));
        connect(this, SIGNAL(m17_out_audio_vol_changed(qreal)), m_m17, SLOT(out_audio_vol_changed(qreal)));
        connect(this, SIGNAL(in_audio_vol_changed(qreal)), m_m17, SLOT(in_audio_vol_changed(qreal)));
        m_modethread_m17->start();
    }
}

void DigiOne::update_sound_m17_data(){
    m17_src = m_m17->get_src();

    if((m17_src != m17_previous_src) && !m17_src.isEmpty()){
        m17List.push_front(m_m17->get_src() + " - Time: " + QTime::currentTime().toString());
        m17Model.setStringList(m17List);
        ui->m17history->setModel(&m17Model);

        m17_previous_src = m17_src;
    }

    m17TimerReceived.start(1000);
    ui->m17Label->setStyleSheet("background-color: rgb(0,255,0)");

    ui->dmrLast->setText("");
    ui->dmrPlusLast->setText("");
    ui->ysfLast->setText("");
    ui->dcsLast->setText("");
    ui->m17Last->setText("Rebent Àudio...");
}

void DigiOne::update_m17_data(){
    if(m_m17->get_status() == M17_CONNECTED_RW){
        m17_connection_status = M17_CONNECTED_RW;
        ui->m17connect->setText("Desconnectar");
        ui->m17transmit->setDisabled(false);
        ui->m17callsign->setDisabled(true);
        ui->m17comboMod->setDisabled(true);
        ui->m17servers->setDisabled(true);
    }
}

void DigiOne::tgid_text_changed(QString s)
{
    qDebug() << "dmrid_text_changed() called s == " << s;
    emit dmr_tgid_changed(s.toUInt());
}

void DigiOne::tgid_text_changed_plus(QString s)
{
    qDebug() << "dmrid_text_changed() called s == " << s;
    emit dmr_tgid_changed_plus(s.toUInt());
}

void DigiOne::dmrChangeButtonColor(){
    dmrTimerReceived.stop();
    ui->dmrLabel->setStyleSheet("background-color: rgb(55, 55, 55)");
    ui->dmrLast->setText("Última recepció");
    ui->dmrPlusLast->setText("");
    ui->ysfLast->setText("");
    ui->dcsLast->setText("");
    ui->m17Last->setText("");
}

void DigiOne::dmrPlusChangeButtonColor(){
    dmrPlusTimerReceived.stop();
    ui->dmrPlusLabel->setStyleSheet("background-color: rgb(55, 55, 55)");
    ui->dmrPlusLast->setText("Última recepció");
    ui->ysfLast->setText("");
    ui->dcsLast->setText("");
    ui->m17Last->setText("");
    ui->dmrLast->setText("");
}

void DigiOne::ysfChangeButtonColor(){
    ysfTimerReceived.stop();
    ui->ysfLabel->setStyleSheet("background-color: rgb(55, 55, 55)");
    ui->ysfLast->setText("Última recepció");
    ui->dmrPlusLast->setText("");
    ui->dcsLast->setText("");
    ui->m17Last->setText("");
    ui->dmrLast->setText("");
}

void DigiOne::dcsChangeButtonColor(){
    dcsTimerReceived.stop();
    ui->dcsLabel->setStyleSheet("background-color: rgb(55, 55, 55)");
    ui->dcsLast->setText("Última recepció");
    ui->dmrPlusLast->setText("");
    ui->ysfLast->setText("");
    ui->m17Last->setText("");
    ui->dmrLast->setText("");
}

void DigiOne::m17ChangeButtonColor(){
    m17TimerReceived.stop();
    ui->m17Label->setStyleSheet("background-color: rgb(55, 55, 55)");
    ui->m17Last->setText("Última recepció");
    ui->dmrPlusLast->setText("");
    ui->ysfLast->setText("");
    ui->dcsLast->setText("");
    ui->dmrLast->setText("");
}

void DigiOne::process_dmr_ids()
{
    QFileInfo check_file(config_path + "/DMRIDs.dat");
    if(check_file.exists() && check_file.isFile()){
        QFile f(config_path + "/DMRIDs.dat");
        if(f.open(QIODevice::ReadOnly)){
            while(!f.atEnd()){
                QString l = f.readLine();
                if(l.at(0) == '#'){
                    continue;
                }
                QStringList ll = l.simplified().split(' ');
                //qDebug() << ll.at(0).simplified() << " " <<  ll.at(2) + ":" + ll.at(4);
                m_dmrids[ll.at(0).toUInt()] = ll.at(1);
            }
        }
        f.close();
    }
    else{
        download_file_dmr_ids("/DMRIDs.dat");
    }
}

void DigiOne::process_ysf_hosts()
{
    QMap<QString, QString> hostmap;
    QFileInfo check_file(config_path + "/YSFHosts.txt");
    if(check_file.exists() && check_file.isFile()){
        qDebug() << "file ysfhosts exists";
        ui->ysfservers->blockSignals(true);
        QFile f(config_path + "/YSFHosts.txt");
        if(f.open(QIODevice::ReadOnly)){
            ui->ysfservers->clear();
            while(!f.atEnd()){
                QString l = f.readLine();
                if(l.at(0) == '#'){
                    continue;
                }
                QStringList ll = l.split(';');
                if(ll.size() > 4){
                    hostmap[ll.at(1).simplified() + " - " + ll.at(2).simplified()] = ll.at(3) + ":" + ll.at(4);
                }
            }
            QMap<QString, QString>::const_iterator i = hostmap.constBegin();
            while (i != hostmap.constEnd()) {
                ui->ysfservers->addItem(i.key(), i.value());
                ++i;
            }
        }
        f.close();
        if(saved_ysfhost.left(3) != "FCS"){
            int i = ui->ysfservers->findText(saved_ysfhost);
            ui->ysfservers->setCurrentIndex(i);
        }
        ui->ysfservers->blockSignals(false);
    }
    else{
        qDebug() << "downloading ysfhosts";
        download_file_ysf("/YSFHosts.txt");
    }
}

void DigiOne::process_m17_hosts()
{
    QMap<QString, QString> hostmap;
    QFileInfo check_file(config_path + "/M17Hosts.txt");
    if(check_file.exists() && check_file.isFile()){
        ui->m17servers->blockSignals(true);
        QFile f(config_path + "/M17Hosts.txt");
        if(f.open(QIODevice::ReadOnly)){
            ui->m17servers->clear();
            while(!f.atEnd()){
                QString l = f.readLine();
                if(l.at(0) == '#'){
                    continue;
                }
                QStringList ll = l.simplified().split(' ');
                if(ll.size() > 2){
                    hostmap[ll.at(0).simplified()] = ll.at(1) + ":" + ll.at(2);
                }
            }
            QMap<QString, QString>::const_iterator i = hostmap.constBegin();
            while (i != hostmap.constEnd()) {
                ui->m17servers->addItem(i.key(), i.value());
                ++i;
            }
        }
        f.close();

        int i = ui->m17servers->findText(saved_m17host);
        ui->m17servers->setCurrentIndex(i);
        ui->m17servers->blockSignals(false);
    }
    else{
        download_file_m17("/M17Hosts.txt");
    }
}

void DigiOne::process_dcs_hosts()
{
    QMap<QString, QString> hostmap;
    QFileInfo check_file(config_path + "/dcs.txt");
    if(check_file.exists() && check_file.isFile()){
        ui->DCSServers->blockSignals(true);
        QFile f(config_path + "/dcs.txt");
        if(f.open(QIODevice::ReadOnly)){
            ui->DCSServers->clear();
            while(!f.atEnd()){
                QString l = f.readLine();
                if(l.at(0) == '#'){
                    continue;
                }
                QStringList ll = l.split('\t');
                if(ll.size() > 1){
                    //ui->hostCombo->addItem(ll.at(0).simplified(), ll.at(1) + ":30051");
                    hostmap[ll.at(0).simplified()] = ll.at(1) + ":30051";
                }
            }
            QMap<QString, QString>::const_iterator i = hostmap.constBegin();
            while (i != hostmap.constEnd()) {
                ui->DCSServers->addItem(i.key(), i.value());
                ++i;
            }
        }
        f.close();
        int i = ui->DCSServers->findText(saved_dcshost);
        ui->DCSServers->setCurrentIndex(i);
        ui->DCSServers->blockSignals(false);
    }
    else{
        download_file_dcs("/dcs.txt");
    }
}

void DigiOne::process_dmr_hosts()
{
    QMap<QString, QString> hostmap;
    QFileInfo check_file(config_path + "/DMRHosts.txt");
    if(check_file.exists() && check_file.isFile()){
        ui->dmrservers->blockSignals(true);
        QFile f(config_path + "/DMRHosts.txt");
        if(f.open(QIODevice::ReadOnly)){
            ui->dmrservers->clear();
            while(!f.atEnd()){
                QString l = f.readLine();
                if(l.at(0) == '#'){
                    continue;
                }
                QStringList ll = l.simplified().split(' ');
                if(ll.size() > 4){
                    //qDebug() << ll.at(0).simplified() << " " <<  ll.at(2) + ":" + ll.at(4);
                    if( (ll.at(0).simplified() != "DMRGateway")
                     && (ll.at(0).simplified() != "DMR2YSF")
                     && (ll.at(0).simplified() != "DMR2NXDN"))
                    {
                        hostmap[ll.at(0).simplified()] = ll.at(2) + ":" + ll.at(4) + ":" + ll.at(3);
                    }
                }
            }
            QMap<QString, QString>::const_iterator i = hostmap.constBegin();
            while (i != hostmap.constEnd()) {
                ui->dmrservers->addItem(i.key(), i.value());
                ui->dmrPlusServers->addItem(i.key(), i.value());
                ++i;
            }
        }
        f.close();
        qDebug() << "saved_dmrhost == " << saved_dmrhost;
        int i = ui->dmrservers->findText(saved_dmrhost);
        ui->dmrservers->setCurrentIndex(i);
        ui->dmrservers->blockSignals(false);
    }
    else{
        qDebug() << "downloading dmrhosts";
        download_file_dmr("/DMRHosts.txt");
    }
}

void DigiOne::update_files(){
    download_file_dmr("/DMRHosts.txt");
    download_file_dcs("/dcs.txt");
    download_file_m17("/M17Hosts.txt");
    download_file_ysf("/YSFHosts.txt");
    download_file_ysf("/YSFHosts.txt");
    download_file_dmr_ids("/DMRIDs.dat");

    QMessageBox::information(this,tr("Fitxers Actualitzats"),"Tots els fitxers de servidors i IDs s'han actualitzat");
}

void DigiOne::download_file_ysf(QString f)
{
    HttpManager *http = new HttpManager(f);
    QThread *httpThread = new QThread;
    http->moveToThread(httpThread);
    connect(httpThread, SIGNAL(started()), http, SLOT(process()));
    connect(http, SIGNAL(file_downloaded(QString)), this, SLOT(process_ysf_hosts()));
    connect(httpThread, SIGNAL(finished()), http, SLOT(deleteLater()));
    httpThread->start();
}

void DigiOne::download_file_dmr(QString f)
{
    HttpManager *http = new HttpManager(f);
    QThread *httpThread = new QThread;
    http->moveToThread(httpThread);
    connect(httpThread, SIGNAL(started()), http, SLOT(process()));
    connect(http, SIGNAL(file_downloaded(QString)), this, SLOT(process_dmr_hosts()));
    connect(httpThread, SIGNAL(finished()), http, SLOT(deleteLater()));
    httpThread->start();
}

void DigiOne::download_file_m17(QString f)
{
    HttpManager *http = new HttpManager(f);
    QThread *httpThread = new QThread;
    http->moveToThread(httpThread);
    connect(httpThread, SIGNAL(started()), http, SLOT(process()));
    connect(http, SIGNAL(file_downloaded(QString)), this, SLOT(process_m17_hosts()));
    connect(httpThread, SIGNAL(finished()), http, SLOT(deleteLater()));
    httpThread->start();
}

void DigiOne::download_file_dmr_ids(QString f)
{
    HttpManager *http = new HttpManager(f);
    QThread *httpThread = new QThread;
    http->moveToThread(httpThread);
    connect(httpThread, SIGNAL(started()), http, SLOT(process()));
    connect(http, SIGNAL(file_downloaded(QString)), this, SLOT(process_dmr_ids()));
    connect(httpThread, SIGNAL(finished()), http, SLOT(deleteLater()));
    httpThread->start();
}

void DigiOne::download_file_dcs(QString f)
{
    HttpManager *http = new HttpManager(f);
    QThread *httpThread = new QThread;
    http->moveToThread(httpThread);
    connect(httpThread, SIGNAL(started()), http, SLOT(process()));
    connect(http, SIGNAL(file_downloaded(QString)), this, SLOT(process_dcs_hosts()));
    connect(httpThread, SIGNAL(finished()), http, SLOT(deleteLater()));
    httpThread->start();
}


