#include"registrationform.h"
#include"ui_registrationform.h"

RegistrationForm::RegistrationForm(QWidget* parent) :QWidget(parent), ui(new ui::RegistrationForm)
{
	ui->setupUi(this);
}
RegistrationForm::~RegistrationForm()
{
	delete ui;
}
void RegistrationForm::on_loginButton_clicked()
{
	emit loginRequested();
}
void RegistrationForm::on_buttonBox_accepted()
{
	if (ui->passwordEdit->text() != ui->passwordConfirmEdit->text())
	{
		QMessageBox::critical(this, tr("Error"), tr("password not match"));
		return;
	}
	auto userID = m_dbPtr->addUser(ui->loginEdit->text().toStdString(), ui->passwordEdit->text().toStdString());
	switch (userID)
	{
	case(-1):
		QMessageBox::critical(this, tr("Error"), tr("Incorect login"));
		return;
	case(-2):
		QMessageBox::critical(this, tr("Error"), tr("Login already exists"));
		return;
	default:
		emit accepted(userID, ui->loginEdit->text());
	}
}
void RegistrationForm::on_buttonBox_rejected()
{
	emit rejected();
}

void RegistrationForm::setDatabase(std::shared_ptr<Database>dbPtr)
{
	m_dbPtr = dbPtr;
}