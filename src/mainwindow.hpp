/***************************************************************************
                               mainwindow.hpp
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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QObject>

#include <sstream>

#include "data.hpp"
#include "converter.hpp"

namespace Ui {
class MainWindow;
} // namespace Ui

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(Data& _data, QWidget* parent=0);
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
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);

private:
	Ui::MainWindow* ui;
	Converter converter;
	Data& data;

	QString n_sch;
	QString out_dir;
	QString out_format;
	QString n_out;
	QString openfile_path;
};

void operator<<(MainWindow& obj, std::stringstream& in);

#endif // MAINWINDOW_HPP
