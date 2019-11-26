/***************************************************************************
                               mainwindow.h
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@protonmail.ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <sstream>
#include <QMainWindow>
#include <QFileDialog>

#include "logger.h"
#include "parser.h"
#include "xycalculator.h"
#include "layoutwriter.h"
#include "preview.h"

#include "microstrip/eqn.h"
#include "microstrip/pac.h"
#include "microstrip/mcorn.h"
#include "microstrip/mcross.h"
#include "microstrip/mcoupled.h"
#include "microstrip/mgap.h"
#include "microstrip/mmbend.h"
#include "microstrip/mlin.h"
#include "microstrip/mopen.h"
#include "microstrip/mrstub.h"
#include "microstrip/mstep.h"
#include "microstrip/mtee.h"
#include "microstrip/mvia.h"

namespace Ui {
class MainWindow;
} // namespace UI

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QString _n_sch, QString _out_dir, QString _out_format, QWidget* parent=0);
	~MainWindow();
	friend void operator<<(MainWindow& obj, std::stringstream& in);

private slots:
	void on_pb_read_clicked(void);
	void on_le_path_in_textChanged(const QString _n_sch);
	void on_le_path_in_returnPressed(void);
	void on_cb_format_currentIndexChanged(const QString _out_format);
	void on_pb_browse_in_clicked(void);
	void on_pb_browse_out_clicked(void);
	void on_le_path_out_textChanged(const QString _out_dir);
	void on_le_path_out_returnPressed(void);
	void on_pb_write_clicked(void);

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

private:
	Ui::MainWindow *ui;
	std::vector<std::shared_ptr<Element>> tab_all;
	long double extrem_pos[4]={0.0, 0.0, 0.0, 0.0};
	QString n_sch;
	QString out_dir;
	QString out_format;
	QString n_out;
	QString openfile_path;

//	int previewprinter(/*Element**& tab_all, int& nelem*/);
};

void operator<<(MainWindow& obj, std::stringstream& in);

#endif // MAINWINDOW_H
