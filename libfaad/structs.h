/*
** FAAD - Freeware Advanced Audio Decoder
** Copyright (C) 2002 M. Bakker
**  
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software 
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
**
** $Id: structs.h,v 1.8 2003/07/09 11:53:07 menno Exp $
**/

#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_CHANNELS        64
#define MAX_SYNTAX_ELEMENTS 48
#define MAX_WINDOW_GROUPS    8
#define MAX_SFB             51
#define MAX_LTP_SFB         40
#define MAX_LTP_SFB_S        8

/* used to save the prediction state */
typedef struct {
    real_t r[2];
    real_t KOR[2];
    real_t VAR[2];
} pred_state;

typedef struct
{
    uint16_t n;
    uint16_t ifac[15];
    complex_t *work;
    complex_t *tab;
} cfft_info;

typedef struct {
    uint16_t N;
    cfft_info *cfft;
    complex_t *sincos;
    complex_t *Z1;
} mdct_info;

typedef struct
{
    real_t *long_window[2];
    real_t *short_window[2];
#ifdef LD_DEC
    real_t *ld_window[2];
#endif

    mdct_info *mdct256;
#ifdef LD_DEC
    mdct_info *mdct1024;
#endif
    mdct_info *mdct2048;
} fb_info;

typedef struct
{
    uint8_t present;

    uint8_t num_bands;
    uint8_t pce_instance_tag;
    uint8_t excluded_chns_present;
    uint8_t band_top[17];
    uint8_t prog_ref_level;
    uint8_t dyn_rng_sgn[17];
    uint8_t dyn_rng_ctl[17];
    uint8_t exclude_mask[MAX_CHANNELS];
    uint8_t additional_excluded_chns[MAX_CHANNELS];

    real_t ctrl1;
    real_t ctrl2;
} drc_info;

typedef struct
{
    uint8_t element_instance_tag;
    uint8_t object_type;
    uint8_t sf_index;
    uint8_t num_front_channel_elements;
    uint8_t num_side_channel_elements;
    uint8_t num_back_channel_elements;
    uint8_t num_lfe_channel_elements;
    uint8_t num_assoc_data_elements;
    uint8_t num_valid_cc_elements;
    uint8_t mono_mixdown_present;
    uint8_t mono_mixdown_element_number;
    uint8_t stereo_mixdown_present;
    uint8_t stereo_mixdown_element_number;
    uint8_t matrix_mixdown_idx_present;
    uint8_t pseudo_surround_enable;
    uint8_t matrix_mixdown_idx;
    uint8_t front_element_is_cpe[16];
    uint8_t front_element_tag_select[16];
    uint8_t side_element_is_cpe[16];
    uint8_t side_element_tag_select[16];
    uint8_t back_element_is_cpe[16];
    uint8_t back_element_tag_select[16];
    uint8_t lfe_element_tag_select[16];
    uint8_t assoc_data_element_tag_select[16];
    uint8_t cc_element_is_ind_sw[16];
    uint8_t valid_cc_element_tag_select[16];

    uint8_t channels;

    uint8_t comment_field_bytes;
    uint8_t comment_field_data[257];

    /* extra added values */
    uint8_t num_front_channels;
    uint8_t num_side_channels;
    uint8_t num_back_channels;
    uint8_t num_lfe_channels;
    uint8_t sce_channel[16];
    uint8_t cpe_channel[16];
} program_config;

typedef struct
{
    uint16_t syncword;
    uint8_t id;
    uint8_t layer;
    uint8_t protection_absent;
    uint8_t profile;
    uint8_t sf_index;
    uint8_t private_bit;
    uint8_t channel_configuration;
    uint8_t original;
    uint8_t home;
    uint8_t emphasis;
    uint8_t copyright_identification_bit;
    uint8_t copyright_identification_start;
    uint16_t aac_frame_length;
    uint16_t adts_buffer_fullness;
    uint8_t no_raw_data_blocks_in_frame;
    uint16_t crc_check;
} adts_header;

typedef struct
{
    uint8_t copyright_id_present;
    int8_t copyright_id[10];
    uint8_t original_copy;
    uint8_t home;
    uint8_t bitstream_type;
    uint32_t bitrate;
    uint8_t num_program_config_elements;
    uint32_t adif_buffer_fullness;

    /* maximum of 16 PCEs */
    program_config pce[16];
} adif_header;

typedef struct
{
    uint8_t last_band;
    uint8_t data_present;
    uint16_t lag;
    uint8_t lag_update;
    uint8_t coef;
    uint8_t long_used[MAX_SFB];
    uint8_t short_used[8];
    uint8_t short_lag_present[8];
    uint8_t short_lag[8];
} ltp_info;

typedef struct
{
    uint8_t limit;
    uint8_t predictor_reset;
    uint8_t predictor_reset_group_number;
    uint8_t prediction_used[MAX_SFB];
} pred_info;

typedef struct
{
    uint8_t number_pulse;
    uint8_t pulse_start_sfb;
    uint8_t pulse_offset[4];
    uint8_t pulse_amp[4];
} pulse_info;

typedef struct
{
    uint8_t n_filt[8];
    uint8_t coef_res[8];
    uint8_t length[8][4];
    uint8_t order[8][4];
    uint8_t direction[8][4];
    uint8_t coef_compress[8][4];
    uint8_t coef[8][4][32];
} tns_info;

#ifdef SSR_DEC
typedef struct
{
    uint8_t max_band;

    uint8_t adjust_num[4][8];
    uint8_t alevcode[4][8][8];
    uint8_t aloccode[4][8][8];
} ssr_info;
#endif

typedef struct
{
    uint8_t max_sfb;

    uint8_t num_swb;
    uint8_t num_window_groups;
    uint8_t num_windows;
    uint8_t window_sequence;
    uint8_t window_group_length[8];
    uint8_t window_shape;
    uint8_t scale_factor_grouping;
    uint16_t sect_sfb_offset[8][15*8];
    uint16_t swb_offset[52];

    uint8_t sect_cb[8][15*8];
    uint16_t sect_start[8][15*8];
    uint16_t sect_end[8][15*8];
    uint8_t sfb_cb[8][8*15];
    uint8_t num_sec[8]; /* number of sections in a group */

    uint8_t global_gain;
    int16_t scale_factors[8][51];

    uint8_t ms_mask_present;
    uint8_t ms_used[MAX_WINDOW_GROUPS][MAX_SFB];

    uint8_t noise_used;

    uint8_t pulse_data_present;
    uint8_t tns_data_present;
    uint8_t gain_control_data_present;
    uint8_t predictor_data_present;

    pulse_info pul;
    tns_info tns;
    pred_info pred;
    ltp_info ltp;
    ltp_info ltp2;
#ifdef SSR_DEC
    ssr_info ssr;
#endif

#ifdef ERROR_RESILIENCE
    /* ER HCR data */
    uint16_t length_of_reordered_spectral_data;
    uint8_t length_of_longest_codeword;
    /* ER RLVC data */
    uint8_t sf_concealment;
    uint8_t rev_global_gain;
    uint16_t length_of_rvlc_sf;
    uint16_t dpcm_noise_nrg;
    uint8_t sf_escapes_present;
    uint8_t length_of_rvlc_escapes;
    uint16_t dpcm_noise_last_position;
#endif
} ic_stream; /* individual channel stream */

typedef struct
{
    uint8_t ele_id;

    uint8_t channel;
    int16_t paired_channel;

    uint8_t element_instance_tag;
    uint8_t common_window;

    ic_stream ics1;
    ic_stream ics2;
} element; /* syntax element (SCE, CPE, LFE) */

typedef struct mp4AudioSpecificConfig
{
    /* Audio Specific Info */
    uint8_t objectTypeIndex;
    uint8_t samplingFrequencyIndex;
    uint32_t samplingFrequency;
    uint8_t channelsConfiguration;

    /* GA Specific Info */
    uint8_t frameLengthFlag;
    uint8_t dependsOnCoreCoder;
    uint16_t coreCoderDelay;
    uint8_t extensionFlag;
    uint8_t aacSectionDataResilienceFlag;
    uint8_t aacScalefactorDataResilienceFlag;
    uint8_t aacSpectralDataResilienceFlag;
    uint8_t epConfig;

} mp4AudioSpecificConfig;

typedef struct faacDecConfiguration
{
    uint8_t defObjectType;
    uint32_t defSampleRate;
    uint8_t outputFormat;
} faacDecConfiguration, *faacDecConfigurationPtr;

typedef struct faacDecFrameInfo
{
    uint32_t bytesconsumed;
    uint32_t samples;
    uint8_t channels;
    uint8_t error;
    uint32_t samplerate;

    /* multichannel configuration */
    uint8_t num_front_channels;
    uint8_t num_side_channels;
    uint8_t num_back_channels;
    uint8_t num_lfe_channels;
    uint8_t channel_position[MAX_CHANNELS];
} faacDecFrameInfo;

typedef struct
{
    uint8_t adts_header_present;
    uint8_t adif_header_present;
    uint8_t sf_index;
    uint8_t object_type;
    uint8_t channelConfiguration;
#ifdef ERROR_RESILIENCE
    uint8_t aacSectionDataResilienceFlag;
    uint8_t aacScalefactorDataResilienceFlag;
    uint8_t aacSpectralDataResilienceFlag;
#endif
    uint16_t frameLength;

    uint32_t frame;

    uint8_t first_syn_ele;
    uint8_t last_syn_ele;
    uint8_t has_lfe;
    uint8_t fr_channels;
    uint8_t fr_ch_ele;

    void *sample_buffer;

    uint8_t window_shape_prev[MAX_CHANNELS];
#ifdef LTP_DEC
    uint16_t ltp_lag[MAX_CHANNELS];
#endif
    fb_info *fb;
    drc_info *drc;

    real_t *time_out[MAX_CHANNELS];

#ifdef SSR_DEC
    real_t *ssr_overlap[MAX_CHANNELS];
    real_t *prev_fmd[MAX_CHANNELS];
    real_t ipqf_buffer[MAX_CHANNELS][4][96/4];
#endif

#ifdef MAIN_DEC
    pred_state *pred_stat[MAX_CHANNELS];
#endif
#ifdef LTP_DEC
    real_t *lt_pred_stat[MAX_CHANNELS];
#endif

#ifndef FIXED_POINT
#if POW_TABLE_SIZE
    real_t *pow2_table;
#endif
#endif

    /* Program Config Element */
    uint8_t pce_set;
    program_config pce;
    uint8_t channel_element[MAX_CHANNELS];
    uint8_t internal_channel[MAX_CHANNELS];

    /* Configuration data */
    faacDecConfiguration config;
} faacDecStruct, *faacDecHandle;



#ifdef __cplusplus
}
#endif
#endif
