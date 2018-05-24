/**
*
* Copyright ${YEAR}$ Future TV, Inc.
*
 * The contents of this file are subject to the terms
 * of the Common Development and Distribution License
 * (the License). You may not use this file except in
 * compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.icntv.tv/licenses/LICENSE-1.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
*
*   @author   zhang.mingliang@icntv.tv
*   @data     20150713
*/

#include "debug.h"

#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <android/log.h>

#define MAX_LOG_MSG_SIZE  (1024 * 8)  //8KB

//get current time, format 20150713145028(year month day hour minute second)
std::string getTime()
{
    struct timeval tv;
    struct timezone tz;
    struct tm *p;
    char time[100] = {0};

    gettimeofday(&tv, &tz);
    //printf("tv_sec:%ld\n",tv.tv_sec);
    //printf("tv_usec:%ld\n",tv.tv_usec);
    //printf("tz_minuteswest:%d\n",tz.tz_minuteswest);
    //printf("tz_dsttime:%d\n",tz.tz_dsttime);

//    p = localtime(&tv.tv_sec);
//    sprintf(time, "%04d-%02d-%02d %02d:%02d:%02d.%ld", \
//            1900+p->tm_year, 1+p->tm_mon, p->tm_mday, \
//            p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec);

    p = localtime(&tv.tv_sec);
    sprintf(time, "%04d%02d%02d%02d%02d%02d", \
                  1900+p->tm_year, 1+p->tm_mon, p->tm_mday, \
                  p->tm_hour, p->tm_min, p->tm_sec);

    std::string t(time);
    return t;
}

void androidLog(std::string level, std::string tag, const char *format, ...)
{
    char buffer[MAX_LOG_MSG_SIZE] = {0};
    va_list ap;

    va_start(ap, format);
    vsnprintf(buffer, sizeof(buffer) - 1, format, ap);
    va_end(ap);

    if (level == "debug")
    {
        __android_log_write(ANDROID_LOG_DEBUG, tag.c_str(), buffer);
    }
    else if (level == "info")
    {
        __android_log_write(ANDROID_LOG_INFO, tag.c_str(), buffer);
    }
    else if (level == "warn")
    {
        __android_log_write(ANDROID_LOG_WARN, tag.c_str(), buffer);
    }
    else if (level == "error")
    {
        __android_log_write(ANDROID_LOG_ERROR, tag.c_str(), buffer);
    }
    else
    {
        __android_log_write(ANDROID_LOG_DEBUG, tag.c_str(), buffer);
    }
}


