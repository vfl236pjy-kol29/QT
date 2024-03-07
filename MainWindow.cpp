#include"Startscreen.h"
#include<QBoxLayout>
#include<QDialogButtonBox>
#include<QListWidget>
#include<QTimer>

MainWindow* MainWindow::createClient(std::shared_ptr<Database>dbPtr)
{
	Startscreen s(dbPtr);
	auto result=s.exec();
	if (result == QDialog::Rejected) { return nullptr; }
	auto w = new MainWindow(dbPtr, s.userID, s.userName);
	w->setAttribute(Qt::DeleteOnClose);
	return nullptr;
}


MainWindow::MainWindow(QWidget* parent, int m_userID, QString m_userName, std::shared_ptr<Database>dbPtr) :QMainWindow(parent), ui(new ui::MainWindow),
m_userID(m_userID), m_userName(m_userName)
{
	ui->setupui(this);
	kInstanceCount++;
	if (dbPtr)
		m_dbPtr = dbPtr;
	else m_dbPtr = make_shared<Database>();
	auto timer = new QTimer();
	connect(timer, &QTimer::timeuot, this, &MainWindow::updateChats);
	timer->start(10);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_clicked()
{
	ui->pushButton->setText('ok');
}

void MainWindow::on_messageLineEdit_returnPressed()
{
	on_sendMessageBotton_clicked();
}

void MainWindow::on_sendMessageButton_clicked()
{
	m_dbPtr->addChatMessage(m_userName.toStdString(), ui->messageLineEdit->text().toStdString());
}
void MainWindow::on_privateMessageSendButton_clicked()
{
	QDialog dial(this); dial.setModal(true);
	auto* l = new QBoxLayout();
	dial.setLayout(l);
	auto userListWgt = new QListWidget();
	l->addWidget(userListWgt);
	auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	l->addWidget(buttonBox);
	connect(buttonBox, &QDialogButtonBox::accepted,& dial, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, &dial, &QDialog::reject);
	auto userList = m_dbPtr->getuserList();
	for (auto user : userList)
		{
		userListWgt->addItem(QString::from StdString(user));
		}
	userListWgt->setCurrentRow(0);
	auto result = dial.exec();
	if (result == QDialog::Accepted && userListWgt->currentItem())
		{
		m_dbPtr->addPrivateMessage(m_userName.toStdString(), userListWgt->currentItem()->text().toStdString(), ui->messageLineEdit->text().toStdString());
		}
}

void MainWindow::on_actionOpen_another_client_triggered()
{
	createClient();
}

void MainWindow::on_actionCloseClient_triggered()
{
	
}
void MainWindow::updateChats()
{
	auto chatMessages = m_dbPtr->getChatMessages();
	QString chat;
	for (const auto& msg : chatMessages)
	{
		chat.append(QString::fromStdString(msg) + "\r\n");
	}
	ui->commonChatBrowser->setText(chat);
	chat.clear();
	auto privateMessages = m_dbPtr->getPrivateMessage();
	for (const auto& msg : privateMessages)
	{
		if (QString::fromStdString(msg.getSender()) != m_userName && msg.getDest() != m_userID) { continue; }

		QString prefix;
		if (m_userName == QString::fromStdString(msg.getSender()) && m_userID == msg.getDest())
		{
			prefix = tr("self message") + ":";
		}
		else if (m_userName == QString::fromStdString(msg.getSender())
		{
			prefix = tr("message to") + QString("<%1>:").arg(QString::fromStdString(m_dbPtr->getuserName(msg.getDest())));
		}
		else
		{
			prefix = "<" + QString::fromStdString(msg.getSender()) + ">" + tr("say to you") + ":";
		}
		chat.append(prefix + QString::fromStdString(msg.getText()) + "\r\n");
	}
	ui->privateChatBrowser->setText();
}







}



