typedef struct
		{ 
			uint8_t 	Hearder[2];
			uint8_t		Length;
			uint8_t		Opcode[2];
			uint8_t		Error;

			union  								// bit7-Relay_____bit6->0-Dim
			{
			//	uint8_t Relay_Dim;    khai bao thi se tang them 1 byte. gia trị == struct duoi
				struct 
				{
					uint8_t Dim 	:7;  //bit0->6
					uint8_t Relay :1;  //bit 7
					
				} Relay_Dim_t; 
			} Relay_Dim;

			uint8_t     Scene_ID_Active[2];

			union                 //    union contain SttScene - Cos -U -I
			{
			//	uint32_t SttS_CosUI;      khai bao thi se tang them 4 byte. gia trị == struct duoi
				struct 
				{
					uint16_t I        :12;  // bit0->11
					uint16_t U 				:12;  // bit 12->23
					uint8_t Cos 			:7;   // bit 24->30
					uint8_t SttScene  :1;   // bit 31 
				} SttS_CosUI_t;
			} SttS_CosUI;

			uint8_t Pow_Now[2];
			uint8_t Pow_Consum[2];
			uint8_t  Temp;
			uint8_t 	EnviLightness[2];
			uint8_t		CRC; 

		} Struct_Mess_OPCODE_TSPH_Rsp;	
void RD_Rsp_OPCODE_TSPH(void)
{
	Struct_Mess_OPCODE_TSPH_Rsp 		Mess_Buff;
	Mess_Buff.Hearder[0] 				= (HEADER_MESS_RSP>>8) 				& 0xFF;
	Mess_Buff.Hearder[1] 				= (HEADER_MESS_RSP ) 				& 0xFF;
	Mess_Buff.Length		 				=  sizeof(Mess_Buff); 
	Mess_Buff.Opcode[0]			    = (OPCODE_TSPH_MR>>8) 					& 0xFF;
	Mess_Buff.Opcode[1]					= (OPCODE_TSPH_MR) 	  				& 0xFF;
	Mess_Buff.Error			        = Sensor_Of_Light_Common.Error[0];

	Mess_Buff.Relay_Dim.Relay_Dim_t.Relay = Light_Stt_Common.Relay;
	Mess_Buff.Relay_Dim.Relay_Dim_t.Dim   = Light_Stt_Common.Dim;

	Mess_Buff.Scene_ID_Active[0] = Light_Stt_Common.Scene_ID_Active[0];
	Mess_Buff.Scene_ID_Active[1] = Light_Stt_Common.Scene_ID_Active[1];

	Mess_Buff.SttS_CosUI.SttS_CosUI_t.SttScene = Scene_Data_Common.Enable;
	Mess_Buff.SttS_CosUI.SttS_CosUI_t.U				 = (uint16_t) ( (Sensor_Of_Light_Common.Voltage[0] << 8) | (Sensor_Of_Light_Common.Voltage[1]) );
	Mess_Buff.SttS_CosUI.SttS_CosUI_t.I				 = (uint16_t) ( (Sensor_Of_Light_Common.Ampe[0] << 8)    | (Sensor_Of_Light_Common.Ampe[1]) );
	Mess_Buff.SttS_CosUI.SttS_CosUI_t.Cos			 = Sensor_Of_Light_Common.Cos_UI;
	
	Mess_Buff.Pow_Now[0]					= Sensor_Of_Light_Common.Power[0];
	Mess_Buff.Pow_Now[1]					= Sensor_Of_Light_Common.Power[1];

	Mess_Buff.Pow_Consum[0]     = 0x00; // not do yet
	Mess_Buff.Pow_Consum[1]			= 0x01; // not do yet 

 	Mess_Buff.Temp							= Sensor_Of_Light_Common.Temp;
	Mess_Buff.EnviLightness[0] 	= Sensor_Of_Light_Common.EnviLightness[0];
	Mess_Buff.EnviLightness[1] 	= Sensor_Of_Light_Common.EnviLightness[1];

	Mess_Buff.CRC								= Checksum_Cal(( TS_GWIF_IncomingData*) &Mess_Buff, sizeof(Mess_Buff) -3);
	 
	UART_PutArray(sizeof(Mess_Buff) , (uint8_t *) &Mess_Buff);
}