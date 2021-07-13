#pragma once
#include <stdint.h>
#include "openrtk_user.h"
#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_INCEPTIO_PACKET_TYPES 8

#pragma pack(push, 1)

	typedef struct
	{
		uint32_t GPS_Week;
		double	 GPS_TimeOfWeek;
		float	 x_accel;
		float	 y_accel;
		float	 z_accel;
		float	 x_gyro;
		float	 y_gyro;
		float	 z_gyro;
	} inceptio_s1_t;

	typedef struct
	{
		uint32_t GPS_Week;
		double	 GPS_TimeOfWeek;
		uint8_t	 positionMode;
		uint32_t latitude;
		uint32_t longitude;
		float	 height;
		uint8_t  numberOfSVs;
		float    hdop;
		uint16_t diffage;
		int16_t	 velocityNorth;
		int16_t  velocityEast;
		int16_t  velocityUp;
		int16_t	 latitude_std;
		int16_t	 longitude_std;
		int16_t	 height_std;
		//struct extend at 2021-07-13
		uint16_t pos_hor_pl;
		uint16_t pos_ver_pl;
		uint8_t pos_status;
		uint16_t vel_hor_pl;
		uint16_t vel_ver_pl;
		uint8_t vel_status;
	} inceptio_gN_t;

#define inceptio_gN_t_size_base			44
#define inceptio_gN_t_size_20210713		54

	typedef struct
	{
		uint32_t GPS_Week;
		double	 GPS_TimeOfWeek;
		uint8_t  insStatus;
		uint8_t  insPositionType;
		int32_t	 latitude;
		int32_t	 longitude;
		float	 height;
		int16_t	 velocityNorth;
		int16_t  velocityEast;
		int16_t  velocityUp;
		int16_t  roll;
		int16_t  pitch;
		int16_t  heading;
	} inceptio_iN_t;

	typedef struct
	{
		uint32_t GPS_Week;
		double	 GPS_TimeOfWeek;
		int16_t	 latitude_std;
		int16_t	 longitude_std;
		int16_t	 height_std;
		int16_t	 north_vel_std;
		int16_t  east_vel_std;
		int16_t  up_vel_std;
		int16_t  roll_std;
		int16_t  pitch_std;
		int16_t  heading_std;
	} inceptio_d1_t;

	typedef struct
	{
		uint32_t GPS_Week;
		double	 GPS_TimeOfWeek;
		uint16_t year;
		uint8_t	 mouth;
		uint8_t	 day;
		uint8_t	 hour;
		uint8_t  min;
		uint8_t  sec;
		uint32_t imu_status;
		float  imu_temperature;
		float  mcu_temperature;
	} inceptio_sT_t;

	typedef struct
	{
		uint16_t GPS_Week;
		uint32_t GPS_TimeOfWeek;
		uint8_t	 mode;
		double	 speed;
		uint8_t	 fwd;
		uint64_t wheel_tick;
	} inceptio_o1_t;

	typedef enum {
		INCEPTIO_OUT_NONE = 0,
		INCEPTIO_OUT_SCALED1,
		INCEPTIO_OUT_INSPVA,
		INCEPTIO_OUT_STD1,
		INCEPTIO_OUT_GNSS,
		INCEPTIO_OUT_STATUS,
		INCEPTIO_OUT_ODO
	} InceptioOutPacketType;

#pragma pack(pop)

	extern void init_inceptio_data();
	extern void set_output_inceptio_file(int output);
	extern void set_base_inceptio_file_name(char* file_name);
	extern void close_inceptio_all_log_file();
	//begin_end : begin = 1 end = -1 other = 0
	extern void write_inceptio_gnss_kml_line(inceptio_gN_t* pak_gnss, int begin_end);
	extern void write_inceptio_gnss_kml_file(inceptio_gN_t* pak_gnss, int begin_end);
	extern void write_inceptio_ins_kml_line(inceptio_iN_t* pak_ins, int begin_end);
	extern void write_inceptio_ins_kml_file(inceptio_iN_t* pak_ins, int begin_end);

	extern int get_inceptio_packet_type();
	extern inceptio_gN_t* get_inceptio_packet_gN();
	extern inceptio_iN_t* get_inceptio_packet_iN();

	extern int input_inceptio_raw(uint8_t data);

#ifdef __cplusplus
}
#endif