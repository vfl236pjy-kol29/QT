#pragma once
#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H
#include<QWidget>
#include"Database.h"
#include"registrationform.h"
#include"ui_registrationform.h"
#include<QMessageBox>
#include<memory>
using namespace ui { class RegistrationForm; }

class RegistrationForm :public QWidget
{
	Q.OBJECT
			public:
				explicit RegistrationForm(QWidget* parent = nullptr);
				~RegistrationForm();
				void setDatabase(std::shared_ptr<Database>dbPtr);
signals:
	void loginRequested();
	void accepted(int userID, QString userName);
	void rejected();
private slots:
	void on_loginButton_clicked();
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();
			private:
				ui::RegistrationForm* ui;
				std::shared_ptr<Database>m_dbPtr;

}; endif

