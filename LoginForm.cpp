#include"loginform.h"
#include"ui_loginform.h"
#include<QMessageBox>
#include"Database.h"

LoginForm::LoginForm(QWidget* parent) :QWidget(parent), ui(new ui::LoginForm)
{
	ui->setupUI(this);
}
LoginForm::~LoginForm()
{
	delete ui;
}

void LoginForm::on_registrationPushButton_clicked()
{
	emit registerRequested();
}

void LoginForm::setDatabase(std::shared_ptr<Database>dbPtr)
{
	m_dbPtr = dbPtr;
}

void LoginForm::on_buttonBox_rejected()
{
	emit rejected();
}

void LoginForm::on_buttonBox_accepted()
{
	auto userID = m_dbPtr->checkPassword(ui->loginEdit->text().toStdString(), ui->passwordEdit->text().toStdString());
	if (userID == -1)
			{
		QMessageBox::critical(this, tr("Error"), tr("password is wrong"));
		return;
			}
	emit accepted(userID, ui->loginEdit->test());
}


