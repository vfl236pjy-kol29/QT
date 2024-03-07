#pragma once
#ifndef LOGINFORM_H
#define LOGINFORM_H
#include<memory>
#include<QWidget>
#include"Database.h"
namespace ui { class LoginForm; }

class LoginForm :public QWidget
{
	Q.OBJECT
			public:
				explicit LoginForm(QWidget* parent = nullptr);
				~LoginForm();
				void setDatabase(std::shared_ptr<Database>dbPtr);
signals:
	void registerRequested();
	void accepted();
	void rejected();
private slots:
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();
	void on_registrationPushButton_clicked();
			private:
				ui::LoginForm* ui;
				std::shared_ptr<Database>m_dbPtr;
};#endif