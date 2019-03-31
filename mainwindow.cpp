/***************************************************************************
                               mainwindow.cpp
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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString _n_sch, QString _out_dir, QString _out_format, QWidget* parent) :
	n_sch(_n_sch),
	out_dir(_out_dir),
	out_format(_out_format),
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    	ui->setupUi(this);
		ui->le_path_in->setText(n_sch);
		ui->le_path_out->setText(out_dir);
		ui->cb_format->addItem(tr(".kicad_pcb"));
		ui->cb_format->addItem(tr(".kicad_mod"));
		ui->cb_format->addItem(tr(".lht"));
		ui->cb_format->setCurrentIndex(ui->cb_format->findText(_out_format, Qt::MatchExactly));
		}
	
MainWindow::~MainWindow() {
    delete ui;
	}

void MainWindow::on_pb_browse_in_clicked(void) {
	n_sch=QFileDialog::getOpenFileName(this, tr("Open schematic"), "./", tr("Qucs schematic (*.sch)"));
	ui->le_path_in->setText(n_sch);
	}

void MainWindow::on_le_path_in_textChanged(const QString _n_sch) {
	n_sch=_n_sch;
	}

void MainWindow::on_pb_read_clicked(void) {
	if(n_sch=="") {
		ui->l_debug->setText("ERROR : Nothing to read.");
	} else {
		tab_all.clear();
		parser(tab_all, n_sch.toStdString());
		xycalculator(tab_all, extrem_pos);
		ui->glw_preview->set(tab_all, extrem_pos);
		}
	}

void MainWindow::on_le_path_in_returnPressed(void) {
	if(n_sch=="") {
		ui->l_debug->setText("ERROR : Nothing to read.");
	} else {
		tab_all.clear();
		parser(tab_all, n_sch.toStdString());
		xycalculator(tab_all, extrem_pos);
		ui->glw_preview->set(tab_all, extrem_pos);
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
	if(tab_all.size()) {
		layoutwriter(tab_all, extrem_pos, n_sch.toStdString(), out_dir.toStdString(), out_format.toStdString());
		ui->l_debug->setText("Write ok.");
	} else {
		ui->l_debug->setText("ERROR : Nothing to write.");
		}
	}

void MainWindow::on_pb_write_clicked(void) {
	if(tab_all.size()) {
		layoutwriter(tab_all, extrem_pos, n_sch.toStdString(), out_dir.toStdString(), out_format.toStdString());
		ui->l_debug->setText("Write ok.");
	} else {
		ui->l_debug->setText("ERROR : Nothing to write.");
		}
	}

void MainWindow::keyPressEvent(QKeyEvent *event) {
	if(event->key()==Qt::Key_Control) ui->glw_preview->flag_ctrl=true;
	if(event->key()==Qt::Key_Shift) ui->glw_preview->flag_shift=true;
	}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
	if(event->key()==Qt::Key_Control) ui->glw_preview->flag_ctrl=false;
	if(event->key()==Qt::Key_Shift) ui->glw_preview->flag_shift=false;
	}
