#pragma once
#include <stdint.h>

#define MAX_beidou_PACKET_TYPES 5

#pragma pack(push, 1)
namespace beidou_Tool {

	typedef struct {
		uint8_t nmea_flag;
		uint8_t flag;
		uint8_t header_len;
		uint8_t header[4];
		uint32_t nbyte;
		uint8_t buff[256];
		uint32_t nmeabyte;
		uint8_t nmea[256];
		uint8_t ntype;
	} usrRaw;

	typedef struct
	{
		uint32_t  week;
		double    timeOfWeek;
		float     accel_g[3];
		float     rate_dps[3];
	} beidou_s1_t;

	struct beidou_gN_t
	{
		uint32_t week;
		double   timeOfWeek;
		uint8_t  positionMode;
		int32_t  latitude;
		int32_t  longitude;
		float    height;
		uint8_t  numberOfSVs;
		float    hdop;
		uint16_t diffage;
		int16_t  north_vel;
		int16_t  east_vel;
		int16_t  up_vel;
		int16_t  latitude_std;
		int16_t  longitude_std;
		int16_t  height_std;
	};

	typedef struct
	{
		uint32_t week;
		double   timeOfWeek;
		uint8_t  insStatus;
		uint8_t  insPositionType;
		int32_t  latitude;
		int32_t  longitude;
		float    height;
		int16_t  north_vel;
		int16_t  east_vel;
		int16_t  up_vel;
		int16_t  roll;
		int16_t  pitch;
		int16_t  heading;
	} beidou_iN_t;

	typedef struct
	{
		uint16_t    gps_week;               // GPS Week number
		uint32_t    gps_millisecs;          // Milliseconds into week
		uint8_t     mode;
		double      speed;
		uint8_t     fwd;
		uint64_t    wheel_tick;
	} beidou_o1_t;


	typedef struct  heading
	{
		uint16_t    gps_week;          // GPS Week number
		uint32_t    gps_millisecs;     // Milliseconds into week
		float       length;
		float       heading;
		float       pitch;
		float       hdgstddev;
		float       ptchstddev;
	}beidou_hG_t;

	typedef enum {
		beidou_OUT_NONE = 0,
		beidou_OUT_SCALED1,
		beidou_OUT_INSPVA,
		beidou_OUT_GNSS,
		beidou_OUT_ODO,
		beidou_OUT_HEADING
	} beidouOutPacketType;

	typedef enum {
		header_old = 0,
		header_new
	} unicoHeaderType;

	typedef struct {
		uint8_t flag;
        unicoHeaderType header_type;
        uint8_t header_to_read;
		uint8_t header_len;
        uint32_t data_len;
		uint8_t header[100];
		uint32_t nbyte;
		uint8_t buff[100*1024];
		uint16_t ntype;
	} unicoRaw;



    typedef struct UnicoHeader_old_t_
    {
        uint8_t sync1;            //!< start of packet first byte (0xAA)
        uint8_t sync2;            //!< start of packet second byte (0x44)
        uint8_t sync3;            //!< start of packet third  byte (0x12)
        uint8_t header_length;
        uint16_t message_id;
        uint8_t message_type;
        uint8_t reserved1;
        uint16_t message_length;
        uint16_t reserved2;
        uint8_t idle_time;
        uint8_t time_status; 
        uint16_t week;
        uint32_t time_of_week;
        uint32_t reserved3;
        uint16_t time_offset_gps;
        uint16_t reserved4;
    } UnicoHeader_old_t;

    typedef struct UnicoHeader_t_
    {
        uint8_t sync1;            //!< start of packet first byte (0xAA)
        uint8_t sync2;            //!< start of packet second byte (0x44)
        uint8_t sync3;            //!< start of packet third  byte (0x12)
        uint8_t cpu_idle;
        uint16_t message_id;
        uint16_t message_length;
        uint8_t time_ref;
        uint8_t time_status;
        uint16_t week;
        uint32_t time_of_week;
        uint32_t reserved3;
        uint8_t version;
        uint8_t leap_sec;
        uint16_t delay_ms;
    } UnicoHeader_t;


    typedef struct RangehData_t_
    {
        uint16_t prn;                   //����PRN�ţ�GPS ��1��32 ��GLONASS: 38��61��BDS1��63��SBAS120��141��183��187��QZSS193��197��
        uint16_t glofreq;               //��GLONASS Ƶ��+ 7����GPS��BDS��Galileo��ʹ��
        double psr;                     //��α�����ֵ���ף�
        float psr_std;                  //��α���׼��ף�
        double adr;                     //�ز���λ���ܣ����ֶ����գ�
        float adr_std;                  //�ز���λ��׼��ܣ�
        float dopp;                     //˲ʱ�����գ�Hz��
        float c_no;                     //����� C/No = 10[log10(S/N0)]��dBHz��
        float locktime;                 //�룬��������ʱ�䣨��������
        uint32_t ch_tr_status;          //ͨ������״̬
    }RangehData_t;

    typedef struct RANGEHB_t_
    {
        UnicoHeader_t header;
        uint32_t satellite_num;     //��������
        RangehData_t **data;
        uint8_t crc[4];
    }RANGEHB_t;

    typedef struct BD2SEPHEM_t_                  //������������
    {
        UnicoHeader_t header;           //ͷ��Ϣ
        uint32_t prn;                   //���� PRN ��ţ� BDS�� 1 ��63��
        double tow;                     //��֡1��ʱ���ʶ������GPSʱ�䣩�� s
        uint32_t health;                //����״̬�C�ڱ��� ICD �ж����һ�� 1 ���صĽ�������
        uint32_t aode_1;                //������������
        uint32_t aode_2;                //������������
        uint32_t week;                  //GPS �ܼ�����GPS Week��
        uint32_t z_week;                //���� GPS �ܵ� Z ����������Ϊ������֡ 1 ��������
        double toe;                     //�����ο�ʱ�̣����� GPS ʱ�䣩�� s
        double a;                       //��������ᣬ m
        double delat_n;                 //����ƽ�����ٶȵĸ���ֵ ��rad/s
        double m_0;                     //�ο�ʱ���ƽ����ǣ� rad
        double ecc;                     //ƫ����
        double omega;                   //���ص���ǣ� rad
        double cuc;                     //γ�ȷ��ǣ���������� rad��
        double cus;                     //γ�ȷ��ǣ���������� rad��
        double crc;                     //����뾶����������� m��
        double crs;                     //����뾶����������� m��
        double cic;                     //��ǣ���������� rad��
        double cis;                     //��ǣ���������� rad��
        double i_0;                     //TOE ʱ������ǣ� rad
        double idot;                    //�����Ǳ仯�ʣ� rad/s
        double omega_0;                 //������ྭ�� rad
        double omega_dot;               //������ྭ�仯�ʣ� rad/s
        uint32_t iodc;                  //ʱ����������
        double toc;                     //�����Ӳ�ο�ʱ�䣬 s
        double tgd_1;                   //B1 Ⱥ�ӳ٣�B1 �����豸ʱ�Ӳ�� s
        double tgd_2;                   //B2 Ⱥ�ӳ٣�B2 �����豸ʱ�Ӳ�� s
        double af_0;                    //�����Ӳ������ s
        double af_1;                    //�������ٲ����� s/s
        double af_2;                    //������Ư������ s/s/s
        uint32_t as;                    //����ƭ��0 = FALSE;1 = TRUE
        double n;                       //����ƽ�����ٶȣ� rad/s
        double ura;                     //�û����뾫�ȣ� m2
        uint8_t crc32[4];
    }BD2SEPHEM_t;


    typedef struct obsVM_data_t_
    {
        uint16_t system_freq;
        uint16_t prn;
        double psr;
        double adr;
        uint16_t psr_std;
        uint16_t adr_std;
        float dopp;
        uint16_t c_no;
        uint16_t reserved;
        float lock_time;
        uint32_t ch_tr_status;
    }obsVM_data_t;

    typedef struct OBSVM_t_
    {
        UnicoHeader_t header;
        uint32_t obs_num;
        // uint16_t system_freq;
        obsVM_data_t **data;
        uint8_t crc[4];
    }OBSVM_t;


#pragma pack(pop)

	extern void init_beidou_data();
	extern void set_output_beidou_file(int output);
	extern void set_base_beidou_file_name(char* file_name);
	extern void write_beidou_kml_files();
	extern void close_beidou_all_log_file();

	extern int input_beidou_raw(uint8_t data);
    extern int input_unico_raw(uint8_t data);

}