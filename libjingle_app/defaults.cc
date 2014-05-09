/*
 * libjingle
 * Copyright 2012, Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "defaults.h"

#include <stdlib.h>
#include <string.h>
#include <ctime>

#ifdef WIN32
#include <winsock2.h>
#else
#include <unistd.h>
#endif

#include "talk/base/common.h"
#include "talk/base/stream.h"
#include "talk/base/scoped_ptr.h"
#include "talk/base/pathutils.h"
#include "talk/base/fileutils.h"
#include "talk/base/timeutils.h"


const char kAudioLabel[] = "audio_label";
const char kVideoLabel[] = "video_label";
const char kStreamLabel[] = "stream_label";

const char kKaerMsgTypeName[] = "type";
const char kKaerMsgCommandName[] = "command";
const char kKaerTunnelMsgTypeValue[] = "tunnel";
const char kKaerPTZCommandValue[] = "ptz";


const uint16 kDefaultServerPort = 8888;

std::string GetEnvVarOrDefault(const char* env_var_name,
                               const char* default_value) {
    std::string value;
    const char* env_var = getenv(env_var_name);
    if (env_var)
        value = env_var;

    if (value.empty())
        value = default_value;

    return value;
}

std::string GetPeerConnectionString() {
    return GetEnvVarOrDefault("WEBRTC_CONNECT", "stun:stun.l.google.com:19302");
}

std::string GetDefaultServerName() {
    return GetEnvVarOrDefault("WEBRTC_SERVER", "localhost");
}

std::string GetPeerName() {
    char computer_name[256];
    if (gethostname(computer_name, ARRAY_SIZE(computer_name)) != 0)
        strcpy(computer_name, "host");
    std::string ret(GetEnvVarOrDefault("USERNAME", "user"));
    ret += '@';
    ret += computer_name;
    return ret;
}


std::string GetConfigFileString(std::string filename)
{
    std::string outstr;
    talk_base::Pathname path;
    bool result = talk_base::Filesystem::GetAppPathname(&path);
    if(!result){
        return false;
    }

    path.AppendPathname(filename);

    talk_base::scoped_ptr<talk_base::FileStream> config_stream;
    config_stream.reset( talk_base::Filesystem::OpenFile(path,"r")) ;

    if (!config_stream->Open(filename, "r+", NULL)) {
        return outstr;
    }
    size_t filesize;
    if(!config_stream->GetSize(&filesize)){
        return outstr;
    }

    char * filedata = new char[filesize+1];

    config_stream->Read(filedata,filesize,NULL,NULL);

    outstr = filedata;
    return outstr;

}


std::string GetAppFilePath(std::string filename)
{
    talk_base::Pathname path;
    bool result = talk_base::Filesystem::GetAppPathname(&path);
    if(!result){
        return "";
    }
    path.AppendPathname(filename);
    return path.pathname();
}
//// Split the message into two parts by the first delimiter.
//static bool SplitByDelimiter(const std::string& message,
//                             const char delimiter,
//                             std::string* field1,
//                             std::string* field2) {
//    // Find the first delimiter
//    size_t pos = message.find(delimiter);
//    if (pos == std::string::npos) {
//        return false;
//    }
//    *field1 = message.substr(0, pos);
//    // The rest is the value.
//    *field2 = message.substr(pos + 1);
//    return true;
//}


std::string GetCurrentDatetime(std::string format)
{
    std::string result;
    struct tm time;
    int microsecond;
    talk_base::CurrentTmTime(&time,&microsecond);
    char mbstr[100];

    if (strftime(mbstr, sizeof(mbstr), format.c_str(), &time)) {
        result = mbstr;
    }
    return result;
}
