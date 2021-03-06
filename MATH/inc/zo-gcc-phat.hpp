#ifndef __ZO_GCC_PHAT_HPP__
#define __ZO_GCC_PHAT_HPP__
#include <stdint.h>
#include <vector>
#include "main.hpp"
#include "wav_decode.hpp"
#include "numeric"
#include <fstream>
#include <iostream>

namespace zo
{
    class GccPhat
    {
    public:
        std::vector<float> cross_correlation;
        double volume_index;
        double target_band_ratio;
        double band_low;
        double band_high;
        Wave1234 *wave1234_no_W;

    public:
        /**
         * @brief Creates an instance of GccPhat
         *
         * @return GccPhat*
         */
        static GccPhat *create();

        /**
         * @brief Initialize GccPhat
         *
         * @param sample_cnt The number of samples.
         */
        virtual void init(const int sample_cnt, double low, double high) = 0;

        /**
         * @brief Terminate and cleanup instance
         *
         */
        virtual void terminate() = 0;

        /**
         * @brief Execute GCC PHAT algorithm.
         * See: http://www.xavieranguera.com/phdthesis/node92.html
         * See: https://github.com/respeaker/mic_array/blob/master/gcc_phat.py
         *
         * @param signal First signal, say from microphone 1
         * @param refsignal Second signal, say from microphone 2
         * @return int "Tau" or distance signal is from refsignal
         */
        virtual void execute(const std::vector<float> &siga, const std::vector<float> &sigb, int margin, double *arg_max) = 0;
        virtual void PHAT_SRP_3mic(Wave1234 *wave1234, int margin, double *arg_max, double confidence_CC_THRESHOLD) = 0;
        virtual void PHAT_SRP_4mic(Wave1234 *wave1234_no_window, Wave1234 *wave1234, int margin, double *arg_max, double confidence_CC_THRESHOLD, double h, double l) = 0;
        virtual void PHAT_SRP_2mic(Wave1234 *wave1234, int margin, double *arg_max, double confidence_CC_THRESHOLD) = 0;
        virtual void PHAT_SRP_2mic_times_4(Wave1234 *wave1234, int margin, double *arg_max, double confidence_CC_THRESHOLD) = 0;
        virtual void GCC_PHAT_4mic(Wave1234 *wave1234_no_window, Wave1234 *wave1234, int margin, double *arg_max, double confidence_CC_THRESHOLD) = 0;
    };
} // namespace zo

#endif // __ZO_GCC_PHAT_HPP__
