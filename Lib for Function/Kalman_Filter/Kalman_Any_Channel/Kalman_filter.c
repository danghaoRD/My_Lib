/*
 * kalman_filter.c
 *
 *  Created on: Oct 19, 2021
 *      Author: DANG HAO
 */
 #include "Kalman_filter.h"
 
 void KalmanFilter_Init(Kalman_Filter_Str* Kalman_Str_In, float mea_init, float est_init, float q)
 {
	Kalman_Str_In->err_measure 		= mea_init;
	Kalman_Str_In->err_estimate 	= est_init;
	Kalman_Str_In->q				= q;
 }
 
 float KalmanFilter_UpdateEstimate(Kalman_Filter_Str* Kalman_Str_In, float measure)
 {
	 Kalman_Str_In->kalman_gain = Kalman_Str_In->err_estimate/(Kalman_Str_In->current_estimate + Kalman_Str_In->err_measure);
	 Kalman_Str_In->current_estimate	= Kalman_Str_In->last_estimate + Kalman_Str_In->kalman_gain * (measure - Kalman_Str_In->last_estimate);
	 Kalman_Str_In->err_estimate		= (1.0 - Kalman_Str_In->kalman_gain) * Kalman_Str_In->err_estimate + fabs(Kalman_Str_In->last_estimate - Kalman_Str_In->current_estimate) * Kalman_Str_In->q;
	 Kalman_Str_In->last_estimate 		= Kalman_Str_In->current_estimate;
	 
	 return Kalman_Str_In->current_estimate;
 }
 
 void KalmanFilter_Set_Measurement_Err(Kalman_Filter_Str* Kalman_Str_In, float mea_err)
 {
	 Kalman_Str_In->err_measure = mea_err;
 }
 
 void KalmanFilter_Set_Esrimate_Err(Kalman_Filter_Str* Kalman_Str_In, float est_err)
 {
	 Kalman_Str_In->err_estimate = est_err;
 }
 
 void KalmanFilter_Set_ProcessNoise(Kalman_Filter_Str* Kalman_Str_In, float q)
 {
	 Kalman_Str_In->q = q;
 }
 
 float KalmanFilter_Get_K_Gain(Kalman_Filter_Str* Kalman_Str_In)
 {
	 return Kalman_Str_In->kalman_gain;
 }
 
float KalmanFilter_Get_Est_Err(Kalman_Filter_Str* Kalman_Str_In)
{
	return Kalman_Str_In->err_estimate;
}
