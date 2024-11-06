///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#ifndef QRFL_MINIMAL

#include <QCoreApplication>
#include <QDesktopServices>
#include <QDir>
#include <QFileDialog>
#include <QString>
#include <QUrl>

#include "logger.hpp"
#include "preview.hpp"
#include "aboutdialog.hpp"
#include "mainwindow.hpp"
using namespace std;

//******************************************************************************
MainWindow::MainWindow(Data& _data, string const& gui_theme, QWidget* parent)
: QMainWindow(parent)
, ui(std::make_unique<Ui::MainWindow>())
, data(_data)
, converter(_data)
, openfile_path(QDir::currentPath()) {
	ui->setupUi(this);
	ui->le_path_in->setText(QString::fromStdString(_data.n_sch.generic_string()));
	ui->le_path_net->setText(QString::fromStdString(_data.n_net.generic_string()));
	ui->le_path_out->setText(QString::fromStdString(_data.out_dir.generic_string()));
	QString out_format(QString::fromStdString(_data.out_format));
	ui->cb_format->addItem(tr(".kicad_pcb"));
	ui->cb_format->addItem(tr(".kicad_mod"));
	ui->cb_format->addItem(tr(".lht"));
	ui->cb_format->addItem(tr(".m"));
	ui->cb_format->addItem(tr(".svg"));
	ui->cb_format->setCurrentText(out_format);
	ui->rb_export_whole->setChecked((_data.export_each_block || _data.export_each_subst) ? false : true);
	ui->rb_export_each_subst->setChecked((_data.export_each_subst && !_data.export_each_block) ? true : false);
	ui->rb_export_each_block->setChecked((_data.export_each_block) ? true : false);
	ui->cb_specify_netlist->setCheckState((_data.n_net=="") ? Qt::Unchecked : Qt::Checked);
	ui->le_oems_end_criteria->setText(QString::fromStdString(data.oems_end_criteria));
	ui->le_oems_highres_div->setText(QString::number(data.oems_highres_div));
	ui->le_oems_metalres_div->setText(QString::number(data.oems_metalres_div));
	ui->le_oems_nf2ff_center->setText(QString::fromStdString(data.oems_nf2ff_center));
	ui->le_oems_substres_div->setText(QString::number(data.oems_substres_div));
	ui->le_oems_timeres->setText(QString::number(data.oems_timeres));
	ui->cb_oems_pkg->setCheckState(_data.oems_pkg ? Qt::Checked : Qt::Unchecked);
	ui->cb_oems_sort_metalresmesh->setCheckState(_data.oems_sort_metalresmesh ? Qt::Checked : Qt::Unchecked);
	ui->cb_transparency->setCheckState(Qt::Unchecked);
	ui->tw_actions->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

	ui->glw_preview->setTheme(gui_theme);
	for(auto const& theme : ui->glw_preview->themes) {
		auto* const action = a_themes.emplace_back(make_unique<QAction>(QString::fromStdString(string(theme.name)), ui->ag_themes)).get();
		action->setCheckable(true);
		action->setChecked((theme.name==ui->glw_preview->getTheme()) ? true : false);
		ui->m_theme->addAction(action);
		}

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

#ifndef __APPLE__
	setWindowIcon(QPixmap(":/qucsrflayout.ico"));
#endif // __APPLE__
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
void MainWindow::read() {
	ui->tb_log->clear();
	if(data.n_sch=="") {
		log_err << "ERROR : Nothing to read.\n";
	} else {
		converter.reset();

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
		ui->glw_preview->set(converter.get_all_elements(), converter.get_extrem_pos());
		}

	}

//******************************************************************************
void MainWindow::write() {
	vector<string> out_names;
	if(converter.size()) {
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
void MainWindow::on_a_about_triggered() {
	AboutDialog about(this);
	about.exec();
	}

//******************************************************************************
static void open_doc_file(QString const& name) {
	static QString const docdir = QDir::cleanPath(QCoreApplication::applicationDirPath() + "/../share/doc/qucsrflayout");
	QDesktopServices::openUrl(QUrl(docdir + "/" + name + ".pdf"));
	}

//******************************************************************************
void MainWindow::on_a_detail_mcorn_triggered() { open_doc_file("detail_mcorn"); }
void MainWindow::on_a_detail_mcoupled_triggered() { open_doc_file("detail_mcoupled"); }
void MainWindow::on_a_detail_mcross_triggered() { open_doc_file("detail_mcross"); }
void MainWindow::on_a_detail_mlin_triggered() { open_doc_file("detail_mlin"); }
void MainWindow::on_a_detail_mmbend_triggered() { open_doc_file("detail_mmbend"); }
void MainWindow::on_a_detail_mrstub_triggered() { open_doc_file("detail_mrstub"); }
void MainWindow::on_a_detail_mtee_triggered() { open_doc_file("detail_mtee"); }
void MainWindow::on_a_oems_mesh_mcorn_triggered() { open_doc_file("oems_mesh_mcorn"); }
void MainWindow::on_a_oems_mesh_mcoupled_triggered() { open_doc_file("oems_mesh_mcoupled"); }
void MainWindow::on_a_oems_mesh_mcross_triggered() { open_doc_file("oems_mesh_mcross"); }
void MainWindow::on_a_oems_mesh_mgap_triggered() { open_doc_file("oems_mesh_mgap"); }
void MainWindow::on_a_oems_mesh_mlin_triggered() { open_doc_file("oems_mesh_mlin"); }
void MainWindow::on_a_oems_mesh_mmbend_triggered() { open_doc_file("oems_mesh_mmbend"); }
void MainWindow::on_a_oems_mesh_mopen_triggered() { open_doc_file("oems_mesh_mopen"); }
void MainWindow::on_a_oems_mesh_mrstub_triggered() { open_doc_file("oems_mesh_mrstub"); }
void MainWindow::on_a_oems_mesh_mstep_triggered() { open_doc_file("oems_mesh_mstep"); }
void MainWindow::on_a_oems_mesh_mtee_triggered() { open_doc_file("oems_mesh_mtee"); }
void MainWindow::on_a_oems_mesh_mvia_triggered() { open_doc_file("oems_mesh_mvia"); }
void MainWindow::on_a_oems_mesh_pac_triggered() { open_doc_file("oems_mesh_pac"); }
void MainWindow::on_a_table_orientation_triggered() { open_doc_file("table_orientation"); }
void MainWindow::on_a_topology_mcorn_triggered() { open_doc_file("topology_mcorn"); }
void MainWindow::on_a_topology_mcoupled_triggered() { open_doc_file("topology_mcoupled"); }
void MainWindow::on_a_topology_mcross_triggered() { open_doc_file("topology_mcross"); }
void MainWindow::on_a_topology_mgap_triggered() { open_doc_file("topology_mgap"); }
void MainWindow::on_a_topology_mlin_triggered() { open_doc_file("topology_mlin"); }
void MainWindow::on_a_topology_mmbend_triggered() { open_doc_file("topology_mmbend"); }
void MainWindow::on_a_topology_mopen_triggered() { open_doc_file("topology_mopen"); }
void MainWindow::on_a_topology_mrstub_triggered() { open_doc_file("topology_mrstub"); }
void MainWindow::on_a_topology_mstep_triggered() { open_doc_file("topology_mstep"); }
void MainWindow::on_a_topology_mtee_triggered() { open_doc_file("topology_mtee"); }
void MainWindow::on_a_topology_mvia_triggered() { open_doc_file("topology_mvia"); }

//******************************************************************************
void MainWindow::on_a_tutorial_oems_triggered() {
	QDesktopServices::openUrl(QUrl(QRFL_OEMS_TUTORIAL));
	}

//******************************************************************************
void MainWindow::on_ag_themes_triggered(QAction* const action) {
	ui->glw_preview->setTheme(action->text().toStdString());
	ui->glw_preview->update();
	}

//******************************************************************************
void MainWindow::on_cb_format_currentTextChanged(QString const& out_format) {
	ui->gb_oems->setEnabled((out_format==".m") ? true : false);
	ui->glw_preview->setF2D((out_format==".kicad_pcb"
	                       ||out_format==".kicad_mod"
	                       ||out_format==".lht"
	                       ||out_format==".svg")
	                       ? true : false);
	ui->glw_preview->resetView();
	data.out_format=out_format.toStdString();
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
		data.n_net=ui->le_path_net->text().toStdString();
		}
	}

//******************************************************************************
void MainWindow::on_cb_transparency_stateChanged(int const state) {
	if(state==Qt::Unchecked) {
		ui->glw_preview->setTransparency(false);
	} else if(state==Qt::Checked) {
		ui->glw_preview->setTransparency(true);
		}
	}

//******************************************************************************
void MainWindow::on_cb_oems_pkg_stateChanged(int const state) {
	if(state==Qt::Unchecked) {
		data.oems_pkg=false;
	} else if(state==Qt::Checked) {
		data.oems_pkg=true;
		}
	}

//******************************************************************************
void MainWindow::on_cb_oems_sort_metalresmesh_stateChanged(int const state) {
	if(state==Qt::Unchecked) {
		data.oems_sort_metalresmesh=false;
	} else if(state==Qt::Checked) {
		data.oems_sort_metalresmesh=true;
		}
	}

//******************************************************************************
void MainWindow::on_le_oems_end_criteria_textChanged(QString const& oems_end_criteria) {
	data.oems_end_criteria=oems_end_criteria.toStdString();
	}

//******************************************************************************
void MainWindow::on_le_oems_highres_div_textChanged(QString const& oems_highres_div) {
	data.oems_highres_div=(unsigned int) oems_highres_div.toFloat();
	}

//******************************************************************************
void MainWindow::on_le_oems_metalres_div_textChanged(QString const& oems_metalres_div) {
	data.oems_metalres_div=(unsigned int) oems_metalres_div.toFloat();
	}

//******************************************************************************
void MainWindow::on_le_oems_nf2ff_center_textChanged(QString const& oems_nf2ff_center) {
	data.oems_nf2ff_center=oems_nf2ff_center.toStdString();
	}

//******************************************************************************
void MainWindow::on_le_oems_substres_div_textChanged(QString const& oems_substres_div) {
	data.oems_substres_div=(unsigned int) oems_substres_div.toFloat();
	}

//******************************************************************************
void MainWindow::on_le_oems_timeres_textChanged(QString const& oems_timeres) {
	data.oems_timeres=(unsigned int) oems_timeres.toFloat();
	}

//******************************************************************************
void MainWindow::on_le_path_in_returnPressed() {
	read();
	}

//******************************************************************************
void MainWindow::on_le_path_in_textChanged(QString const& n_sch) {
	data.n_sch=n_sch.toStdString();
	}

//******************************************************************************
void MainWindow::on_le_path_net_returnPressed() {
	read();
	}

//******************************************************************************
void MainWindow::on_le_path_net_textChanged(QString const& n_net) {
	data.n_net=n_net.toStdString();
	}

//******************************************************************************
void MainWindow::on_le_path_out_returnPressed() {
	write();
	}

//******************************************************************************
void MainWindow::on_le_path_out_textChanged(QString const& out_dir) {
	data.out_dir=out_dir.toStdString();
	}

//******************************************************************************
void MainWindow::on_pb_add_clicked() {
	add_action();
	}

//******************************************************************************
void MainWindow::on_pb_browse_in_clicked() {
	QString n_sch=QFileDialog::getOpenFileName(this, tr("Open schematic"), openfile_path, tr("Qucs schematic (*.sch)"));

	if(n_sch.isEmpty()) {
		ui->le_path_in->setText("");
		return;
		}

	openfile_path=QFileInfo(n_sch).path(); // Store path for next time.
	ui->le_path_in->setText(n_sch);
	data.n_sch=n_sch.toStdString();
	}

//******************************************************************************
void MainWindow::on_pb_browse_net_clicked() {
	QString n_net=QFileDialog::getOpenFileName(this, tr("Open netlist"), openfile_path, tr("Qucs netlist (*.net)"));

	if(n_net.isEmpty()) {
		ui->le_path_net->setText("");
		return;
		}

	openfile_path=QFileInfo(n_net).path(); // Store path for next time.
	ui->le_path_net->setText(n_net);
	data.n_net=n_net.toStdString();
	}

//******************************************************************************
void MainWindow::on_pb_browse_out_clicked() {
	QString out_dir=QFileDialog::getExistingDirectory(this, tr("Output directory"), "./", QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
	ui->le_path_out->setText(out_dir);
	data.out_dir=out_dir.toStdString();
	}

//******************************************************************************
void MainWindow::on_pb_read_clicked() {
	read();
	}

//******************************************************************************
void MainWindow::on_pb_remove_clicked() {
	ui->tw_actions->removeRow(ui->tw_actions->currentRow());
	}

//******************************************************************************
void MainWindow::on_pb_write_clicked() {
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

#endif // QRFL_MINIMAL
