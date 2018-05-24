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
*/

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <string>

#define LOG_TAG "FrameDataHandle"    // android log tag

std::string getTime();
void androidLog(std::string level, std::string tag, const char *format, ...);

#define LOGDEBUG(x, ...)\
{\
    androidLog("debug", LOG_TAG, "D<%s>[%s-%d]: " x, getTime().c_str(), __FILE__, __LINE__,  ##__VA_ARGS__);\
}

#define LOGINFO(x, ...)\
{\
    androidLog("info", LOG_TAG, "I<%s>[%s-%d]: " x, getTime().c_str(), __FILE__, __LINE__,  ##__VA_ARGS__);\
}

#define LOGWARN(x, ...)\
{\
    androidLog("warn", LOG_TAG, "W<%s>[%s-%d]: " x, getTime().c_str(), __FILE__, __LINE__,  ##__VA_ARGS__);\
}

#define LOGERROR(x, ...)\
{\
    androidLog("error", LOG_TAG, "E<%s>[%s-%d]: " x, getTime().c_str(), __FILE__, __LINE__,  ##__VA_ARGS__);\
}

#endif
