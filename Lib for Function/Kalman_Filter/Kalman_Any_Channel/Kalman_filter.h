/*
 * kalman_filter.h
 *  Created on: Oct 19, 2021
 *      Author: DANG HAO
 */
 
#ifndef INC_KALMAN_FILTER_H_
#define INC_KALMAN_FILTER_H_

#include "MyLibMCU.h"
typedef struct
{
	float	err_measure;
	float	err_estimate;
	float	q;
	float	current_estimate;
	float 	last_estimate;
	float 	kalman_gain;
} Kalman_Filter_Str;

void KalmanFilter_Init(Kalman_Filter_Str* Kalman_Str_In, float mea_init, float est_init, float q);
float KalmanFilter_UpdateEstimate(Kalman_Filter_Str* Kalman_Str_In, float measure);
void KalmanFilter_Set_Measurement_Err(Kalman_Filter_Str* Kalman_Str_In, float mea_err);
void KalmanFilter_Set_Esrimate_Err(Kalman_Filter_Str* Kalman_Str_In, float est_err);
void KalmanFilter_Set_ProcessNoise(Kalman_Filter_Str* Kalman_Str_In, float q);
float KalmanFilter_Get_K_Gain(Kalman_Filter_Str* Kalman_Str_In);
float KalmanFilter_Get_Est_Err(Kalman_Filter_Str* Kalman_Str_In);
#endif /*INC_KALMAN_FILTER_H_*/