///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#include <QRegularExpression>

#include "changelog.hpp"
#include "version.hpp"

#include "aboutdialog.hpp"
using namespace std;

//******************************************************************************
AboutDialog::AboutDialog(QWidget* parent)
: QDialog(parent, Qt::Dialog)
, ui(make_unique<Ui::AboutDialog>()) {
	ui->setupUi(this);
	ui->l_version->setText(ui->l_version->text() + VERSION);
	// Font size x-large does not work in UI file stylesheet. Rather setting it
	// here than using a fixed size in px, that actually works there.
	ui->l_title->setText(QString("<span style='font-size:x-large; font-weight:bold;'>") + ui->l_title->text() + "</span>");

	static QString const changelog_md(QString(changelog.data())
		.replace(QRegularExpression("  \\*"), "-")                                    // Bullet points
		.replace(QRegularExpression("    \\*"), "  -")                                // Bullet points
		.replace(QRegularExpression("#([0-9]+)"), "[#\\1](" QRFL_BUGREPORT "/\\1)")   // Issues
		.replace(QRegularExpression(" -- ([^<]+)<.*> +(.*)"), "*\\1 - \\2*\n\n---")   // Signature/Date line
		.replace(QRegularExpression("(qucsrflayout \\([0-9.]+\\))"), "### \\1")       // Release title line
		.replace(QRegularExpression("  \\[ (.*) \\]"), "#### \\1"));                  // Category line

	ui->tb_changelog->setMarkdown(changelog_md);
	//ui->tb_changelog->setPlainText(changelog_md); // For converter debug.

	ui->tb_contact->setMarkdown(
		"Homepage: " QRFL_HOMEPAGE "\n\n"
		"Bug report: " QRFL_BUGREPORT "\n\n"
		"Main developer: <thomas.lepoix@protonmail.ch>\n\n"
		"Funding: " QRFL_FUNDING);
	}

//******************************************************************************
void AboutDialog::on_pb_ok_clicked() {
	accept();
	}
