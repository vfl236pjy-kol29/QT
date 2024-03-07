#pragma once
#ifndef STARTSCREEN_H
#define STARTSCREEN_H
#include<QDialog>
namespace ui { class Startscreen; }

class Startscreen :public QDialog
{
			public:
				explisit Startscreen();
				~Startscreen();
				void setLoginForm();
				void setRegistrationForm();
				int userID const;
				QString userName() const;
			private:
				ui::Startscreen* ui;
				int m_userID();
				QString m_userName;
public slots:
	void onLoggedIn(uint userID, QString userName);
}; #endif