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

#include <cstdint>
#include <iomanip>
#include <math.h>
#include "AudioSinkBase.h"
#include "SynthMark.h"
#include "synth/Synthesizer.h"
#include "tools/CpuAnalyzer.h"
#include "tools/TimingAnalyzer.h"
#include "tools/LogTool.h"
#include "tools/TestHarnessBase.h"

#ifndef SYNTHMARK_JITTERMARK_HARNESS_H
#define SYNTHMARK_JITTERMARK_HARNESS_H


/**
 * Determine buffer latency required to avoid glitches.
 * The "LatencyMark" is the minimum buffer size that is a multiple
 * of a block size that can be used for N minutes without glitching.
 */
class JitterMarkHarness : public TestHarnessBase {
public:
    JitterMarkHarness(AudioSinkBase *audioSink, SynthMarkResult *result, LogTool *logTool = NULL)
    : TestHarnessBase(audioSink, result, logTool) {
        mTestName = "JitterMark";
    }

    virtual ~JitterMarkHarness() {
    }

    void onBeginMeasurement() override {
        mResult->setTestName(mTestName);
        mLogTool->log("---- Measure scheduling jitter ---- #voices = %d\n", getNumVoices());
        setupJitterRecording();
    }

    virtual int32_t onBeforeNoteOn() override {
        return 0;
    }

    virtual void onEndMeasurement() override {

        double measurement = 0.0;
        std::stringstream resultMessage;
        resultMessage << mTestName << " = " << measurement << std::endl;

        resultMessage << dumpJitter();
        resultMessage << "Underruns " << mAudioSink->getUnderrunCount() << "\n";
        resultMessage << mCpuAnalyzer.dump();

        mResult->setMeasurement(measurement);
        mResult->setResultMessage(resultMessage.str());
    }


};

#endif // SYNTHMARK_JITTERMARK_HARNESS_H
