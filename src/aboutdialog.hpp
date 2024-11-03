///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#pragma once

#ifndef QRFL_MINIMAL

#include <QDialog>
#include <QObject>

#include <memory>

#include "ui_aboutdialog.h"

//******************************************************************************
class AboutDialog : public QDialog {
	Q_OBJECT
private:
	std::unique_ptr<Ui::AboutDialog> ui;

private slots:
	void on_pb_ok_clicked();

public:
	explicit AboutDialog(QWidget* parent=0);
	~AboutDialog()=default;
};

#endif // QRFL_MINIMAL
