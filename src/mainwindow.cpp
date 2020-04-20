/***************************************************************************
                               mainwindow.cpp
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@protonmail.ch
 ***************************************************************************/

/***************************************************************************
 *                                    	                                 *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <QFileDialog>

#include "logger.hpp"
#include "preview.hpp"
#include "mainwindow.hpp"
#include "ui_mainwindow.h"
using namespace std;

MainWindow::MainWindow(Data& _data, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	data(_data),
	converter(_data),
	n_sch(QString::fromStdString(_data.n_sch)),
	out_dir(QString::fromStdString(_data.out_dir)),
	out_format(QString::fromStdString(_data.out_format)) {
		ui->setupUi(this);
		ui->le_path_in->setText(n_sch);
		ui->le_path_out->setText(out_dir);
		ui->cb_format->addItem(tr(".kicad_pcb"));
		ui->cb_format->addItem(tr(".kicad_mod"));
		ui->cb_format->addItem(tr(".lht"));
		ui->cb_format->addItem(tr(".m"));
		ui->cb_format->setCurrentIndex(ui->cb_format->findText(QString::fromStdString(_data.out_format), Qt::MatchExactly));
		ui->rb_export_whole->setChecked((_data.export_each_block || _data.export_each_subst) ? false : true);
		ui->rb_export_each_subst->setChecked((_data.export_each_subst && !_data.export_each_block) ? true : false);
		ui->rb_export_each_block->setChecked((_data.export_each_block) ? true : false);
		}
	
MainWindow::~MainWindow() {
	delete ui;
	}

void MainWindow::on_pb_browse_in_clicked(void) {
	if(this->openfile_path.length() == 0) {
		this->openfile_path = QDir::currentPath();
		}

	n_sch=QFileDialog::getOpenFileName(this, tr("Open schematic"), this->openfile_path, tr("Qucs schematic (*.sch)"));

	if(!n_sch.length()) {
		ui->le_path_in->setText("");
		return;
		}

	this->openfile_path = QFileInfo(n_sch).path(); // store path for next time
	ui->le_path_in->setText(n_sch);
	}

void MainWindow::on_le_path_in_textChanged(const QString _n_sch) {
	n_sch=_n_sch;
	}

void MainWindow::on_pb_read_clicked(void) {

	ui->tb_log->clear();
	if(n_sch=="") {
		log_err << "ERROR : Nothing to read.\n";
	} else {
		converter.clear();
		converter.reset(n_sch.toStdString(), out_dir.toStdString(), out_format.toStdString());
		converter.read();
		ui->glw_preview->set(converter.get_tab_all(), converter.get_extrem_pos());
		}
	}

void MainWindow::on_le_path_in_returnPressed(void) {
	ui->tb_log->clear();
	if(n_sch=="") {
		log_err << "ERROR : Nothing to read.\n";
	} else {
		converter.clear();
		converter.reset(n_sch.toStdString(), out_dir.toStdString(), out_format.toStdString());
		converter.read();
		ui->glw_preview->set(converter.get_tab_all(), converter.get_extrem_pos());
		}
	}

void MainWindow::on_cb_format_currentIndexChanged(const QString _out_format) {
	out_format=_out_format;
	}

void MainWindow::on_pb_browse_out_clicked(void) {
	out_dir=QFileDialog::getExistingDirectory(this, tr("Output directory"), "./", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	ui->le_path_out->setText(out_dir);
	}

void MainWindow::on_le_path_out_textChanged(const QString _out_dir) {
	out_dir=_out_dir;
	}

void MainWindow::on_le_path_out_returnPressed(void) {
	vector<string> out_names;
	if(converter.size()) {
		converter.reset(n_sch.toStdString(), out_dir.toStdString(), out_format.toStdString());
		if(!converter.write(out_names)) {
			for(string out : out_names) {
				log_err << "Write : " << out << "\n";
				}
			}
	} else {
		log_err << "ERROR : Nothing to write.\n";
		}
	}

void MainWindow::on_pb_write_clicked(void) {
	vector<string> out_names;
	if(converter.size()) {
		converter.reset(n_sch.toStdString(), out_dir.toStdString(), out_format.toStdString());
		if(!converter.write(out_names)) {
			for(string out : out_names) {
				log_err << "Write : " << out << "\n";
				}
			}
	} else {
		log_err << "ERROR : Nothing to write.\n";
		}
	}

void MainWindow::on_rb_export_whole_toggled(bool const is_checked) {
	if(is_checked) {
		data.export_each_subst=false;
		data.export_each_block=false;
		}
	}

void MainWindow::on_rb_export_each_subst_toggled(bool const is_checked) {
	if(is_checked) {
		data.export_each_subst=true;
		data.export_each_block=false;
		}
	}

void MainWindow::on_rb_export_each_block_toggled(bool const is_checked) {
	if(is_checked) {
		data.export_each_subst=false;
		data.export_each_block=true;
		}
	}

void MainWindow::keyPressEvent(QKeyEvent *event) {
	if(event->key()==Qt::Key_Control) ui->glw_preview->setFCtrl(true);
	if(event->key()==Qt::Key_Shift) ui->glw_preview->setFShift(true);
	}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
	if(event->key()==Qt::Key_Control) ui->glw_preview->setFCtrl(false);
	if(event->key()==Qt::Key_Shift) ui->glw_preview->setFShift(false);
	}

void operator<<(MainWindow& obj, stringstream& in) {
	obj.ui->tb_log->insertPlainText(QString::fromStdString(in.str()));
	}

