QT       += core gui serialport network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = digione
TEMPLATE = app
VERSION_BUILD='$(shell cd $$PWD;git rev-parse --short HEAD)'
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += VERSION_NUMBER=\"\\\"$${VERSION_BUILD}\\\"\"
#DEFINES += USE_FLITE
DEFINES += USE_SWTX
CONFIG += c++11

SOURCES += \
        dmr/DMRFullLC.cpp \
        dmr/DMRLC.cpp \
        dmr/DMRShortLC.cpp \
        dmr/DMRSlotType.cpp \
        dmr/Log.cpp \
        dmr/QR1676.cpp \
        dmr/Utils.cpp \
        mbelib/ambe3600x2400.c \
        mbelib/ambe3600x2450.c \
        mbelib/ecc.c \
        mbelib/imbe7100x4400.c \
        mbelib/imbe7200x4400.c \
        mbelib/mbelib.c \
        mbelib/ambe.c \
        mbelib/mbedec.cpp \
        mbelib/mbeenc.cc \
        common/CRCenc.cpp \
        common/audioengine.cpp \
        common/chamming.cpp \
        common/httpmanager.cpp \
        common/serialambe.cpp \
        dmr/DMRData.cpp \
        dmr/dmrcodec.cpp \
        dmr/dmrcontrol.cpp \
        dmr/cbptc19696.cpp \
        dmr/cgolay2087.cpp \
        dmr/crs129.cpp \
        dmr/SHA256.cpp \
        ysf/Golay24128.cpp \
        ysf/YSFConvolution.cpp \
        ysf/YSFFICH.cpp \
        ysf/ysfcodec.cpp \
        codec2/codebooks.cpp \
        codec2/codec2.cpp \
        codec2/kiss_fft.cpp \
        codec2/lpc.cpp \
        codec2/nlp.cpp \
        codec2/pack.cpp \
        codec2/qbase.cpp \
        codec2/quantise.cpp \
        imbe_vocoder/aux_sub.cc \
        imbe_vocoder/basicop2.cc \
        imbe_vocoder/ch_decode.cc \
        imbe_vocoder/ch_encode.cc \
        imbe_vocoder/dc_rmv.cc \
        imbe_vocoder/decode.cc \
        imbe_vocoder/dsp_sub.cc \
        imbe_vocoder/encode.cc \
        imbe_vocoder/imbe_vocoder.cc \
        imbe_vocoder/math_sub.cc \
        imbe_vocoder/pe_lpf.cc \
        imbe_vocoder/pitch_est.cc \
        imbe_vocoder/pitch_ref.cc \
        imbe_vocoder/qnt_sub.cc \
        imbe_vocoder/rand_gen.cc \
        imbe_vocoder/sa_decode.cc \
        imbe_vocoder/sa_encode.cc \
        imbe_vocoder/sa_enh.cc \
        imbe_vocoder/tbls.cc \
        imbe_vocoder/uv_synt.cc \
        imbe_vocoder/v_synt.cc \
        imbe_vocoder/v_uv_det.cc \
        m17/m17codec.cpp \
        main.cpp \
        nxdn/nxdncodec.cpp \
        p25/p25codec.cpp \
        ref/refcodec.cpp \
        xrf/xrfcodec.cpp \
        dcs/dcscodec.cpp \
        digione.cpp

HEADERS += \
        dmr/DMRFullLC.h \
        dmr/DMRLC.h \
        dmr/DMRShortLC.h \
        dmr/DMRSlotType.h \
        dmr/Log.h \
        dmr/QR1676.h \
        dmr/Utils.h \
        mbelib/ambe3600x2400_const.h \
        mbelib/ambe3600x2450_const.h \
        mbelib/ecc_const.h \
        mbelib/imbe7200x4400_const.h \
        mbelib/mbelib.h \
        mbelib/mbelib_const.h \
        mbelib/ambe.h \
        mbelib/ambe3600x2250_const.h \
        mbelib/ambe3600x2400_const.h \
        mbelib/mbedec.h \
        mbelib/mbeenc.h \
        mbelib/mbelib_parms.h \
        common/CRCenc.h \
        common/serialambe.h \
        common/audioengine.h \
        common/chamming.h \
        dmr/DMRData.h \
        dmr/DMRDefines.h \
        dmr/dmrcodec.h \
        dmr/dmrcontrol.h \
        dmr/cbptc19696.h \
        dmr/cgolay2087.h \
        dmr/crs129.h \
        dmr/SHA256.h \
        ysf/Golay24128.h \
        ysf/YSFConvolution.h \
        ysf/YSFFICH.h \
        ysf/vocoder_tables.h \
        ysf/ysfcodec.h \
        codec2/codec2.h \
        codec2/codec2_internal.h \
        codec2/defines.h \
        codec2/kiss_fft.h \
        codec2/lpc.h \
        codec2/nlp.h \
        codec2/qbase.h \
        codec2/quantise.h \
        digione.h \
        common/httpmanager.h \
        imbe_vocoder/aux_sub.h \
        imbe_vocoder/basic_op.h \
        imbe_vocoder/ch_decode.h \
        imbe_vocoder/ch_encode.h \
        imbe_vocoder/dc_rmv.h \
        imbe_vocoder/decode.h \
        imbe_vocoder/dsp_sub.h \
        imbe_vocoder/encode.h \
        imbe_vocoder/globals.h \
        imbe_vocoder/imbe.h \
        imbe_vocoder/imbe_vocoder.h \
        imbe_vocoder/math_sub.h \
        imbe_vocoder/pe_lpf.h \
        imbe_vocoder/pitch_est.h \
        imbe_vocoder/pitch_ref.h \
        imbe_vocoder/qnt_sub.h \
        imbe_vocoder/rand_gen.h \
        imbe_vocoder/sa_decode.h \
        imbe_vocoder/sa_encode.h \
        imbe_vocoder/sa_enh.h \
        imbe_vocoder/tbls.h \
        imbe_vocoder/typedef.h \
        imbe_vocoder/typedefs.h \
        imbe_vocoder/uv_synt.h \
        imbe_vocoder/v_synt.h \
        imbe_vocoder/v_uv_det.h \
        m17/m17codec.h \
        nxdn/nxdncodec.h \
        p25/p25codec.h \
        ref/refcodec.h \
        xrf/xrfcodec.h \
        dcs/dcscodec.h

FORMS += \
    digione.ui

win32:QMAKE_LFLAGS += -static

QMAKE_LFLAGS_WINDOWS += --enable-stdcall-fixup

LIBS += -LC:\Qt\mbelib\build_x32 -LC:\Qt\mbelib\build_x64 -lmbe
contains(DEFINES, USE_FLITE){
	LIBS += -lflite_cmu_us_slt -lflite_cmu_us_kal16 -lflite_cmu_us_awb -lflite_cmu_us_rms -lflite_usenglish -lflite_cmulex -lflite -lasound
}
RC_ICONS = images/dstar.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    digione.qrc

DISTFILES +=
