///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#pragma once

#ifndef QRFL_MINIMAL

#include <QAction>
#include <QMainWindow>
#include <QObject>

#include <memory>
#include <sstream>
#include <vector>

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
	std::vector<std::unique_ptr<QAction>> a_themes;

	void add_action(QString const action_str="Shift port", QString const val1="", QString const val2="", QString const val3="");
	void read();
	void write();

	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;

	void log(std::stringstream& in) override;

private slots:
	void on_a_about_triggered();
	void on_a_detail_mcorn_triggered();
	void on_a_detail_mcoupled_triggered();
	void on_a_detail_mcross_triggered();
	void on_a_detail_mlin_triggered();
	void on_a_detail_mmbend_triggered();
	void on_a_detail_mrstub_triggered();
	void on_a_detail_mtee_triggered();
	void on_a_oems_mesh_mcorn_triggered();
	void on_a_oems_mesh_mcoupled_triggered();
	void on_a_oems_mesh_mcross_triggered();
	void on_a_oems_mesh_mgap_triggered();
	void on_a_oems_mesh_mlin_triggered();
	void on_a_oems_mesh_mmbend_triggered();
	void on_a_oems_mesh_mopen_triggered();
	void on_a_oems_mesh_mrstub_triggered();
	void on_a_oems_mesh_mstep_triggered();
	void on_a_oems_mesh_mtee_triggered();
	void on_a_oems_mesh_mvia_triggered();
	void on_a_oems_mesh_pac_triggered();
	void on_a_table_orientation_triggered();
	void on_a_topology_mcorn_triggered();
	void on_a_topology_mcoupled_triggered();
	void on_a_topology_mcross_triggered();
	void on_a_topology_mgap_triggered();
	void on_a_topology_mlin_triggered();
	void on_a_topology_mmbend_triggered();
	void on_a_topology_mopen_triggered();
	void on_a_topology_mrstub_triggered();
	void on_a_topology_mstep_triggered();
	void on_a_topology_mtee_triggered();
	void on_a_topology_mvia_triggered();
	void on_ag_themes_triggered(QAction* const action);
	void on_cb_format_currentTextChanged(QString const& out_format);
	void on_cb_specify_netlist_stateChanged(int const state);
	void on_cb_transparency_stateChanged(int const state);
	void on_cb_oems_pkg_stateChanged(int const state);
	void on_cb_oems_sort_metalresmesh_stateChanged(int const state);
	void on_le_oems_end_criteria_textChanged(QString const& oems_end_criteria);
	void on_le_oems_highres_div_textChanged(QString const& oems_highres_div);
	void on_le_oems_metalres_div_textChanged(QString const& oems_metalres_div);
	void on_le_oems_nf2ff_center_textChanged(QString const& oems_nf2ff_center);
	void on_le_oems_substres_div_textChanged(QString const& oems_substres_div);
	void on_le_oems_timeres_textChanged(QString const& oems_timeres);
	void on_le_path_in_returnPressed();
	void on_le_path_in_textChanged(QString const& n_sch);
	void on_le_path_net_returnPressed();
	void on_le_path_net_textChanged(QString const& n_net);
	void on_le_path_out_returnPressed();
	void on_le_path_out_textChanged(QString const& out_dir);
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
	MainWindow(Data& _data, std::string const& gui_theme, QWidget* parent=0);
	~MainWindow()=default;
};

#endif // QRFL_MINIMAL
