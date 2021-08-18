#pragma once

#include <QThread>
#include <QTime>
#include "ins401.h"

enum emDecodeFormat {
	emDecodeFormat_openrtk_user,
	emDecodeFormat_openrtk_inceptio,
	emDecodeFormat_mixed_raw,
	emDecodeFormat_imu,
	emDecodeFormat_ins401,
};

class DecodeThread : public QThread
{
	Q_OBJECT

public:
	DecodeThread(QObject *parent);
	~DecodeThread();
	void run();
	void stop();
	void setFileFormat(int format);
	void setFileName(QString file);
	void makeOutPath(QString filename);
protected:
	void decode_openrtk_user();
	void decode_openrtk_inceptio();
	void decode_mixed_raw();
	void decode_imu();
	void decode_ins401();
private:
	int getFileSize(FILE* file);
private:
	bool m_isStop;
	int m_FileFormat;
	QString m_FileName;
	QString m_OutBaseName;
	QTime m_TimeCounter;
	Ins401::Ins401_decoder* ins401_decoder;
signals:
	void sgnProgress(int present, int msecs);
	void sgnFinished();
};
