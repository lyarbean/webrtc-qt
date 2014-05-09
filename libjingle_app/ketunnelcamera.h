#ifndef KETUNNELCAMERA_H
#define KETUNNELCAMERA_H

#include "KeMsgProcess.h"




class KeTunnelCamera:public KeMsgProcessContainer{
    friend class KeMessageProcessCamera;
public:

    virtual void OnTunnelOpened(PeerTerminalInterface * t,
                                const std::string & peer_id);
    virtual void OnRouterMessage(const std::string &peer_id,
                                 const std::string &msg);
    virtual void SetVideoClarity(int);
    virtual int GetVideoClarity();
    virtual void SetPtz(std::string  ptz_key,int param);

protected:
    sigslot::signal2<const char *, int > SignalVideoData1;
    sigslot::signal2<const char *, int > SignalVideoData2;

    sigslot::signal2<const char *, int > SignalAudioData;
    virtual void OnRecvVideoClarity(std::string peer_id,int clarity);
    virtual void OnRecvRecordQuery(std::string peer_id, std::string condition);
    virtual void RecvGetWifiInfo(std::string peer_id);
    virtual void SetWifiInfo(std::string peer_id,std::string param);
    virtual void OnToPlayFile(const std::string &peer_id,
                              const std::string &filename);
    virtual void OnRecvTalkData(const std::string & peer_id,
                                const char * data,int len);

};



class KeMessageProcessCamera: public KeMsgProcess
{
public:
    KeMessageProcessCamera(std::string peer_id,KeTunnelCamera * container);
    void OnVideoData(const char *data, int len);
    void OnAudioData(const char * data,int len);
    void OnRecordData(const char * data,int len);

    sigslot::signal2<const std::string &,const std::string & > SignalToPlayFile;
    sigslot::signal3<const std::string &,const char *,int > SignalRecvTalkData;

protected:
    virtual void OnMessageRespond(talk_base::Buffer & msgData);
    virtual void RecvAskMediaMsg(talk_base::Buffer &msgData);
    virtual void RecvPlayFile(talk_base::Buffer &msgData);
    virtual void RecvTalkData(talk_base::Buffer &msgData);
private:
    bool video_started_;
    bool audio_started_;
    bool talk_started_;

};

#endif // KETUNNELCAMERA_H
