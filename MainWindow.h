#pragma once
#include<memory>
#include<QWidget>
#include<QMainWindow>
#include"Database.h"
namespace ui { class MainWindow; }

class MainWindow :public QMainWindow
{
	Q.OBJECT
public:
	explicit MainWindow(QWidget* parent = nullptr, int userID, QString userName, std::shared_ptr<Database>_dbPtr=nullptr);
	~MainWindow();
	static MainWindow* createClient(std::shared_ptr<Database>dbPtr=nullptr );
	static int kInstanceCount;
private slots:
	void on_messageLineEdit_returnPressed();
	void on_sendMessageButton_clicked();
	void on_privateMessageSendButton_clicked();
	void on_actionOpen_another_client_triggered();
		void on_actionCloseClient_triggered();
	void on_privateMessageSendButton_clicked();
	void updateChats();

private:
	ui::MainWindow* ui;
	std::shared_ptr<Database>m_dbPtr;
	int m_userID; QString m_userName;
}; #endif