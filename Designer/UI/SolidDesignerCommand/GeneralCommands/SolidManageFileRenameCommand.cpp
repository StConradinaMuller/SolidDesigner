//Owner: hananiah
#include "SolidManageFileRenameCommand.h"

#include "AliceCommandParameter.h"
#include "AliceCoreAppUtil.h"
#include "AliceISession.h"
#include "AliceIDocument.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QLineEdit>
#include "AliceIOperation.h"

using namespace alice;
using namespace sdr;

SolidManageFileRenameCommand::SolidManageFileRenameCommand() noexcept
	: AppCommandBase(std::string("manage_file.rename"))
{
}

SolidManageFileRenameCommand::~SolidManageFileRenameCommand() = default;

bool SolidManageFileRenameCommand::IsSupported() const
{
	return CoreAppUtil::GetCurrentSession() != nullptr;
}

bool SolidManageFileRenameCommand::IsVisible() const
{
	return true;
}

bool SolidManageFileRenameCommand::IsEnabled() const
{
	ISession* session = CoreAppUtil::GetCurrentSession();
	return session && session->GetActiveDocument();
}

std::string SolidManageFileRenameCommand::DisabledReason() const
{
	ISession* session = CoreAppUtil::GetCurrentSession();
	if (!session)
		return "Session is not available.";
	if (!session->GetActiveDocument())
		return "There is no active document.";
	return {};
}

std::unique_ptr<IOperation> SolidManageFileRenameCommand::Execute(const CommandParameter& /*param*/)
{
	if (!IsEnabled())
		return nullptr;

	ISession* session = CoreAppUtil::GetCurrentSession();
	IDocument* doc = session ? session->GetActiveDocument() : nullptr;
	if (!doc)
		return nullptr;

	const QString curName = QString::fromStdWString(doc->GetDocumentName());
	bool ok = false;
	QString newName = QInputDialog::getText(nullptr, QObject::tr("Rename"), QObject::tr("New name:"), QLineEdit::Normal, curName, &ok);
	if (!ok)
		return nullptr;
	newName = newName.trimmed();
	if (newName.isEmpty())
		return nullptr;

	doc->SetDocumentName(newName.toStdWString());
	QMessageBox::information(nullptr, QObject::tr("Rename"), QObject::tr("Renamed to: %1").arg(newName));
	return nullptr;
}
