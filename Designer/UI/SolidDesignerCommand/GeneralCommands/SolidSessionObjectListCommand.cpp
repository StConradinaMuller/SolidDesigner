//Owner: hananiah
#include "SolidSessionObjectListCommand.h"

#include "AliceCommandParameter.h"
#include "AliceCoreAppUtil.h"
#include "AliceISession.h"
#include "AliceIDocument.h"
#include "AliceDocumentKind.h"

#include <QDialog>
#include <QDialogButtonBox>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include "AliceIOperation.h"

using namespace alice;
using namespace sdr;

SolidSessionObjectListCommand::SolidSessionObjectListCommand() noexcept
	: AppCommandBase(std::string("data.object_list"))
{
}

SolidSessionObjectListCommand::~SolidSessionObjectListCommand() = default;

bool SolidSessionObjectListCommand::IsSupported() const { return CoreAppUtil::GetCurrentSession() != nullptr; }
bool SolidSessionObjectListCommand::IsVisible() const { return true; }
bool SolidSessionObjectListCommand::IsEnabled() const { return CoreAppUtil::GetCurrentSession() != nullptr; }
std::string SolidSessionObjectListCommand::DisabledReason() const { return {}; }

std::unique_ptr<IOperation> SolidSessionObjectListCommand::Execute(const CommandParameter& /*param*/)
{
	ISession* session = CoreAppUtil::GetCurrentSession();
	if (!session)
		return nullptr;
	const auto docs = session->GetDocuments();

	QString txt;
	for (IDocument* d : docs)
	{
		if (!d)
			continue;
		txt += QStringLiteral("- ");
		txt += QString::fromStdWString(d->GetDocumentName());
		txt += QStringLiteral("  [");
		txt += QString::fromUtf8(ToString(d->GetDocumentKind()));
		txt += QStringLiteral("]\n");
		const std::wstring& uri = d->GetSourceUri();
		if (!uri.empty())
		{
			txt += QStringLiteral("    ");
			txt += QString::fromStdWString(uri);
			txt += QLatin1Char('\n');
		}
	}

	QDialog dlg(nullptr);
	dlg.setWindowTitle(QObject::tr("Object List"));
	dlg.resize(640, 480);
	auto* layout = new QVBoxLayout(&dlg);
	auto* edit = new QPlainTextEdit(&dlg);
	edit->setReadOnly(true);
	edit->setPlainText(txt.isEmpty() ? QObject::tr("No documents in session.") : txt);
	layout->addWidget(edit, 1);
	auto* buttons = new QDialogButtonBox(QDialogButtonBox::Close, &dlg);
	QObject::connect(buttons, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
	layout->addWidget(buttons);
	dlg.exec();
	return nullptr;
}
