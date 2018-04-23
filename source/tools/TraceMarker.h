/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TRACE_MARKER_H
#define TRACE_MARKER_H

#include <fstream>
#include <string>


#define TRACE_MARKER_ENABLED

/*
 * Simple function wrapper to simply output data to the
 * "/sys/kernel/debug/tracing/trace_marker"
 * file, to inject userspace traces to the kernel tracing system.
 */
class TraceMarker : public std::basic_ostream< char, std::char_traits<char> > {
    static TraceMarker *mInstance;
    static std::basic_filebuf<char> *mStrbuf;

    TraceMarker(std::basic_streambuf< char, std::char_traits< char > >* sb) :
        std::basic_ostream< char, std::char_traits< char > >(sb) {}
 public:
    static TraceMarker &getInstance() {
        if (mInstance == nullptr) {
#if defined(TRACE_MARKER_ENABLED) && !defined(__APPLE__)
            mStrbuf = new std::basic_filebuf<char>();
            mStrbuf->open("/sys/kernel/debug/tracing/trace_marker",
                          std::ios_base::out);
#endif
            mInstance = new TraceMarker(mStrbuf);
        }
        return *mInstance;
    }
};

static inline TraceMarker &traceMarker()
{
    return TraceMarker::getInstance();
}

#endif /* TRACE_MARKER_H */
