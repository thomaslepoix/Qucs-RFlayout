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
using namespace std;

//******************************************************************************
MainWindow::MainWindow(Data& _data, QWidget *parent) :
		QMainWindow(parent),
		ui(std::make_unique<Ui::MainWindow>()),
		data(_data),
		converter(_data),
		n_sch(QString::fromStdString(_data.n_sch)),
		n_net(QString::fromStdString(_data.n_net)),
		out_dir(QString::fromStdString(_data.out_dir)),
		out_format(QString::fromStdString(_data.out_format)),
		openfile_path(QDir::currentPath()) {
	ui->setupUi(this);
	ui->le_path_in->setText(n_sch);
	ui->le_path_net->setText(n_net);
	ui->le_path_out->setText(out_dir);
	ui->cb_format->addItem(tr(".kicad_pcb"));
	ui->cb_format->addItem(tr(".kicad_mod"));
	ui->cb_format->addItem(tr(".lht"));
	ui->cb_format->addItem(tr(".m"));
	ui->cb_format->setCurrentText(QString::fromStdString(_data.out_format));
	ui->rb_export_whole->setChecked((_data.export_each_block || _data.export_each_subst) ? false : true);
	ui->rb_export_each_subst->setChecked((_data.export_each_subst && !_data.export_each_block) ? true : false);
	ui->rb_export_each_block->setChecked((_data.export_each_block) ? true : false);
	ui->cb_specify_netlist->setCheckState((_data.n_net=="") ? Qt::Unchecked : Qt::Checked);
	ui->le_oems_highres_div->setText(QString::number(data.oems_highres_div));
	ui->le_oems_metalres_div->setText(QString::number(data.oems_metalres_div));
	ui->le_oems_substres_div->setText(QString::number(data.oems_substres_div));
	ui->le_oems_timeres->setText(QString::number(data.oems_timeres));
	ui->le_oems_nf2ff_center->setText(QString::fromStdString(data.oems_nf2ff_center));
	ui->tw_actions->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

	for(std::tuple<unsigned long, std::string, std::string> arg : data.port_shift_args) {
		add_action("Shift port",
			QString::number(get<0>(arg)),
			QString::fromStdString(get<1>(arg)),
			QString::fromStdString(get<2>(arg)));
		}
	for(std::tuple<unsigned long, std::string, std::string> arg : data.port_size_args) {
		add_action("Resize port",
			QString::number(get<0>(arg)),
			QString::fromStdString(get<1>(arg)),
			QString::fromStdString(get<2>(arg)));
		}
	for(std::string excluded : data.excluded_elements) {
		add_action("Exclude", QString::fromStdString(excluded));
		}
	for(std::string used : data.used_elements) {
		add_action("Use", QString::fromStdString(used));
		}
	}

//******************************************************************************
void MainWindow::add_action(QString const action_str, QString const val1, QString const val2, QString const val3) {
	int row=ui->tw_actions->rowCount();
	ui->tw_actions->insertRow(row);
	ui->tw_actions->setCellWidget(row, 0, new QComboBox);
	ui->tw_actions->setItem(row, 1, new QTableWidgetItem);
	ui->tw_actions->setItem(row, 2, new QTableWidgetItem);
	ui->tw_actions->setItem(row, 3, new QTableWidgetItem);

	QComboBox* action=qobject_cast<QComboBox*>(ui->tw_actions->cellWidget(row, 0));
	action->addItem(tr("Shift port"));
	action->addItem(tr("Resize port"));
	action->addItem(tr("Exclude"));
	action->addItem(tr("Use"));

	connect(action, &QComboBox::currentTextChanged, [this, action](QString const& text) {
		int row=0;
		bool is_found=false;

		// Find row
		for(int i=0;i<ui->tw_actions->rowCount();i++) {
			if(ui->tw_actions->cellWidget(i, 0)==action) {
				row=i;
				is_found=true;
				break;
				}
			}
		if(!is_found)
			return;

		if(text=="Shift port") {
			ui->tw_actions->item(row, 2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsEnabled);
			ui->tw_actions->item(row, 3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsEnabled);
			ui->tw_actions->item(row, 1)->setToolTip("Number of port to shift");
			ui->tw_actions->item(row, 2)->setToolTip("X shift (m)");
			ui->tw_actions->item(row, 3)->setToolTip("Y shift (m)");
		} else if(text=="Resize port") {
			ui->tw_actions->item(row, 2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsEnabled);
			ui->tw_actions->item(row, 3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsEnabled);
			ui->tw_actions->item(row, 1)->setToolTip("Number of port to resize");
			ui->tw_actions->item(row, 2)->setToolTip("X size (m)");
			ui->tw_actions->item(row, 3)->setToolTip("Y size (m)");
		} else if(text=="Exclude") {
			ui->tw_actions->item(row, 2)->setFlags(Qt::NoItemFlags);
			ui->tw_actions->item(row, 3)->setFlags(Qt::NoItemFlags);
			ui->tw_actions->item(row, 1)->setToolTip("Label of element to exclude");
			ui->tw_actions->item(row, 2)->setToolTip("");
			ui->tw_actions->item(row, 3)->setToolTip("");
		} else if(text=="Use") {
			ui->tw_actions->item(row, 2)->setFlags(Qt::NoItemFlags);
			ui->tw_actions->item(row, 3)->setFlags(Qt::NoItemFlags);
			ui->tw_actions->item(row, 1)->setToolTip("Label of element not to exclude (exclude every others)");
			ui->tw_actions->item(row, 2)->setToolTip("");
			ui->tw_actions->item(row, 3)->setToolTip("");
			}
		ui->tw_actions->item(row, 1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsEnabled);
		ui->tw_actions->item(row, 1)->setText("");
		ui->tw_actions->item(row, 2)->setText("");
		ui->tw_actions->item(row, 3)->setText("");
		});

	action->setCurrentText(action_str);
	if(action_str=="Shift port" || action_str=="Resize port") {
		ui->tw_actions->item(row, 1)->setText(val1);
		ui->tw_actions->item(row, 2)->setText(val2);
		ui->tw_actions->item(row, 3)->setText(val3);
	} else if(action_str=="Exclude" || action_str=="Use") {
		ui->tw_actions->item(row, 1)->setText(val1);
		}
	}

//******************************************************************************
void MainWindow::read(void) {
	ui->tb_log->clear();
	if(n_sch=="") {
		log_err << "ERROR : Nothing to read.\n";
	} else {
		converter.clear();
		converter.reset(n_sch.toStdString(), n_net.toStdString(), out_dir.toStdString(), out_format.toStdString());

		for(int i=0;i<ui->tw_actions->rowCount();i++) {
			QString action_str=qobject_cast<QComboBox*>(ui->tw_actions->cellWidget(i, 0))->currentText();
			if(action_str=="Shift port") {
				data.port_shift_args.push_back(make_tuple(
					ui->tw_actions->item(i, 1)->text().toLong(),
					ui->tw_actions->item(i, 2)->text().toStdString(),
					ui->tw_actions->item(i, 3)->text().toStdString()));
			} else if(action_str=="Resize port") {
				data.port_size_args.push_back(make_tuple(
					ui->tw_actions->item(i, 1)->text().toLong(),
					ui->tw_actions->item(i, 2)->text().toStdString(),
					ui->tw_actions->item(i, 3)->text().toStdString()));
			} else if(action_str=="Exclude") {
				data.excluded_elements.push_back(ui->tw_actions->item(i, 1)->text().toStdString());
			} else if(action_str=="Use") {
				data.used_elements.push_back(ui->tw_actions->item(i, 1)->text().toStdString());
				}
			}

		converter.read();
		ui->glw_preview->set(converter.get_tab_all(), converter.get_extrem_pos());
		}

	}

//******************************************************************************
void MainWindow::write(void) {
	vector<string> out_names;
	if(converter.size()) {
		converter.reset(n_sch.toStdString(), n_net.toStdString(), out_dir.toStdString(), out_format.toStdString());
		if(!converter.write(out_names)) {
			for(string out : out_names) {
				log_err << "Write : " << out << "\n";
				}
			}
	} else {
		log_err << "ERROR : Nothing to write.\n";
		}
	}

//******************************************************************************
void MainWindow::on_cb_format_currentIndexChanged(const QString _out_format) {
	ui->gb_oems->setEnabled((_out_format==".m") ? true : false);
	out_format=_out_format;
	}

//******************************************************************************
void MainWindow::on_cb_specify_netlist_stateChanged(int const state) {
	if(state==Qt::Unchecked) {
		ui->l_netlist->setEnabled(false);
		ui->le_path_net->setEnabled(false);
		ui->pb_browse_net->setEnabled(false);
		data.n_net="";
	} else if(state==Qt::Checked) {
		ui->l_netlist->setEnabled(true);
		ui->le_path_net->setEnabled(true);
		ui->pb_browse_net->setEnabled(true);
		data.n_net=n_net.toStdString();
		}
	}

//******************************************************************************
void MainWindow::on_le_oems_highres_div_textChanged(QString const oems_highres_div) {
	data.oems_highres_div=(unsigned int) oems_highres_div.toFloat();
	}

//******************************************************************************
void MainWindow::on_le_oems_metalres_div_textChanged(QString const oems_metalres_div) {
	data.oems_metalres_div=(unsigned int) oems_metalres_div.toFloat();
	}

//******************************************************************************
void MainWindow::on_le_oems_substres_div_textChanged(QString const oems_substres_div) {
	data.oems_substres_div=(unsigned int) oems_substres_div.toFloat();
	}

//******************************************************************************
void MainWindow::on_le_oems_timeres_textChanged(QString const oems_timeres) {
	data.oems_timeres=(unsigned int) oems_timeres.toFloat();
	}

//******************************************************************************
void MainWindow::on_le_oems_nf2ff_center_textChanged(QString const oems_nf2ff_center) {
	data.oems_nf2ff_center=oems_nf2ff_center.toStdString();
	}

//******************************************************************************
void MainWindow::on_le_path_in_returnPressed(void) {
	read();
	}

//******************************************************************************
void MainWindow::on_le_path_in_textChanged(QString const _n_sch) {
	n_sch=_n_sch;
	}

//******************************************************************************
void MainWindow::on_le_path_net_returnPressed(void) {
	read();
	}

//******************************************************************************
void MainWindow::on_le_path_net_textChanged(QString const _n_net) {
	n_net=_n_net;
	data.n_net=_n_net.toStdString();
	}

//******************************************************************************
void MainWindow::on_le_path_out_returnPressed(void) {
	write();
	}

//******************************************************************************
void MainWindow::on_le_path_out_textChanged(QString const _out_dir) {
	out_dir=_out_dir;
	}

//******************************************************************************
void MainWindow::on_pb_add_clicked(void) {
	add_action();
	}

//******************************************************************************
void MainWindow::on_pb_browse_in_clicked(void) {
	n_sch=QFileDialog::getOpenFileName(this, tr("Open schematic"), openfile_path, tr("Qucs schematic (*.sch)"));

	if(!n_sch.length()) {
		ui->le_path_in->setText("");
		return;
		}

	openfile_path=QFileInfo(n_sch).path(); // Store path for next time.
	ui->le_path_in->setText(n_sch);
	}

//******************************************************************************
void MainWindow::on_pb_browse_net_clicked(void) {
	n_net=QFileDialog::getOpenFileName(this, tr("Open netlist"), openfile_path, tr("Qucs netlist (*.net)"));

	if(!n_net.length()) {
		ui->le_path_net->setText("");
		return;
		}

	openfile_path=QFileInfo(n_net).path(); // Store path for next time.
	ui->le_path_net->setText(n_net);
	}

//******************************************************************************
void MainWindow::on_pb_browse_out_clicked(void) {
	out_dir=QFileDialog::getExistingDirectory(this, tr("Output directory"), "./", QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
	ui->le_path_out->setText(out_dir);
	}

//******************************************************************************
void MainWindow::on_pb_read_clicked(void) {
	read();
	}

//******************************************************************************
void MainWindow::on_pb_remove_clicked(void) {
	ui->tw_actions->removeRow(ui->tw_actions->currentRow());
	}

//******************************************************************************
void MainWindow::on_pb_write_clicked(void) {
	write();
	}

//******************************************************************************
void MainWindow::on_rb_export_each_block_toggled(bool const is_checked) {
	if(is_checked) {
		data.export_each_subst=false;
		data.export_each_block=true;
		}
	}

//******************************************************************************
void MainWindow::on_rb_export_each_subst_toggled(bool const is_checked) {
	if(is_checked) {
		data.export_each_subst=true;
		data.export_each_block=false;
		}
	}

//******************************************************************************
void MainWindow::on_rb_export_whole_toggled(bool const is_checked) {
	if(is_checked) {
		data.export_each_subst=false;
		data.export_each_block=false;
		}
	}

//******************************************************************************
void MainWindow::keyPressEvent(QKeyEvent* event) {
	if(event->key()==Qt::Key_Control) ui->glw_preview->setFCtrl(true);
	if(event->key()==Qt::Key_Shift) ui->glw_preview->setFShift(true);
	}

//******************************************************************************
void MainWindow::keyReleaseEvent(QKeyEvent* event) {
	if(event->key()==Qt::Key_Control) ui->glw_preview->setFCtrl(false);
	if(event->key()==Qt::Key_Shift) ui->glw_preview->setFShift(false);
	}

//******************************************************************************
void MainWindow::log(stringstream& in) {
	ui->tb_log->insertPlainText(QString::fromStdString(in.str()));
	}
