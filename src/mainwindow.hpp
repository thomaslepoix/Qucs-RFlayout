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
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QObject>

#include <memory>
#include <sstream>

#include "converter.hpp"
#include "data.hpp"
#include "logger.hpp"
#include "ui_mainwindow.h"

//******************************************************************************
class MainWindow : public QMainWindow, public Loggable {
	Q_OBJECT
private:
	std::unique_ptr<Ui::MainWindow> ui;
	Data& data;
	Converter converter;

	QString openfile_path;

	void add_action(QString const action_str="Shift port", QString const val1="", QString const val2="", QString const val3="");
	void read();
	void write();

	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;

	void log(std::stringstream& in) override;

private slots:
	void on_cb_format_currentTextChanged(const QString&  out_format);
	void on_cb_specify_netlist_stateChanged(int const state);
	void on_cb_oems_pkg_stateChanged(int const state);
	void on_cb_oems_sort_metalresmesh_stateChanged(int const state);
	void on_le_oems_end_criteria_textChanged(QString const oems_end_criteria);
	void on_le_oems_highres_div_textChanged(QString const oems_highres_div);
	void on_le_oems_metalres_div_textChanged(QString const oems_metalres_div);
	void on_le_oems_nf2ff_center_textChanged(QString const oems_nf2ff_center);
	void on_le_oems_substres_div_textChanged(QString const oems_substres_div);
	void on_le_oems_timeres_textChanged(QString const oems_timeres);
	void on_le_path_in_returnPressed();
	void on_le_path_in_textChanged(QString const n_sch);
	void on_le_path_net_returnPressed();
	void on_le_path_net_textChanged(QString const n_net);
	void on_le_path_out_returnPressed();
	void on_le_path_out_textChanged(QString const out_dir);
	void on_pb_add_clicked();
	void on_pb_browse_in_clicked();
	void on_pb_browse_net_clicked();
	void on_pb_browse_out_clicked();
	void on_pb_read_clicked();
	void on_pb_remove_clicked();
	void on_pb_write_clicked();
	void on_rb_export_each_block_toggled(bool const is_checked);
	void on_rb_export_each_subst_toggled(bool const is_checked);
	void on_rb_export_whole_toggled(bool const is_checked);

public:
	explicit MainWindow(Data& _data, QWidget* parent=0);
	~MainWindow()=default;
};

#endif // MAINWINDOW_HPP
