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

MainWindow::MainWindow(Element**& _tab_all, int& _nelem, QString _n_sch, QString _out_dir, QString _out_format, QWidget* parent) :
	tab_all(_tab_all),
	nelem(_nelem),
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
	for(int ielem=0;ielem<nelem;ielem++) {
		delete tab_all[ielem];
		}	
	if(nelem) delete[] tab_all;
	}

void MainWindow::on_pb_browse_in_clicked(void) {
	n_sch=QFileDialog::getOpenFileName(this, tr("Open schematic"), "./", tr("Qucs schematic (*.sch)"));
	ui->le_path_in->setText(n_sch);
	}

void MainWindow::on_le_path_in_textChanged(const QString _n_sch) {
	n_sch=_n_sch;
	}

void MainWindow::on_pb_read_clicked(void) {
	if(nelem!=0) {
		for(int ielem=0;ielem<nelem;ielem++) {
			delete tab_all[ielem];
			}
		nelem=0;
		}
	parser(tab_all, n_sch.toStdString(), nelem);
	xycalculator(tab_all, nelem);
	}

void MainWindow::on_le_path_in_returnPressed(void) {
	if(nelem!=0) {
		for(int ielem=0;ielem<nelem;ielem++) {
			delete tab_all[ielem];
			}
		nelem=0;
		}
	parser(tab_all, n_sch.toStdString(), nelem);
	xycalculator(tab_all, nelem);
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

void MainWindow::on_pb_write_clicked(void) {
	if(nelem) {
		layoutwriter(tab_all, nelem, n_sch.toStdString(), out_dir.toStdString(), out_format.toStdString());
		ui->l_debug->setText("Write ok.");
	} else {
		ui->l_debug->setText("ERROR : Nothing to write.");
		}
	}

