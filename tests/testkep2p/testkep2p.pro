TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt




include (../../talk/talk_common.pri)

DESTDIR = $$output_dir/$$TARGET

message("DESTDIR is "$$DESTDIR)

INCLUDEPATH     +=  \
    ../../third_party/jsoncpp/overrides/include ../../third_party/jsoncpp/source/include \
    ../../third_party/cppzmq/include

win32 {
    #for zmqhelper
    DEFINES += __WINDOWS__ ZMQ_STATIC
    LIBS +=-lwinmm -liphlpapi -lcomsupp -lsecur32 -lws2_32  -lcrypt32 -lAdvapi32 -luser32
    LIBS += -lStrmiids -lshell32 -lrpcrt4
    LIBS += -L$$output_dir/libs
    LIBS += -ljsoncpp  -lcppzmq
    LIBS += -ljingle_app  -ljingle_p2p  -ljingle
} else {
    #QMAKE_CXXFLAGS += -std=c++11
    LIBS += -L$$output_dir/libs
    LIBS +=   -ljingle_app  -ljingle_p2p  -ljingle
    LIBS += -lcppzmq -ljsoncpp
    LIBS += -pthread -ldl
    #PRE_TARGETDEPS += $$DESTDIR/libjsoncpp.a $$DESTDIR/libjingle_p2p.a $$DESTDIR/libjingle.a $$DESTDIR/libjingle_app.a
}

SOURCES += main.cpp
