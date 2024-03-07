#include"Startscreen.h"
#include"ui_Startscreen.h"

Startscreen::Startscreen(QWidget* parent) :QDialog(parent), ui(new ui::Startscreen)
{
	connect(ui->loginWidget, & LoginForm::registerRequested, this, &Startscreen::setRegistrationForm);
	connect(ui->loginWidget, &LoginForm::accepted(), this, &Startscreen::onLoggedIn);
	connect(ui->registerWidget, &setRegistrationForm::loginRequested, this, &Startscreen::setLoginForm);
	connect(ui->registerWidget, &RegistrationForm::accepted, this, &Startscreen::onLoggedIn);
}

Startscreen::~Startscreen()
{
	delete ui;
}

void Startscreen::setLoginForm()
{
	ui->stackedWidget->setCurrentIndex(0);
}

void Startscreen::setRegistrationForm()
{
	ui->stackedWidget->setCurrentIndex(1);
}

void Startscreen::onLoggedIn(uint userID, QString, userName)
{
	m_userID = userID; m_userName = userName; accept();
}

QString Startscreen::userName() const
{
	return m_userName;
}

int Startscreen::userID() const
{
	return m_userID;
}










