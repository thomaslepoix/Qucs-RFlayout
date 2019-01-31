/***************************************************************************
                               mainwindow.h
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@gmail.com
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

#include <QMainWindow>
#include <QFileDialog>
//#include <QString>

#include "parser.h"
#include "xycalculator.h"
#include "layoutwriter.h"

#include "eqn.h"
#include "pac.h"
#include "mcorn.h"
#include "mcross.h"
#include "mcoupled.h"
#include "mgap.h"
#include "mmbend.h"
#include "mlin.h"
#include "mopen.h"
#include "mrstub.h"
#include "mstep.h"
#include "mtee.h"
#include "mvia.h"

namespace Ui {
	class MainWindow;
	}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(Element**& tab_all, int& nelem, QString _n_sch, QString out_dir, QString out_format, QWidget* parent=0);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
	Element** tab_all;
	int nelem;
	QString n_sch;
	QString out_dir;
	QString out_format;
	QString n_out;
};

#endif // MAINWINDOW_H
